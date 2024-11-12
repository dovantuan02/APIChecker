#ifndef GIEC_API_COMMON_H
#define GIEC_API_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 配置SD卡路径。\n
 * 可在giec_param.c中配置，替换为实际的SD卡路径，一般为/mnt/sdcard。\n
 * Configure the SD card path.\n
 * You can configure it in the giec_param.c file, replace it with the actual SD card path, generally /mnt/sdcard.
 */
extern const char * G_SD_PATH;

/**
 * @brief 设置库内部为隐私模式。在此模式下，各功能暂时关闭，以保护用户隐私。\n
 * 比如暂停推送视频流到云端，暂停推送告警消息等。\n
 * Set the library to privacy mode(aka sleep mode). In this mode, various functions are temporarily closed to protect user privacy.\n
 * For example, pause pushing video streams to the cloud, pause pushing alarm messages, etc.
 * @param mode 输入，0：退出隐私模式，1：使能隐私模式\n
 * Input, 0: exit privacy mode, 1: enable privacy mode.
 * @return 0表示成功，其他表示失败。
 * return 0 means success, other means failure.
 */
int giec_common_set_sleep_mode(int mode);

/**
 * @brief 获取隐私模式状态\n
 * Get the privacy mode status.\n
 * @return 0: 隐私模式关闭，1: 隐私模式使能\n
 * return 0: privacy mode is off, 1: privacy mode is on.
 */
int giec_common_get_sleep_mode(void);

/**
 * @brief LED灯效状态\n
 * LED light effect status.\n
 */
typedef enum {
    GIEC_LED_RED_ON,               //红灯常亮, Red light always on.
    GIEC_LED_RED_OFF,              //红灯关闭, Red light off.
    GIEC_LED_BLUE_ON,              //蓝灯常亮, Blue light always on.
    GIEC_LED_BLUE_OFF,             //蓝灯关闭, Blue light off.
    GIEC_LED_GREEN_ON,             //绿灯常亮, Green light always on.
    GIEC_LED_GREEN_OFF = 5,        //绿灯关闭, Green light off.
    GIEC_LED_YELLOW_ON,            //黄灯常亮, Yellow light always on.
    GIEC_LED_YELLOW_OFF,           //黄灯关闭, Yellow light off.
    GIEC_LED_RGB_ON,               //三色白灯常亮, RGB light always on.
    GIEC_LED_RGB_OFF,              //三色白灯关闭, RGB light off.
    GIEC_IRLED_ON = 10,            //红外灯常亮, Infrared light always on.
    GIEC_IRLED_OFF,                //红外灯关闭, Infrared light off.
    GIEC_LED_RED_BLINK_FAST,       //红灯快闪, Red light fast blink.
    GIEC_LED_RED_BLINK_SLOW,       //红灯慢闪, Red light slow blink.
    GIEC_LED_BLUE_BLINK_FAST,      //蓝灯快闪, Blue light fast blink.
    GIEC_LED_BLUE_BLINK_SLOW = 15, //蓝灯慢闪, Blue light slow blink.
    GIEC_LED_GREEN_BLINK_FAST,     //绿灯快闪, Green light fast blink.
    GIEC_LED_GREEN_BLINK_SLOW ,    //绿灯慢闪, Green light slow blink.
    GIEC_LED_YELLOW_BLINK_FAST,    //黄灯快闪, Yellow light fast blink.
    GIEC_LED_YELLOW_BLINK_SLOW,    //黄灯慢闪, Yellow light slow blink.
    GIEC_LED_RING_BLINK = 20,      //环形交替闪烁, Ring light blink alternately.
    GIEC_WHITELED_ON,              //白光补光灯常亮, White light always on.
    GIEC_WHITELED_OFF,             //白光补光灯关闭, White light off.
    GIEC_LED_WHITE_BLINK_FAST,     //白光快闪, White light fast blink.
    GIEC_LED_WHITE_BLINK_SLOW ,    //白光慢闪, White light slow blink.
    GIEC_LED_RG_BLINK_FAST = 25,   //红绿灯交替快闪, Red and green lights blink alternately fast.
    GIEC_LED_RG_BLINK_SLOW,        //红绿灯交替慢闪, Red and green lights blink alternately slow.
    GIEC_LED_RB_BLINK_FAST,        //红蓝灯交替快闪, Red and blue lights blink alternately fast.
    GIEC_LED_RB_BLINK_SLOW,        //红蓝灯交替慢闪, Red and blue lights blink alternately slow.
    GIEC_LED_RING_ON,              //环形交替常亮, Ring light always on.
    GIEC_LED_RING_OFF = 30,        //环形交替关闭, Ring light off.
    GIEC_LED_RING_BLINK_FAST,      //环形交替快闪, Ring light blink alternately fast.
    GIEC_LED_RING_BLINK_SLOW,      //环形交替慢闪, Ring light blink alternately slow.
    GIEC_LED_RING_BLINK_BREATH_START,   //环形呼吸灯开始, Ring light breathing start.
    GIEC_LED_RING_BLINK_BREATH_STOP,    //环形呼吸灯停止, Ring light breathing stop.
    GIEC_LED_RING_BLINK_ROLL,           //环形跑马灯, Ring light roll.
    GIEC_LED_RING_BLINK_BREATH_ONCE,    //单次呼吸灯, Single breathing light.
    GIEC_LED_RING_BLINK_BREATH_TWICE,   //两次呼吸灯, Double breathing light.
    GIEC_FILL_LIGHT_ON,                 //白光补光灯打开, White light on.
    GIEC_FILL_LIGHT_OFF,                //白光补光灯关闭, White light off.
    GIEC_LED_STATUS_NULL,               //无灯效, No effect.
    GIEC_LED_RED_BLINKING,              //红灯自定义时间闪烁, Red light blinking.
    GIEC_LED_GREEN_BLINKING,            //绿灯自定义时间闪烁, Green light blinking.
    GIEC_LED_STATUS_MAX,
} GIEC_SYS_LED_STATUS;

/**
 * @brief SDK公共部分初始化。\n
 * Initialize the common part of the SDK.
 * @note 该接口需要调用其他API之前调用\n
 * This interface needs to be called before calling other APIs.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_sdk_init();

#ifdef __cplusplus
}
#endif

#endif
