#ifndef GIEC_API_VIDEO_H
#define GIEC_API_VIDEO_H
#include "ak_common.h"
#include "ak_venc.h"

#ifdef __cplusplus
extern "C" {
#endif

//Video

/**
 * @brief 初始化VI时配置的子码流分辨率的最大宽度，可能会被 @ref giec_set_video_config 重置\n
 * The maximum width of the sub video stream resolution configured when initializing VI, which may be reset by @ref giec_set_video_config.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，AV100平台，支持的范围是 1280 ~ 16\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file. supported range is 1280 ~ 16.
 */
extern const int G_VI_MAX_WIDTH_SUB;

/**
 * @brief 初始化VI时配置的子码流分辨率的最大高度，可能会被 @ref giec_set_video_config 重置\n
 * The maximum height of the sub video stream resolution configured when initializing VI, which may be reset by @ref giec_set_video_config.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，AV100平台，支持的范围是 1024 ~ 16\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file. supported range is 1024 ~ 16.
 */
extern const int G_VI_MAX_HEIGHT_SUB;

/**
 * @brief VIDEO IN通道的编码类型\n
 * Encoding type of VIDEO IN channel.
 */
typedef enum {
    FCA_CODEC_VIDEO_H264 = 0,
    FCA_CODEC_VIDEO_H265,
    FCA_CODEC_VIDEO_MJPEG,
} FCA_VIDEO_IN_CODEC_E;

/**
 * @brief VIDEO IN通道的编码模式\n
 * Encoding mode of VIDEO IN channel.
 */
typedef enum
{
    FCA_VIDEO_ENCODING_MODE_CBR = 0,
    FCA_VIDEO_ENCODING_MODE_VBR,
    FCA_VIDEO_ENCODING_MODE_AVBR,
} FCA_VIDEO_IN_ENCODING_MODE_E;

/**
 * @brief VIDEO IN通道的配置参数\n
 * Configuration parameters of VIDEO IN channel.
 */
typedef struct
{
    FCA_VIDEO_IN_CODEC_E codec; // Codec type
    FCA_VIDEO_IN_ENCODING_MODE_E encoding_mode; // CBR/AVBR/VBR
    int bitrate_target;                         // The target bitrate(kbps). CBR target = 3/4 max
    int bitrate_max;                            // The maximum bitrate (kbps).
    int gop;                                    // Group of pictures of the stream. */
    int fps;                                    // The frame rate to be captured. (1-25 fps, frames per second) */
    int width;                                  // The width of a video frame, in pixels */
    int height;                                 // The VBR quality, used in VBR */
    int max_qp;                                 // Quantization parameter maximum
    int min_qp;                                 // Quantization parameter minimum
} fca_video_in_config_t;

/**
 * @brief 帧类型\n
 * Frame type.
 */
typedef enum {
    FCA_VIDEO_IN_FRAME_TYPE_P = 0,
    FCA_VIDEO_IN_FRAME_TYPE_I,
    FCA_VIDEO_IN_FRAME_TYPE_PI,
} FCA_VIDEO_IN_FRAME_TYPE_E;

/**
 * @brief 函数 @ref fca_video_in_start_callback 的回调函数参数。\n
 * The parameter of the callback function used by @ref fca_video_in_start_callback.
 */
typedef struct {
    unsigned char *data;
    unsigned int size;
    unsigned long long timestamp;
    unsigned long sequence;
    FCA_VIDEO_IN_FRAME_TYPE_E type;
} fca_video_in_frame_t;

/**
 * @brief 回调函数的类型，用于接收视频帧,并推送到云端\n
 * The type of the callback function used to receive video frames and push them to the cloud.
 */
typedef void (*FCA_VIDEO_IN_CALLBACK)(const fca_video_in_frame_t *video_frame);

/**
 * @brief 画面翻转的类型，用于画面翻转和镜像\n
 * The type of the video mirror and flip.
 */
typedef enum {
    FCA_ISP_MIRROR_FLIP_NONE,
    FCA_ISP_MIRROR, // Mirror
    FCA_ISP_FLIP, // Flip
    FCA_ISP_MIRROR_AND_FLIP // Mirror and flip
} FCA_ISP_MIRROR_FLIP_E;


/**
 * @brief ISP配置文件路径\n
 * ISP configuration file path.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const char* G_ISP_CONF_PATH;

//QRCODE

/**
 * @brief zbar工作时的临时图片暂存路径\n
 * Temporary image storage path during zbar work.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
extern const char* GIEC_QRCODE_IMAGE_PATH;

/**
 * @brief 传给zbar模块的图像宽度，即子码流图像宽度\n
 * The width of the image passed to zbar, which is the width of the sub video stream.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
//extern const int GIEC_QRCODE_IMAGE_W;

/**
 * @brief 传给zbar模块的图像高度，即子码流图像高度\n
 * The height of the image passed to zbar, which is the height of the sub video stream.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值\n
 * This variable is used by the library and configured to the actual value in the giec_param.c file.
 */
//extern const int GIEC_QRCODE_IMAGE_H;

//FUNCTION

/**
 * @brief 初始化视频输入模块\n
 * Initialize the video input module.
 * @note 必须在调用任何涉及视频的API之前调用，比如录像，截图，二维码，各种侦测算法等等，建议最早调用此函数。\n
 * Must be called before calling any API that involves video, such as recording, snapshots, QR code, detection, etc., 
 * and it is recommended to call this function as early as possible.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_video_in_init(void);

/**
 * @brief 设置/重置指定码流的配置参数和编码参数\n
 * Set/reset the vi parameters and encoding parameters of the specified video stream.
 * @param index 输入，通道索引，0：主码流通道，1：子码流&截图 2: 第三码流(与子码流共享VI通道)\n
 * input, stream index, 0: main video stream, 1: sub video stream and snapshot channel, 2: third video stream (VI CHN shared with sub video stream).
 * @param config 输入，配置参数指针\n
 * input, configuration parameters pointer.
 * @note 在调用 @ref fca_video_in_init 之后调用，在任何涉及视频的API之前调用，比如录像，截图，二维码，各种侦测算法等等。\n
 * Must be called after @ref fca_video_in_init, and must be called before any API that involves video, such as recording, snapshots, QR code, detection, etc.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_video_in_set_config(int index, fca_video_in_config_t *config);

/**
 * @brief 获取VIDEO IN码流的配置参数\n
 * Get the configuration parameters of VIDEO IN stream.
 * @param index 输入，通道索引，0：主码流，1：子码流 2: 第三码流(与子码流共享VI通道)\n
 * input, channel index, 0: main video stream, 1: sub video stream. 2: third video stream (VI CHN shared with sub video stream).
 * @param config 输出，配置参数指针，请提前分配内存\n
 * output, configuration parameters pointer，please pre-allocate memory.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_video_in_get_config(int index, fca_video_in_config_t *config);

/**
 * @brief 反初始化视频输入模块\n
 * Uninitialize the video input module.
 * @note 在关闭所有功能后再调用。当前未实现此函数。\n
 * 一般不调用此函数。如果需要处理比如OTA升级前回收内存等场景，请进一步沟通\n
 * This function is not implemented currently. It should be called after all functions are closed. 
 * If you need to handle scenarios such as memory reclaiming before OTA upgrade, please further discuss.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_video_in_uninit(void);

/**
 * @brief 对子码流截图, 格式为jpeg\n
 * Snapshot the sub video stream, format is jpeg.
 * @param snap_addr 输出，需要提前分配存储图像的buff，函数接收此buff地址,用于保存图像\n
 * output, caller needs to pre-allocate the buffer to store the image, and this buffer address is used to save the image.
 * @param snap_size 输出，需要提前分配一个int变量，函数接收此变量的地址，用于保存图像大小\n
 * output, caller needs to pre-allocate an int variable, and this variable address is used to save the image size.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_video_in_get_snapshot(char *snap_addr, int *snap_size);

/**
 * @brief 开启一个内部线程，不断地将指定码流的每一个视频帧传输给cb函数处理。\n
 * Start an internal thread that continuously transfers each video frame of the specified stream to the cb function for processing.
 * @param index 输入，码流索引，0：主码流，1：子码流 2: 第三码流(与子码流共享VI通道)\n
 * input, stream index, 0: main video stream, 1: sub video stream.
 * @param cb 输入，回调函数的指针，用于接收视频帧后做处理，比如推送到云端。\n
 * input, a pointer to the callback function, which is used to receive video frames and process them, such as pushing them to the cloud.
 * @note 仅调用一次，非阻塞，非线程安全。需要先调用 @ref fca_video_in_set_config 配置 index 对应码流的参数后，才能调用这个函数启动推流。\n
 * Only call once, non-blocking, non-thread-safe. Must call @ref fca_video_in_set_config to configure the parameters of the corresponding stream before calling this function to start streaming.
 * @note 必须按顺序启动指定码流的推流： 先启动主码流，再启动子码流，再启动第三码流。\n
 * Must start the streaming of the specified stream in order: first start the main video stream, then start the sub video stream, and finally start the third video stream.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_video_in_start_callback(int index, FCA_VIDEO_IN_CALLBACK cb);

/**
 * @brief 停止由 @ref fca_video_in_start_callback 开启的内部线程，结束指定码流视频帧的传输。\n
 * Stop the internal thread started by @ref fca_video_in_start_callback and end the transmission of video frames of the specified stream.
 * @param index 输入，通道索引，0：主码流，1：子码流\n
 * input, stream index, 0: main video stream, 1: sub video stream, 2: third video stream.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_video_in_stop_callback(int index);

/**
 * @brief 解析出二维码内容时的回调函数，是 @ref fca_video_in_qrcode_scan_start 的参数类型\n
 * The callback function used when parsing QR code content, which is the parameter type of @ref fca_video_in_qrcode_scan_start.
 */
typedef  void (*FCA_VIDEO_IN_QRCODE_CALLBACK)(char *qrcode_str, int qrcode_len);

/**
 * @brief 开启一个内部线程，不断检测子码流中的二维码，获取到二维码后线程结束，并将二维码内容和长度通过回调函数传递给用户\n
 * Start an internal thread that continuously detects QR codes in the sub video stream, 
 * and when a QR code is obtained, the thread ends and the QR code content and length are passed to the user through the callback function.
 * @param callback 输入，二维码回调函数，参数qrcode_str为二维码内容，参数qrcode_len为二维码长度。用户不需要为qrcode_str分配内存，函数内部会分配内存。\n
 * input, QR code callback function, parameter qrcode_str is the QR code content, parameter qrcode_len is the QR code length. 
 * The user does not need to allocate memory for qrcode_str, the function will allocate memory internally.
 * @note 必须调用 @ref fca_video_in_start_callback 使能子码流后才能调用这个接口\n
 * Must call @ref fca_video_in_start_callback to enable the sub video stream before calling this interface.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_video_in_qrcode_scan_start(FCA_VIDEO_IN_QRCODE_CALLBACK cb);

/**
 * @brief 停止扫描二维码，即停止由 @ref fca_video_in_qrcode_scan_start 开启的内部线程\n
 * Stop scanning QR codes, which means stopping the internal thread started by @ref fca_video_in_qrcode_scan_start
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_video_in_qrcode_scan_stop();

/**
 * @brief 设置视频画面旋转和镜像\n
 * Set the video image rotation and mirror.
 * @param direction 输入，参考 @ref FCA_ISP_MIRROR_FLIP_E\n
 * input, refer to @ref FCA_ISP_MIRROR_FLIP_E.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_isp_set_mirror_flip(FCA_ISP_MIRROR_FLIP_E direction);

/**
 * @brief 获取当前的画面旋转和镜像设置\n
 * Get the current video image rotation and mirror setting.
 * @param direction 输出，参考 @ref FCA_ISP_MIRROR_FLIP_E\n
 * output, refer to @ref FCA_ISP_MIRROR_FLIP_E.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_isp_get_mirror_flip(FCA_ISP_MIRROR_FLIP_E *direction);

#ifdef __cplusplus
}
#endif

#endif //GIEC_API_VIDEO_H