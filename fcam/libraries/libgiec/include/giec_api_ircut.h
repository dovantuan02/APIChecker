#ifndef GIEC_API_IRCUT_H
#define GIEC_API_IRCUT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 配置SD卡的路径\n
 * Configure the path of the SD card.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const char * G_SD_PATH;

/**
 * @brief 当前图像处于白视还是夜视的枚举类型\n
 * enum type of currnt image in white or night vision.
 */
typedef enum {
	FCA_DAY_STATE = 0,
	FCA_NIGHT_STATE,
} FCA_DAY_NIGHT_STATE_E;

/**
 * @brief 由应用下发的软光敏控制模式\n
 * Soft photosensitive control mode issued by the application.
 */
typedef enum {
        FCA_DN_MODE_AUTO,  // Auto mode
        FCA_DN_MODE_DAY,   // Day mode
        FCA_DN_MODE_NIGHT  // Night mode
} FCA_DN_MODE_E;

/**
 * @brief 白视夜视状态切换的回调函数句柄\n
 * The callback function handle for day or night vision state switch.
 * @param
 * state: 输出切换后状态\n
 * Output the state after switch
 * user_date: 调用者传递进来的指针参数\n
 * Pointer parameter passed in by the caller
 */
typedef void (*FCA_DAYNIGHT_CALLBACK)(FCA_DAY_NIGHT_STATE_E state, const void *user_data);

/**
 * @brief 软光敏参数结构体\n
 * Soft photosensitivity parameter structure body
 * @note
 * u32lock_time:在1分钟内反复切换黑白夜视多次后的锁定时间。【单位：分钟; 范围：≥0, 0：表示不锁定状态】。\n
 * Lock time after repeatedly switching between black and day night vision for several times within 1 minute.\n
 * [unit: minute; range:≥0, 0: indicates an unlocked status]\n
 * 
 * u32trigger_interval:检查是否需要切换模式的时间间隔。【单位：毫秒; 范围：>0】。\n
 * Check whether the time interval to switch the mode is required. [unit: minute; range:>0]\n
 * 
 * u32trigger_times:反复切换昼夜模式的连续次数。【单位：次数; 范围：>0】\n
 * The number of consecutive times day/night mode is repeatedly switched. [unit: times; range:>0]\n
 * 
 * s32day2night_threshold:白视切换到夜视的阈值。【单位：数值; 范围：[-50, 50]】。\n
 * The threshold for day vision switching to night vision. [unit: value; range: [-50, 50]]\n
 * 
 * s32night2day_threshold:夜视切换到白视的阈值。【单位：数值; 范围：[-50, 50]】。\n
 * The threshold for night vision switching to day vision. [unit: value; range: [-50, 50]]\n
 * 
 * e32init_mode:初始化控制模式。【范围：[0, 2]】\n
 * Initial control mode. [range: [0, 2]]\n
 * 
 * cb:完成白视夜视切换后的回调函数。\n
 * The callback function after completing the day night vision switch\n
 * 
 * user_data:给cb回调函数的输入参数。\n
 * Input arguments to the "cb" callback function
 */
typedef struct t_fca_dn_attr {
	unsigned int u32lock_time;
	unsigned int u32trigger_interval;
	unsigned int u32trigger_times;
	int s32day2night_threshold;
	int s32night2day_threshold;
	FCA_DN_MODE_E e32init_mode;
	FCA_DAYNIGHT_CALLBACK cb;
	const void *user_data;
} fca_dn_attr_t;

/**
 * @brief 设置软光敏参数\n
 * Set the soft photosensitive parameters
 * @param dn_attr 软光敏参数结构体指针\n
 * Soft photosensitive parameter structure body pointer
 * @return int 返回值【0：成功， -1：失败】\n
 * Return value [0: success, -1: failure]
 */
int fca_dn_switch_set_config(fca_dn_attr_t *dn_attr);

/**
 * @brief 获取软光敏参数\n
 * Get the soft photosensitive parameters
 * @param dn_attr 软光敏参数结构体指针\n
 * Soft photosensitive parameter structure body pointer
 * @return int 返回值【0：成功， -1：失败】\n
 * Return value [0: success, -1: failure]
 */
int fca_dn_switch_get_config(fca_dn_attr_t *dn_attr);

/**
 * @brief 设置黑白夜视切换的控制模式，必须先设置软光敏参数\n
 * Set the control mode for day night vision switching, the soft photosensitive parameters must be set first
 * @param mode 软光敏控制模式\n
 * Soft photosensitive control mode
 */
void fca_dn_set_config_mode(FCA_DN_MODE_E mode);

/**
 * @brief 获取黑白夜视切换的控制模式\n
 * Get the control mode for day night vision switching.
 * @param mode 软光敏控制模式\n
 * Soft photosensitive control mode
 */
void fca_dn_get_config_mode(FCA_DN_MODE_E *mode);

/**
 * @brief 设置黑白夜视切换阈值\n
 * Set the day and night vision switching threshold
 * @param s32day2night_threshold 白视切换到夜视的阈值\n
 * The threshold of day vision to night vision
 * @param s32night2day_threshold 夜视切换到白视的阈值\n
 * The threshold of night vision to day vision
 */
void fca_user_dn_threshold_set(int s32day2night_threshold, int s32night2day_threshold);

/**
 * @brief 获取当前图像处于白视还是夜视状态\n
 * Gets the current image to be in the day or night vision state
 * @param daynight_status 返回的图像状态值\n
 * The returned image status value
 * @return int 返回值【0：成功， -1：失败】\n
 * Return value [0: success, -1: failure]
 */
int fca_get_dn_status_by_image_sensor(FCA_DAY_NIGHT_STATE_E *daynight_status);


#ifdef __cplusplus
}
#endif

#endif /* GIEC_API_IRCUT_H */
