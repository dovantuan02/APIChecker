#include "app.h"
#include "app_dbg.h"
#include "utils.h"
#include "fca_parameter.h"
#include "json.hpp"

#include "parser_json.h"

using namespace std;
using json = nlohmann::json;

bool fca_jsonGetNetMQTT(json &json_in, fca_netMQTT_t *param) {
	try {
		string serial = SERIAL;
		char clientId[80];
		snprintf(clientId, sizeof(clientId), "%s-%s", "ipc", serial.c_str());
		string str = json_in["Password"].get<string>();
		str == "" ? safe_strcpy(param->password, serial.c_str(), sizeof(param->password)) : safe_strcpy(param->password, str.data(), sizeof(param->password));
		str = json_in["Username"].get<string>();
		str == "" ? safe_strcpy(param->username, serial.c_str(), sizeof(param->username)) : safe_strcpy(param->username, str.data(), sizeof(param->username));
		str = json_in["ClientID"].get<string>();
		str == "" ? safe_strcpy(param->clientID, clientId, sizeof(param->clientID)) : safe_strcpy(param->clientID, str.data(), sizeof(param->clientID));
		safe_strcpy(param->host, json_in["Host"].get<string>().data(), sizeof(param->host));
		param->port		  = json_in["Port"].get<int>();
		param->bTLSEnable = json_in["TLSEnable"].get<bool>();
		safe_strcpy(param->TLSVersion, json_in["TLSVersion"].get<string>().data(), sizeof(param->TLSVersion));
		safe_strcpy(param->protocol, json_in["Protocol"].get<string>().data(), sizeof(param->protocol));
		param->bEnable	 = json_in["Enable"].get<bool>();
		param->keepAlive = json_in["KeepAlive"].get<int>();
		param->QOS		 = json_in["QOS"].get<int>();
		param->retain	 = json_in["Retain"].get<int>();
		return true;
	}
	catch (const exception &e) {
		APP_DBG("json error: %s\n", e.what());
	}
	return false;
}
