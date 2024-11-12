#ifndef __APP_H__
#define __APP_H__

#include <string>

#include "app_config.h"

using namespace std;

/*****************************************************************************/
/* task GW_SYS define.
 */
/*****************************************************************************/
/* define timer */
#define GW_SYS_WATCH_DOG_TIMEOUT_INTERVAL		(120)	  // 120s watchdog
#define GW_SYS_WATCH_DOG_PING_TASK_REQ_INTERVAL (5000)	  // 5s reset watchdog
/* define signal */
enum {
	GW_SYS_WATCH_DOG_PING_NEXT_TASK_REQ = AK_USER_DEFINE_SIG,
	GW_SYS_WATCH_DOG_PING_NEXT_TASK_RES,
	GW_SYS_RESET_WATCH_DOG_REQ,
	GW_SYS_CLOUD_REBOOT_REQ,
	GW_SYS_REBOOT_REQ,
	GW_SYS_CMD_REBOOT_REQ,
	GW_SYS_START_WATCH_DOG_REQ,
	GW_SYS_STOP_WATCH_DOG_REQ,
	GW_SYS_SET_TELNET_REQ,
	GW_SYS_GET_TELNET_REQ,
	GW_SYS_SET_LOGIN_INFO_REQ,
	GW_SYS_GET_LOGIN_INFO_REQ,
	GW_SYS_RUNNING_CMDS_REQ,
	GW_SYS_LOAD_SYSTEM_CONTROLS_CONFIG_REQ,
	GW_SYS_SET_SYSTEM_CONTROLS_REQ,
	GW_SYS_GET_SYSTEM_CONTROLS_REQ,
	GW_SYS_LOAD_AUDIO_CONFIG_REQ,
	GW_SYS_LOAD_SPEAKER_MIC_CONFIG_REQ,
};

/*****************************************************************************/
/*  task GW_CONSOLE define
 */
/*****************************************************************************/
/* define timer */

/* define signal */
enum {
	GW_CONSOLE_INTERNAL_LOGIN_CMD = AK_USER_DEFINE_SIG,
};

/*****************************************************************************/
/*  task GW_CLOUD define
 */
/*****************************************************************************/
/* define timer */
#define GW_CLOUD_MQTT_GEN_STATUS_TIMEOUT_INTERVAL			(3000)
#define GW_CLOUD_MQTT_TRY_CONNECT_TIMEOUT_INTERVAL			(5000)
#define GW_CLOUD_MQTT_SUB_TOPIC_STATUS_INTERVAL				(5000)
#define GW_CLOUD_MQTT_CHECK_SUB_TOPIC_TIMEOUT_INTERVAL		(7000)
#define GW_CLOUD_MQTT_CHECK_CONNECT_STATUS_INTERVAL			(10000)
#define GW_CLOUD_MQTT_TRY_CONNECT_AFTER_DISCONNECT_INTERVAL (20000)

/* define signal */
enum {
	GW_CLOUD_WATCHDOG_PING_REQ = AK_USER_WATCHDOG_SIG,
	GW_CLOUD_MQTT_INIT_REQ	   = AK_USER_DEFINE_SIG,
	GW_CLOUD_MQTT_TRY_CONNECT_REQ,
	GW_CLOUD_MQTT_CHECK_CONNECT_STATUS_REQ,
	GW_CLOUD_DATA_COMMUNICATION,
	GW_CLOUD_SET_MQTT_CONFIG_REQ,
	GW_CLOUD_GET_MQTT_CONFIG_REQ,
	GW_CLOUD_CAMERA_STATUS_RES,
	GW_CLOUD_CAMERA_CONFIG_RES,
	GW_CLOUD_CAMERA_ALARM_RES,
	GW_CLOUD_SIGNALING_MQTT_RES,
	GW_CLOUD_MESSAGE_LENGTH_OUT_OF_RANGE_REP,
	GW_CLOUD_CHECK_BROKER_STATUS_REQ,
	GW_CLOUD_GEN_MQTT_STATUS_REQ,
	GW_CLOUD_MQTT_SUB_TOPIC_REP,
	GW_CLOUD_MQTT_CHECK_SUB_TOPIC_REQ,
};

/*****************************************************************************/
/* task GW_LED define
 */
/*****************************************************************************/
/* define timer */
#define GW_LED_BLINK_1S_INTERVAL	(10000)
#define GW_LED_BLINK_500MS_INTERVAL (5000)
/* define signal */

