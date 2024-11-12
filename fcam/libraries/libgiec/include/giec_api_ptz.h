#ifndef GIEC_API_PTZ_H
#define GIEC_API_PTZ_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief 最大预置点数量，固定为6个。不可修改。\n
 * The maximum number of preset points, which is fixed to 6. It cannot be modified.
 */
#define G_PTZ_MAX_PRESET_POINT_CNT 6

/**
 * @brief 收藏点结构体\n
 * The structure of preset point.
 * @note 当前只支持h,v 两个参数, z参数暂未支持\n
 * Only h,v two parameters are supported, z parameter is not supported yet.
 */
typedef struct GIEC_PTZ_PRESET_S {
    int h; //pan step
    int v; //tilt step
    int z; //zoom
} GIEC_PTZ_PRESET;

/**
 * @brief PTZ电机水平方向的总步数\n
 * The total steps of the horizontal PTZ motor.
 * @note 该变量被库使用，必须与电机驱动匹配，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, and must match the motor driver, which is configured in the giec_param.c file, do not modify it.
 */
extern const int G_PTZ_MAX_POS_H;

/**
 * @brief PTZ电机竖直方向的总步数\n
 * The total steps of the vertical PTZ motor.
 * @note 该变量被库使用，必须与电机驱动匹配，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, and must match the motor driver, which is configured in the giec_param.c file, do not modify it.
 */
extern const int G_PTZ_MAX_POS_V;

/**
 * @brief PTZ电机竖直方向的默认位置\n
 * The default position of the vertical PTZ motor.
 * @note 该变量被库使用，必须与电机驱动匹配，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, and must match the motor driver, which is configured in the giec_param.c file, do not modify it.
 */
extern const int G_PTZ_DEF_POS_V;

/**
 * @brief 隐私遮挡水平方向位置\n
 * The horizontal position of sleep mode(aka. privacy mode).
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, which is configured in the giec_param.c file, do not modify it.
 */
extern const int G_PTZ_SLEEPMODE_DEF_H;

/**
 * @brief 隐私遮挡竖直方向位置\n
 * The vertical position of sleep mode(aka. privacy mode).
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, which is configured in the giec_param.c file, do not modify it.
 */
extern const int G_PTZ_SLEEPMODE_DEF_V;

/**
 * @brief 自检后归位的默认水平位置\n
 * The default horizontal position after self-check.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, which is configured in the giec_param.c file, do not modify it.
 */
extern const int G_PTZ_SELFCHECK_DEF_H;

/**
 * @brief 自检后归位的默认竖直位置\n
 * The default vertical position after self-check.
 * @note 该变量被库使用，在giec_param.c中配置为实际的值，请勿修改。\n
 * This variable is used by the library, which is configured in the giec_param.c file, do not modify it.
 */
extern const int G_PTZ_SELFCHECK_DEF_V;

/**
 * @brief PTZ调度模式\n
 * The PTZ scheduling type.
 * @note 按优先级从高到低排序，序号从0开始连续递增。该变量被库使用，请勿修改。\n
 * The priority is sorted from high to low, starts from 0 and increases continuously. 
 * This variable is used by the library, do not modify it.
 */
enum GIEC_PTZ_SCH_TYPE {
    GIEC_PTZ_SCH_TYPE_EXIT = 0,
    GIEC_PTZ_SCH_TYPE_UNINIT,
    GIEC_PTZ_SCH_TYPE_SLEEPMODE,
    GIEC_PTZ_SCH_TYPE_SELFCHECK,
    GIEC_PTZ_SCH_TYPE_DIRECTION,
    GIEC_PTZ_SCH_TYPE_POSITION,
    GIEC_PTZ_SCH_TYPE_REALPOSITION,
    GIEC_PTZ_SCH_TYPE_TRACK_PATROL,
    GIEC_PTZ_SCH_TYPE_IDLE,
    GIEC_PTZ_SCH_TYPE_MAX
};

