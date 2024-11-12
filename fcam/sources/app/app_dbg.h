#ifndef __APP_DBG_H__
#define __APP_DBG_H__

#include <stdio.h>
#include "sys_dbg.h"

#define APP_DBG_EN		  1
#define APP_PRINT_EN	  1
#define APP_ERR_EN		  0
#define APP_DBG_SIG_EN	  1
#define APP_DBG_DRIVER_EN 1
#define APP_DBG_ISP_EN	  1
#define APP_DBG_RTC_EN	  1
#define APP_DBG_NET_EN	  1
#define APP_DBG_MQTT_EN	  1
#define APP_DBG_MD_EN	  1
#define APP_DBG_OSD_EN	  1
#define APP_DBG_CMD_EN	  1
#define APP_DBG_OTA_EN	  1
#define APP_DBG_AV_EN	  1
#define APP_DBG_VIDEO_EN  1
#define APP_DBG_AUDIO_EN  1

/* module debug */
#define SD_DEBUG	 0
#define RECORD_DEBUG 0

#if (APP_PRINT_EN == 1)
#define APP_PRINT(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
#define APP_PRINT(fmt, ...)
#endif

#if !defined(RELEASE) && (APP_DBG_EN == 1)
#define APP_DBG(fmt, ...) __LOG__(fmt, "APP_DBG", ##__VA_ARGS__)
#else
#define APP_DBG(fmt, ...)
#endif

#if !defined(RELEASE) && (APP_DBG_ISP_EN == 1)
#define APP_DBG_ISP(fmt, ...) __LOG__(fmt, "APP_DBG_ISP", ##__VA_ARGS__)
#else
#define APP_DBG_ISP(fmt, ...)
#endif

#if !defined(RELEASE) && (APP_DBG_CMD_EN == 1)
#define APP_DBG_CMD(fmt, ...) __LOG__(fmt, "APP_DBG_CMD", ##__VA_ARGS__)
#else
#define APP_DBG_CMD(fmt, ...)
#endif

#if !defined(RELEASE) && (APP_DBG_RTC_EN == 1)
#define APP_DBG_RTC(fmt, ...) __LOG__(fmt, "APP_DBG_RTC", ##__VA_ARGS__)
#else
#define APP_DBG_RTC(fmt, ...)
#endif

#if !defined(RELEASE) && (APP_DBG_NET_EN == 1)
#define APP_DBG_NET(fmt, ...) __LOG__(fmt, "APP_DBG_NET", ##__VA_ARGS__)
#else
#define APP_DBG_NET(fmt, ...)
#endif

#if !defined(RELEASE) && (APP_DBG_MD_EN == 1)
#define APP_DBG_MD(fmt, ...) __LOG__(fmt, "APP_DBG_MD", ##__VA_ARGS__)
#else
#define APP_DBG_MD(fmt, ...)
#endif

#if !defined(RELEASE) && (APP_DBG_OSD_EN == 1)
#define APP_DBG_OSD(fmt, ...) __LOG__(fmt, "APP_DBG_OSD_EN", ##__VA_ARGS__)
#else
#define APP_DBG_OSD(fmt, ...)
#endif

#if !defined(RELEASE) && (APP_DBG_MQTT_EN == 1)
#define APP_DBG_MQTT(fmt, ...) __LOG__(fmt, "APP_DBG_MQTT", ##__VA_ARGS__)
#else
#define APP_DBG_MQTT(fmt, ...)
#endif

#if !defined(RELEASE) && (APP_DBG_OTA_EN == 1)
#define APP_DBG_OTA(fmt, ...) __LOG__(fmt, "APP_DBG_OTA", ##__VA_ARGS__)
#else
#define APP_DBG_OTA(fmt, ...)
#endif

#if !defined(RELEASE) && (APP_DBG_AV_EN == 1)
#define APP_DBG_AV(fmt, ...) __LOG__(fmt, "APP_DBG_AV", ##__VA_ARGS__)
#else
#define APP_DBG_AV(fmt, ...)
#endif

#if !defined(RELEASE) && (APP_DBG_VIDEO_EN == 1)
#define APP_DBG_VIDEO(fmt, ...) __LOG__(fmt, "APP_DBG_VIDEO", ##__VA_ARGS__)
#else
#define APP_DBG_VIDEO(fmt, ...)
#endif

#if !defined(RELEASE) && (APP_DBG_AUDIO_EN == 1)
#define APP_DBG_AUDIO(fmt, ...) __LOG__(fmt, "APP_DBG_AUDIO", ##__VA_ARGS__)
#else
#define APP_DBG_AUDIO(fmt, ...)
#endif

#if !defined(RELEASE) && (APP_DBG_DRIVER_EN == 1)
#define APP_DRIVER(fmt, ...) __LOG__(fmt, "APP_DRIVER", ##__VA_ARGS__)
#else
#define APP_DRIVER(fmt, ...)
#endif

#if (APP_ERR_EN == 1)
#define APP_ERR(x...)                                         \
	do {                                                      \
		printf("\033[1;31m%s->%d: ", __FUNCTION__, __LINE__); \
		printf(x);                                            \
		printf("\033[0m\n");                                  \
	} while (0)
#else
#define APP_ERR(fmt, ...)
#endif

#if (APP_DBG_SIG_EN == 1)
#define APP_DBG_SIG(fmt, ...) __LOG__(fmt, "SIG -> ", ##__VA_ARGS__)
#else
#define APP_DBG_SIG(fmt, ...)
#endif

#endif	  //__APP_DBG_H__
