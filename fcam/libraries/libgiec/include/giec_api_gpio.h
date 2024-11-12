#ifndef GIEC_API_GPIO_H
#define GIEC_API_GPIO_H

#include "giec_api_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 复位键的GPIO口编号\n
 * GPIO pin number of reset button.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值。不使用则配置为-1\n
 * This variable is used by the library, which can be configured as the actual value in the giec_param.c file. If not used, it is configured as -1.
 */
extern const int GIEC_GPIO_KEY_RESET;

/**
 * @brief 通话键的GPIO口编号\n
 * GPIO pin number of call button.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值。不使用则配置为-1\n
 * This variable is used by the library, which can be configured as the actual value in the giec_param.c file. If not used, it is configured as -1.
 */
extern const int GIEC_GPIO_KEY_CALL;

/**
 * @brief LED灯的极性\n
 * LED polarity.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, which is configured as the actual value in the giec_param.c file, please do not modify.
 */
extern const int GIEC_GPIO_LED_POLARITY;

/**
 * @brief 红灯的GPIO口编号\n
 * GPIO pin number of red LED.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值。不使用则配置为-1\n
 * This variable is used by the library, which can be configured as the actual value in the giec_param.c file. If not used, it is configured as -1.
 */
extern const int GIEC_GPIO_LED_RED;

/**
 * @brief 绿灯的GPIO口编号\n
 * GPIO pin number of green LED.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值。不使用则配置为-1\n
 * This variable is used by the library, which can be configured as the actual value in the giec_param.c file. If not used, it is configured as -1.
 */
extern const int GIEC_GPIO_LED_GREEN;

/**
 * @brief IRCUT的P引脚GPIO口编号\n
 * GPIO pin number of IRCUT P pin.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, which is configured as the actual value in the giec_param.c file, please do not modify.    
 */
extern const int GIEC_GPIO_IRCUT_P;

/**
 * @brief IRCUT的N引脚GPIO口编号\n
 * GPIO pin number of IRCUT N pin.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, which is configured as the actual value in the giec_param.c file, please do not modify.
 */
extern const int GIEC_GPIO_IRCUT_N;

/**
 * @brief 红外灯的GPIO口编号\n
 * GPIO pin number of infrared LED.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值。请勿修改。\n
 * This variable is used by the library, which is configured as the actual value in the giec_param.c file, please do not modify.
 */
extern const int GIEC_GPIO_LED_IR;

/**
 * @brief 白光灯的GPIO口编号\n
 * GPIO pin number of white LED.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值。请勿修改。\n
 * This variable is used by the library, which is configured as the actual value in the giec_param.c file, please do not modify.
 */
extern const int GIEC_GPIO_LED_WHITE;

/**
 * @brief 红外灯的名字\n
 * Infrared LED name.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值。请勿修改。\n
 * This variable is used by the library, which is configured as the actual value in the giec_param.c file, please do not modify.
 */
extern const char* GIEC_GPIO_LED_IR_NAME;

//extern const int GIEC_GPIO_LED_WRITE;
//extern const int GIEC_GPIO_SPK_EN;

/**
 * @brief LED灯的控制方式\n
 * LED control mode.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值。请勿修改。\n
 * This variable is used by the library, which is configured as the actual value in the giec_param.c file, please do not modify.
 */
extern const int GIEC_GPIO_CTL_VER;

/**
 * @brief 函数 @ref giec_gpio_key_init 的参数的类型，用于配置GPIO按键的功能
 * Parameter type for @ref giec_gpio_key_init function, used to configure the function of the GPIO buttons.
 * @note key_reset_longpress_cb_func: 函数指针， 复位键长按时，会调用该函数\n
 * key_reset_shortpress_cb_func: 函数指针， 复位键短按时，会调用该函数\n
 * key_call_longpress_cb_func: 函数指针， 一键通话键长按时，会调用该函数\n
 * key_call_shortpress_cb_func: 函数指针， 一键通话键短按时，会调用该函数\n
 * key_longpress_ms: 长按时间阈值，单位毫秒\n
 * key_shortpress_ms: 短按时间阈值，单位毫秒\n
 * key_reset_longpress_cb_func: function pointer, the function will be called when the reset button is long pressed.\n
 * key_reset_shortpress_cb_func: function pointer, the function will be called when the reset button is short pressed.\n
 * key_call_longpress_cb_func: function pointer, the function will be called when the call button is long pressed.\n
 * key_call_shortpress_cb_func: function pointer, the function will be called when the call button is short pressed.\n
 * key_longpress_ms: long press threshold, unit: ms.\n
 * key_shortpress_ms: short press threshold, unit: ms.
 */
typedef struct GIEC_GPIO_KEY_CB_PARAM_S {
    void* key_reset_longpress_cb_func;
    void* key_reset_shortpress_cb_func;
    void* key_call_longpress_cb_func;
    void* key_call_shortpress_cb_func;
    int key_longpress_ms;
    int key_shortpress_ms;
} GIEC_GPIO_KEY_CB_PARAM;

/**
 * @brief 初始化GPIO按键，库内部开启按键检测线程，并调用回调函数\n
 * Initialize GPIO buttons, the library starts the button detection thread internally and calls the callback function.
 * @param key_cb_param 输入，一个 @ref GIEC_GPIO_KEY_CB_PARAM 类型变量的指针，用于配置GPIO按键的功能\n
 * Input, a pointer to a GIEC_GPIO_KEY_CB_PARAM type variable, used to configure the function of the GPIO buttons.
 * @return 0表示成功，其他表示失败。\n
 * Return 0 for success, other for failure.
 */
