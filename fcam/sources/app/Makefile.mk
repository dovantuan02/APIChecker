ifdef TERMINAL
-include sources/app/interfaces/Makefile.mk
endif
-include sources/app/mqtt/Makefile.mk
-include sources/app/ota/Makefile.mk
-include sources/app/json/Makefile.mk
-include sources/app/button/Makefile.mk
-include sources/app/socket_helper/Makefile.mk

CXXFLAGS	+= -I./sources/app

VPATH += sources/app

OBJ += $(OBJ_DIR)/giec_params.o
OBJ += $(OBJ_DIR)/app.o
OBJ += $(OBJ_DIR)/app_config.o
OBJ += $(OBJ_DIR)/app_data.o
OBJ += $(OBJ_DIR)/app_bsp.o
OBJ += $(OBJ_DIR)/task_list.o

ifdef TERMINAL
OBJ += $(OBJ_DIR)/shell.o
OBJ += $(OBJ_DIR)/task_console.o
endif

OBJ += $(OBJ_DIR)/task_sys.o
OBJ += $(OBJ_DIR)/task_cloud.o
OBJ += $(OBJ_DIR)/task_network.o
OBJ += $(OBJ_DIR)/task_fw.o
OBJ += $(OBJ_DIR)/task_gpio.o
OBJ += $(OBJ_DIR)/task_ircut.o
OBJ += $(OBJ_DIR)/task_video.o
ifdef FEATURE_RTMP
OBJ += $(OBJ_DIR)/task_rtmp.o
endif

