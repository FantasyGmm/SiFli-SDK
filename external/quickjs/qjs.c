/*
 * QuickJS stand alone interpreter
 * 
 * Copyright (c) 2017-2021 Fabrice Bellard
 * Copyright (c) 2017-2021 Charlie Gordon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#ifdef _MSC_VER
#include <unistd_pc.h>
#else
#include <unistd.h>
#endif
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#if defined(__APPLE__)
#include <malloc/malloc.h>
#elif defined(__linux__)
#include <malloc.h>
#endif

#include "cutils.h"
#include "quickjs-libc.h"

extern const uint8_t qjsc_repl[];
extern const uint32_t qjsc_repl_size;
#ifdef CONFIG_BIGNUM
extern const uint8_t qjsc_qjscalc[];
extern const uint32_t qjsc_qjscalc_size;
static int bignum_ext;
#endif

int eval_buf(JSContext *ctx, const void *buf, int buf_len,
                    const char *filename, int eval_flags)
{
    JSValue val;
    int ret;

    if ((eval_flags & JS_EVAL_TYPE_MASK) == JS_EVAL_TYPE_MODULE) {
        /* for the modules, we compile then run to be able to set
           import.meta */
        val = JS_Eval(ctx, buf, buf_len, filename,
                      eval_flags | JS_EVAL_FLAG_COMPILE_ONLY);
        if (!JS_IsException(val)) {
            js_module_set_import_meta(ctx, val, TRUE, TRUE);
            val = JS_EvalFunction(ctx, val);
        }
    } else {
        val = JS_Eval(ctx, buf, buf_len, filename, eval_flags);
    }
    if (JS_IsException(val)) {
        js_std_dump_error(ctx);
        ret = -1;
    } else {
        ret = 0;
    }
    JS_FreeValue(ctx, val);
    return ret;
}

int eval_file(JSContext *ctx, const char *filename, int module)
{
    uint8_t *buf;
    int ret, eval_flags;
    size_t buf_len;
    
    buf = js_load_file(ctx, &buf_len, filename);
    if (!buf) {
        perror(filename);
        exit(1);
    }

    if (module < 0) {
        module = (has_suffix(filename, ".mjs") ||
                  JS_DetectModule((const char *)buf, buf_len));
    }
    if (module)
        eval_flags = JS_EVAL_TYPE_MODULE;
    else
        eval_flags = JS_EVAL_TYPE_GLOBAL;
    ret = eval_buf(ctx, buf, buf_len, filename, eval_flags);
    js_free(ctx, buf);
    return ret;
}

/* also used to initialize the worker context */
static JSContext *JS_NewCustomContext(JSRuntime *rt)
{
    JSContext *ctx;
    ctx = JS_NewContext(rt);
    if (!ctx)
        return NULL;
#ifdef CONFIG_BIGNUM
    if (bignum_ext) {
        JS_AddIntrinsicBigFloat(ctx);
        JS_AddIntrinsicBigDecimal(ctx);
        JS_AddIntrinsicOperators(ctx);
        JS_EnableBignumExt(ctx, TRUE);
    }
#endif
    /* system modules */
    js_init_module_std(ctx, "std");
    js_init_module_os(ctx, "os");
    return ctx;
}

#if defined(__APPLE__)
#define MALLOC_OVERHEAD  0
#else
#define MALLOC_OVERHEAD  8
#endif

struct trace_malloc_data {
    uint8_t *base;
};

static inline unsigned long long js_trace_malloc_ptr_offset(uint8_t *ptr,
                                                struct trace_malloc_data *dp)
{
    return ptr - dp->base;
}

/* default memory allocation functions with memory limitation */
static inline size_t js_trace_malloc_usable_size(void *ptr)
{
#if defined(__APPLE__)
    return malloc_size(ptr);
#elif defined(_WIN32)
    return _msize(ptr);
#elif defined(EMSCRIPTEN)
    return 0;
#elif defined(__linux__)
    return malloc_usable_size(ptr);
#else
    /* change this to `return 0;` if compilation fails */
    //return malloc_usable_size(ptr);
    return 0;
#endif
}

