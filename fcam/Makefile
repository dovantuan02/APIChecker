###############################################################################
# author: ThanNT
# date: 6/1/2017
###############################################################################

-include config.mk
-include libraries/Makefile.mk
-include sources/Makefile.mk

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

IP_SERVER=192.168.1.80

# Compiler path --====================================================================================
CROSS_COMPILE=/arm-linux-
# --==================================================================================================

CXX	  =$(CROSS_COMPILE)g++
CC	  =$(CROSS_COMPILE)gcc
AR	  =$(CROSS_COMPILE)ar
STRIP =$(CROSS_COMPILE)strip
OBJNM  =$(CROSS_COMPILE)nm

# Release build option
ifdef RELEASE
	ifeq ($(RELEASE), 1)
		OBJ_DIR		= _build_$(VENDOR_NAME)_$(FW_PRODUCT)-release-watchdog
		NAME_MODULE	= fcam-$(FW_PRODUCT)-release-watchdog
	else
		OBJ_DIR		= _build_$(VENDOR_NAME)_$(FW_PRODUCT)-release-nowatchdog
		NAME_MODULE	= fcam-$(FW_PRODUCT)-release-nowatchdog
	endif
else
	OBJ_DIR		= _build_$(VENDOR_NAME)_$(FW_PRODUCT)-debug
	NAME_MODULE	= APIChecker
endif

# Library option
LDFLAGS	+= -Wl,-Map=$(OBJ_DIR)/$(NAME_MODULE).map

LDLIBS	+=\
		-lpthread			\
		-lrt				\
		-lm					

# CXX compiler option
ifdef FEATURE_RTMP
GENERAL_FLAGS += -DFEATURE_RTMP
endif

ifdef FEATURE_AI
GENERAL_FLAGS += -DFEATURE_AI
endif

ifdef VOICE_GUIDE
GENERAL_FLAGS += -DVOICE_GUIDE
endif

ifdef FEATURE_RECORD
GENERAL_FLAGS += -DFEATURE_RECORD
endif

ifdef FEATURE_BBCRY
GENERAL_FLAGS += -DFEATURE_BBCRY
endif

ifdef TERMINAL
GENERAL_FLAGS += -DTERMINAL
endif

#|---------------------------------------------------------------------------------------------------|
#| OPTIMIZE LEVELS                                                                                   |
#|------------|----------------------------------|--------------|---------|------------|-------------|
#|   option   | optimization levels              |execution time|code size|memory usage|complile time|
#|------------|----------------------------------|--------------|---------|------------|-------------|
#|   -O0      | compilation time                 |     (+)      |   (+)   |     (-)    |    (-)      |
#| -O1 || -O  | code size && execution time      |     (-)      |   (-)   |     (+)    |    (+)      |
#|   -O2      | more code size && execution time |     (--)     |         |     (+)    |    (++)     |
#|   -O3      | more code size && execution time |     (---)    |         |     (+)    |    (+++)    |
#|   -Os      | code size                        |              |   (--)  |            |    (++)     |
#|  -Ofast    | O3 with none math cals           |     (---)    |         |     (+)    |    (+++)    |
#|------------|----------------------------------|--------------|---------|------------|-------------|
OPTIMIZE_OPTION	=	-g -s -O3
WARNNING_OPTION	+=	-Werror -W -Wno-missing-field-initializers -Wextra

ifdef RELEASE
	ifeq ($(RELEASE), 1)
		GENERAL_FLAGS += -DRELEASE=1
		WARNNING_OPTION =
	else
		GENERAL_FLAGS += -DRELEASE=0
	endif
endif

CXXFLAGS	+=\
		$(OPTIMIZE_OPTION)	\
		$(WARNNING_OPTION)	\
		-Wall				\
		-Wno-deprecated-declarations	\
		-Wno-psabi	\
		-pipe				\
		-ggdb	\
		$(GENERAL_FLAGS)
		
all: create $(OBJ_DIR)/$(NAME_MODULE) size

upx: $(OBJ_DIR)/$(NAME_MODULE)
	@echo upx start file: $(OBJ_DIR)/$(NAME_MODULE)
	$(ROOT_DIR)/tools/upx --best $(OBJ_DIR)/$(NAME_MODULE)

create:
	@echo mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)

	rm -rf $(OBJ_DIR)/$(NAME_MODULE)

