#include <arpa/inet.h>
#include <net/if.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include "ak.h"
#include "app.h"
#include "app_data.h"
#include "app_dbg.h"
#include "giec_api_net.h"
#include "task_list.h"
#include "timer.h"

q_msg_t gw_task_network_mailbox;

void *gw_task_network_entry(void *) {
    ak_msg_t *msg = AK_MSG_NULL;
    wait_all_tasks_started();
    APP_DBG_NET("[STARTED] gw_task_network_entry\n");

    while (1) {
        /* get messge */
        msg = ak_msg_rev(GW_TASK_NETWORK_ID);

        switch (msg->header->sig) {
            case GW_NET_WATCHDOG_PING_REQ: {
                task_post_pure_msg(GW_TASK_NETWORK_ID, GW_TASK_SYS_ID,
                                   GW_SYS_WATCH_DOG_PING_NEXT_TASK_RES);
            } break;

            case GW_NET_NETWORK_INIT_REQ: {
            } break;

            case GW_NET_NETWORK_WIFI_GET_MAC_REQ: {
                APP_DBG("GW_NET_NETWORK_WIFI_GET_MAC_REQ");
                char addr[32] = {0};
                fca_wifi_get_mac(addr, 17) == 0
                    ? APP_DBG("AP mode stop success !\n")
                    : APP_DBG("AP mode stop failed !\n");
                APP_DBG("%s\n", addr);
            } break;

            case GW_NET_NETWORK_WIFI_START_AP_MODE_REQ: {
                static bool state_ap = 0;
                if (state_ap == 1) {
                    state_ap = 0;
                    task_post_pure_msg(GW_TASK_NETWORK_ID,
                                       GW_NET_NETWORK_WIFI_STOP_AP_MODE_REQ);
                    timer_set(GW_TASK_NETWORK_ID,
                              GW_NET_NETWORK_WIFI_START_AP_MODE_REQ, 1000,
                              TIMER_ONE_SHOT);
                    break;
                }
                APP_DBG("GW_NET_NETWORK_WIFI_START_AP_MODE_REQ");
                string interface = "wlan0";
                string user = "tuan";
                string pass = "12345678";
                string ip = "192.168.5.5";
                fca_wifi_start_ap_mode(interface.data(), user.data(),
                                       pass.data(), ip.data()) == 0
                    ? APP_DBG("AP mode start success !\n")
                    : APP_DBG("AP mode start failed !\n");
                APP_DBG("IF [%s] - User [%s] - Pass [%s] - IP [%s]\n",
                        interface.c_str(), user.c_str(), pass.c_str(),
                        ip.c_str());
				state_ap = 1;
            } break;

            case GW_NET_NETWORK_WIFI_STOP_AP_MODE_REQ: {
                APP_DBG("GW_NET_NETWORK_WIFI_STOP_AP_MODE_REQ");
                fca_wifi_stop_ap_mode("wlan0") == 0
                    ? APP_DBG("AP mode stop success !\n")
                    : APP_DBG("AP mode stop failed !\n");
            } break;

            case GW_NET_NETWORK_WIFI_CONNECT_REQ: {
                fca_wifi_connect("wlan0", "IOT_LS_N", "ftelecomiot1")== 0
                    ? APP_DBG("Wifi connect to [IOT_LS_N] success !\n")
                    : APP_DBG("Wifi connect failed !\n");
            } break;

            case GW_NET_NETWORK_WIFI_DISCONN_REQ: {
				fca_wifi_disconnect("wlan0")== 0
                    ? APP_DBG("Wifi disconnect success !\n")
                    : APP_DBG("Wifi disconnect failed !\n");
            } break;

            case GW_NET_NETWORK_WIFI_DHCP_REQ: {
				fca_wifi_connect_dhcp("wlan0")== 0
                    ? APP_DBG("Wifi connect dhcp success !\n")
                    : APP_DBG("Wifi connect dhcp failed !\n");
            } break;

            case GW_NET_NETWORK_WIFI_STATIC_REQ: {
				static_ip_config_t wificonfig;
				string ip = string((char*)msg->header->payload, msg->header->len);
				APP_DBG("%s\n", ip.c_str());
				sprintf(wificonfig.ip_address, "%s", ip.data());
				strcpy(wificonfig.subnet_mask, "255.255.225.0");
				strcpy(wificonfig.gateway, "192.168.1.1");
				strcpy(wificonfig.dns1, "192.168.1.1");
				strcpy(wificonfig.dns2, "");
				fca_wifi_set_static_ip("wlan0",&wificonfig) == 0
					? APP_DBG("Set wlan0 static ip success\n")
					: APP_DBG("Set wlan0 static ip failed\n");
            } break;

            case GW_NET_NETWORK_WIFI_SCAN_REQ: {
				wifi_network_info_t wifiNetwork[20];
				fca_wifi_scan(wifiNetwork, 20);
				int index = 0;
				for (index = 0; index < 20; index++)
				{
					printf("index:%d ssid:%s signal_strength:%d encrypt_mode:%s mac_address:%s\r\n",
						index, wifiNetwork[index].ssid, wifiNetwork[index].signal_strength, wifiNetwork[index].encrypt_mode, wifiNetwork[index].mac_address);
				}
            } break;

            case GW_NET_NETWORK_WIFI_GET_CONN_REQ: {
				APP_DBG_SIG("GW_NET_NETWORK_WIFI_GET_CONN_REQ\n");
				bool flag;
				fca_wifi_get_status("wlan0", &flag) == 0 
					? APP_DBG("Get State success: %d\n", flag)
					: APP_DBG("Get State failed\n");

            } break;


			case GW_NET_NETWORK_ETH_GET_MAC_REQ: {
				APP_DBG_SIG("GW_NET_NETWORK_ETH_GET_MAC_REQ\n");
				char addr[32] = { 0 };
				fca_ethernet_get_mac(addr, sizeof(addr)) == 0 
				? APP_DBG("Mac: %s\n", addr)
				: APP_DBG("Get Mac failed\n");
			} break;

			case GW_NET_NETWORK_ETH_CONNECT_REQ: {
				APP_DBG_SIG("GW_NET_NETWORK_ETH_GET_MAC_REQ\n");
				fca_ethernet_init("eth0") == 0 
					? APP_DBG("Dhcp success\n")
					: APP_DBG("Dhcp failed\n");
			} break;

			case GW_NET_NETWORK_ETH_DISCONN_REQ: {
				fca_ethernet_disconnect("eth0") == 0 
					? APP_DBG("Dhcp success\n")
					: APP_DBG("Dhcp failed\n");
			} break;

			case GW_NET_NETWORK_ETH_DHCP_REQ: {
				fca_ethernet_connect_dhcp("eth0") == 0 
					? APP_DBG("Dhcp success\n")
					: APP_DBG("Dhcp failed\n");
			} break;

			case GW_NET_NETWORK_ETH_STATIC_REQ: {
				static_ip_config_t ethconfig;
				string ip = string((char*)msg->header->payload, msg->header->len);
				APP_DBG("%s\n", ip.c_str());
				sprintf(ethconfig.ip_address, "%s", ip.data());
				strcpy(ethconfig.subnet_mask, "255.255.225.0");
				strcpy(ethconfig.gateway, "192.168.1.1");
				strcpy(ethconfig.dns1, "192.168.1.1");
				strcpy(ethconfig.dns2, "");
				fca_ethernet_set_static_ip("eth0",&ethconfig) == 0
					? APP_DBG("Set eth0 static ip success\n")
					: APP_DBG("Set eth0 static ip failed\n");
			} break;

			case GW_NET_NETWORK_ETH_STATE_CAPLE_REQ: {
				switch (fca_check_cable("eth0")) {
					case FCA_NET_ETH_STATE_UNPLUG:
						APP_DBG("Cable unplug\n");
						break;
					case FCA_NET_ETH_STATE_PLUG:
						APP_DBG("Cable plugged\n");
						break;
					case FCA_NET_ETH_STATE_UNKNOWN:
					default:
						APP_DBG("Cable state unknown\n");
						break;
				}
			} break;

			
            default:
                break;
        }

        /* free message */
        ak_msg_free(msg);
    }
    return (void *)0;
}