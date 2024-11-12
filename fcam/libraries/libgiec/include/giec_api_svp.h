#ifndef GIEC_API_SVP_H
#define GIEC_API_SVP_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Anyka SVP param文件路径\n
 * Path of Anyka SVP param file.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, and is configured to the actual value in the giec_param.c file, do not modify it.
 */
extern const char* G_SVP_FILE_PATH;

/**
 * @brief Anyka SVP 通道号\n
 * Anyka SVP channel number
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, and is configured to the actual value in the giec_param.c file, do not modify it.
 */
extern const int G_SVP_CHN_NUM;

/**
 * @brief Anyka SVP 帧率\n
 * Anyka SVP FPS
 * @note 该变量被库使用，必须与sensor的FPS匹配，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, and must match the FPS of the sensor, and is configured to the actual value in the giec_param.c file, do not modify it.
 */
extern const int G_SVP_CHN_FPS;

/**
 * @brief Anyka SVP AK_SVP_MODEL_E 配置\n
 * Anyka SVP AK_SVP_MODEL_E configuration
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, and is configured to the actual value in the giec_param.c file, do not modify it.
 */
extern const int GIEC_SVP_HP;

/**
 * @brief Anyka SVP AK_SVP_TARGET_TYPE_E 配置\n
 * Anyka SVP AK_SVP_TARGET_TYPE_E configuration
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, and is configured to the actual value in the giec_param.c file, do not modify it.
 */
extern const int GIEC_SVP_TYPE;

/**
 * @brief Anyka SVP AK_SVP_THRESHOLD_S classsify threshold 配置\n
 * Anyka SVP AK_SVP_THRESHOLD_S classsify threshold configuration
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, and is configured to the actual value in the giec_param.c file, do not modify it.
 */
extern const int GIEC_SVP_CLASSIFY_THRESHOLD;

/**
 * @brief Anyka SVP AK_SVP_THRESHOLD_S IoU threshold 配置\n
 * Anyka SVP AK_SVP_THRESHOLD_S IoU threshold configuration
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, and is configured to the actual value in the giec_param.c file, do not modify it.
 */
extern const int GIEC_SVP_IOU_THRESHOLD;

/**
 * @brief 函数 @ref giec_svp_init 的参数的类型\n
 * Parameter type of the function @ref giec_svp_init
 * @note giec_humfil_result_cb: 函数指针，库内部会频繁调用该函数通知人形检测结果，传入的参数0表示此刻没有检测到人，1表示此刻检测到人\n
 * giec_alarmzone_result_cb: 函数指针，库内部会频繁调用该函数通知区域侦测结果，传入的参数0表示此刻区域中没有变动，1表示此刻区域中发生变动\n
 * giec_get_live_quality_cb: 函数指针，库内部会频繁调用该函数获取当前预览流是标清0还是高清1\n
 * giec_alarmzone_result_cb: function pointer, the library will frequently call this function to notify the area detection result, 
 * the parameter 0 means that no change is detected in the area at this time, and 1 means that a change is detected in the area at this time.\n
 * giec_humfil_result_cb: function pointer, the library will frequently call this function to notify the human detection result, 
 * the parameter 0 means that no human is detected at this time, and 1 means that a human is detected at this time.\n
 * giec_get_live_quality_cb: function pointer, the library will frequently call this function to get the current preview stream is SD 0 or HD 1.
 */
typedef struct GIEC_SVP_CB_PARAM_S {
    int (*giec_humfil_result_cb)(int status);
    int (*giec_alarmzone_result_cb)(int status);
    int (*giec_get_live_quality_cb)(void);
} GIEC_SVP_CB_PARAM;

/**
 * @brief 初始化SVP功能\n
 * Initialize SVP function\n
 * @param md_param 输入，SVP功能初始化参数，一个 @ref GIEC_SVP_CB_PARAM 类型变量的指针\n
 * input, SVP function initialization parameter, a pointer to a @ref GIEC_SVP_CB_PARAM type variable.
 * @note 必须在video/audio初始化之后调用，在SVP相关的API调用前调用，只可调用一次\n
 * Must be called after video/audio initialization, before calling the SVP-related API, can only be called once.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_svp_init(GIEC_SVP_CB_PARAM* svp_param);

/**
 * @brief 反初始化SVP功能，在关闭所有SVP功能之后调用。\n
 * Uninitialize SVP function, call it after closing all SVP functions.
 * @note 当前版本未实现。\n
 * Current version does not implement.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_svp_uninit_block(void);

/**
 * @brief 人形过滤开关\n
 * Turn on or off human filtering.
 * @param onoff 输入， 1：使能，0：关闭\n
 * input, 1: enable, 0: disable.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_svp_humfil_set_onoff(int onoff);

/**
 * @brief 人形追焦开关\n
 * Turn on or off human focus.
 * @param onoff 输入， 1：使能，0：关闭\n
 * input, 1: enable, 0: disable.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_svp_humfocus_set_onoff(int onoff);

/**
 * @brief 区域侦测开关\n
 * Turn on or off alarmzone detection.
 * @param onoff 输入， 1：使能，0：关闭\n
 * input, 1: enable, 0: disable.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_svp_alarmzone_set_onoff(int onoff);

/**
 * @brief 设置区域侦测区域\n
 * Set the alarmzone detection area.
 * @param index 输入，区域索引，0表示第一个区域，当前只支持1个矩形区域\n
 * input, region index, 0 represents the first region, currently only one rectangular region is supported.
 * @param x 输入，区域左上角x坐标，范围 0 ~ @ref G_PTZ_MAX_POS_H\n
 * input, the x coordinate of the upper left corner of the region, ranging from 0 to @ref G_PTZ_MAX_POS_H.
 * @param y 输入，区域左上角y坐标，范围 0 ~ @ref G_PTZ_MAX_POS_V\n
 * input, the y coordinate of the upper left corner of the region, ranging from 0 to @ref G_PTZ_MAX_POS_V.
 * @param w 输入，区域宽度，范围 0 ~ @ref G_PTZ_MAX_POS_H ，且 x + w 不超过 @ref G_PTZ_MAX_POS_H\n
 * input, the width of the region, ranging from 0 to @ref G_PTZ_MAX_POS_H, and x + w does not exceed @ref G_PTZ_MAX_POS_H.
 * @param h 输入，区域高度，范围 0 ~ @ref G_PTZ_MAX_POS_V ，且 y + h 不超过 @ref G_PTZ_MAX_POS_V\n
 * input, the height of the region, ranging from 0 to @ref G_PTZ_MAX_POS_V, and y + h does not exceed @ref G_PTZ_MAX_POS_V.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_svp_alarmzone_set_area(int index, int x, int y, int w, int h);

#ifdef __cplusplus
}
#endif

#endif // GIEC_API_SVP_H
