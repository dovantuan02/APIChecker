#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#include <stdint.h>
#include <string.h>

#include "ak.h"
#include "app.h"
#include "app_data.h"
#include "ak_dbg.h"
#include "sys_dbg.h"
#include "json.hpp"

#include "fca_parameter.h"

using namespace std;
using json = nlohmann::json;

#define APP_CONFIG_SUCCESS			  (0)
#define APP_CONFIG_ERROR_FILE_OPEN	  (-1)
#define APP_CONFIG_ERROR_DATA_MALLOC  (-2)
#define APP_CONFIG_ERROR_DATA_INVALID (-3)
#define APP_CONFIG_ERROR_DATA_DIFF	  (-4)
#define APP_CONFIG_ERROR_TIMEOUT	  (-5)
#define APP_CONFIG_ERROR_BUSY		  (-6)
#define APP_CONFIG_ERROR_ANOTHER	  (-7)
#define APP_CONFIG_ERROR_DATA_MISSING (-8)

/******************************************************************************
 * APP CONFIGURE CLASS (BASE)
 ******************************************************************************/
class app_config {
public:
	app_config();

	void initializer(char *);
	/* configure file */
	void set_config_file_path(char *);
	void set_config_file_path(string);
	void get_config_file_path(char *);
	void get_config_file_path(string &);

	int read_config_file_to_str(string &cfg);
	bool read_config_file_to_js(json &);
	int write_config_file_to_str(string &cfg);
	bool write_config_file_from_js(json &);

private:
	string m_config_path;
};

/******************************************************************************
 * global config
 ******************************************************************************/
#define MESSAGE_TYPE_DEVINFO			   "DeviceInfo"
#define MESSAGE_TYPE_UPGRADE			   "UpgradeFirmware"
#define MESSAGE_TYPE_UPGRADE_STATUS		   "UpgradeStatus"
#define MESSAGE_TYPE_ALARM				   "AlarmInfo"
#define MESSAGE_TYPE_MQTT				   "MQTTSetting"
#define MESSAGE_TYPE_RTMP				   "RTMPSetting"
#define MESSAGE_TYPE_MOTION				   "MotionSetting"
#define MESSAGE_TYPE_MOTION_DETECT		   "MotionDetect"
#define MESSAGE_TYPE_HUMAN_DETECT		   "HumanDetect"
#define MESSAGE_TYPE_BABYCRYING_DETECT	   "BabyCryingDetect"
#define MESSAGE_TYPE_ENCODE				   "EncodeSetting"
#define MESSAGE_TYPE_REBOOT				   "Reboot"
#define MESSAGE_TYPE_RESET				   "ResetSetting"
#define MESSAGE_TYPE_STORAGE_FORMAT		   "StorageFormat"
#define MESSAGE_TYPE_STORAGE_INFO		   "StorageInfo"
#define MESSAGE_TYPE_CAMERA_PARAM		   "ParamSetting"
#define MESSAGE_TYPE_WIFI				   "WifiSetting"
#define MESSAGE_TYPE_ETHERNET			   "EthernetSetting"
#define MESSAGE_TYPE_WATERMARK			   "WatermarkSetting"
#define MESSAGE_TYPE_S3					   "S3Setting"
#define MESSAGE_TYPE_NETWORK_INFO		   "NetworkInfo"
#define MESSAGE_TYPE_SYSTEM_INFO		   "SystemInfo"
#define MESSAGE_TYPE_NETWORKAP			   "NetworkAp"
#define MESSAGE_TYPE_P2P				   "P2PSetting"
#define MESSAGE_TYPE_P2P_INFO			   "P2Pinfo"
#define MESSAGE_TYPE_PTZ				   "PTZ"
#define MESSAGE_TYPE_UPLOAD_FILE		   "UploadFile"
#define MESSAGE_TYPE_RECORD				   "RecordSetting"
#define MESSAGE_TYPE_SIGNALING			   "Signaling"
#define MESSAGE_TYPE_STUN_SERVER		   "StunServer"
#define MESSAGE_TYPE_TURN_SERVER		   "TurnServer"
#define MESSAGE_TYPE_WEB_SOCKET_SERVER	   "WebSocketServer"
#define MESSAGE_TYPE_CONTROL_LED_INDICATOR "LedIndicator"
#define MESSAGE_TYPE_OWNER_STATUS		   "OwnerStatus"
#define MESSAGE_TYPE_ALARM_CONTROL		   "AlarmControl"
#define MESSAGE_TYPE_TELNET_CONTROL		   "Telnet"
#define MESSAGE_TYPE_LOGIN_INFO			   "LoginInfo"
#define MESSAGE_TYPE_RUNNING_CMDS		   "ExecutingCommands"
#define MESSAGE_TYPE_SYSTEM_CONTROLS	   "SystemControls"

extern int fca_configGetDeviceInfoStr(json &devInfoJs);
extern int fca_configGetUpgradeStatus(json &dataJs);

extern int fca_configGetMQTT(fca_netMQTT_t *mqttCfg);
#endif	  //__APP_CONFIG_H__
