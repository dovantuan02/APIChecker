#ifndef _fca_parameter_h_
#define _fca_parameter_h_

#define FCA_NAME_LEN		   (64)
#define FCA_NAME_PASSWORD_LEN (1024)
#define FCA_CLIENT_ID_LEN	   (64)

typedef struct {
	int bEnable; /* 1: Enable; 0: Disable */
	int bTLSEnable;
	char clientID[FCA_CLIENT_ID_LEN];
	char username[FCA_NAME_LEN];
	char password[FCA_NAME_PASSWORD_LEN];
	char host[FCA_NAME_LEN];
	char TLSVersion[8];
	int keepAlive;
	int QOS;
	int retain;
	int port;
	char protocol[16];	  // IPCP_MQTT_PROTOCOL_TYPE_E
} fca_netMQTT_t;

typedef struct {
	char topicStatus[128];
	char topicRequest[128];
	char topicResponse[128];
} mqttTopicCfg_t;

#endif