enum {
	GW_LED_WATCHDOG_PING_REQ = AK_USER_WATCHDOG_SIG,
	GW_LED_WHITE_BLINK		 = AK_USER_DEFINE_SIG,
	GW_LED_WHITE_ON,
	GW_LED_WHITE_OFF,
	GW_LED_ORANGE_BLINK,
	GW_LED_ORANGE_ON,
	GW_LED_ORANGE_OFF,
};

/*****************************************************************************/
/* task GW_NETWORK define
 */
/*****************************************************************************/
/* define timer */
#define GW_NET_RESTART_NETWORK_SERVICES_TIMEROUT_INTERVAL (240000)	 /* 4min */
#define GW_NET_RELOAD_WIFI_DRIVER_TIMEROUT_INTERVAL		  (900000)	 /* 15min */
#define GW_NET_REBOOT_ERROR_NETWORK_TIMEROUT_INTERVAL	  (14400000) /* 4h */
#define GW_NET_RETRY_CONNECT_MQTT_INTERVAL				  (5000)	 /* 5000ms */
#define GW_NET_START_AP_MODE_TIMEOUT_INTERVAL			  (5000)	 /* 5000ms */
#define GW_NET_CHECK_CONNECT_ROUTER_INTERVAL			  (1000)	 /* 1s */
#define GW_NET_CHECK_STATE_PLUG_LAN_INTERVAL			  (500)		 /* 500ms */

/* define signal */
enum {
	/* wifi station interface */
	GW_NET_WATCHDOG_PING_REQ = AK_USER_WATCHDOG_SIG,
	GW_NET_NETWORK_INIT_REQ	 = AK_USER_DEFINE_SIG,

	GW_NET_WIFI_MQTT_SET_CONF_REQ,
	GW_NET_WIFI_MQTT_GET_CONF_REQ,
	GW_NET_ETHERNET_MQTT_SET_CONF_REQ,
	GW_NET_ETHERNET_MQTT_GET_CONF_REQ,
	GW_NET_WIFI_MQTT_GET_LIST_AP_REQ,
	GW_NET_MQTT_GET_NETWORK_INFO_REQ,

	GW_NET_STA_CONTROL_WITH_CONFIG_REQ,
	GW_NET_ETHERNET_CONTROL_WITH_CONFIG_REQ,
	GW_NET_WIFI_AP_START_REQ,

	GW_NET_WIFI_STA_CONNECT_TO_ROUTER,
	GW_NET_WIFI_STA_CONNECTED_TO_ROUTER,

	GW_NET_INTERNET_STATUS_REQ,
	GW_NET_GET_STATE_LAN_REQ,

	GW_NET_RESET_WIFI_REQ,
	GW_NET_PLAY_VOICE_NETWORK_CONNECTED_REQ,
	GW_NET_RESTART_UDHCPC_NETWORK_INTERFACES_REQ,
	GW_NET_RELOAD_WIFI_DRIVER_REQ,
	GW_NET_REBOOT_ERROR_NETWORK_REQ,
};

/*****************************************************************************/
/* task GW_FW_TASK define
 */
/*****************************************************************************/
/* define timer */
#define GW_FW_UPGRADE_FIRMWARE_TIMEOUT_INTERVAL (300000) /* 5min */

/* define signal */
enum {
	/* wifi station interface */
	GW_FW_WATCHDOG_PING_REQ = AK_USER_WATCHDOG_SIG,
	GW_FW_GET_URL_REQ		= AK_USER_DEFINE_SIG,
	GW_FW_DOWNLOAD_START_REQ,
	GW_FW_UPGRADE_START_REQ,
	GW_FW_RELEASE_OTA_STATE_REQ,
};

/*****************************************************************************/
/* task GW_FW_VIDEO define
 */
/*****************************************************************************/
/* define timer */


/* define signal */
enum {
	/* wifi station interface */
	GW_VIDEO_WATCHDOG_PING_REQ = AK_USER_WATCHDOG_SIG,
	GW_VIDEO_INIT_REQ		= AK_USER_DEFINE_SIG,
	GW_VIDEO_START_REQ,
	GW_VIDEO_STOP_REQ,
};


/*****************************************************************************/
/*  global define variable
 */
/*****************************************************************************/
#define APP_OK (0x00)
#define APP_NG (0x01)

#define APP_FLAG_OFF (0x00)
#define APP_FLAG_ON	 (0x01)

