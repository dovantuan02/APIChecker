#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <ctime>
#include <memory>
#include <string.h>
#include <iostream>

#include "ak.h"
#include "timer.h"
#include "app.h"
#include "app_dbg.h"
#include "app_data.h"
#include "app_config.h"
#include "task_list.h"
#include "mqtt.h"

static void process_mqtt_msg(unsigned char *pload, int len);

static bool mqttInitialized		  = false;
static int mqttFailCnt			  = 0;
static fca_netMQTT_t mqttService = {0};
static mqttTopicCfg_t mqttTopics;

unique_ptr<mqtt> mospp;

static void init_topic() {
	string serial = string(SERIAL);
	sprintf(mqttTopics.topicStatus, "ipc/fss/%s/%s", serial.c_str(), "status");
	sprintf(mqttTopics.topicRequest, "ipc/fss/%s/%s", serial.c_str(), "reqcfg");
	sprintf(mqttTopics.topicResponse, "ipc/fss/%s/%s", serial.c_str(), "rescfg");
}

q_msg_t gw_task_cloud_mailbox;

void *gw_task_cloud_entry(void *) {
	ak_msg_t *msg = AK_MSG_NULL;
	wait_all_tasks_started();
	APP_DBG_MQTT("[STARTED] gw_task_cloud_entry\n");

	task_post_pure_msg(GW_TASK_CLOUD_ID, GW_CLOUD_MQTT_INIT_REQ);
	while (1) {
		/* get messge */
		msg = ak_msg_rev(GW_TASK_CLOUD_ID);

		switch (msg->header->sig) {

		case GW_CLOUD_MQTT_INIT_REQ: {
			APP_DBG_SIG("GW_CLOUD_MQTT_INIT_REQ\n");
			if (!mqttInitialized && fca_configGetMQTT(&mqttService) == APP_CONFIG_SUCCESS) {
				mqttInitialized = true;
				init_topic();
				task_post_pure_msg(GW_TASK_CLOUD_ID, GW_CLOUD_MQTT_TRY_CONNECT_REQ);
			}
			else {
				APP_PRINT("[ERR] mqtt config file not foud\n");
			}
		} break;


	case GW_CLOUD_MQTT_TRY_CONNECT_REQ: {
			APP_DBG_SIG("GW_CLOUD_MQTT_TRY_CONNECT_REQ\n");

			if (!mqttInitialized) {
				task_post_pure_msg(GW_TASK_CLOUD_ID, GW_CLOUD_MQTT_INIT_REQ);
				break;
			}

			timer_remove_attr(GW_TASK_CLOUD_ID, GW_CLOUD_MQTT_TRY_CONNECT_REQ);
			timer_remove_attr(GW_TASK_CLOUD_ID, GW_CLOUD_MQTT_CHECK_CONNECT_STATUS_REQ);
			timer_remove_attr(GW_TASK_CLOUD_ID, GW_CLOUD_MQTT_CHECK_SUB_TOPIC_REQ);

			// string caPath = MTCE_DFAUL_CONF_PATH "/" MTCE_NETWORK_CA_FILE;
			string caPath = "/app/default/Bundle_RapidSSL_2023.cert";

			APP_DBG_MQTT("CERTIFICATE Path: %s\n", caPath.c_str());
			APP_DBG_MQTT("MQTT CONNECTION\n");
			APP_DBG_MQTT("\tHost: %s\n", mqttService.host);
			APP_DBG_MQTT("\tUsername: %s\n", mqttService.username);
			APP_DBG_MQTT("\tPassword: %s\n", mqttService.password);
			APP_DBG_MQTT("\tID: %s\n", mqttService.clientID);

			mospp.reset();
			mospp	  = make_unique<mqtt>(&mqttTopics, &mqttService);
			int ecode = mospp->tryConnect(caPath.c_str());
			APP_DBG_MQTT("MQTT_ECODE: %d\n", ecode);
			if (ecode != 0) {
				timer_set(GW_TASK_CLOUD_ID, GW_CLOUD_MQTT_TRY_CONNECT_REQ, GW_CLOUD_MQTT_TRY_CONNECT_TIMEOUT_INTERVAL, TIMER_ONE_SHOT);
			}
			else {
				timer_set(GW_TASK_CLOUD_ID, GW_CLOUD_MQTT_CHECK_CONNECT_STATUS_REQ, GW_CLOUD_MQTT_CHECK_CONNECT_STATUS_INTERVAL, TIMER_ONE_SHOT);
			}

			/* check mqtt connect fail */
			// if (networkStatus) {
			if (1) {
				// if (++mqttFailCnt > MQTT_FAIL_COUNT_MAX) {
				// 	APP_DBG_MQTT("set mqtt default server\n");
				// 	systemCmd("rm -f %s/%s", MTCE_USER_CONF_PATH, MTCE_NETWORK_MQTT_FILE);
				// 	mtce_configGetMQTT(&mqttService);
				// 	mqttFailCnt = 0;
				// }
			}
			else {
				APP_DBG_MQTT("network fail\n");
				mqttFailCnt = 0;
			}
			APP_DBG_MQTT("mqtt retry connect counter: %d\n", mqttFailCnt);
		} break;

		case GW_CLOUD_DATA_COMMUNICATION: {
			APP_DBG_SIG("GW_CLOUD_DATA_COMMUNICATION\n");
			uint8_t *data = (uint8_t *)msg->header->payload;
			int len		  = (int)msg->header->len;
			process_mqtt_msg(data, len);
		} break;

		case GW_CLOUD_MQTT_CHECK_SUB_TOPIC_REQ: {
			// APP_DBG_SIG("GW_CLOUD_MQTT_CHECK_SUB_TOPIC_REQ\n");
			if (mospp) {
				mospp->retrySubTopics();
			}
		} break;

		case GW_CLOUD_MQTT_CHECK_CONNECT_STATUS_REQ: {
			// APP_DBG_SIG("GW_CLOUD_MQTT_CHECK_CONNECT_STATUS_REQ\n");
			if (mospp) {
				if (!mospp->isConnected()) {
					task_post_pure_msg(GW_TASK_CLOUD_ID, GW_CLOUD_MQTT_TRY_CONNECT_REQ);
				}
				else {
					APP_DBG_MQTT("mqtt connect ok, reset retry counter\n");
					mqttFailCnt = 0;
				}
			}
		} break;
		
		case GW_CLOUD_WATCHDOG_PING_REQ: {
			// APP_DBG_SIG("GW_CLOUD_WATCHDOG_PING_REQ\n");
			task_post_pure_msg(GW_TASK_CLOUD_ID, GW_TASK_SYS_ID, GW_SYS_WATCH_DOG_PING_NEXT_TASK_RES);
		} break;

		default:
			break;
		}

		/* free message */
		ak_msg_free(msg);
	}

	return (void *)0;
}