static void
#ifndef BSP_USING_RTTHREAD
__attribute__((format(printf, 2, 3)))
#endif
    js_trace_malloc_printf(JSMallocState *s, const char *fmt, ...)
{
    va_list ap;
    int c;

    va_start(ap, fmt);
    while ((c = *fmt++) != '\0') {
        if (c == '%') {
            /* only handle %p and %zd */
            if (*fmt == 'p') {
                uint8_t *ptr = va_arg(ap, void *);
                if (ptr == NULL) {
                    printf("NULL");
                } else {
                    printf("H%+06lld.%zd",
                           js_trace_malloc_ptr_offset(ptr, s->opaque),
                           js_trace_malloc_usable_size(ptr));
                }
                fmt++;
                continue;
            }
            if (fmt[0] == 'z' && fmt[1] == 'd') {
                size_t sz = va_arg(ap, size_t);
                printf("%zd", sz);
                fmt += 2;
                continue;
            }
        }
        putc(c, stdout);
    }
    va_end(ap);
}

static void js_trace_malloc_init(struct trace_malloc_data *s)
{
    free(s->base = malloc(8));
}

static void *js_trace_malloc(JSMallocState *s, size_t size)
{
    void *ptr;

    /* Do not allocate zero bytes: behavior is platform dependent */
    assert(size != 0);

    if (unlikely(s->malloc_size + size > s->malloc_limit))
        return NULL;
    ptr = malloc(size);
    js_trace_malloc_printf(s, "A %zd -> %p\n", size, ptr);
    if (ptr) {
        s->malloc_count++;
        s->malloc_size += js_trace_malloc_usable_size(ptr) + MALLOC_OVERHEAD;
    }
    return ptr;
}

static void js_trace_free(JSMallocState *s, void *ptr)
{
    if (!ptr)
        return;

    js_trace_malloc_printf(s, "F %p\n", ptr);
    s->malloc_count--;
    s->malloc_size -= js_trace_malloc_usable_size(ptr) + MALLOC_OVERHEAD;
    free(ptr);
}

static void *js_trace_realloc(JSMallocState *s, void *ptr, size_t size)
{
    size_t old_size;

    if (!ptr) {
        if (size == 0)
            return NULL;
        return js_trace_malloc(s, size);
    }
    old_size = js_trace_malloc_usable_size(ptr);
    if (size == 0) {
        js_trace_malloc_printf(s, "R %zd %p\n", size, ptr);
        s->malloc_count--;
        s->malloc_size -= old_size + MALLOC_OVERHEAD;
        free(ptr);
        return NULL;
    }
    if (s->malloc_size + size - old_size > s->malloc_limit)
        return NULL;

    js_trace_malloc_printf(s, "R %zd %p", size, ptr);

    ptr = realloc(ptr, size);
    js_trace_malloc_printf(s, " -> %p\n", ptr);
    if (ptr) {
        s->malloc_size += js_trace_malloc_usable_size(ptr) - old_size;
    }
    return ptr;
}

static const JSMallocFunctions trace_mf = {
    js_trace_malloc,
    js_trace_free,
    js_trace_realloc,
#if defined(__APPLE__)
    malloc_size,
#elif defined(_WIN32)
    (size_t (*)(const void *))_msize,
#elif defined(EMSCRIPTEN)
    NULL,
#elif defined(__linux__)
    (size_t (*)(const void *))malloc_usable_size,
#else
    /* change this to `NULL,` if compilation fails */
    //malloc_usable_size,
    NULL,
#endif
};

#define PROG_NAME "qjs"


#if defined(FINSH_USING_MSH) && defined(LVGL_QJS_TEST)
int quickjs_main(int argc, char **argv);
MSH_CMD_EXPORT_ALIAS(quickjs_main,qjs, Quick JS);

#else
#define quickjs_main main
#endif

#ifdef QJS_ORIGINAL
void help(void)
{
    printf("QuickJS version " CONFIG_VERSION "\n"
           "usage: " PROG_NAME " [options] [file [args]]\n"
           "-h  --help         list options\n"
           "-e  --eval EXPR    evaluate EXPR\n"
           "-i  --interactive  go to interactive mode\n"
           "-m  --module       load as ES6 module (default=autodetect)\n"
           "    --script       load as ES6 script (default=autodetect)\n"
           "-I  --include file include an additional file\n"
           "    --std          make 'std' and 'os' available to the loaded script\n"
#ifdef CONFIG_BIGNUM
           "    --bignum       enable the bignum extensions (BigFloat, BigDecimal)\n"
           "    --qjscalc      load the QJSCalc runtime (default if invoked as qjscalc)\n"
#endif
           "-T  --trace        trace memory allocation\n"
           "-d  --dump         dump the memory usage stats\n"
           "    --memory-limit n       limit the memory usage to 'n' bytes\n"
           "    --stack-size n         limit the stack size to 'n' bytes\n"
           "    --unhandled-rejection  dump unhandled promise rejections\n"
           "-q  --quit         just instantiate the interpreter and quit\n");
    exit(1);
}

