#ifndef GIEC_API_AUDIO_H
#define GIEC_API_AUDIO_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 音频资源文件A的路径，指向一个符合音频格式要求的pcm文件。\n
 * 该变量被库使用，可在giec_param.c中配置，替换为实际的pcm文件路径。\n
 * Audio file path A, pointed to a pcm file with the required audio format.\n
 * The variable is used by the library, which can be configured in the giec_param.c file, and replaced with the actual pcm file path.
 */
extern const char* G_AUDIO_OUT_FILE_A;

/**
 * @brief 音频资源文件B的路径，指向一个符合音频格式要求的pcm文件。\n
 * 该变量被库使用，可在giec_param.c中配置，替换为实际的pcm文件路径。\n
 * Audio file path B, pointed to a pcm file with the required audio format.\n
 * The variable is used by the library, which can be configured in the giec_param.c file, and replaced with the actual pcm file path.
 */
extern const char* G_AUDIO_OUT_FILE_B;

/**
 * @brief 音频资源文件C的路径，指向一个符合音频格式的pcm文件。\n
 * 该变量暂未使用，可在giec_param.c中配置，替换为实际的pcm文件路径。\n
 * Audio file path C, pointed to a pcm file with the required audio format.\n
 * The variable is not used, which can be configured in the giec_param.c file, and replaced with the actual pcm file path.
 */
extern const char* G_AUDIO_OUT_FILE_C;

/**
 * @brief 警笛声文件的路径，指向一个符合音频格式的pcm文件。\n
 * 该变量被库使用，可在giec_param.c中配置，替换为实际的pcm文件路径。\n
 * Siren sound file path, pointed to a pcm file with the required audio format.\n
 * The variable is used by the library, which can be configured in the giec_param.c file, and replaced with the actual pcm file path.
 */
extern const char* G_AUDIO_OUT_FILE_S;

/**
 * @brief 音频编码类型。\n
 * Audio Encoding Type.
 */
typedef enum
{
    FCA_AUDIO_CODEC_AAC,
    FCA_AUDIO_CODEC_G711_ALAW, /* G.711 A-law */
    FCA_AUDIO_CODEC_G711_ULAW, /* G.711 μ-law */
    FCA_AUDIO_CODEC_PCM
} FCA_AUDIO_CODEC;

/**
 * @brief 音频采样率。\n
 * audio sample rate.
 */
typedef enum
{
    FCA_AUDIO_SAMPLE_RATE_8_KHZ = 8000,
    FCA_AUDIO_SAMPLE_RATE_16_KHZ = 16000,
    FCA_AUDIO_SAMPLE_RATE_32_KHZ = 32000,
    FCA_AUDIO_SAMPLE_RATE_44_1_KHZ = 44100,
    FCA_AUDIO_SAMPLE_RATE_48_KHZ = 48000,
} FCA_AUDIO_SAMPLE_RATE;

/**
 * @brief 音频初始化参数。\n
 * Audio initialization parameters.
 */
typedef struct
{
    FCA_AUDIO_CODEC codec;
    FCA_AUDIO_SAMPLE_RATE rate;
    int channel; /**> channel (1:mono, currently only has one microphone) */
    int format; /**> bit width (16: each audio sample is 16 bit) */
} fca_audio_config_t;

/**
 * @brief fpt定制数据帧格式。\n
 * FPT customized data frame format.
 */
typedef struct
{
    unsigned char* data;
    unsigned int size;
    unsigned long long timestamp;
    unsigned long sequence;
} fca_audio_frame_t;

/**
 * @brief 回调函数类型，用于推送音频流至云端。\n
 * Callback function type, used to push audio streams to the cloud.
 */
typedef int (*FCA_AUDIO_IN_CALLBACK)(const fca_audio_frame_t* audio_frame);

/**
 * @brief 音频输入初始化函数。\n
 * Audio input initialization function.
 */
int fca_audio_in_init(void);

/**
 * @brief 音频输入设置参数函数。\n
 * Audio input setting parameter function.
 * @param index 输入，通道索引，0：主码流通道，1：子码流通道。\n
 * Input, channel index, 0: main stream channel, 1: sub stream channel.
 * @param config 输入，音频初始化参数。\n
 * Input, audio initialization parameters.
 */
int fca_audio_in_set_config(int index, fca_audio_config_t* config);

/**
 * @brief 获取当前通道参数。\n
 * Audio input initialization function.
 * @param index 输入，通道索引，0：主码流通道，1：子码流通道。\n
 * Input, channel index, 0: main stream channel, 1: sub stream channel.
 * @param config 输出，音频初始化参数。\n
 * Ouput, audio initialization parameters.
 * @note 在调用 fca_audio_in_init 之后再获取。\n
 * Note: Retrieve after calling fca_audio_in_init
 */
