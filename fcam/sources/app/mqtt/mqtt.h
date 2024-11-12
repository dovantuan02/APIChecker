#ifndef __MQTT__H__
#define __MQTT__H__

#include <stdint.h>
#include <string.h>
#include <atomic>

#include <mosquittopp.h>

#include "ak.h"

#include "app.h"
#include "app_dbg.h"
#include "fca_parameter.h"

class mqtt : public mosqpp::mosquittopp {
public:
	mqtt(mqttTopicCfg_t *mqtt_parameter, fca_netMQTT_t *mqtt_config);
	~mqtt() {
		loop_stop(true);	// Force stop thread (true)
		if (lastMsgPtr != NULL) {
			free(lastMsgPtr);
		}
		// disconnect();
		mosqpp::lib_cleanup();
		pthread_mutex_destroy(&m_mutex);
		APP_DBG("~mqtt() called\n");
	}

	// Publish functions
	bool publishResponse(json &js, int qos = 0, bool retain = false);
	bool publishStatus(json &js, int qos = 0, bool retain = true);
	bool subcribePerform(string &topic, int qos = 0);
	bool unsubcribePerform(string &topic);
	int tryConnect(const char *capath);
	void clearRetainMsg(const char *topic, bool is_retain);
	int addSubTopicMap(const string &topic, const int &mid, const int &qos);
	int removeSubTopicMap(const string &topic);
	int removeSubTopicMap(const int &mid);
	void showSubTopicMap();
	void retrySubTopics();

	// getter and setter
	void setConnected(bool state);
	bool isConnected(void);

	// Callback functions
	void on_connect(int rc);
	void on_disconnect(int rc);
	void on_publish(int mid);
	void on_subscribe(int mid, int qos_count, const int *granted_qos);
	void on_message(const struct mosquitto_message *message);
	void on_log(int level, const char *log_str);

protected:
	bool checkMessageDuplicate(const struct mosquitto_message *message);

private:
	// store topic: default it will sub 1 topic when MQTT is connected
	fca_netMQTT_t m_cfg;
	mqttTopicCfg_t m_topics;
	int m_mid;
	std::atomic<bool> m_connected;
	int lenLastMsg;
	uint8_t *lastMsgPtr;
	std::map<std::string, std::map<std::string, int>> m_subTopicMap;
	pthread_mutex_t m_mutex;
};

#endif	  //__MQTT__H__