int quickjs_main(int argc, char **argv)
{
    JSRuntime *rt;
    JSContext *ctx;
    struct trace_malloc_data trace_data = { NULL };
    int optind;
    char *expr = NULL;
    int interactive = 0;
    int dump_memory = 0;
    int trace_memory = 0;
    int empty_run = 0;
    int module = -1;
    int load_std = 0;
    int dump_unhandled_promise_rejection = 0;
    size_t memory_limit = 0;
    char *include_list[32];
    int i, include_count = 0;
#ifdef CONFIG_BIGNUM
    int load_jscalc;
#endif
    size_t stack_size = 0;
    
#ifdef CONFIG_BIGNUM
    /* load jscalc runtime if invoked as 'qjscalc' */
    {
        const char *p, *exename;
        exename = argv[0];
        p = strrchr(exename, '/');
        if (p)
            exename = p + 1;
        load_jscalc = !strcmp(exename, "qjscalc");
    }
#endif
    
    /* cannot use getopt because we want to pass the command line to
       the script */
    optind = 1;
    while (optind < argc && *argv[optind] == '-') {
        char *arg = argv[optind] + 1;
        const char *longopt = "";
        /* a single - is not an option, it also stops argument scanning */
        if (!*arg)
            break;
        optind++;
        if (*arg == '-') {
            longopt = arg + 1;
            arg += strlen(arg);
            /* -- stops argument scanning */
            if (!*longopt)
                break;
        }
        for (; *arg || *longopt; longopt = "") {
            char opt = *arg;
            if (opt)
                arg++;
            if (opt == 'h' || opt == '?' || !strcmp(longopt, "help")) {
                help();
                continue;
            }
            if (opt == 'e' || !strcmp(longopt, "eval")) {
                if (*arg) {
                    expr = arg;
                    break;
                }
                if (optind < argc) {
                    expr = argv[optind++];
                    break;
                }
                fprintf(stderr, "qjs: missing expression for -e\n");
                exit(2);
            }
            if (opt == 'I' || !strcmp(longopt, "include")) {
                if (optind >= argc) {
                    fprintf(stderr, "expecting filename");
                    exit(1);
                }
                if (include_count >= countof(include_list)) {
                    fprintf(stderr, "too many included files");
                    exit(1);
                }
                include_list[include_count++] = argv[optind++];
                continue;
            }
            if (opt == 'i' || !strcmp(longopt, "interactive")) {
                interactive++;
                continue;
            }
            if (opt == 'm' || !strcmp(longopt, "module")) {
                module = 1;
                continue;
            }
            if (!strcmp(longopt, "script")) {
                module = 0;
                continue;
            }
            if (opt == 'd' || !strcmp(longopt, "dump")) {
                dump_memory++;
                continue;
            }
            if (opt == 'T' || !strcmp(longopt, "trace")) {
                trace_memory++;
                continue;
            }
            if (!strcmp(longopt, "std")) {
                load_std = 1;
                continue;
            }
            if (!strcmp(longopt, "unhandled-rejection")) {
                dump_unhandled_promise_rejection = 1;
                continue;
            }
#ifdef CONFIG_BIGNUM
            if (!strcmp(longopt, "bignum")) {
                bignum_ext = 1;
                continue;
            }
            if (!strcmp(longopt, "qjscalc")) {
                load_jscalc = 1;
                continue;
            }
#endif
            if (opt == 'q' || !strcmp(longopt, "quit")) {
                empty_run++;
                continue;
            }
            if (!strcmp(longopt, "memory-limit")) {
                if (optind >= argc) {
                    fprintf(stderr, "expecting memory limit");
                    exit(1);
                }
                memory_limit = (size_t)strtod(argv[optind++], NULL);
                continue;
            }
            if (!strcmp(longopt, "stack-size")) {
                if (optind >= argc) {
                    fprintf(stderr, "expecting stack size");
                    exit(1);
                }
                stack_size = (size_t)strtod(argv[optind++], NULL);
                continue;
            }
            if (opt) {
                fprintf(stderr, "qjs: unknown option '-%c'\n", opt);
            } else {
                fprintf(stderr, "qjs: unknown option '--%s'\n", longopt);
            }
            help();
        }
    }

    if (load_jscalc)
        bignum_ext = 1;

    if (trace_memory) {
        js_trace_malloc_init(&trace_data);
        rt = JS_NewRuntime2(&trace_mf, &trace_data);
    } else {
        rt = JS_NewRuntime();
    }
    if (!rt) {
        fprintf(stderr, "qjs: cannot allocate JS runtime\n");
        exit(2);
    }
    if (memory_limit != 0)
        JS_SetMemoryLimit(rt, memory_limit);
    if (stack_size != 0)
        JS_SetMaxStackSize(rt, stack_size);
    js_std_set_worker_new_context_func(JS_NewCustomContext);
    js_std_init_handlers(rt);
    ctx = JS_NewCustomContext(rt);
    if (!ctx) {
        fprintf(stderr, "qjs: cannot allocate JS context\n");
        exit(2);
    }

    /* loader for ES6 modules */
    JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);

    if (dump_unhandled_promise_rejection) {
        JS_SetHostPromiseRejectionTracker(rt, js_std_promise_rejection_tracker,
                                          NULL);
    }
    
    if (!empty_run) {
#ifdef CONFIG_BIGNUM
        if (load_jscalc) {
            js_std_eval_binary(ctx, qjsc_qjscalc, qjsc_qjscalc_size, 0);
        }
#endif
        js_std_add_helpers(ctx, argc - optind, argv + optind);

        /* make 'std' and 'os' visible to non module code */
        if (load_std) {
            const char *str = "import * as std from 'std';\n"
                "import * as os from 'os';\n"
                "globalThis.std = std;\n"
                "globalThis.os = os;\n";
            eval_buf(ctx, str, strlen(str), "<input>", JS_EVAL_TYPE_MODULE);
        }

        for(i = 0; i < include_count; i++) {
            if (eval_file(ctx, include_list[i], module))
                goto fail;
        }

        if (expr) {
            if (eval_buf(ctx, expr, strlen(expr), "<cmdline>", 0))
                goto fail;
        } else
        if (optind >= argc) {
            /* interactive mode */
            interactive = 1;
        } else {
            const char *filename;
            filename = argv[optind];
            if (eval_file(ctx, filename, module))
                goto fail;
        }
        if (interactive) {
            js_std_eval_binary(ctx, qjsc_repl, qjsc_repl_size, 0);
        }
        js_std_loop(ctx);
    }
    
    if (dump_memory) {
        JSMemoryUsage stats;
        JS_ComputeMemoryUsage(rt, &stats);
        JS_DumpMemoryUsage(stdout, &stats, rt);
    }
    js_std_free_handlers(rt);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);

    if (empty_run && dump_memory) {
        clock_t t[5];
        double best[5];
        int i, j;
        for (i = 0; i < 100; i++) {
            t[0] = clock();
            rt = JS_NewRuntime();
            t[1] = clock();
            ctx = JS_NewContext(rt);
            t[2] = clock();
            JS_FreeContext(ctx);
            t[3] = clock();
            JS_FreeRuntime(rt);
            t[4] = clock();
            for (j = 4; j > 0; j--) {
                double ms = 1000.0 * (t[j] - t[j - 1]) / CLOCKS_PER_SEC;
                if (i == 0 || best[j] > ms)
                    best[j] = ms;
            }
        }
        printf("\nInstantiation times (ms): %.3f = %.3f+%.3f+%.3f+%.3f\n",
               best[1] + best[2] + best[3] + best[4],
               best[1], best[2], best[3], best[4]);
    }
    return 0;
 fail:
    js_std_free_handlers(rt);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    return 1;
}

