/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-02-24     Bernard      first version
 * 2006-05-03     Bernard      add IRQ_DEBUG
 * 2016-08-09     ArdaFu       add interrupt enter and leave hook.
 */

#include <rthw.h>
#include <rtthread.h>
#if defined(RT_USING_PM)
    #include <drivers/pm.h>
#endif /* RT_USING_PM */

//#include "rtdevice.h"


#ifdef RT_USING_HOOK

static void (*rt_interrupt_enter_hook)(void);
static void (*rt_interrupt_leave_hook)(void);

/**
 * @ingroup Hook
 * This function set a hook function when the system enter a interrupt
 *
 * @note the hook function must be simple and never be blocked or suspend.
 */
__ROM_USED void rt_interrupt_enter_sethook(void (*hook)(void))
{
    rt_interrupt_enter_hook = hook;
}
/**
 * @ingroup Hook
 * This function set a hook function when the system exit a interrupt.
 *
 * @note the hook function must be simple and never be blocked or suspend.
 */
__ROM_USED void rt_interrupt_leave_sethook(void (*hook)(void))
{
    rt_interrupt_leave_hook = hook;
}
#endif

/* #define IRQ_DEBUG */

/**
 * @addtogroup Kernel
 */

/**@{*/

__ROM_USED volatile rt_uint8_t rt_interrupt_nest;

/**
 * This function will be invoked by BSP, when enter interrupt service routine
 *
 * @note please don't invoke this routine in application
 *
 * @see rt_interrupt_leave
 */
__ROM_USED void rt_interrupt_enter(void)
{
    rt_base_t level;

    RT_DEBUG_LOG(RT_DEBUG_IRQ, ("irq coming..., irq nest:%d\n",
                                rt_interrupt_nest));

    level = rt_hw_interrupt_disable();
    rt_interrupt_nest ++;
#if defined(RT_USING_PM)
    rt_pm_exit_idle();
#endif /* RT_USING_PM && SF32LB55X */
    RT_OBJECT_HOOK_CALL(rt_interrupt_enter_hook, ());
    rt_hw_interrupt_enable(level);
}
RTM_EXPORT(rt_interrupt_enter);

/**
 * This function will be invoked by BSP, when leave interrupt service routine
 *
 * @note please don't invoke this routine in application
 *
 * @see rt_interrupt_enter
 */
__ROM_USED void rt_interrupt_leave(void)
{
    rt_base_t level;

    RT_DEBUG_LOG(RT_DEBUG_IRQ, ("irq leave, irq nest:%d\n",
                                rt_interrupt_nest));

    level = rt_hw_interrupt_disable();
    RT_ASSERT(rt_interrupt_nest > 0);
    rt_interrupt_nest --;
    RT_OBJECT_HOOK_CALL(rt_interrupt_leave_hook, ());
    rt_hw_interrupt_enable(level);
}
RTM_EXPORT(rt_interrupt_leave);

/**
 * This function will return the nest of interrupt.
 *
 * User application can invoke this function to get whether current
 * context is interrupt context.
 *
 * @return the number of nested interrupts.
 */
__ROM_USED rt_uint8_t rt_interrupt_get_nest(void)
{
    return rt_interrupt_nest;
}
RTM_EXPORT(rt_interrupt_get_nest);

RTM_EXPORT(rt_hw_interrupt_disable);
RTM_EXPORT(rt_hw_interrupt_enable);

/**@}*/