int giec_gpio_key_init(GIEC_GPIO_KEY_CB_PARAM* key_cb_param);

/**
 * @brief 开启库内部的LED灯效线程，它会根据网络状态自动切换LED灯效\n
 * Start the LED lighting thread inside the library, which will automatically switch the LED lighting according to the network status.
 * @note 需要先调用 @ref giec_network_set_callback 后，才能调用此函数\n
 * This function needs to be called after @ref giec_network_set_callback is called.
 * @param onoff 输入，0：退出LED灯效线程 1：使能LED灯效线程\n
 * Input, 0: exit LED lighting thread 1: start LED lighting thread.
 * @return 0表示成功，其他表示失败。\n
 * Return 0 for success, other for failure.
 */
int giec_gpio_led_network_set_onoff(int onoff);

/**
 * @brief 手动设置LED灯效状态\n
 * Manually set the LED lighting status.
 * @param status 输入，GIEC_SYS_LED_STATUS类型变量，用于设置LED灯效状态\n
 * Input, GIEC_SYS_LED_STATUS type variable, used to set the LED lighting status.
 * @return 0表示成功，其他表示失败。\n
 * Return 0 for success, other for failure.
 */
int giec_gpio_led_status_set(GIEC_SYS_LED_STATUS status);

typedef enum {
    FCA_BTN_RESET,
    FCA_BTN_USER
} FCA_BTN_TYPE;

typedef enum
{
    FCA_BTN_STATUS_UNKNOWN = 0,
    FCA_BTN_STATUS_PRESS,
    FCA_BTN_STATUS_RELEASE,
} FCA_BTN_STATUS;

/**
 * @brief 获取按键当前状态\n
 * Get button status.
 * @param status 输入，FCA_BTN_TYPE类型变量，用于设置按键类型\n
 * Input, FCA_BTN_TYPE type variable, used to set the button type.
 * @note 需要先调用 @ref giec_gpio_key_init 初始化后，才能调用此函数\n
 * This function needs to be called after @ref giec_gpio_key_init is called.
 * @return 0表示成功，其他表示失败。\n
 * Return 0 for success, other for failure.
 */
int fca_get_button_status(FCA_BTN_TYPE type, FCA_BTN_STATUS *status);

typedef enum
{
    FCA_LIGHTING_LED_WHITE=0,
    FCA_LIGHTING_LED_IR
} FCA_LIGHTING_LED_TYPE;

/**
 * @brief 设置当前补光灯状态\n
 * Set lighting led status.
 * @param status 输入，FCA_LIGHTING_LED_TYPE类型变量，用于设置补光灯类型，value类型变量，1:ON, 0: OFF\n
 * Input, FCA_LIGHTING_LED_TYPE type variable, used to set the led type, value, 1:ON, 0: OFF.
 * @return 0表示成功，其他表示失败。\n
 * Return 0 for success, other for failure.
 */
int fca_set_led_lighting(FCA_LIGHTING_LED_TYPE type, int value);

/**
 * @brief 获取当前补光灯状态\n
 * Get lighting led status.
 * @param status 输入，FCA_LIGHTING_LED_TYPE类型变量，用于设置补光灯类型，value类型变量，1:ON, 0: OFF\n
 * Input, FCA_LIGHTING_LED_TYPE type variable, used to get the led type, value, 1:ON, 0: OFF.
 * @return 0表示成功，其他表示失败。\n
 * Return 0 for success, other for failure.
 */
int fca_get_led_lighting(FCA_LIGHTING_LED_TYPE type, int *value);

typedef enum
{
    FCA_LED_COLOR_UNKNOWN = 0,
    FCA_LED_COLOR_YELLOW = 1,
    FCA_LED_COLOR_WHITE = 2,
    FCA_LED_COLOR_MAX
} FCA_LED_COLOR_E;

typedef enum
{
    FCA_LED_MODE_OFF = 0,
    FCA_LED_MODE_ON,
    FCA_LED_MODE_BLINKING,
} FCA_LED_MODE_E;

typedef struct
{
    FCA_LED_COLOR_E color;
    FCA_LED_MODE_E mode;
    int interval; // blinking interval in ms
} fca_led_status_t;

/**
 * @brief 设置指示灯状态\n
 * Set guiding led status.
 * @param status 输入，fca_led_status_t类型变量，用于设置指示灯类型\n
 * Input, fca_led_status_t type variable, used to set the guiding led type.
 * @return 0表示成功，其他表示失败。\n
 * Return 0 for success, other for failure.
 */
int fca_gpio_led_status_set(fca_led_status_t status);

/**
 * @brief 获取指示灯状态\n
 * Get guiding led status.
 * @param status 输入，fca_led_status_t指针变量，用于获取指示灯类型\n
 * Input, fca_led_status_t * type variable, used to get the guiding led type.
 * @note 需要先调用 @ref fca_gpio_led_status_set 后，才能调用此函数并返回set后的状态，否则返回的是默认值\n
 * This function needs to be called after @ref fca_gpio_led_status_set is called, otherwise, the default value will be returned.
 * @return 0表示成功，其他表示失败。\n
 * Return 0 for success, other for failure.
 */
int fca_gpio_led_status_get(fca_led_status_t *status);

#ifdef __cplusplus
}
#endif

#endif
