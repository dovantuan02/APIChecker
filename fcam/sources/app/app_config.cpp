#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex>
#include <string.h>

#include <iostream>
#include <cstring>

using namespace std;

#include "utils.h"

#include "app.h"
#include "app_dbg.h"
#include "app_config.h"
#include "fca_parameter.h"
#include "parser_json.h"
#include "ota.h"

/******************************************************************************
 * APP CONFIGURE CLASS (BASE)
 ******************************************************************************/

#include <vector>

app_config::app_config() {}

void app_config::initializer(char *path) {
	this->set_config_file_path(static_cast<string>((const char *)path));
}

void app_config::set_config_file_path(char *path) {
	m_config_path = static_cast<string>(path);
}

void app_config::set_config_file_path(string path) {
	m_config_path = path;
}

void app_config::get_config_file_path(char *path) {
	strcpy(path, (const char *)m_config_path.data());
}

void app_config::get_config_file_path(string &path) {
	path = m_config_path;
}

int app_config::read_config_file_to_str(string &cfg) {
	struct stat file_info;
	int configure_file_obj = APP_CONFIG_ERROR_FILE_OPEN;
	int buffer_len;
	char *buffer;

	configure_file_obj = open(m_config_path.data(), O_RDONLY);

	if (configure_file_obj < 0) {
		return APP_CONFIG_ERROR_FILE_OPEN;
	}

	fstat(configure_file_obj, &file_info);

	buffer_len = file_info.st_size + 1;
	buffer	   = (char *)malloc(buffer_len);

	if (buffer == NULL) {
		return APP_CONFIG_ERROR_DATA_MALLOC;
	}

	memset(buffer, 0, buffer_len);

	/*get data*/
	pread(configure_file_obj, buffer, file_info.st_size, 0);

	close(configure_file_obj);

	cfg = string(buffer);

	free(buffer);

	return 0;
}

bool app_config::read_config_file_to_js(json &cfg) {
	if (read_json_file(cfg, m_config_path))
		return true;
	return false;
}

int app_config::write_config_file_to_str(string &cfg) {
	const char *buffer = cfg.data();

	FILE *file_config_obj = fopen(m_config_path.data(), "w");

	if (file_config_obj == NULL) {
		return APP_CONFIG_ERROR_FILE_OPEN;
	}

	fwrite(buffer, 1, cfg.length(), file_config_obj);

	fclose(file_config_obj);

	return 0;
}

bool app_config::write_config_file_from_js(json &cfg) {
	if (write_json_file(cfg, m_config_path))
		return true;
	return false;
}

int fca_readConfigUsrDfaulFileToJs(json &cfgJs, string &file) {
	// string filePath = FCA_USER_CONF_PATH + string("/") + file;
	string filePath = "/tmp/" + file;
	if (!read_json_file(cfgJs, filePath)) {
		APP_PRINT("Can not read: %s\n", filePath.data());
		filePath = FCA_DFAUL_CONF_PATH + string("/") + file;
		cfgJs.clear();
		if (!read_json_file(cfgJs, filePath)) {
			APP_PRINT("Can not read: %s\n", filePath.data());
			return APP_CONFIG_ERROR_FILE_OPEN;
		}
	}
	return APP_CONFIG_SUCCESS;
}

int fca_configGetDeviceInfoStr(json &devInfoJs) {
	json cfgJs;
	string file = FCA_DEVICE_INFO_PATH;

	if (!read_json_file(cfgJs, file)) {
		APP_DBG("Can not read: %s\n", file.data());
		return APP_CONFIG_ERROR_FILE_OPEN;
	}

	devInfoJs = {
		{"MessageType", string(MESSAGE_TYPE_DEVINFO)},
		{"Serial",	   SERIAL},
		{"Data",		 cfgJs					   },
	};
	return APP_CONFIG_SUCCESS;
}

int fca_configGetUpgradeStatus(json &dataJs) {
	string content;
	string filePath = FCA_USER_CONF_PATH "/" FCA_OTA_STATUS;
	if (!read_raw_file(content, filePath)) {
		APP_DBG("Can not read: %s\n", filePath.data());
		return APP_CONFIG_ERROR_FILE_OPEN;
	}

	dataJs["Data"]["UpgradeStatus"] = fca_otaStatusUpgrade(stoi(content));

	return APP_CONFIG_SUCCESS;
}

int fca_configGetMQTT(fca_netMQTT_t *mqttCfg) {
	json cfgJs;

	string fileName = FCA_NETWORK_MQTT_FILE;
	if (fca_readConfigUsrDfaulFileToJs(cfgJs, fileName)) {
		return APP_CONFIG_ERROR_FILE_OPEN;
	}

	if (fca_jsonGetNetMQTT(cfgJs, mqttCfg)) {
		APP_DBG("MQTT config: %s\n", cfgJs.dump().data());
		return APP_CONFIG_SUCCESS;
	}
	else {
		APP_DBG("Can not convert: %s\n", fileName.data());
		return APP_CONFIG_ERROR_DATA_INVALID;
	}
}