void process_mqtt_msg(unsigned char *pload, int len) {
	APP_DBG_MQTT("HELLO FROM BROKER MQTT\n");
	try {
		// parse json string
		json recv_js = json::parse(string((const char *)pload, len));
		APP_DBG_MQTT("Message MQTT: \n %s \n", recv_js.dump(4).data());

		string method  = recv_js.contains("Method") ? recv_js["Method"] : "";
		string msgType = recv_js["MessageType"];
		json data	   = recv_js["Data"];

#ifdef RELEASE
		int msgTs	   = recv_js["Timestamp"];
		time_t rawtime = time(nullptr);
		int realtime   = stoi(to_string(rawtime));
		/* Parse local web command */
		if ((msgTs >= realtime && msgTs < realtime + 180) || (msgTs <= realtime && msgTs + 180 > realtime)) {
#endif
			if (!method.empty()) {
				if (msgType == MESSAGE_TYPE_UPGRADE) {
						// Post to task
						task_post_dynamic_msg(GW_TASK_FW_ID, GW_FW_GET_URL_REQ, (uint8_t *)data.dump().data(), data.dump().length() + 1);
				}
			}
#ifdef RELEASE
		}
#endif
	}
	catch (const exception &e) {
		(void)e;
		APP_DBG_MQTT("json::parse()\n");
		APP_DBG_MQTT("msg = %s\n", pload);
	}
	return;
}