/* define file name */
#define FCA_SERIAL_FILE			   "Serial"
#define FCA_ACCOUNT_FILE		   "Account"
#define FCA_P2P_FILE			   "P2P"
#define FCA_ENCODE_FILE			   "Encode"
#define FCA_DEVINFO_FILE		   "DeviceInfo"
#define FCA_MOTION_FILE			   "Motion"
#define FCA_WIFI_FILE			   "Wifi"
#define FCA_ETHERNET_FILE		   "Ethernet"
#define FCA_WATERMARK_FILE		   "Watermark"
#define FCA_S3_FILE				   "S3"
#define FCA_RTMP_FILE			   "RTMP"
#define FCA_NETWORK_CA_FILE		   "Bundle_RapidSSL_2023.cert"
#define FCA_NETWORK_MQTT_FILE	   "MQTTService"
#define FCA_NETWORK_WPA_FILE	   "wpa_supplicant.conf"
#define FCA_CAMERA_PARAM_FILE	   "CameraParam"
#define FCA_PTZ_FILE			   "PTZ"
#define FCA_LOG_FILE			   "app.log"
#define FCA_RTC_SERVERS_FILE	   "RtcServersConfig"
#define FCA_STORAGE_FILE		   "Storage"
#define FCA_RECORD_FILE			   "Record"
#define FCA_CHECKSUM_FILE		   "SdChecksumFile"
#define FCA_OTA_STATUS			   "OTAStatus"
#define FCA_IO_DRIVER_CONTROL_FILE "IoControl"
#define FCA_RAINBOW_FILE		   "rainbow.json"
#define FCA_OWNER_STATUS		   "OwnerStatus"
#define FCA_ALARM_CONTROL_FILE	   "AlarmControl"
#define FCA_STEP_MOTOR_FILE		   "StepMotors"
#define FCA_DEVICE_LOGIN_INFO_FILE "LoginInfo"
#define FCA_SYSTEM_CONTROLS_FILE   "SystemControls"
#define FCA_SERIAL_NUM_DEFAULT	   "24010000004"
#define FCA_MAC_DEFAULT			   "00:E0:4C:35:00:00"

/* define path name */
#define FCA_DEVICE_SOUND_PATH		  "/app/sound"
#define FCA_DEVICE_INFO_PATH		  "/app/version"
#define FCA_USER_CONF_PATH			  "/usr/conf"
#define FCA_DFAUL_CONF_PATH			  "/app/default"
#define FCA_LOG_FILE_PATH			  FCA_USER_CONF_PATH "/log"
#define FCA_MEDIA_JPEG_PATH			  "/tmp/jpeg"
#define FCA_MEDIA_MP4_PATH			  "/tmp/mp4"
#define FCA_JPEG_MOTION_TMP_PATH	  "/tmp/jpeg"
#define FCA_SDCARD_CHECKSUM_FILE_PATH "/tmp/sdFileInfo"
#define FCA_RTSP_KEY_GEN_FILE_PATH	  "/tmp/rtspKeyGen"

/* use for wifi and network */
#define FCA_NET_WIRED_IF_NAME		 "eth0"
#define FCA_NET_WIFI_STA_IF_NAME	 "wlan0"
#define FCA_NET_WIFI_AP_IF_NAME		 "wlan1"
#define FCA_UDHCPC_SCRIPT			 "/app/bin/udhcpc.sh"
#define FCA_NET_UDHCPC_PID_FILE		 "/var/run/%s.pid"
#define FCA_NET_WIFI_AP_UDHCPD_FILE	 "/tmp/udhcpd.conf"
#define FCA_NET_WIFI_AP_HOSTADP_FILE "/tmp/hostapd.conf"
#define FCA_NET_WIFI_STA_WPA_FILE	 "/tmp/wpa_supplicant.conf"
#define FCA_NET_HOSTS_FILE			 "/tmp/hosts"
#define FCA_DNS_FILE				 "/tmp/resolv.conf"

#define FCA_AUDIO_AAC_EXT  ".aac"
#define FCA_AUDIO_G711_EXT ".g711"

#define FCA_MQTT_KEEPALIVE	90
#define FCA_SSL_VERIFY_NONE 0
#define FCA_SSL_VERIFY_PEER 1

#define FCA_SOUND_REBOOT_DEVICE_FILE	   "reboot_device.pcm"
#define FCA_SOUND_WAIT_CONNECT_FILE		   "waiting_for_connection.pcm"
#define FCA_SOUND_HELLO_DEVICE_FILE		   "hello_fpt_camera.pcm"
#define FCA_SOUND_NET_CONNECT_SUCCESS_FILE "connection_success.pcm"
#define FCA_SOUND_MOTION_ALARM_FILE		   "motion_alarm.pcm"

#define FCA_GET_SERIAL_INFO					"2220-I03S-R18-C03O24020000044"
#define SERIAL 								"c03o24020000044"

#endif	  // __APP_H__