int fca_audio_in_get_config(int index, fca_audio_config_t* config);

/**
 * @brief 反初始化音频输入模块。\n
 * Uninitialize the audio input module.
 * @note 一般不需要调用此函数。如果需要处理比如OTA升级前回收内存等场景,请进一步沟通如何调用此函数.\n
 * Note that this function is generally not needed.
 * If you need to handle scenarios such as memory recycling before OTA upgrade, please further discuss how to call this function.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_audio_in_uninit(void);

/**
 * @brief 获取当前音频输入的数字增益。\n
 * Obtain the digital gain of the current audio input.
 * @param volume 输出，当前ai的数字增益。\n
 * Output, current AI digital gain.
 */
int fca_get_audio_input_volume(int* volume);

/**
 * @brief 设置当前音频输入的数字增益。\n
 * Set the digital gain of the current audio input.
 * @param volume 输入，设置当前ai的数字增益。\n
 * Input, set the digital gain of the current AI.
 */
int fca_set_audio_input_volume(int volume);

/**
 * @brief 获取重采样和编码后的音频数据回调函数。\n
 * Retrieve resampled and encoded audio data callback function.
 * @param index 输入，通道索引，0：主码流通道，1：子码流通道。\n
 * Input, channel index, 0: main stream channel, 1: sub stream channel.
 * @param FCA_AUDIO_CALLBACK 输入，推流回调函数。\n
 * Input, push stream callback function.
 */
int fca_audio_in_start_callback(int index, FCA_AUDIO_IN_CALLBACK cb);

/**
 * @brief 停止获取音频数据函数。\n
 * Stop obtaining audio data function.
 */
int fca_audio_in_stop_callback(int index);



/**
 * @brief 回声消除以及降噪相关参数。\n
 * Echo cancellation and noise reduction related parameters.
 */
typedef struct
{
    int aecns_enable; /**> enable aecns, aec_enable and ns_enable can be set only when aecns_enable is 1 */
    int aec_en; /**> enable AEC (0..1) */
    int ns_en; /**> enable denoise (0..1) */
    int aec_thr; /**> threshold for mute (0-32768) */
    int aec_scale; /**> coefficient of amplification for AEC, capture volume will be aec_scale*0.5x( value 0 is for 1x scale)(0-1024)*/
} fca_audio_aec_t;

/**
 * @brief 音频输出初始化函数\n
 * Audio output initialization function
 * @note 必须在调用任何音频输出api之前调用\n
 * Must be called before calling any audio output api.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_audio_out_init(void);

/**
 * @brief 音频输出参数设置模块\n
 * Audio output parameter setting module
 * @note 必须在调用fca_audio_out_init之后调用\n
 * Must be called after calling fca_audio_out_init.
 * @param config 输入，音频初始化参数。\n
 * Input, audio initialization parameters.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_audio_out_set_config(fca_audio_config_t* config);

/**
 * @brief 获取音频输出参数函数\n
 * Get audio output parameter function
 * @param config 输出，音频初始化参数。\n
 * Output, audio initialization parameters.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_audio_out_get_config(fca_audio_config_t* config);

/**
 * @brief 反初始化音频输出模块，在关闭所有音频功能后才能调用。\n
 * Uninitialize the audio output module, which can only be called after all audio functions are closed.
 * @note 一般不需要调用此函数。如果需要处理比如OTA升级前回收内存等场景,请进一步沟通如何调用此函数.\n
 * Note that this function is generally not needed.
 * If you need to handle scenarios such as memory recycling before OTA upgrade, please further discuss how to call this function.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_audio_out_uninit(void);

/**
 * @brief 获取设备播放音量\n
 * Get the device playback volume.
 * @param volume 输出，音量值，范围-90-20\n
 * Ouput, volume value, range -90-20.
 */
int fca_audio_out_get_volume(int* volume);

/**
 * @brief 设置设备播放音量\n
 * Set the device playback volume.
 * @param volume 输入，音量值，范围0-100\n
 * Input, volume value, range 0-100.
 */
int fca_audio_out_set_volume(int volume);

/**
 * @brief 播放一个pcm文件\n
 * Play a pcm file.
 * @param file_path 输入，pcm文件路径, 不能为空\n
 * Input, pcm file path. Cannot be NULL.
 * @note 阻塞式播放。音频文件的格式为16比特位深，单声道，8K采样率\n
 * Blocking playback. The format of the audio file is 16-bit deep, single-channel, 8K sampling rate.
 */
