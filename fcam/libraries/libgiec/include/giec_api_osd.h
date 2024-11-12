#ifndef GIEC_API_OSD_H
#define GIEC_API_OSD_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief OSD前景色，范围[0,15]\n
 * OSD foreground color, range [0,15]\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const int G_OSD_FRONT_COLOR;

/**
 * @brief OSD背景色，范围[0,15]\n
 * OSD background color, range [0,15]\n
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const int G_OSD_BG_COLOR;

/**
 * @brief OSD字库文件路径\n
 * Path of the OSD font file.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const char* G_OSD_FONT_FILE;

/**
 * @brief OSD字库字体大小\n
 * Size of the OSD font.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const int G_OSD_FONT_SIZE;

/**
 * @brief 客制化字符串最大长度\n
 * Maximum length of the custom string.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const int G_OSD_CUS_STR_MAX_LEN;

/**
 * @brief OSD时间水印或客制化字符串显示位置类型\n
 * Type of the OSD time watermark or custom string display position.
 */
typedef enum
{
    FCA_OSD_TOP_LEFT = 0,
    FCA_OSD_BOTTOM_LEFT,
    FCA_OSD_TOP_RIGHT,
    FCA_OSD_BOTTOM_RIGHT,
    FCA_OSD_DISABLE,
} FCA_OSD_POSITION_E;

/**
 * @brief 初始化OSD\n
 * Initialize OSD
 * @note 必须在调用 @ref fca_video_in_init 之后调用\n
 * Must be called after @ref fca_video_in_init is called.
 * @note 必须在调用任何OSD相关的API之前调用，比如显示时间水印，区域侦测等。\n
 * Must be called before calling any OSD-related API, such as time watermarks, alarmzone detection, etc.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_osd_init(void);

/**
 * @brief 反初始化OSD\n
 * Uninitialize OSD
 * @note 需要在所有OSD功能关闭后才能调用，或者不调用\n
 * It should be called after all OSD functions are closed, or not called.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_osd_uninit(void);

/**
 * @brief 设置夏令时时间(时间水印提前1小时)\n
 * Set summer time，(time watermark is 1 hour earlier)
 * @param onoff 输入，0：设置为非夏令时，1：设置为夏令时\n
 * input, 0: set as non-summer time, 1: set as summer time.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_osd_dls_set_onoff(int onoff);

/**
 * @brief 在指定位置显示OSD文本 或 隐藏内容为 text，长度为 text_len 的字符串\n
 * Show text on the specified position, or hide the text which's content is text, length is text_len
 * @param position 输入，OSD显示位置\n
 * input, OSD display position.
 * @param text 输入，OSD显示文本\n
 * input, OSD display text.
 * @param text_len 输入，text长度\n
 * input, text length
 * @note text_len 的字符数不超过 @ref G_OSD_CUS_STR_MAX_LEN - 1 个字节\n
 * The number of characters in text_len does not exceed @ref G_OSD_CUS_STR_MAX_LEN - 1 bytes.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_isp_set_osd_text(FCA_OSD_POSITION_E position, char *text, int text_len);

/**
 * @brief 获取指定位置的OSD文本\n
 * Retrieves the current position of the on-screen display (OSD) for displaying custom text.
 * @param position 输入，待获取字符串的位置\n
 * input, position of the string to be retrieved.
 * @param text 输出，OSD显示文本\n
 * output, OSD display text.
 * @param text_len 输入，text的长度\n
 * input, length of text.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_isp_get_osd_text(FCA_OSD_POSITION_E position, char *text, int text_len);

/**
 * @brief 在指定位置显示时间水印, 或者隐藏时间水印\n
 * Show or hide time watermark on the specified position.
 * @param position 输入，时间水印显示位置\n
 * input, time watermark display position.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_isp_set_osd_time(FCA_OSD_POSITION_E position);

/**
 * @brief 获取时间水印的位置\n
 * Retrieves the current position of the on-screen display (OSD) for displaying time.
 * @param position 输出，时间水印显示位置\n
 * output, time watermark display position.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_isp_get_osd_time(FCA_OSD_POSITION_E *position);

#ifdef __cplusplus
}
#endif

#endif //GIEC_API_OSD_H