#ifndef GIEC_API_NET_H
#define GIEC_API_NET_H

#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief cable status
 */
typedef enum {
	FCA_NET_ETH_STATE_UNPLUG,
	FCA_NET_ETH_STATE_PLUG,
	FCA_NET_ETH_STATE_UNKNOWN,
} FCA_NET_ETH_STATE_PORT_E;

/**
 * @brief Static IP config
 */
typedef struct {
	char ip_address[16];   //IP address
	char subnet_mask[16];  //subnet mask
	char gateway[16];      //gateway
	char dns1[16];			//DNS
	char dns2[16];			//DNS, can be left blank
}static_ip_config_t;

/**
 * @brief WIFI information
 */
typedef struct {
	char ssid[32];					//WIFI ssid
	char encrypt_mode[32];			//WIFI encrypt mode
	int signal_strength;			//WIFI signal strength in dBm
	unsigned char mac_address[18];	//WIFI mac address
}wifi_network_info_t;

/**
 * @brief get the Wi-Fi MAC address.
 * @param macaddr output, mac address, eg:D4:5D:64:DA:03:BC.
 * @param len input, length of mac address.
 * @note The value of 'len' must be 17.
 * @return 0 means success, other means failure.
 */
int fca_wifi_get_mac(char *macaddr, int len);

/**
 * @brief sets up the device to act as an AP with the specified SSID,password,IP.
 * @param ifname input, network interface name. eg:"wlan0".
 * @param ssid input, SSID for the Wi-Fi Access Point. eg:"fca".
 * @param passwd input, passwd for the Wi-Fi Access Point. eg:"12345678".
 * @param ip input, ip address for the Wi-Fi Access Point. eg:"192.168.175.4".
 * @return 0 means success, other means failure.
 */
int fca_wifi_start_ap_mode(const char *ifname, const char *ssid, const char *passwd, const char *ip);

/**
 * @brief stop the Wi-Fi Access Point (AP) mode.
 * @param ifname input, network interface name. eg:"wlan0".
 * @return 0 means success, other means failure.
 */
int fca_wifi_stop_ap_mode(const char *ifname);

/**
 * @brief connect wifi with interface name.
 * @param ifname input, network interface name. eg:"wlan0".
 * @param ssid input, wifi ssid. eg:"fca".
 * @param passwd input, wifi password. eg:"12345678".
 * @return 0 means success, other means failure.
 */
int fca_wifi_connect(const char *ifname, const char *ssid, const char *passwd);

/**
 * @brief get wifi connection status to router.
 * @param ifname input, network interface name. eg:"wlan0".
 * @param isConnected output, true:Connected, false: not Connected.
 * @return 0 means success, other means failure.
 */
int fca_wifi_get_status(const char *ifname, bool *isConnected);

/**
 * @brief DHCP wifi connection.
 * @param ifname input, network interface name. eg:"wlan0".
 * @return 0 means success, other means failure.
 */
int fca_wifi_connect_dhcp(const char *ifname);

/**
 * @brief Disconnect wifi.
 * @param ifname input, network interface name. eg:"wlan0".
 * @return 0 means success, other means failure.
 */
int fca_wifi_disconnect(const char *ifname);

/**
 * @brief get the Etherent MAC address.
 * @param macaddr output, mac address, eg:D4:5D:64:DA:03:BC.
 * @param len input, length of mac address.
 * @note The value of 'len' must be 17.
 * @return 0 means success, other means failure.
 */
int fca_ethernet_get_mac(char *macaddr, int len);

/**
 * @brief Initializations for ethernet.
 * @param ifname input, network interface name. eg:"eth0".
 * @return 0 means success, other means failure.
 */
int fca_ethernet_init(const char *ifname);

/**
 * @brief DHCP Ethernet connection.
 * @param ifname input, network interface name. eg:"eth0".
 * @return 0 means success, other means failure.
 */
int fca_ethernet_connect_dhcp(const char *ifname);

/**
 * @brief Check LAN port status.
 * @param ifname input, network interface name. eg:"eth0".
 * @return refer to @ref FCA_NET_ETH_STATE_PORT_E.
 */
FCA_NET_ETH_STATE_PORT_E fca_check_cable(const char *ifname);

/**
 * @brief Disconnect Ethernet.
 * @param ifname input, network interface name. eg:"eth0".
 * @return 0 means success, other means failure.
 */
int fca_ethernet_disconnect(const char *ifname);

/**
 * @brief Set static IP for WIFI.
 * @param ifname input, network interface name. eg:"wlan0".
 * @param config input, static IP config refer to @ref StaticIPConfig. 
 * @note eg:
 *			static_ip_config_t wificonfig;
 *			strcpy(wificonfig.ip_address, "192.168.30.101");
 *			strcpy(wificonfig.subnet_mask, "255.255.224.0");
 *			strcpy(wificonfig.gateway, "192.168.30.1");
 *			strcpy(wificonfig.dns1, "192.168.175.1");
 *			strcpy(wificonfig.dns2, "");
 *			fca_ethernet_set_static_ip("eth0",&wificonfig);
 * 
 * @return 0 means success, other means failure.
 */
int fca_wifi_set_static_ip(const char *ifname, const static_ip_config_t *config);

/**
 * @brief Set static IP for Ethernet.
 * @param ifname input, network interface name. eg:"eth0".
 * @param config input, static IP config refer to @ref StaticIPConfig.
 * @note eg:
 *			static_ip_config_t ethconfig;
 *			strcpy(ethconfig.ip_address, "192.168.30.101");
 *			strcpy(ethconfig.subnet_mask, "255.255.224.0");
 *			strcpy(ethconfig.gateway, "192.168.100.1");
 *			strcpy(ethconfig.dns1, "192.168.175.1");
 *			strcpy(ethconfig.dns2, "");
 *			fca_ethernet_set_static_ip("eth0",&ethconfig);
 * 
 * @return 0 means success, other means failure.
 */
int fca_ethernet_set_static_ip(const char *ifname, const static_ip_config_t *config);

/**
 * @brief Start scanning for available Wi-Fi Access Points(APs).
 * @param networks output, WIFI info array refer to @ref wifi_network_info_t.
 * @param networks_len input, WIFI info array length.
 * @note eg:
 *			wifi_network_info_t wifiNetwork[20];
 *			fca_wifi_scan(wifiNetwork, 20);
 *			for (int index = 0; index < 20; index++) {
 *				printf("index:%d ssid:%s signal_strength:%d encrypt_mode:%s mac_address:%s\r\n",
 *					index, wifiNetwork[index].ssid, wifiNetwork[index].signal_strength, 
 *					wifiNetwork[index].encrypt_mode, wifiNetwork[index].mac_address);
 *			}
 * 
 * @return 0 means success, other means failure.
 */
int fca_wifi_scan(wifi_network_info_t *networks, int networks_len);

#ifdef __cplusplus
}
#endif

#endif