int fca_audio_out_play_file_block(const char* file_path);

/**
 * @brief 播放一个音频帧\n
 * Play an audio frame.
 * @param frame_data 输入, 一个指向音频帧数据的指针。\n
 * Input, a pointer to the audio frame data.
 * @param frame_len 输入，音频帧数据的长度，单位：byte\n
 * Input, the length of the audio frame data, unit: byte
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_audio_out_play_frame(unsigned char* frame_data, int frame_len);

/**
 * @brief 立刻停止音频播放\n
 * Immediately stop audio playback.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_audio_out_stop(void);

/**
 * @brief 获取回声消除参数函数。\n
 * Obtain echo cancellation parameter function.
 * * @param aec_config 输出, 一个指向回声消除参数结构体的指针。\n
 * Output, a pointer to the echo cancellation parameter structure.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_get_audio_aec_config(fca_audio_aec_t* aec_config);

/**
 * @brief 设置回声消除参数函数。\n
 * Set echo cancellation parameter function.
 * * @param aec_config 输入, 一个指向回声消除参数结构体的指针。\n
 * Input, a pointer to the echo cancellation parameter structure.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_set_audio_aec_config(fca_audio_aec_t* aec_config);



/**
 * @brief 声明一个哭声检测初始化回调函数类型。\n
 * Declare a cry detection initialization callback function type.
 */
typedef void (*FCA_AUDIO_CRYING_CALLBACK)(int score);

/**
 * @brief 打开声音检测功能\n
 * Turn on the decibel detection function.
 * @param onoff 输入，1: 打开声音检测，0: 关闭声音检测\n
 * Input, 1 means turn on the decibel detection, 0 means turn off the decibel detection.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_audio_in_decibel_detection_set_onoff(int onoff);

/**
 * @brief 设置声音侦测的灵敏度\n
 * Set the sensitivity of the decibel detection.
 * @param level 输入， 0：低灵敏度，1：高灵敏度\n
 * Input, 0: low sensitivity, 1: high sensitivity.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_audio_in_decibel_detection_set_sensitivity(int level);

/**
*@brief 获取当前的声音侦测结果\n
* Get the current decibel detection status.
* @note 可以循环调用此函数，实时获取声音侦测结果。仅在 @ref giec_audio_in_decibel_detection_set_onoff 打开后有效。\n
* Note that this function is valid only after @ref giec_audio_in_decibel_detection_set_onoff is turned on.
* @return 1：此刻声音达到@ref giec_audio_in_decibel_detection_set_sensitivity 设置的阈值，0：此刻声音低于阈值\n
* return 1 means the sound is above the threshold set by @ref giec_audio_in_decibel_detection_set_sensitivity, 0 means the sound is below the threshold.
*/
int fca_audio_in_get_decibel_status(void);

/**
 * @brief 打开哭声检测功能\n
 * Turn on the cry detection function.
 * @param onoff 输入， 1：打开哭声检测，0：关闭哭声检测\n
 * Input, 1 means turn on the cry detection, 0 means turn off the cry detection.
 * @note 必须调用 fca_audio_in_cry_detection_init 之后才可以调用。\n
 * Note FCa_audio_in_cry_detection_init must be called before it can be called.
 * @return 0表示成功，其他表示失败。\n
 * return 0 means success, other means failure.
 */
int fca_audio_in_cry_detection_set_onoff(int onoff);

/**
 * @brief 获取当前检测到的哭声结果\n
 * Get the current cry detection status.
 * @note 可以循环调用此函数，实时获取哭声检测结果。仅在 @ref giec_audio_in_cry_detection_set_onoff 打开后有效。\n
 * Note that this function is valid only after @ref giec_audio_in_cry_detection_set_onoff is turned on.
 * @return 1：此刻侦测到哭声，0：此刻没有哭声\n
 * return 1 means cry detected now, 0 means no cry now.
 */
int fca_audio_in_get_cry_status(void);

/**
 * @brief 初始化哭声检测函数\n
 * Initialize the crying detection function.
 * @param cb 输入， 一个回调函数，用来初始化哭声检测\n
 * Input, a callback function used to initialize crying detection.
 */
int fca_audio_in_cry_detection_init(FCA_AUDIO_CRYING_CALLBACK cb);

/**
 * @brief 反初始化哭声检测\n
 * Reverse initialization of crying detection.
 */
void fca_audio_in_cry_detection_uninit();





#ifdef __cplusplus
}
#endif

#endif