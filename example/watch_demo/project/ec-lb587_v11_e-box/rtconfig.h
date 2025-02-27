/*Auto generated configuration*/
#ifndef RT_CONFIG_H
#define RT_CONFIG_H

#define SOC_SF32LB58X 1
#define MEMCPY_NON_DMA 1
#define PSRAM_CACHE_WB 1
#define CORE "HCPU"
#define CPU "Cortex-M33"
#define BSP_USING_BOARD_EC_LB587XXX 1
#define LXT_FREQ 32768
#define LXT_LP_CYCLE 200
#define BT_TX_POWER_VAL 1
#define BT_TX_POWER_VAL_MAX 10
#define BT_TX_POWER_VAL_MIN 0
#define BT_TX_POWER_VAL_INIT 0
#define ASIC 1
#define TOUCH_IRQ_PIN 69
#define BSP_SUPPORT_DSI 1
#define BSP_SUPPORT_DSI_VIDEO 1
#define BSP_LCDC1_USE_LCDC2_TE 1
#define LCD_HOR_RES_MAX 800
#define LCD_VER_RES_MAX 800
#define LCD_DPI 235
#define BSP_USING_PSRAM 1
#define BT_USING_AVRCP 1
#define BT_USING_HID 1
#define RT_USING_BT 1
#define BT_DEVICE_NAME "bt_device"
#define BT_USING_AG 1
#define BSP_USING_LCD 1
#define LCD_USING_TFT_AH034A01ZJINV4C30 1
#define BSP_USING_LCD_FRAMEBUFFER 1
#define BSP_USING_GPIO 1
#define BSP_GPIO_HANDLE 2
#define BSP_USING_DMA 1
#define BSP_USING_UART 1
#define BSP_USING_UART1 1
#define BSP_UART1_RX_USING_DMA 1
#define BSP_USING_SPI 1
#define BSP_USING_SPI3 1
#define BSP_USING_I2C 1
#define BSP_USING_I2C1 1
#define BSP_USING_I2C3 1
#define BSP_I2C3_USING_DMA 1
#define BSP_USING_I2C4 1
#define BSP_USING_I2C5 1
#define BSP_USING_TIM 1
#define BSP_USING_GPTIM4 1
#define BSP_USING_BTIM1 1
#define BSP_USING_LPTIM1 1
#define BSP_USING_MPI 1
#define BSP_USING_SPI_FLASH 1
#define BSP_ENABLE_MPI1 1
#define BSP_ENABLE_QSPI1 1
#define BSP_MPI1_MODE_4 1
#define BSP_QSPI1_MODE 4
#define BSP_USING_PSRAM1 1
#define BSP_QSPI1_MEM_SIZE 32
#define BSP_ENABLE_MPI2 1
#define BSP_ENABLE_QSPI2 1
#define BSP_MPI2_MODE_4 1
#define BSP_QSPI2_MODE 4
#define BSP_USING_PSRAM2 1
#define BSP_QSPI2_MEM_SIZE 32
#define BSP_ENABLE_MPI4 1
#define BSP_ENABLE_QSPI4 1
#define BSP_MPI4_MODE_1 1
#define BSP_QSPI4_MODE 1
#define BSP_QSPI4_USING_DMA 1
#define BSP_USING_NAND_FLASH4 1
#define BSP_QSPI4_MEM_SIZE 128
#define BSP_USING_SPI_NAND 1
#define BSP_USING_EXT_DMA 1
#define BSP_USING_HW_AES 1
#define BSP_USING_ONCHIP_RTC 1
#define BSP_RTC_PPM 0
#define BSP_USING_EPIC 1
#define BSP_USING_LCDC 1
#define BSP_USING_SDIO 1
#define BSP_USING_SDHCI 1
#define BSP_USING_SDHCI2 1
#define SD2_MAX_FREQ 48000000
#define SD2_DMA_MODE 2
#define SDIO2_CARD_MODE 0
#define BSP_USING_PINMUX 1
#define BSP_USING_LCPU_PATCH 1
#define BSP_ENABLE_AUD_PRC 1
#define BSP_AUDPRC_TX0_DMA 1
#define BSP_AUDPRC_RX0_DMA 1
#define BSP_ENABLE_AUD_CODEC 1
#define BT_USING_SIFLI 1
#define LCD_USING_NV3051F1 1
#define BSP_LCDC_USING_DSI_VIDEO 1
#define BSP_USING_RAMLESS_LCD 1
#define BSP_USING_ROUND_TYPE_LCD 1
#define BSP_USING_KEY1 1
#define BSP_KEY1_PIN 150
#define BSP_KEY1_ACTIVE_HIGH 1
#define PMIC_CTRL_ENABLE 1
#define PMICC_SCL_PIN 148
#define PMICC_SDA_PIN 147
#define PA_USING_AW87390 1
#define BSP_USING_RTTHREAD 1
#define RT_USING_COMPONENTS_INIT 1
#define RT_USING_USER_MAIN 1
#define RT_MAIN_THREAD_STACK_SIZE 4096
#define RT_MAIN_THREAD_PRIORITY 10
#define RT_USING_CPLUSPLUS 1
#define RT_USING_FINSH 1
#define FINSH_THREAD_NAME "tshell"
#define FINSH_USING_HISTORY 1
#define FINSH_HISTORY_LINES 5
#define FINSH_USING_SYMTAB 1
#define FINSH_USING_DESCRIPTION 1
#define FINSH_THREAD_PRIORITY 20
#define FINSH_THREAD_STACK_SIZE 4096
#define FINSH_CMD_SIZE 80
#define FINSH_USING_MSH 1
#define FINSH_USING_MSH_DEFAULT 1
#define FINSH_ARG_MAX 10
#define RT_USING_DFS 1
#define DFS_USING_WORKDIR 1
#define DFS_FILESYSTEMS_MAX 2
#define DFS_FILESYSTEM_TYPES_MAX 2
#define DFS_FD_MAX 16
#define RT_USING_DFS_ELMFAT 1
#define RT_DFS_ELM_CODE_PAGE 437
#define RT_DFS_ELM_WORD_ACCESS 1
#define RT_DFS_ELM_USE_LFN_3 1
#define RT_DFS_ELM_USE_LFN 3
#define RT_DFS_ELM_MAX_LFN 255
#define RT_DFS_ELM_DRIVES 2
#define RT_DFS_ELM_MAX_SECTOR_SIZE 2048
#define RT_DFS_ELM_USE_ERASE 1
#define RT_DFS_ELM_REENTRANT 1
#define RT_USING_DFS_DEVFS 1
#define RT_USING_DEVICE_IPC 1
#define RT_PIPE_BUFSZ 512
#define RT_USING_SYSTEM_WORKQUEUE 1
#define RT_SYSTEM_WORKQUEUE_STACKSIZE 2048
#define RT_SYSTEM_WORKQUEUE_PRIORITY 23
#define RT_USING_SERIAL 1
#define RT_SERIAL_USING_DMA 1
#define RT_SERIAL_RB_BUFSZ 4096
#define RT_SERIAL_DEFAULT_BAUDRATE 1000000
#define RT_USING_HWTIMER 1
#define RT_USING_HWMAILBOX 1
#define RT_USING_I2C 1
#define RT_USING_PIN 1
#define RT_USING_BLUETOOTH 1
#define RT_USING_MTD_NAND 1
#define RT_USING_RTC 1
#define RT_USING_ALARM 1
#define RT_USING_SDIO 1
#define RT_SDIO_STACK_SIZE 2048
#define RT_SDIO_THREAD_PRIORITY 15
#define RT_MMCSD_STACK_SIZE 2048
#define RT_MMCSD_THREAD_PREORITY 22
#define RT_MMCSD_MAX_PARTITION 16
#define RT_MMCSD_USER_OFFSET 0
#define RT_USING_SPI 1
#define RT_USING_AUDIO 1
#define RT_USING_SENSOR 1
#define RT_USING_LIBC 1
#define RT_USING_POSIX 1
#define RT_USING_SAL 1
#define SAL_USING_LWIP 1
#define SAL_USING_POSIX 1
#define RT_USING_NETDEV 1
#define NETDEV_USING_IFCONFIG 1
#define NETDEV_USING_PING 1
#define NETDEV_USING_NETSTAT 1
#define NETDEV_USING_AUTO_DEFAULT 1
#define RT_USING_LWIP 1
#define RT_USING_LWIP202 1
#define RT_LWIP_IGMP 1
#define RT_LWIP_ICMP 1
#define RT_LWIP_DNS 1
#define RT_LWIP_DHCP 1
#define IP_SOF_BROADCAST 1
#define IP_SOF_BROADCAST_RECV 1
#define RT_LWIP_IPADDR "192.168.1.30"
#define RT_LWIP_GWADDR "192.168.1.1"
#define RT_LWIP_MSKADDR "255.255.255.0"
#define RT_LWIP_UDP 1
#define RT_LWIP_TCP 1
#define RT_LWIP_RAW 1
#define RT_MEMP_NUM_NETCONN 8
#define RT_LWIP_PBUF_NUM 16
#define RT_LWIP_RAW_PCB_NUM 4
#define RT_LWIP_UDP_PCB_NUM 4
#define RT_LWIP_TCP_PCB_NUM 4
#define RT_LWIP_TCP_SEG_NUM 40
#define RT_LWIP_TCP_SND_BUF 8196
#define RT_LWIP_TCP_WND 8196
#define RT_LWIP_TCPTHREAD_PRIORITY 10
#define RT_LWIP_TCPTHREAD_MBOX_SIZE 8
#define RT_LWIP_TCPTHREAD_STACKSIZE 1024
#define RT_LWIP_ETHTHREAD_PRIORITY 12
#define RT_LWIP_ETHTHREAD_STACKSIZE 1024
#define RT_LWIP_ETHTHREAD_MBOX_SIZE 8
#define LWIP_NETIF_STATUS_CALLBACK 1
#define LWIP_NETIF_LINK_CALLBACK 1
#define SO_REUSE 1
#define LWIP_SO_RCVTIMEO 1
#define LWIP_SO_SNDTIMEO 1
#define LWIP_SO_RCVBUF 1
#define LWIP_NETIF_LOOPBACK 0
#define RT_LWIP_USING_PING 1
#define RT_LWIP_USING_HTTP 1
#define RT_USING_RYM 1
#define RT_USING_ULOG 1
#define ULOG_OUTPUT_LVL_D 1
#define ULOG_OUTPUT_LVL 7
#define ULOG_USING_ISR_LOG 1
#define ULOG_ASSERT_ENABLE 1
#define ULOG_LINE_BUF_SIZE 128
#define ULOG_OUTPUT_FLOAT 1
#define ULOG_OUTPUT_TIME 1
#define ULOG_OUTPUT_LEVEL 1
#define ULOG_OUTPUT_TAG 1
#define ULOG_OUTPUT_THREAD_NAME 1
#define ULOG_BACKEND_USING_CONSOLE 1
#define RT_NAME_MAX 8
#define RT_ALIGN_SIZE 4
#define RT_THREAD_PRIORITY_32 1
#define RT_THREAD_PRIORITY_MAX 32
#define RT_TICK_PER_SECOND 1000
#define RT_USING_OVERFLOW_CHECK 1
#define RT_USING_HOOK 1
#define RT_USING_IDLE_HOOK 1
#define RT_IDEL_HOOK_LIST_SIZE 4
#define IDLE_THREAD_STACK_SIZE 512
#define RT_USING_TIMER_SOFT 1
#define RT_TIMER_THREAD_PRIO 4
#define RT_TIMER_THREAD_STACK_SIZE 1024
#define RT_DEBUG 1
#define RT_USING_SEMAPHORE 1
#define RT_USING_MUTEX 1
#define RT_USING_EVENT 1
#define RT_USING_MAILBOX 1
#define RT_USING_MESSAGEQUEUE 1
#define RT_USING_MEMPOOL 1
#define RT_USING_MEMHEAP 1
#define RT_USING_SMALL_MEM 1
#define RT_USING_MEMTRACE 1
#define RT_USING_HEAP 1
#define RT_USING_DEVICE 1
#define RT_USING_CONSOLE 1
#define RT_CONSOLEBUF_SIZE 128
#define RT_CONSOLE_DEVICE_NAME "uart1"
#define RT_VER_NUM 0x30103
#define PKG_USING_NETUTILS 1
#define PKG_NETUTILS_PATH "/packages/iot/netutils"
#define PKG_NETUTILS_IPERF 1
#define PKG_USING_NETUTILS_LATEST_VERSION 1
#define PKG_NETUTILS_VER "latest"
#define BSP_USING_EMPTY_ASSERT 1
#define BLUETOOTH 1
#define BSP_BLE_SIBLES 1
#define BSP_BLE_NVDS_SYNC 1
#define NVDS_AUTO_UPDATE_MAC_ADDRESS 1
#define BT_RF_TEST 1
#define BSP_BLE_CONNECTION_MANAGER 1
#define BLE_CTKD_ENABLE 1
#define BSP_BLE_ANCS 1
#define BSP_BLE_TIMEC 1
#define BSP_BLE_PXPR 1
#define BSP_BLE_SERIAL_TRANSMISSION 1
#define BT_FINSH 1
#define BSP_BT_CONNECTION_MANAGER 1
#define BT_AUTO_CONNECT_LAST_DEVICE 1
#define BSP_BT_APP 1
#define ROM_ATT_BUF_SIZE 3084
#define ROM_LOG_SIZE 4096
#define BT_DUAL_HOST_MEM 1
#define MB_PORT 1
#define UART_PORT1 1
#define UART_PORT1_PORT "uart4"
#define BSP_USING_DATA_SVC 1
#define DATA_SVC_MBOX_THREAD_STACK_SIZE 1024
#define DATA_SVC_MBOX_THREAD_PRIORITY 13
#define DATA_SVC_PROC_THREAD_STACK_SIZE 4096
#define DATA_SVC_PROC_THREAD_PRIORITY 14
#define BSP_USING_ANCS_SVC 1
#define BSP_SHARE_PREFS 1
#define BSP_USING_LVGL_INPUT_AGENT 1
#define GUI_APP_FRAMEWORK 1
#define APP_TRANS_ANIMATION_NONE 1
#define GUI_MAX_RUNNING_APPS 2
#define USING_BUTTON_LIB 1
#define BUTTON_MAX_NUM 2
#define BUTTON_ADV_ACTION_CHECK_DELAY 3000
#define USING_IPC_QUEUE 1
#define USING_CPU_USAGE_PROFILER 1
#define CPU_PROFILER_MAX_THREAD_SWITCH_HIST_LEN 64
#define USING_EZIPA_DEC 1
#define EZIPA_MEM_CUSTOM 1
#define EZIPA_CUSTOM_INCLUDE_FILE "app_mem.h"
#define AUDIO 1
#define AUDIO_PATH_USING_HCI 1
#define AUDIO_USING_AUDPROC 1
#define AUDIO_USING_MANAGER 1
#define AUDIO_LOCAL_MUSIC 1
#define AUDIO_BT_AUDIO 1
#define AUDIO_SPEAKER_USING_CODEC 1
#define AUDIO_MIC_USING_CODEC 1
#define USING_PARTITION_TABLE 1
#define RT_USING_RTT_CMSIS 1
#define PKG_USING_FFMPEG 1
#define PKG_USING_FFMPEG_AUDIO 1
#define PKG_USING_FFMPEG_MJPEG 1
#define PKG_USING_FLASHDB 1
#define PKG_FLASHDB_PATH "/external/FlashDB"
#define FDB_KV_CACHE_TABLE_SIZE 1024
#define PKG_FLASHDB_ERASE_GRAN 2048
#define PKG_FLASHDB_START_ADDR 0
#define PKG_FLASHDB_DEBUG 1
#define PKG_FDB_USING_FILE_POSIX_MODE 1
#define PKG_FREETYPE 1
#define USING_JPEG_NANODEC 1
#define PKG_USING_LIBHELIX 1
#define PKG_USING_LITTLEVGL2RTT 1
#define LVGL_V8 1
#define DISABLE_LVGL_V9 1
#define DISABLE_LVGL_V7 1
#define LV_CONF_SKIP 1
#define LV_USING_EXT_RESOURCE_MANAGER 1
#define LV_COLOR_DEPTH_24 1
#define LV_COLOR_DEPTH 24
#define LV_COLOR_MIX_ROUND_OFS 128
#define LV_COLOR_CHROMA_KEY_HEX 0x00FF00
#define LV_MEM_SIZE_KILOBYTES 32
#define LV_MEM_ADDR 0x0
#define LV_MEM_BUF_MAX_NUM 16
#define LV_DISP_DEF_REFR_PERIOD 16
#define LV_INDEV_DEF_READ_PERIOD 16
#define LV_DPI_DEF_USELESS 130
#define LV_DRAW_COMPLEX 1
#define LV_SHADOW_CACHE_SIZE 0
#define LV_CIRCLE_CACHE_SIZE 4
#define LV_LAYER_SIMPLE_BUF_SIZE 24576
#define LV_IMG_CACHE_DEF_SIZE 16
#define LV_GRADIENT_MAX_STOPS 2
#define LV_GRAD_CACHE_DEF_SIZE 0
#define LV_DISP_ROT_MAX_BUF 10240
#define LV_USE_ASSERT_NULL 1
#define LV_USE_ASSERT_MALLOC 1
#define LV_ASSERT_HANDLER_INCLUDE "assert.h"
#define LV_USE_USER_DATA 1
#define LV_ATTRIBUTE_MEM_ALIGN_SIZE 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_DEFAULT_MONTSERRAT_14 1
#define LV_USE_FONT_PLACEHOLDER 1
#define LV_TXT_ENC_UTF8 1
#define LV_TXT_BREAK_CHARS " ,.;:-_"
#define LV_TXT_LINE_BREAK_LONG_LEN 0
#define LV_TXT_COLOR_CMD "#"
#define LV_USE_ARC 1
#define LV_USE_BAR 1
#define LV_USE_BTN 1
#define LV_USE_BTNMATRIX 1
#define LV_USE_CANVAS 1
#define LV_USE_CHECKBOX 1
#define LV_USE_DROPDOWN 1
#define LV_USE_IMG 1
#define LV_USE_LABEL 1
#define LV_LABEL_TEXT_SELECTION 1
#define LV_LABEL_LONG_TXT_HINT 1
#define LV_USE_LINE 1
#define LV_USE_ROLLER 1
#define LV_ROLLER_INF_PAGES 7
#define LV_USE_SLIDER 1
#define LV_USE_SWITCH 1
#define LV_USE_TEXTAREA 1
#define LV_TEXTAREA_DEF_PWD_SHOW_TIME 1500
#define LV_USE_TABLE 1
#define LV_USE_ANIMIMG 1
#define LV_USE_CALENDAR 1
#define LV_USE_CALENDAR_HEADER_ARROW 1
#define LV_USE_CALENDAR_HEADER_DROPDOWN 1
#define LV_USE_CHART 1
#define LV_USE_COLORWHEEL 1
#define LV_USE_IMGBTN 1
#define LV_USE_KEYBOARD 1
#define LV_USE_LED 1
#define LV_USE_LIST 1
#define LV_USE_MENU 1
#define LV_USE_METER 1
#define LV_USE_MSGBOX 1
#define LV_USE_SPAN 1
#define LV_SPAN_SNIPPET_STACK_SIZE 64
#define LV_USE_SPINBOX 1
#define LV_USE_SPINNER 1
#define LV_USE_TABVIEW 1
#define LV_USE_TILEVIEW 1
#define LV_USE_WIN 1
#define LV_USE_FLEX 1
#define LV_USE_GRID 1
#define LV_USE_FS_POSIX 1
#define LV_FS_POSIX_LETTER 47
#define LV_FS_POSIX_PATH ""
#define LV_FS_POSIX_CACHE_SIZE 0
#define LV_USE_GIF 1
#define LV_USE_QRCODE 1
#define LV_USE_SNAPSHOT 1
#define LV_USING_FREETYPE_ENGINE 1
#define FREETYPE_TINY_FONT 1
#define LV_USE_EZIP 1
#define LV_EXT_RES_NON_STANDALONE 1
#define LV_EXT_IMG_SEC_NAME ".ROM3_IMG"
#define LV_EXT_RES_DEFAULT_LANGUAGE "en_us"
#define LVGL_LCD_FB_CFG_INDEPENDENT 1
#define BSP_USING_TWO_COMPRESSED_FRAMEBUFFER 1
#define LV_FB_LINE_NUM 200
#define LV_RES_AUTO 1
#define PKG_USING_MPU6XXX 1
#define PKG_MPU6XXX_PATH "/packages/peripherals/mpu6xxx"
#define PKG_USING_MPU6XXX_LATEST_VERSION 1
#define PKG_MPU6XXX_VER "latest"
#define PKG_USING_QUICKJS 1
#define QUICKJS_LVGL 1
#define QUICKJS_USING_PSRAM 1
#define QUICKJS_PSRAM_SIZE 524288
#define PKG_USING_RLOTTIE 1
#define LOTTIE_JSON_SUPPORT 1
#define PKG_USING_WEBRTC 1
#define WEBRTC_ANS_FIX 1
#define WEBRTC_AGC_FIX 1
#define WEBRTC_AECM 1
#define FFT_USING_WEBRTC 1
#define PKG_USING_STATE_MACHINE 1
#define BSP_USING_TEST_SVC 1
#define BSP_USING_ALARM_MANAGER_SVC 1
#define BSP_ALARM_MAX 8
#define ROTATE_MEM_IN_SRAM 1
#define FREETYPE_CACHE_IN_PSRAM 1
#define MESSAGE_CACHE_IN_PSRAM 1
#define IMAGE_CACHE_IN_PSRAM_SIZE 12000000
#define IMAGE_CACHE_IN_SRAM_SIZE 50000
#define FT_CACHE_SIZE 320000
#define MESSAGE_CACHE_SIZE 96000
#define BF0_HCPU 1
#define SOLUTION_ALLOC_MEM 1
#define CUSTOM_MEM_MAP 1
#define FREETYPE_TINY_FONT_LITE 1
#endif
