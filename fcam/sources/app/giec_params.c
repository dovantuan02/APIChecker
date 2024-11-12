//This file is used to store the variables defined in the header files separately, not packaged in the library, which is convenient for modification based on actual needs.
#include "ak_common.h"
#include "ak_venc.h"

//***********************giec_api_audio.h***********************//
const char* G_AUDIO_OUT_FILE_A = "/etc/resource/audio/beep_A.pcm"; //ringtone
const char* G_AUDIO_OUT_FILE_B = "/etc/resource/audio/beep_B.pcm";
const char* G_AUDIO_OUT_FILE_C = "/etc/resource/audio/beep_C.pcm";
const char* G_AUDIO_OUT_FILE_S = "/etc/resource/audio/beep_siren.pcm"; //siren


//***********************giec_api_common.h***********************//
const char* G_SD_PATH = "/mnt/sdcard";


//***********************giec_api_gpio.h***********************//
const int GIEC_GPIO_KEY_RESET = 3;
const int GIEC_GPIO_KEY_CALL = 7;

const int GIEC_GPIO_LED_POLARITY = 0;
const int GIEC_GPIO_LED_RED = 5;
const int GIEC_GPIO_LED_GREEN = 9;
const int GIEC_GPIO_LED_WHITE = 17;

const int GIEC_GPIO_IRCUT_P = 8;
const int GIEC_GPIO_IRCUT_N = 4;
const int GIEC_GPIO_LED_IR = 48;
const char* GIEC_GPIO_LED_IR_NAME = "irled";
const int GIEC_GPIO_LED_WRITE = -1;

const int GIEC_GPIO_SPK_EN = -1;
const int GIEC_GPIO_CTL_VER = 2;

//***********************giec_api_ircut.h***********************//


//***********************giec_api_md.h***********************//
const int GIEC_MD_SEN_H = 81;
const int GIEC_MD_SEN_M = 33;
const int GIEC_MD_SEN_L = 0;


//***********************giec_api_ptz.h***********************//
const int G_PTZ_MAX_POS_H = 3755; //PTZ max steps in horizontal direction
const int G_PTZ_MAX_POS_V = 854; //PTZ max steps in vertical direction
const int G_PTZ_DEF_POS_V = 228; //PTZ default position in vertical direction
const int G_PTZ_SLEEPMODE_DEF_H = (3755 / 2); //PTZ horizontal position for privacy mask 
const int G_PTZ_SLEEPMODE_DEF_V = 228; //PTZ vertical position for privacy mask 
const int G_PTZ_SELFCHECK_DEF_H = (3755 / 2); //PTZ horizontal position after self-check done 
const int G_PTZ_SELFCHECK_DEF_V = 228; //PTZ vertical position after self-check done 


//***********************giec_api_svp.h***********************//
const char* G_SVP_FILE_PATH = "/usr/sbin/dt640_param.bin";
const int G_SVP_CHN_NUM = 16;
const int G_SVP_CHN_FPS = 25;

const int GIEC_SVP_HP = 2; //AK_SVP_MODEL_E
const int GIEC_SVP_TYPE = 2; //AK_SVP_TARGET_TYPE_E
const int GIEC_SVP_CLASSIFY_THRESHOLD = 700; //set svp classsify threshold, default is 700, range[400-900], the less, the more sensitive, but the less accurate
const int GIEC_SVP_IOU_THRESHOLD = 3; //set the IoU threshold, range [3-10], default is 3


//***********************giec_api_sys.h***********************//
const char* G_SBOOT_FILE = "/etc/config/g_sboot_config";


//***********************giec_api_video.h***********************//
//VIDEO
const int G_VI_MAX_WIDTH_SUB = 1280;
const int G_VI_MAX_HEIGHT_SUB = 720;

/**
 * \brief ISP config file path
 */
const char* G_ISP_CONF_PATH = "/etc/config/isp/isp_sc3336_mipi_2lane_h322.conf";

//QRCODE
const char* GIEC_QRCODE_IMAGE_PATH = "/tmp";
const int GIEC_QRCODE_IMAGE_W = 1280;
const int GIEC_QRCODE_IMAGE_H = 720;

//***********************giec_api_osd.h***********************//
//color for osd, range [0,15]
const int G_OSD_FRONT_COLOR = 1;
const int G_OSD_BG_COLOR = 0;

/**
 * \brief OSD font file path
 */
const char* G_OSD_FONT_FILE = "/etc/resource/font/Font_MS-Gothic_Bold_Unicode_48.bin";
const int G_OSD_FONT_SIZE = 64;
const int G_OSD_CUS_STR_MAX_LEN = 31;


//***********************giec_api_onvif.h***********************//


const unsigned int G_ONVIF_VIDEO_RES_W_MAIN = 2304; //must same as g_resolutions[g_main_res].width
const unsigned int G_ONVIF_VIDEO_RES_H_MAIN = 1296; //must same as g_resolutions[g_main_res].height
const unsigned int G_ONVIF_VIDEO_RES_W_SUB = 1280; //must same as g_resolutions[g_sub_res].width
const unsigned int G_ONVIF_VIDEO_RES_H_SUB = 720; //must same as g_resolutions[g_sub_res].height
const unsigned int G_ONVIF_VIDEO_FPS_MAIN = 25; //must same as g_vi_fps
const unsigned int G_ONVIF_VIDEO_FPS_SUB = 25; //must same as g_vi_fps
const unsigned int G_ONVIF_VIDEO_BITRATE_MAIN = 2048; //KB
const unsigned int G_ONVIF_VIDEO_BITRATE_SUB = 512; //KB
const unsigned int G_ONVIF_VIDEO_QUALITY_MAIN = 2;
const unsigned int G_ONVIF_VIDEO_QUALITY_SUB = 2;
const unsigned int G_ONVIF_VIDEO_ENC_TYPE_MAIN = 2; //0:H.264, 1:JPEG, 2:H.265
const unsigned int G_ONVIF_VIDEO_ENC_TYPE_SUB = 0; //0:H.264, 1:JPEG, 2:H.265
const unsigned int G_ONVIF_AUDIO_SAMPLE_RATE = 8000;
const char* G_ONVIF_CONFIG_FILE_NET = "/etc/config/network.ini"; //rw
const char* G_ONVIF_CONFIG_FILE_VCOLOR = "/etc/config/videocolor.ini"; //rw
const char* G_ONVIF_CONFIG_FILE_VIDEO = "/etc/config/videoprofile.ini"; //rw
const unsigned int G_ONVIF_PRESET_MAX_NUM = 6;
const char* G_ONVIF_CONFIG_FILE_PRESET = "/etc/config/g_onvif_preset.ini"; //rw
