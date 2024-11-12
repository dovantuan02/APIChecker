#ifndef _AK_MUX_H_
#define _AK_MUX_H_

#include "ak_common.h"
#include "ak_common_audio.h"
#include "ak_common_video.h"
#include "ak_venc.h"

enum ak_mux_error_type
{
    ERROR_MUX_OPEN_LIB_ERROR = (MODULE_ID_MUX << 24) + 0,
    ERROR_MUX_CLOSE_LIB_ERROR,
    ERROR_MUX_GET_LIB_INFO_ERROR,
    ERROR_MUX_START_LIB_ERROR,
    ERROR_MUX_STOP_LIB_ERROR,
    ERROR_MUX_OPEN_TOO_MANY,
    ERROR_MUX_USER_NULL,
    ERROR_MUX_SET_AUDIO_INPUT_ERROR,
    ERROR_MUX_SET_VIDEO_INPUT_ERROR,
    ERROR_MUX_ADD_ERROR,
    ERROR_MUX_ADD_VIDEO_FIRST
};

enum ak_mux_type
{
    MUX_TYPE_AVI,
    MUX_TYPE_MP4,// 3GP
    MUX_TYPE_NUM
};

enum ak_mux_data_dest
{
    MUX_DATA_TO_UNKNOWN = 0x00,
    MUX_DATA_TO_LOCAL_FILE,
    MUX_DATA_TO_INTERNET
};

enum ak_mux_status
{
    AK_MUX_STATUS_OPEN,
    AK_MUX_STATUS_STOP,
    AK_MUX_STATUS_DOING,
    AK_MUX_STATUS_SYSERR,
    AK_MUX_STATUS_MEMFULL,
    AK_MUX_STATUS_SYNERR,
    AK_MUX_STATUS_WAITING,
    AK_MUX_STATUS_PAUSE,
    AK_MUX_STATUS_NUM,
};

struct ak_mux_start_param
{
    char *file_path;
    int i_buff_record;
    char *pc_buff_record;
    int i_buff_index;
    char *pc_buff_index;
};

struct ak_mux_input
{
    /* video */
    enum encode_output_type video_type;
    unsigned short width;
    unsigned short height;
    int file_fps;                    //save file fps

    /* audio */
    unsigned char capture_audio;
    enum ak_audio_type audio_type;
    struct ak_audio_data_attr audio_attr;
    int frame_interval;

    /* mux */
    enum ak_mux_type media_rec_type;
    enum ak_mux_data_dest data_dest;
    unsigned int record_second;
};

struct mux_fileinfo                                                             //录像修复接口的文件信息返回
{
    unsigned long total_ms ;                                                    //修复后的录像时长
};

#define MUX_NODE_AVI_IDX 0x1

enum MUX_NODE {                                                                 //录像写入的文件类型
    MUX_NODE_RECORD = 0x00,
    MUX_NODE_IDX,
    MUX_NODE_MP4_MOOV,
    MUX_NODE_MP4_STBL,
    MUX_NODE_NUM
};

/**
 * ak_mux_get_version - get mux version
 * return: version string
 * notes:
 */
const char* ak_mux_get_version(void);

/**
 * ak_mux_open - open mux lib
 * @mux_param[IN]: mux input param
 * @mux_handle_id[OUT]: mux handle id
 * return: 0 success, other failed
 */
int ak_mux_open(const struct ak_mux_input *mux_param, int *mux_handle_id);

/**
 * ak_mux_start - mux start
 * @mux_handle_id[IN]: opened mux handle id
 * @start_param[IN]: save file pointer
 * return: 0 success, other failed
 */
int ak_mux_start(int mux_handle_id, struct ak_mux_start_param *start_param);

/**
 * ak_mux_add_audio - add audio to mux
 * @mux_handle_id[IN]: opened mux handle id
 * @audio[IN]: audio stream info
 * return: 0 success, other failed
 */
int ak_mux_add_audio(int mux_handle_id, const struct audio_stream *audio);

/**
 * ak_mux_add_video - add video to mux
 * @mux_handle_id[IN]: opened mux handle id
 * @video[IN]: video stream info
 * return: 0 success, other failed
 */
int ak_mux_add_video(int mux_handle_id, const struct video_stream *video);

/**
 * ak_mux_stop - mux stop
 * @mux_handle_id[IN]: opened mux handle id
 * return: 0 success, other failed
 */
int ak_mux_stop(int mux_handle_id);

/**
 * ak_mux_close - close mux module
 * @mux_handle_id[IN]: opened mux handle
 * return: 0 success, other failed
 */
int ak_mux_close(int mux_handle_id);

/**
 * ak_mux_print_runtime_status - print runtime debug information
 * @mux_handle_id[IN]: mux handle id
 * return: 0 success, other failed
 * notes:
 */
int ak_mux_print_runtime_status(int mux_handle_id);

/**
 * ak_mux_fix_file - release mux lib resource
 * @pFILE_record[IN]: record file pointer
 * @pFILE_index[IN]:  avi index file pointer
 * @pFILE_moov[IN]:  mp4 moov file pointer
 * @pFILE_stbl[IN]:  mp4 stbl file pointer
 * @mux_type[IN]:  MUX_TYPE_AVI | MUX_TYPE_MP4
 * @p_mux_fileinfo[OUT]:  return file info
 * return: 0 success, other failed
 */
int ak_mux_fix_file(FILE *pFILE_record, FILE *pFILE_index, FILE *pFILE_moov, FILE *pFILE_stbl, enum ak_mux_type mux_type, struct mux_fileinfo *p_mux_fileinfo );

/**
 * ak_mux_pause - pause mux audio video to file
 * @mux_handle_id[IN]:  mux handle id
 * return: 0 success, other failed
 */
int ak_mux_pause(int mux_handle_id);

/**
 * ak_mux_continue - continue mux audio video to file
 * @mux_handle_id[IN]:  mux handle id
 * return: 0 success, other failed
 */
int ak_mux_continue(int mux_handle_id);

/**
 * ak_mux_get_status - get mux lib status
 * @mux_handle_id[IN]: mux handle id
 * @p_mux_status[OUT]: status result. Can't be NULL.
 * return: 0 success, other failed
 */
int ak_mux_get_status(int mux_handle_id, enum ak_mux_status *p_mux_status );

#endif
