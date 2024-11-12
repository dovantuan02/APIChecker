#ifndef GIEC_API_SYS_H
#define GIEC_API_SYS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 静默重启标志文件的路径\n
 * Path of the silent reboot param file.
 * @note 需要在可读写分区。该文件被库读写，保存一些静默重启相关的参数，供重启后使用。在giec_param.c中配置为实际的值。\n
 * Should be in a read-write partition. This file is read and written by the library, 
 * and it saves some parameters related to silent reboot, which will be used after the reboot. 
 * It is configured in the giec_param.c file as the actual value.
 */
extern const char* G_SBOOT_FILE;

/**
 * @brief 可选的，启动看门狗\n
 * Optional, Initialize the watchdog.
 * @param timeout 输入，喂狗超时时间, 单位s\n
 * input, watchdog timeout, unit: s
 * @note 0 < timeout <= 300, 如果值错误，自动设置为120\n
 * 0 < timeout <= 300, if the value is incorrect, it will be automatically set to 120.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_sys_watchdog_init(int timeout);

/**
 * @brief 暂停看门狗\n
 * Stop the watchdog.
 * @note 可以被 @ref fca_sys_watchdog_refresh 重新使能\n
 * Can be re-enabled by @ref fca_sys_watchdog_refresh.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_sys_watchdog_stop_block(void);

/**
 * @brief 喂狗\n
 * Feed the watchdog.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_sys_watchdog_refresh(void);

/**
 * @brief 可选，开机后检查静默重启状态，如果本次开机是静默重启，那么将PTZ坐标修正为重启前保存的值\n
 * Optional, check the silent reboot status after boot, if the current boot is a silent reboot, then correct the PTZ coordinates to the saved values before the reboot.
 * @note 需要在PTZ初始化后调用。从文件 @ref G_SBOOT_FILE 中读取参数\n
 * Needs to be called after the PTZ is initialized. Read parameters from file @ref G_SBOOT_FILE.
 */
void fca_sys_sboot_restore(void);

/**
 * @brief 检查本次开机是否为静默重启, 用户可据此决定是否转动电机和播放提示音.\n
 * Check if the current boot is a silent reboot, and the user can decide whether to turn the motor and play the prompt sound.
 * @note 需要在调用 @ref fca_sys_sboot_restore 之后调用\n
 * Needs to be called after calling @ref fca_sys_sboot_restore
 * @return 1: 静默重启, 0: 正常重启\n
 * return 1: silent reboot, 0: normal reboot.
 */
int fca_sys_sboot_is_sboot(void);

/**
 * @brief 清除静默重启标记\n
 * Clear the silent reboot flag.
 */
void fca_sys_sboot_clear_sboot(void);

/**
 * @brief 可选，启动静默重启守护线程\n
 * Optional, start the silent reboot daemon thread.
 * @param sboot_pre_cb 输入，库检测到设备需要静默重启，在重启前，会调用该函数。用户可以这该函数中执行一些必要的操作，比如停止云存储、上报消息等\n
 * input, the function will be called before the device enter silence reboot. 
 * The user can perform some necessary operations, such as stopping cloud storage and reporting messages.
 * @note 开机后，等各个模块初始化完成后，再调用此函数。\n
 * Should be called after all modules are initialized.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_sys_sboot_start(void(*sboot_pre_cb)(void));

/**
 * @brief 停止静默重启守护线程\n
 * Stop the silent reboot daemon thread.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_sys_sboot_stop(void);

#ifdef __cplusplus
}
#endif

#endif /* GIEC_API_SYS_H */