/**
 * @brief 设置巡航时段\n
 * Set the time period for patrol.
 * @param start_hour 输入，开始时间的小时，范围：0 ~ 23\n
 * input, start time hour, range: 0 ~ 23
 * @param start_minute 输入，开始时间的分钟，范围：0 ~ 59\n
 * input, start time minute, range: 0 ~ 59
 * @param end_hour 输入，结束时间的小时，范围：0 ~ 23\n
 * input, end time hour, range: 0 ~ 23
 * @param end_minute 输入，结束时间的分钟，范围：0 ~ 59\n
 * input, end time minute, range: 0 ~ 59
 * @note 设备开机后，首次打开巡航前，需要调用此API先设置巡航时段\n
 * Before enabling patrol for the first time after the device is powered on, you need to call this API to set the time period for patrol.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_ptz_patrol_set_time_period(int start_hour, int start_minute, int end_hour, int end_minute);

/**
 * @brief 设置巡航到位后，停留在巡航点的时长\n
 * Set the time period that PTZ stays at the patrol point after reaching it.
 * @param stay_time 输入，停留时长，单位：秒，范围：1 ~ 60\n
 * input, stay time, unit: second, range: 1 ~ 60
 * @note 开机后首次打开巡航前，可以调用此API先设置停留时长，如果不设置，默认停留时长为10秒\n
 * Before enabling patrol for the first time after the device is powered on, you need to call this API to set the time period that PTZ stays at the patrol point.
 * If not set, the default stay time is 10 seconds.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_ptz_patrol_set_stay_time(int stay_time);

/**
 * @brief 设置巡航模式\n
 * Set the patrol mode.
 * @param pmode 输入，0:全景巡航，1: 收藏点往复巡航，2：无限位的收藏点顺时针巡航，3：无限位的收藏点逆时针巡航\n
 * input, 0:panorama round patrol 1:preset point round patrol, 2:preset point clockwise patrol, 3:preset point counterclockwise patrol
 * @note 当前只支持0, 1。开机后首次打开巡航前，需要调用此API先设置巡航模式\n
 * Current version only supports 0, 1. Before enabling patrol for the first time after the device is powered on, you need to call this API to set the patrol mode.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_ptz_patrol_set_pmode(int pmode);

/**
 * @brief 设置巡航时间模式\n
 * Set the patrol time mode.
 * @param tmode 输入， 0: 全天巡航 1: 单次巡航 2: 按 @ref giec_ptz_patrol_set_time_period 所设定的时间段进行自定义巡航\n
 * input, 0: all day patrol, 1: one-time patrol, 2: custom patrol based on @ref giec_ptz_patrol_set_time_period
 * @note 开机后首次打开巡航前，需要调用此API先设置巡航时间模式\n
 * Before enabling patrol for the first time after the device is powered on, you need to call this API to set the patrol time mode.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_ptz_patrol_set_tmode(int tmode);

/**
 * @brief 设置巡航点\n
 * Set the patrol points.
 * @param cnt 输入，收藏点数组的个数，范围：2 ~ @ref G_PTZ_MAX_PRESET_POINT_CNT\n
 * input, the number of preset points in the array, range: 2 ~ @ref G_PTZ_MAX_PRESET_POINT_CNT
 * @param list 输入，收藏点数组\n
 * input, preset point array
 * @note 开机后首次打开巡航前，需要调用此API先设置巡航点。必须在停止巡航的情况下调用此API设置巡航点，否则设置无效。\n
 * Before enabling patrol for the first time after the device is powered on, you need to call this API to set the patrol points.
 * You must call this API to set the patrol points while stopping patrol, otherwise the setting is invalid.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int giec_ptz_patrol_set_preset_point(int cnt, GIEC_PTZ_PRESET* list);


/**
 * @brief 函数 @ref giec_ptz_init 的参数的类型\n
 * Parameter type of function @ref giec_ptz_init\n
 * @note giec_ptz_get_saved_pos_cb: 函数指针，库内部会将2个int类型变量的指针作为参数调用该函数，获取保存的位置坐标\n
 * giec_ptz_set_saved_pos_cb: 函数指针，库内部会将PTZ当前位置作为参数调用该函数。用于保存当前位置坐标\n
 * giec_ptz_get_saved_pos_cb: function pointer, the library will call this function with a pointer to two int type variables as parameters to get the saved position coordinates.\n
 * giec_ptz_set_saved_pos_cb: function pointer, the library will call this function with the current PTZ position as a parameter to save the current position coordinates.
 */
