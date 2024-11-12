#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/statvfs.h>
#include <fstream>

#include "ak.h"
#include "timer.h"
#include "app.h"
#include "app_dbg.h"
#include "app_data.h"
#include "task_list.h"
#include "cmd_line.h"

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