#else

JSRuntime *quickjs_rt()
{
    JSRuntime *rt;
    struct trace_malloc_data trace_data = { NULL };
    int trace_memory = 0;
    size_t stack_size = 0;
    size_t memory_limit = 0;

    if (trace_memory) {
         js_trace_malloc_init(&trace_data);
         rt = JS_NewRuntime2(&trace_mf, &trace_data);
    } else {
        rt = JS_NewRuntime();
    }
    if (rt) {
        if (memory_limit != 0)
            JS_SetMemoryLimit(rt, memory_limit);
        if (stack_size != 0)
            JS_SetMaxStackSize(rt, stack_size);
        js_std_init_handlers(rt);
    }
    else {
        rt_kprintf("qjs: cannot allocate JS runtime\n");
    }
    return rt;
}

JSContext *quickjs_ctx(JSRuntime *rt)
{
    JSContext *ctx;
    int load_std = 0;
        
    ctx = JS_NewCustomContext(rt);
    if (ctx) {        
        /* loader for ES6 modules */
        JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);
        
        js_std_add_helpers(ctx, 0, NULL);
        
        /* make 'std' and 'os' visible to non module code */
        if (load_std) {
            const char *str = "import * as std from 'std';\n"
                "import * as os from 'os';\n"
                "globalThis.std = std;\n"
                "globalThis.os = os;\n";
            eval_buf(ctx, str, strlen(str), "<input>", JS_EVAL_TYPE_MODULE);
        }
    }
    else {
        rt_kprintf("qjs: cannot allocate JS context\n");
    }
        
    return ctx;
}