typedef struct FCA_PTZ_CB_PARAM_S {
    int (*giec_ptz_get_saved_pos_cb)(int* h, int* v); //从文件中获取保存的位置坐标,一般是用户键控位置
    int (*giec_ptz_set_saved_pos_cb)(int h, int v); //保存位置坐标到文件，一般是用户键控位置
} FCA_PTZ_CB_PARAM;

/**
 * @brief 隐私模式类型\n
 * Type of sleep mode.
 * @note GIEC_PTZ_SLEEPMODE_OFF： 退出隐私模式\n
 * GIEC_PTZ_SLEEPMODE_CURR_POS： 进入隐私模式，电机保持在当前位置\n
 * GIEC_PTZ_SLEEPMODE_DEF_POS： 进入隐私模式，电机转动到物理遮蔽位置\n
 * GIEC_PTZ_SLEEPMODE_OFF: exit sleep mode(aka. privacy mode)\n
 * GIEC_PTZ_SLEEPMODE_CURR_POS: enter sleep mode(aka. privacy mode), ptz keeps current position\n
 * GIEC_PTZ_SLEEPMODE_DEF_POS: enter sleep mode(aka. privacy mode), ptz turns to sleep mode position
 */
enum FCA_PTZ_SLEEPMODE {
    GIEC_PTZ_SLEEPMODE_OFF = 0,
    GIEC_PTZ_SLEEPMODE_CURR_POS,
    GIEC_PTZ_SLEEPMODE_DEF_POS
};

/**
 * @brief 自检类型\n
 * Type of self-check.
 * @note GIEC_PTZ_SELFCHECK_OFF： 退出自检\n
 * GIEC_PTZ_SELFCHECK_CURR_POS： 自检结束后回到当前位置\n
 * GIEC_PTZ_SELFCHECK_DEF_POS： 自检结束后回到出厂默认位置\n
 * GIEC_PTZ_SELFCHECK_SAVED_POS： 自检结束后回到保存的点(开机自检)\n
 * GIEC_PTZ_SELFCHECK_OFF: exit self-check\n
 * GIEC_PTZ_SELFCHECK_CURR_POS: self-check ends, ptz turns to current position\n
 * GIEC_PTZ_SELFCHECK_DEF_POS: self-check ends, ptz turns to factory default position\n
 * GIEC_PTZ_SELFCHECK_SAVED_POS: self-check ends, ptz turns to saved position(power on self-check)
 */
enum FCA_PTZ_SELFCHECK {
    GIEC_PTZ_SELFCHECK_OFF = 0,
    GIEC_PTZ_SELFCHECK_CURR_POS,
    GIEC_PTZ_SELFCHECK_DEF_POS,
    GIEC_PTZ_SELFCHECK_SAVED_POS
};

/**
 * @brief 键控方向\n
 * Direction of ptz
 * @note 当前只支持UP,DOWN,LEFT,RIGHT,STOP这5种方向，其他方向暂未支持\n
 * Only UP,DOWN,LEFT,RIGHT,STOP are supported, other directions are not supported yet.
 */
enum FCA_PTZ_DIRECTION {
    GIEC_PTZ_DIRECTION_UP = 0,
    GIEC_PTZ_DIRECTION_DOWN,
    GIEC_PTZ_DIRECTION_LEFT,
    GIEC_PTZ_DIRECTION_RIGHT,
    GIEC_PTZ_DIRECTION_UPLEFT, //暂未支持 not supported yet
    GIEC_PTZ_DIRECTION_UPRIGHT, //暂未支持 not supported yet
    GIEC_PTZ_DIRECTION_DOWNLEFT, //暂未支持 not supported yet
    GIEC_PTZ_DIRECTION_DOWNRIGHT, //暂未支持 not supported yet
    GIEC_PTZ_DIRECTION_STOP
};

