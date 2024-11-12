#ifndef GIEC_API_MD_H
#define GIEC_API_MD_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 移动侦测高灵敏度的阈值\n
 * High sensitivity threshold for motion detection
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library, and is configured to the actual value in the giec_param.c file.
 */
extern const int GIEC_MD_SEN_H;

/**
 * @brief 移动侦测中灵敏度的阈值\n
 * Medium sensitivity threshold for motion detection
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library, and is configured to the actual value in the giec_param.c file.
 */
extern const int GIEC_MD_SEN_M;

/**
 * @brief 移动侦测低灵敏度的阈值\n
 * Low sensitivity threshold for motion detection
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library, and is configured to the actual value in the giec_param.c file.
 */
extern const int GIEC_MD_SEN_L;

/**
 * @brief 函数 @ref giec_md_init 的参数的类型\n
 * Parameter type of the function @ref giec_md_init used to initialize the motion detection function
 * @note giec_md_result_cb: 函数指针，库内部会频繁调用该函数通知移动侦测结果，传入的参数0表示此刻没有检测到移动，1表示此刻检测到移动\n
 * giec_md_result_cb： function pointer, the library will frequently call this function to notify the motion detection result, 
 * the input parameter 0 means that no motion is detected at this time, and 1 means that motion is detected at this time.
 */
typedef struct GIEC_MD_CB_PARAM_S {
    int (*giec_md_result_cb)(int status);
} GIEC_MD_CB_PARAM;

/**
 * @brief 初始化移动侦测功能\n
 * Initialize the motion detection function
 * @param md_param 输入，移动侦测功能初始化参数，一个 @ref GIEC_MD_CB_PARAM 类型变量的指针\n
 * Input, initialization parameters for the motion detection function, a pointer to a @ref GIEC_MD_CB_PARAM type variable
 * @note 必须在video/audio初始化之后调用，在移动侦测相关的API调用前调用，只可调用一次\n
 * Must be called after video/audio initialization, and must be called before the motion detection-related API is called. Can only be called once.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_md_init(GIEC_MD_CB_PARAM* md_param);

/**
 * @brief 反初始化移动侦测功能，在关闭所有侦测功能之后调用。\n
 * Uninitialize the motion detection function, which should be called after all detection functions are closed.
 * @note 一般不需要调用此函数。如果需要处理比如OTA升级前回收内存等场景,请进一步沟通如何调用此函数.\n
 * Note that this function is generally not needed. If you need to reclaim memory for example before OTA upgrade, please further discuss how to call this function.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_md_uninit_block(void);

/**
 * @brief 设置移动侦测灵敏度\n
 * Set the sensitivity of the motion detection function.
 * @param sen_level 输入，灵敏度级别，0: 低灵敏度，1： 中灵敏度，2：高灵敏度\n
 * Input, sensitivity level, 0: low sensitivity, 1: medium sensitivity, 2: high sensitivity.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_md_set_sensitivity(int sen_level);

/**
 * @brief 使能/关闭移动侦测\n
 * Enable/disable the motion detection function.
 * @param onoff 输入，0：关闭， 1：使能
 * Input, 0: disable, 1: enable.
 * @return 0表示成功，其他表示失败
 * return 0 means success, other means failure.
 */
int giec_md_set_onoff(int onoff);

#ifdef __cplusplus
}
#endif

#endif // GIEC_API_MD_H