#ifdef LVGL_QJS_TEST
void quickjs_dump(JSRuntime *rt)
{
    int dump_memory = 1;
    if (dump_memory) {
        JSMemoryUsage stats;
        JS_ComputeMemoryUsage(rt, &stats);
        JS_DumpMemoryUsage(stdout, &stats, rt);
    }
}

void quickjs_exit(JSRuntime *rt)
{
    js_std_free_handlers(rt);
    JS_FreeRuntime(rt);
}

int quickjs_main(int argc, char **argv)
{
    JSRuntime *rt=quickjs_rt();
    JSContext *ctx=NULL;
    int r=0;
    
    if (rt&&(ctx=quickjs_ctx(rt))) {
        if (eval_file(ctx,argv[1],-1)==0)
            js_std_loop(ctx);
    }
    else {
        r=-1;
    }
    JS_FreeContext(ctx);
    quickjs_exit(rt);
    return r;
}

JSRuntime* test_rt;
JSContext* test_ctx;
int quickjs_init(int argc, char** argv)
{
    test_rt = quickjs_rt();
    rt_kprintf("QJS Init\n");
    return 0;
}

int quickjs_stop(int argc, char** argv)
{
    return 0;
}

int _quickjs_exit(int argc, char** argv)
{
    JS_RunGC(test_rt);
    quickjs_exit(test_rt);
    rt_kprintf("QJS Exit\n");
    return 0;
}

int quickjs_alloc(int argc, char** argv)
{
     {
        const char* buf = "app = new app1(0); \n";
        rt_kprintf(buf);
        eval_buf(test_ctx, buf, strlen(buf), "<input>", 0);
    }
    {
        const char* buf = "app.start(); \n";
        rt_kprintf(buf);
        eval_buf(test_ctx, buf, strlen(buf), "<input>", 0);
    }
    return 0;
}

int quickjs_free(int argc, char** argv)
{
    {
        const char* buf = "app.resume();\n";
        rt_kprintf(buf);
        eval_buf(test_ctx, buf, strlen(buf), "<input>", 0);
    }
    {
        const char* buf = "app.pause();\n";
        rt_kprintf(buf);
        eval_buf(test_ctx, buf, strlen(buf), "<input>", 0);
    }
    {
        const char* buf = "app.stop();\n";
        rt_kprintf(buf);
        eval_buf(test_ctx, buf, strlen(buf), "<input>", 0);
    }
    {
        const char* buf = "delete app;\n";
        rt_kprintf(buf);
        eval_buf(test_ctx, buf, strlen(buf), "<input>", 0);
    }
    JS_RunGC(test_rt);
    return 0;
}

int quickjs_run(int argc, char** argv)
{
    int steps = 1;

    test_ctx = quickjs_ctx(test_rt);
    {
        extern JSModuleDef *js_add_lvgl(JSContext *ctx, const char *module_name);    
        js_add_lvgl(test_ctx, "lv");
        extern JSModuleDef *js_add_lvgl_ext(JSContext *ctx, const char *module_name);    
        js_add_lvgl_ext(test_ctx, "lvext");
    }
    eval_file(test_ctx, "./JA_app1/main.js", 1);
    for (int i = 0; i < steps; i++) {
        quickjs_alloc(0,NULL);
        quickjs_free(0, NULL);
        extern void list_mem(void); 
        list_mem();
    }
    JS_FreeContext(test_ctx);
    return 0;
}

MSH_CMD_EXPORT_ALIAS(quickjs_init, q_init, Init Quick JS);
MSH_CMD_EXPORT_ALIAS(quickjs_run, q_run, Run Quick JS);
MSH_CMD_EXPORT_ALIAS(quickjs_stop, q_stop, Stop Quick JS);
MSH_CMD_EXPORT_ALIAS(_quickjs_exit, q_exit, Exit Quick JS);
MSH_CMD_EXPORT_ALIAS(quickjs_alloc, q_alloc, Alloc Quick JS);
MSH_CMD_EXPORT_ALIAS(quickjs_free, q_free, Free Quick JS);

#endif

#endif