/**
 * @brief PTZ速度\n
 * Speed of ptz
 * @note 当前未支持配置速度\n
 * Not supported yet.
 */
enum FCA_PTZ_SPEED {
    TURN_SPEED_LOW = 5000,  //25HZ
    TURN_SPEED_MID = 3125,  //40Hz
    TURN_SPEED_HIGH = 1250,  //100HZ
};

/**
 * @brief PTZ电机类型\n
 * Type of ptz motor.
 */
typedef enum
{
    FCA_MOTOR_PAN = 0,
    FCA_MOTOR_TILT,
} FCA_MOTOR_TYPE;

/**
 * @brief 视频放大缩小\n
 * Video zoom in and out.
 */
typedef enum {
    ZOOM_IN,  // Zoom in
    ZOOM_OUT  // Zoom out
} ZOOM_DIRECTION;

/**
 * @brief 初始化PTZ功能，开启电机调度线程\n
 * Initialize PTZ function, start motor scheduling thread.
 * @note 该函数必须在所有涉及PTZ的功能初始化之前调用，只可调用一次。\n
 * Must be called before all functions that involve PTZ are initialized, can only be called once.
 * @param ptz_cb_param 输入，PTZ初始化参数，一个 @ref GIEC_PTZ_CB_PARAM 类型变量的指针\n
 * Input, PTZ initialization parameter, a pointer to a @ref GIEC_PTZ_CB_PARAM type variable.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_init(FCA_PTZ_CB_PARAM* ptz_cb_param);

/**
 * @brief 反初始化PTZ功能，关闭电机调度线程，释放资源\n
 * Uninitialize PTZ function, stop motor scheduling thread, release resources.
 * @note 阻塞,只可调用一次，必须在所有PTZ操作停止后调用。\n
 * Blocking, can only be called once, must be called after all PTZ operations are stopped.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_uninit_block(void);

/**
 * @brief 控制PTZ进入隐私模式\n
 * Let PTZ enter sleep mode(aka. privacy mode).
 * @param mode 输入，参考 @ref GIEC_PTZ_SLEEPMODE 定义的模式\n
 * Input, refer to the definition of @ref GIEC_PTZ_SLEEPMODE for the mode.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_sleepmode(enum FCA_PTZ_SLEEPMODE mode);

/**
 * @brief 控制PTZ进行自检\n
 * Let PTZ perform self-check.
 * @param mode 输入，参考 @ref GIEC_PTZ_SELFCHECK 定义的模式\n
 * Input, refer to the definition of @ref GIEC_PTZ_SELFCHECK for the mode.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_selfcheck(enum FCA_PTZ_SELFCHECK mode);

/**
 * @brief 控制PTZ转动指定方向\n
 * Let PTZ turn to the specified direction.
 * @param direct 输入，参考 @ref GIEC_PTZ_DIRECTION 定义的方向\n
 * Input, refer to the definition of @ref GIEC_PTZ_DIRECTION for the direction.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_go_direction(enum FCA_PTZ_DIRECTION direction);

/**
 * @brief 控制PTZ转动到指定位置\n
 * Let PTZ turn to the specified position.
 * @param h 输入，水平方向位置，范围：0 ~ @ref G_PTZ_MAX_POS_H\n
 * input, horizontal position, range: 0 ~ @ref G_PTZ_MAX_POS_H
 * @param v 输入，竖直方向位置，范围：0 ~ @ref G_PTZ_MAX_POS_V\n
 * input, vertical position, range: 0 ~ @ref G_PTZ_MAX_POS_V
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_go_position(int h, int v);

/**
 * @brief 获取PTZ当前位置坐标\n
 * Get the current position of PTZ.
 * @param h 输出，水平方向坐标，范围：0 ~ @ref G_PTZ_MAX_POS_H\n
 * output, horizontal position, range: 0 ~ @ref G_PTZ_MAX_POS_H
 * @param v 输出，竖直方向坐标，范围：0 ~ @ref G_PTZ_MAX_POS_V\n
 * output, vertical position, range: 0 ~ @ref G_PTZ_MAX_POS_V
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_get_position(int* h, int* v);

/**
 * @brief 使能/关闭移动追踪\n
 * Enable/disable motion tracking.
 * @param onoff 输入，0：关闭，1：使能\n
 * input, 0: disable, 1: enable
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_set_track_onoff(int onoff);

/**
 * @brief 使能/关闭巡航\n
 * Enable/disable patrol.
 * @param onoff 输入， 0：关闭，1：使能\n
 * input, 0: disable, 1: enable
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_set_patrol_onoff(int onoff);

/**
 * @brief 设置PTZ水平方向速度\n
 * Set the speed of PTZ in horizontal direction.
 * @param speed 输入，参考 @ref GIEC_PTZ_SPEED 定义的速度\n
 * input, refer to the definition of @ref GIEC_PTZ_SPEED for the speed.
 * @note 当前版本暂未实现速度控制功能\n
 * Current version does not implement speed control function.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_set_speed_h(enum FCA_PTZ_SPEED speed);

/**
 * @brief 设置PTZ竖直方向速度\n
 * Set the speed of PTZ in vertical direction.
 * @param speed 输入，参考 @ref GIEC_PTZ_SPEED 定义的速度\n
 * input, refer to the definition of @ref GIEC_PTZ_SPEED for the speed.
 * @note 当前版本暂未实现速度控制功能\n
 * Current version does not implement speed control function.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_set_speed_v(enum FCA_PTZ_SPEED speed);

/**
 * @brief 设置PTZ竖直方向的相对步数\n
 * Set the relative number of steps in the vertical direction of PTZ.
 * @param step 输入，走相对步数: 向左/向上定为负数, 向右/向下定为正数\n
 * Input, take relative steps: set left/up as negative number, set right/down as positive number.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_set_step_v(int step);

/**
 * @brief 设置PTZ水平方向的相对步数\n
 * Set the relative number of steps in the horizontal direction of PTZ.
 * @param step 输入，走相对步数: 向左/向上定为负数, 向右/向下定为正数\n
 * Input, take relative steps: set left/up as negative number, set right/down as positive number.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_set_step_h(int step);

/**
 * @brief 获取电机各个方向的最大步数\n
 * Set the relative number of steps in the horizontal direction of PTZ.
 * @param type 输出，电机方向类型，水平还是垂直电机\n
 * Output, motor direction type, horizontal or vertical motor.
 * @param max_steps 输出，电机允许转动最大步数\n
 * Output, maximum number of steps allowed for motor rotation.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_get_motor_max_steps(FCA_MOTOR_TYPE type, int* max_steps);



/**
 * @brief 电子变焦放大函数，使用前必须先初始化视频编码器。\n
 * The electronic zoom function requires the initialization of the video encoder before use.
 * @param index 输入，0：主码流，1：子码流\n
 * Input, 0: main stream, 1: sub stream.
 * @param x,y 输入，坐标，要放大矩形框的左上角坐标\n
 * Input, coordinates, to enlarge the top left corner coordinates of the rectangular box.
 * @param multiple 输入，放大倍数，最大支持两倍，范围1-2\n
 * Input, Magnification factor, supports up to twice, range 1-2.
  * @param speed 输入，执行步数，1为立即执行\n
 * Input, Execution steps, 1 for immediate execution.
 * @return 0表示成功，其他表示失败\n
 * return 0 means success, other means failure.
 */
int fca_ptz_zoom_out(int index, int x, int y, float multiple, int speed);

#ifdef __cplusplus
}
#endif

#endif /* GIEC_API_PTZ_H */
