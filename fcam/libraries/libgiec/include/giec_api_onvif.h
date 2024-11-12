#ifndef GIEC_API_ONVIF_H
#define GIEC_API_ONVIF_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief ONVIF主视频流分辨率的宽度\n
 * The width of the main video stream resolution of ONVIF.\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const unsigned int G_ONVIF_VIDEO_RES_W_MAIN;

/**
 * @brief ONVIF主视频流分辨率的高度\n
 * The height of the main video stream resolution of ONVIF.\n
 * @ note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const unsigned int G_ONVIF_VIDEO_RES_H_MAIN;

/**
 * @brief ONVIF子视频流分辨率的宽度\n
 * The width of the sub video stream resolution of ONVIF.\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const unsigned int G_ONVIF_VIDEO_RES_W_SUB;

/**
 * @brief ONVIF子视频流分辨率的高度\n
 * The height of the sub video stream resolution of ONVIF.\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const unsigned int G_ONVIF_VIDEO_RES_H_SUB;

/**
 * @brief ONVIF主视频流帧率\n
 * The frame rate of the main video stream of ONVIF.\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const unsigned int G_ONVIF_VIDEO_FPS_MAIN;

/**
 * @brief ONVIF子视频流帧率\n
 * The frame rate of the sub video stream of ONVIF.\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const unsigned int G_ONVIF_VIDEO_FPS_SUB;

/**
 * @brief ONVIF主视频流码率\n
 * The bitrate of the main video stream of ONVIF.\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const unsigned int G_ONVIF_VIDEO_BITRATE_MAIN;

/**
 * @brief ONVIF子视频流码率\n
 * The bitrate of the sub video stream of ONVIF.\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const unsigned int G_ONVIF_VIDEO_BITRATE_SUB;

/**
 * @brief ONVIF主视频流质量\n
 * The quality of the main video stream of ONVIF.\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请不要修改\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file. Do not modify this variable.
 */
extern const unsigned int G_ONVIF_VIDEO_QUALITY_MAIN;

/**
 * @brief ONVIF子视频流质量\n
 * The quality of the sub video stream of ONVIF.\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请不要修改\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file. Do not modify this variable.
 */
extern const unsigned int G_ONVIF_VIDEO_QUALITY_SUB;

/**
 * @brief ONVIF主视频流编码类型\n
 * The encoding type of the main video stream of ONVIF.\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值. 0:H.264, 1:JPEG, 2:H.265\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file. 0:H.264, 1:JPEG, 2:H.265.
 */
extern const unsigned int G_ONVIF_VIDEO_ENC_TYPE_MAIN;

/**
 * @brief ONVIF子视频流编码类型\n
 * The encoding type of the sub video stream of ONVIF.\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值. 0:H.264, 1:JPEG, 2:H.265\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file. 0:H.264, 1:JPEG, 2:H.265.
 */
extern const unsigned int G_ONVIF_VIDEO_ENC_TYPE_SUB;

/**
 * @brief ONVIF音频流采样率\n
 * The sample rate of the audio stream of ONVIF.\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值。\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const unsigned int G_ONVIF_AUDIO_SAMPLE_RATE;

/**
 * @brief ONVIF网络配置文件的路径\n
 * ONVIF network configuration file path.\n
 * @note 该变量被库使用，可在giec_param.c中配置，必须为可读写的路径\n
 * This variable is used by the library and can be configured in the giec_param.c file. It must be a readable and writable path.
 */
extern const char* G_ONVIF_CONFIG_FILE_NET;

/**
 * @brief ONVIF画质配置文件的路径\n
 * ONVIF video color configuration file path.\n
 * @note 该变量被库使用，可在giec_param.c中配置，必须为可读写的路径\n
 * This variable is used by the library and can be configured in the giec_param.c file. It must be a readable and writable path.
 */
extern const char* G_ONVIF_CONFIG_FILE_VCOLOR;

/**
 * @brief ONVIF视频参数配置文件的路径\n
 * ONVIF video configuration file path.\n
 * @note 该变量被库使用，可在giec_param.c中配置，必须为可读写的路径\n
 * This variable is used by the library and can be configured in the giec_param.c file. It must be a readable and writable path.
 */
