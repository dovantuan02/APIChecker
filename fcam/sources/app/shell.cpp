#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/statvfs.h>
#include <unistd.h>

#include <fstream>

#include "ak.h"
#include "app.h"
#include "app_data.h"
#include "app_dbg.h"
#include "cmd_line.h"
#include "task_list.h"
#include "timer.h"

static int32_t shell_ver(uint8_t *argv);
static int32_t shell_help(uint8_t *argv);
static int32_t shell_get(uint8_t *argv);
static int32_t shell_set(uint8_t *argv);

cmd_line_t lgn_cmd_table[] = {
	{(const int8_t *)"ver",	shell_ver,	   (const int8_t *)"get kernel version"},
	{(const int8_t *)"help", shell_help,	 (const int8_t *)"help command info" },
	{(const int8_t *)"get",	shell_get,	   (const int8_t *)"get info"			 },
	{(const int8_t *)"set",	shell_set,	   (const int8_t *)"set config"		   },

	/* End Of Table */
	{(const int8_t *)0,		(pf_cmd_func)0, (const int8_t *)0					 }
};

int32_t shell_ver(uint8_t *argv) {
	(void)argv;
	APP_PRINT("version: %s\n", AK_VERSION);

	return 0;
}

int32_t shell_help(uint8_t *argv) {
	uint32_t idx = 0;
	switch (*(argv + 4)) {
	default:
		APP_PRINT("\nCOMMANDS INFORMATION:\n\n");
		while (lgn_cmd_table[idx].cmd != (const int8_t *)0) {
			APP_PRINT("%s\n\t%s\n\n", lgn_cmd_table[idx].cmd, lgn_cmd_table[idx].info);
			idx++;
		}
		break;
	}
	return 0;
}

int32_t shell_get(uint8_t *argv) {
	uint8_t len = cmd_str_parser((char *)argv, ' ');
	if (len == 2) {
		string cmd1 = (char *)cmd_str_parser_get_attr(1);
	}
	else if (len == 3) {
		// vvtk_get_light_sensor_raw
		string cmd1 = (char *)cmd_str_parser_get_attr(1);
	}
	else {
		APP_PRINT("please dbg --help\n");
	}
	return 0;
}

int32_t shell_set(uint8_t *argv) {
	uint8_t len = cmd_str_parser((char *)argv, ' ');
	if (len == 2) {
		string cmd1 = (char *)cmd_str_parser_get_attr(1);
		if (cmd1 == "li") {
			task_post_pure_msg(GW_TASK_GPIO_ID, GW_GPIO_LIGHTNING_WHITE_REQ);
		}
		else if (cmd1 == "ir") {
			task_post_pure_msg(GW_TASK_GPIO_ID, GW_GPIO_LIGHTNING_IR_REQ);
		}
		else if (cmd1 == "wifi")  {
			task_post_pure_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_WIFI_GET_CONN_REQ);
		}
	}
	else if (len == 3) {
		// vvtk_get_light_sensor_raw
		string cmd1 = (char *)cmd_str_parser_get_attr(1);
		if (cmd1 == "le") {
			string cmd2 = (char *)cmd_str_parser_get_attr(2);
			if (cmd2 == "w") {
				task_post_pure_msg(GW_TASK_GPIO_ID, GW_GPIO_LED_WHITE_REQ);
			}
			else if (cmd2 == "y") {
				task_post_pure_msg(GW_TASK_GPIO_ID, GW_GPIO_LED_YELLOW_REQ);
			}
			else {
				APP_PRINT("please dbg --help\n");
			}
		}
		else if (cmd1 == "wifi") {
			string cmd2 = (char *)cmd_str_parser_get_attr(2);
			if (cmd2 == "ap") {
				task_post_pure_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_WIFI_START_AP_MODE_REQ);
			}
			else if (cmd2 == "staconn") {
				task_post_pure_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_WIFI_CONNECT_REQ);
			}
			else if (cmd2 == "stadisc") {
				task_post_pure_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_WIFI_DISCONN_REQ);
			}
			else if (cmd2 == "stadhcp") {
				task_post_pure_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_WIFI_DHCP_REQ);
			}
			else if (cmd2 == "scan") {
				task_post_pure_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_WIFI_SCAN_REQ);
			}
			else if (cmd2 == "mac") {
				task_post_pure_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_WIFI_GET_MAC_REQ);
			}
		}
		else if (cmd1 == "eth") {
			string cmd2 = (char *)cmd_str_parser_get_attr(2);
			if (cmd2 == "conn") {
				task_post_pure_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_ETH_CONNECT_REQ);
			}
			else if (cmd2 == "disc") {
				task_post_pure_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_ETH_DISCONN_REQ);
			}
			else if (cmd2 == "dhcp") {
				task_post_pure_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_WIFI_DHCP_REQ);
			}
			else if (cmd2 == "caple") {
				task_post_pure_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_ETH_STATE_CAPLE_REQ);
			}
			else if (cmd2 == "mac") {
				task_post_pure_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_ETH_GET_MAC_REQ);
			}
		}
	}
	else if (len == 4) {
		string cmd1 = (char *)cmd_str_parser_get_attr(1);
		if (cmd1 == "le") {
			string cmd2 = (char *)cmd_str_parser_get_attr(2);
			string cmd3 = (char *)cmd_str_parser_get_attr(3);
			if (cmd2 == "w") {
				task_post_dynamic_msg(GW_TASK_GPIO_ID, GW_GPIO_LED_WHITE_BLINK_REQ, (uint8_t *)cmd3.data(), cmd3.length());
			}
			else if (cmd2 == "y") {
				task_post_dynamic_msg(GW_TASK_GPIO_ID, GW_GPIO_LED_YELLOW_BLINK_REQ, (uint8_t *)cmd3.data(), cmd3.length());
			}
			else if (cmd2 == "m") {
				task_post_dynamic_msg(GW_TASK_GPIO_ID, GW_GPIO_LED_MAX_BLINK_REQ, (uint8_t *)cmd3.data(), cmd3.length());
			}
			else {
				APP_PRINT("please dbg --help\n");
			}
		}
		else if (cmd1 == "wifi") {
			string cmd2 = (char *)cmd_str_parser_get_attr(2);
			string cmd3 = (char *)cmd_str_parser_get_attr(3);
			if (cmd2 == "sta") {
				task_post_dynamic_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_WIFI_STATIC_REQ, (uint8_t*) cmd3.data(), cmd3.length());
			}
		}
		else if (cmd1 == "eth") {
			string cmd2 = (char *)cmd_str_parser_get_attr(2);
			string cmd3 = (char *)cmd_str_parser_get_attr(3);
			if (cmd2 == "sta") {
				task_post_dynamic_msg(GW_TASK_NETWORK_ID, GW_NET_NETWORK_ETH_STATIC_REQ, (uint8_t*) cmd3.data(), cmd3.length());
			}
		}
	}
	else {
		APP_PRINT("please dbg --help\n");
	}
	return 0;
}