$(OBJ_DIR)/%.o: %.cpp
	@echo CXX $<
	@$(CXX) -c -o $@ $< $(CXXFLAGS) -std=c++17 $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@echo CC $<
	@$(CC) -c -o $@ $< $(CXXFLAGS) $(LDFLAGS)

$(OBJ_DIR)/$(NAME_MODULE): $(OBJ)
	@echo ---------- START LINK PROJECT ----------
	@echo "\n\n"
	@echo LIB $(LDLIBS) "\n\n"audio_stream
	@echo $(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS)
	@$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

size: $(OBJ_DIR)/$(NAME_MODULE)
	@size $(OBJ_DIR)/$(NAME_MODULE)

sym: $(OBJ_DIR)/$(NAME_MODULE)
	# $(OBJNM) --size-sort --print-size $(OBJ_DIR)/$(NAME_MODULE) > sym.txt
	# $(OBJNM) -C --line-numbers --size-sort  --print-size $(OBJ_DIR)/$(NAME_MODULE) > sym.txt
	$(OBJNM) -C -l $(OBJ_DIR)/$(NAME_MODULE) | grep "gw_task_webrtc_entry" > sym_func.txt

.PHONY: copy
copy: $(OBJ_DIR)/$(NAME_MODULE)
# copy bin file to another folder (e.g. sudo cp $(OBJ_DIR)/$(NAME_MODULE) /mnt/hgfs/shareFd)

.PHONY: scp
scp:
# e.g. scp $(OBJ_DIR)/$(NAME_MODULE) huynt@192.168.1.55:/home/huynt/Workspace/FPT/Github/Camera/vvtk_nfs

.PHONY: clean
clean: 
	@echo rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)

.PHONY: strip
strip:
	$(STRIP) $(OBJ_DIR)/$(NAME_MODULE)

show_variables:
	@echo "LDFLAGS: $(LDFLAGS), LDLIBS: $(LDLIBS)"
	@echo "CXXFLAGS: $(CXXFLAGS)"
	@echo "ROOT_DIR: $(ROOT_DIR)"

show-build:
ifdef RELEASE
	@echo "\033[1;32m----------------- Project is build Release -----------------\033[0m"
else
	@echo "\033[1;31m----------------- Project is build Debug -----------------\033[0m"
endif

agent-cp:
	cp -r $(OBJ_DIR)/$(NAME_MODULE) $(FCA_AGENT_DIR)/bin/fcam

check:
ifneq ($(BUILD_ERROR), '')
	$(error error is $(BUILD_ERROR))
endif

clean-lib:
	rm -rf $(ROOT_DIR)/rootfs/fpt_lib.sqsh4

build-lib:
	echo "start build fpt_lib"
	cd $(ROOT_DIR)/rootfs; \
	./create_fpt_lib.sh;

clean-agent:
	rm -rf $(ROOT_DIR)/rootfs/root_app.sqsh4

build-agent: check agent-cp generate_config generate_script #copy

	@echo "\033[1;32mBuild model [$(FW_MODEL)]\033[0m"

# @mkdir -p $(FCA_DEPLOY_AGENT_DIR)

	$(eval FW_NAME_TMP := $(shell $(ROOT_DIR)/scripts/auto_gen.sh $(FCA_AGENT_DIR)/version  $(FCA_NAME) $(FW_MODEL) $(FW_NAME) $(VERSION) $(DATE_CURR) $(BUILD_TIME)))
	
	cd $(ROOT_DIR)/rootfs; \
	./create_app.sh;

	@echo "\033[1;32mBuild model [$(FW_MODEL)]\033[0m"