extern const char* G_ONVIF_CONFIG_FILE_VIDEO;

/**
 * @brief 函数 @ref giec_onvif_init 的参数的类型\n
 * Parameter type of function @ref giec_onvif_init\n
 * @note password onvif密码，建议包含且仅包含大写字母、小写字母和数字，不支持特殊字符。最长64个字符\n
 * Password onvif, it is recommended to contain only uppercase letters, lowercase letters and numbers, and does not support special characters. The maximum length is 64 characters.
 */
typedef struct GIEC_ONVIF_INIT_PARAM_S {
    char password[65];
} GIEC_ONVIF_INIT_PARAM;

/**
 * @brief 初始化ONVIF功能\n
 * Initialize ONVIF function.
 * @param onvif_param 输入，ONVIF初始化参数，一个 @ref GIEC_ONVIF_INIT_PARAM 类型变量的指针\n
 * Input, ONVIF initialization parameter, a pointer to a @ref GIEC_ONVIF_INIT_PARAM type variable.
 * @note 该函数必须在所有涉及ONVIF的功能初始化之前调用，只可调用一次。\n
 * Must be called before all functions that involve ONVIF are initialized, can only be called once.
 * @note 如果长度为0或者超过64，则会自动设置为"admin"。\n
 * If the length is 0 or exceeds 64, it will be automatically set to "admin".
 * @return 0表示成功，其他表示失败\n
 * Return 0 for success, other for failure.
 */
int giec_onvif_init(GIEC_ONVIF_INIT_PARAM* onvif_param);

/**
 * @brief 释放ONVIF资源\n
 * Release ONVIF resources.
 * @note 该函数必须在所有涉及ONVIF的功能释放之后调用，只可调用一次。\n
 * Must be called after all functions that involve ONVIF are released, can only be called once.
 * @return 0表示成功，其他表示失败\n
 * Return 0 for success, other for failure.
 */
int giec_onvif_uninit();

/**
 * @brief 设置ONVIF密码\n 
 * Set ONVIF password.
 * @param password 输入，密码字符串\n
 * Input, password string.
 * @note 建议包含且仅包含大写字母、小写字母和数字，不支持特殊字符。最长64字符\n
 * It is recommended to contain only uppercase letters, lowercase letters and numbers, and does not support special characters. The maximum length is 64 characters.
 * @note 如果长度为0或者超过64字符，则会自动设置为"admin"。\n
 * If the length is 0 or exceeds 64, it will be automatically set to "admin".
 * @return 0表示成功，其他表示失败。\n
 * Return 0 for success, other for failure.
 */
int giec_onvif_set_password(const char* password);

/**
 * @brief 获取ONVIF模块记录的密码\n 
 * Get the password saved in the ONVIF module.
 * @param password 输出，密码字符串指针，用于接收密码字符串，需要提前分配长度为64的空间，不能为空指针。\n
 * Output, password string pointer, used to receive the password string, needs to be pre-allocated, cannot be a null pointer.
 * @return 0表示成功，其他表示失败。\n
 * Return 0 for success, other for failure.
 */
int giec_onvif_get_password(char* password);

/**
 * @brief 通知ONVIF模块有移动告警事件产生\n
 * Notify the ONVIF module of a moving alarm event.
 * @param type 输入，告警类型，当前版本未实现，可填任意值。\n
 * Input, alarm type, not implemented in the current version, can fill any value.
 * @return 0表示成功，其他表示失败。\n
 * Return 0 for success, other for failure.
 */
int giec_onvif_notify_motion(int type);


/**
 * @brief ONVIF预置点最大数量\n
 * The maximum number of ONVIF preset points.\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const unsigned int G_ONVIF_PRESET_MAX_NUM;
/**
 * @brief ONVIF保存预点的文件路径\n
 * The file path to save the ONVIF preset points.\n
 * @note 该变量被库使用，可在giec_param.c中配置，必须为可读写的路径\n
 * This variable is used by the library and can be configured in the giec_param.c file. It must be a readable and writable path.
 */
extern const char* G_ONVIF_CONFIG_FILE_PRESET;

#ifdef __cplusplus
}
#endif

#endif /* GIEC_API_ONVIF_H */