#ifndef _parser_json_h_
#define _parser_json_h_

#include "fca_parameter.h"
#include "json.hpp"

using json = nlohmann::json;

extern bool fca_jsonGetNetMQTT(json &json_in, fca_netMQTT_t *param);

#endif