ota-cp:
	cp -f $(ROOT_DIR)/rootfs/*sqsh4 $(ROOT_DIR)/vendor/sdk/ota

ifdef RELEASE
	ifeq ($(RELEASE), 1)
		@echo "\033[1;32m----------------- Project is build Release -----------------\033[0m"
	else
		@echo "\033[1;33m----------------- Project is build Release disable watchdog -----------------\033[0m"
	endif
else
	@echo "\033[1;31m----------------- Project is build Debug -----------------\033[0m"
endif

build-release: check
	@echo $(FW_RELEASE)

clean-release:
	rm -rf $(FCA_OTA_FW_DIR)/$(RELEASE_MODEL)

clean-ota:
	rm -rf $(FCA_OTA_APP_DIR)/$(RELEASE_MODEL)

build-ota:
	@echo $(FW_RELEASE)

# gen param config
ISP_DAY_BRIGHTNESS_DEFAULT	 = -15
ISP_DAY_CONTRAST_DEFAULT	 = 50
ISP_DAY_SATURATION_DEFAULT	 = 45
ISP_DAY_SHARPNESS_DEFAULT	 = 55
ISP_NIGHT_BRIGHTNESS_DEFAULT = 40
ISP_NIGHT_CONTRAST_DEFAULT	 = 70
ISP_NIGHT_SATURATION_DEFAULT = 0
ISP_NIGHT_SHARPNESS_DEFAULT	 = 60
ISP_AUTO_CONTROL_TYPE_DEFAULT = 1 # 1: SLS, 2 ALS
ISP_AUTO_ALS_ENABLE_DEFAULT = 0 # 1: en, 0 dis
ISP_ALS_THRESHOLD_DEFAULT	 = 300
ISP_ALS_RANGE_DEFAULT		 = 1200
ISP_AUTO_LIGHTING_CONTROL_TYPE_DEFAULT = 2 # 1: SLS, 2 ALS
ISP_ALS_LIGHTING_THRESHOLD_DEFAULT = 301
ISP_ALS_LIGHTING_RANGE_DEFAULT		 = 1201
ISP_AUTO_DAY_CONTROL_TYPE_DEFAULT = 1 # 1: SLS, 2 ALS
ISP_ALS_COLOR_NIGHT_THRESHOLD_DEFAULT = 303
ISP_ALS_COLOR_NIGHT_RANGE_DEFAULT		 = 903
ISP_AUTO_NIGHT_CONTROL_TYPE_DEFAULT = 1 # 1: SLS, 2 ALS
ISP_ALS_NIGHT_THRESHOLD_DEFAULT = 304
ISP_ALS_NIGHT_RANGE_DEFAULT		 = 904
ISP_ALS_IQ_GROUP_DEFAULT		 = 1

.PHONY: generate_config
generate_config:
	rm -rf CameraParam
	@echo '{' > CameraParam
	@echo '    "AntiFlickerMode":0,' >> CameraParam
	@echo '    "PictureFlip": false,' >> CameraParam
	@echo '    "PictureMirror": false,' >> CameraParam
	@echo '    "IrcutSwap": true,' >> CameraParam
	@echo '    "LightingEnable": true,' >> CameraParam
ifneq ($(value BUILD_PLAY4),)
	@echo '    "NightVisionMode": 1,' >> CameraParam
	@echo '    "LightingMode": 1,' >> CameraParam
else
	@echo '    "NightVisionMode": 0,' >> CameraParam
	@echo '    "LightingMode": 2,' >> CameraParam
endif
	@echo '    "Brightness": $(ISP_DAY_BRIGHTNESS_DEFAULT),' >> CameraParam
	@echo '    "Contrast": $(ISP_DAY_CONTRAST_DEFAULT),' >> CameraParam
	@echo '    "Saturation": $(ISP_DAY_SATURATION_DEFAULT),' >> CameraParam
	@echo '    "Sharpness": $(ISP_DAY_SHARPNESS_DEFAULT),' >> CameraParam
	@echo '    "IrBrightness": $(ISP_NIGHT_BRIGHTNESS_DEFAULT),' >> CameraParam
	@echo '    "IrContrast": $(ISP_NIGHT_CONTRAST_DEFAULT),' >> CameraParam
	@echo '    "IrSaturation": $(ISP_NIGHT_SATURATION_DEFAULT),' >> CameraParam
	@echo '    "IrSharpness": $(ISP_NIGHT_SHARPNESS_DEFAULT),' >> CameraParam
	@echo '    "AutoControlType": $(ISP_AUTO_CONTROL_TYPE_DEFAULT),' >> CameraParam
	@echo '    "AutoAlsEnable": $(ISP_AUTO_ALS_ENABLE_DEFAULT),' >> CameraParam
	@echo '    "AlsThreshold": $(ISP_ALS_THRESHOLD_DEFAULT),' >> CameraParam
	@echo '    "AlsRange": $(ISP_ALS_RANGE_DEFAULT),' >> CameraParam
	@echo '    "AutoLightingControlType": $(ISP_AUTO_LIGHTING_CONTROL_TYPE_DEFAULT),' >> CameraParam
	@echo '    "AlsLightingThreshold": $(ISP_ALS_LIGHTING_THRESHOLD_DEFAULT),' >> CameraParam
	@echo '    "AlsLightingRange": $(ISP_ALS_LIGHTING_RANGE_DEFAULT),' >> CameraParam
	@echo '    "AutoDayControlType": $(ISP_AUTO_DAY_CONTROL_TYPE_DEFAULT),' >> CameraParam
	@echo '    "AlsColorNightThreshold": $(ISP_ALS_COLOR_NIGHT_THRESHOLD_DEFAULT),' >> CameraParam
	@echo '    "AlsColorNightRange": $(ISP_ALS_COLOR_NIGHT_RANGE_DEFAULT),' >> CameraParam
	@echo '    "AutoNightControlType": $(ISP_AUTO_NIGHT_CONTROL_TYPE_DEFAULT),' >> CameraParam
	@echo '    "AlsNightThreshold": $(ISP_ALS_NIGHT_THRESHOLD_DEFAULT),' >> CameraParam
	@echo '    "AlsNightRange": $(ISP_ALS_NIGHT_RANGE_DEFAULT),' >> CameraParam
	@echo '    "IqDefault": $(ISP_ALS_IQ_GROUP_DEFAULT)' >> CameraParam
	@echo '}' >> CameraParam
	cp CameraParam $(FCA_AGENT_DIR)/default
	@rm -rf CameraParam

.PHONY: generate_script
generate_script:
	rm -rf fpt_services_management.sh
	@echo '#!/bin/sh' > fpt_services_management.sh
	@echo 'BIN_DIR="/app/bin"\n' > fpt_services_management.sh
	@echo 'fw_setenv mfg_mode\n' >> fpt_services_management.sh
	@echo 'source /etc/profile\n' >> fpt_services_management.sh
	@echo 'cp -r /app/default/TZ /var/conf/\n' >> fpt_services_management.sh
ifneq ($(value BUILD_IQ4),)
	@echo 'udhcpc -s $$BIN_DIR/udhcpc.sh -i eth0 -p /var/run/eth0.pid &\n' >> fpt_services_management.sh
endif
	@echo '$$BIN_DIR/fcam_ntpdate.sh > /dev/null 2>&1 &\n' >> fpt_services_management.sh
	@echo 'sleep 10\n' >> fpt_services_management.sh
	@echo 'killall telnetd' >> fpt_services_management.sh
	@echo 'killall syslogd\n' >> fpt_services_management.sh
	@echo "amixer -Dhw:0 cset name='Rear Amic Capture Volume' 35" >> fpt_services_management.sh
	@echo "amixer -Dhw:0 cset name='Master Playback Volume' 127\n" >> fpt_services_management.sh
	@echo "echo 5000 > /proc/sys/vm/min_free_kbytes\n" >> fpt_services_management.sh
	# @echo '$$BIN_DIR/fcam_onvif.sh &\n' >> fpt_services_management.sh
	@echo 'APP_FCAM="$$BIN_DIR/fcam"\n' >> fpt_services_management.sh
ifdef RELEASE
	@echo 'echo Firmware is Release ------------------' >> fpt_services_management.sh
	@echo 'if [ -e $$APP_FCAM ]; then' >> fpt_services_management.sh
	@echo '    LD_LIBRARY_PATH=/app/lib/ $$APP_FCAM > /dev/null 2>&1' >> fpt_services_management.sh
else
	@echo 'echo Firmware is Debug ------------------' >> fpt_services_management.sh
	@echo 'if [ -e $$APP_FCAM ]; then' >> fpt_services_management.sh
	@echo '    LD_LIBRARY_PATH=/app/lib/ $$APP_FCAM & echo $$$$! > /var/run/fcam.pid' >> fpt_services_management.sh
endif
	@echo 'else' >> fpt_services_management.sh
	@echo '    echo "file $$APP_FCAM not exist"' >> fpt_services_management.sh
	@echo 'fi' >> fpt_services_management.sh
	@chmod +x fpt_services_management.sh
	cp fpt_services_management.sh $(FCA_AGENT_DIR)/init
	@rm -rf fpt_services_management.sh
