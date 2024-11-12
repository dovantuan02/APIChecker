#ifndef GIEC_API_NETWORK_H
#define GIEC_API_NETWORK_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Wi-Fi状态，同tuya WF_STATION_STAT_E\n
 * Wi-Fi station status, same as tuya WF_STATION_STAT_E
 */
typedef enum {
    G_WSS_IDLE = 0,                       ///< not connected
    G_WSS_CONNECTING,                     ///< connecting wifi
    G_WSS_PASSWD_WRONG,                   ///< passwd not match
    G_WSS_NO_AP_FOUND,                    ///< ap is not found
    G_WSS_CONN_FAIL,                      ///< connect fail
    G_WSS_CONN_SUCCESS,                   ///< connect wifi success
    G_WSS_GOT_IP,                         ///< get ip success
} G_WF_STATION_STAT_E;

/**
 * @brief 函数 @ref giec_network_set_callback 的参数的类型\n
 * Parameter type of function @ref giec_network_set_callback
 * @note get_wf_status: 函数指针。库内部会频繁调用该函数，根据返回值获取wifi状态，不能为NULL。\n
 * get_online: 函数指针。库内部会频繁调用该函数，根据返回值获取设备在线状态，不能为NULL。\n
 * get_wf_status: Function pointer. The library will frequently call this function to get the wifi status, which cannot be NULL. \n
 * get_online: Function pointer. The library will frequently call this function to get the device online status, which cannot be NULL.
 */
typedef struct G_NETWORK_CB_PARAM_S {
    G_WF_STATION_STAT_E* (*get_wf_status)(void);
    int (*get_online)(void);
} G_NETWORK_CB_PARAM;

/**
 * @brief 设置网络相关的回调函数，给库内部调用\n
 * Set callback function related to network, for library internal use
 * @note 需要在使能LED功能之前调用\n
 * Need to be called before init LED function
 * @param cb_param 输入，网络功能初始化参数，一个 @ref G_NETWORK_CB_PARAM 类型变量的指针\n
 * Input, initialization parameters of network function, a pointer to a @ref G_NETWORK_CB_PARAM type variable
 * @return 0表示成功, 其他表示失败\n
 * return 0 means success, other means failure
 */
int giec_network_set_callback(G_NETWORK_CB_PARAM *cb_param);

#ifdef __cplusplus
}
#endif

#endif /* GIEC_API_NETWORK_H */