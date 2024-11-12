
ROOT_DIR=$(shell git rev-parse --show-toplevel)

VENDOR_NAME=giec

#######################################################
# build settings
#######################################################
VERSION=1.1.7
FCA_NAME='FPTCamera'

# RELEASE=1
# FACTORY=1

# FEATURE_RTMP=1
# FEATURE_AI=1
VOICE_GUIDE=1
FEATURE_RECORD=1
# FEATURE_BBCRY=1
TERMINAL=1

#######################################################
# build agent settings
#######################################################
FCA_AGENT_DIR=$(ROOT_DIR)/rootfs/app
FCA_LIB_DIR=$(ROOT_DIR)/rootfs/fpt_lib
FCA_DEPLOY_AGENT_DIR=$(ROOT_DIR)/deploy/agent
FCA_OTA_FW_DIR=$(ROOT_DIR)/deploy/ota_fw
FCA_OTA_APP_DIR=$(ROOT_DIR)/deploy/ota_app
VENDOR_OTA_FW_DIR=$(ROOT_DIR)/vendor/ota/bin
VENDOR_OTA_VPACK_DIR=$(ROOT_DIR)/vendor/tools/fwpack
# VPACK_FLAGS=-m 0
VPACK_FLAGS=

#######################################################
# camera models
#######################################################
# BUILD_PLAY4=1
BUILD_IQ4=1

PRODUCT_PLAY4=P04L
PRODUCT_IQ4=I04L

HARDWARE_PLAY4=0709-$(PRODUCT_PLAY4)-A01
HARDWARE_IQ4=0709-$(PRODUCT_IQ4)-A01

MODEL_PLAY4='FPT Camera Play 4'
MODEL_IQ4='FPT Camera IQ 4S'

MONTH_CURR=`date +'20%y.%m'`
DATE_CURR=`date +'20%y.%m.%d'`
BUILD_TIME=`date +'%H.%M.%S'`

BUILD_ERROR = ''

ifdef BUILD_PLAY4
FW_NAME=$(VERSION)-$(HARDWARE_PLAY4)-$(DATE_CURR)T$(BUILD_TIME)
FW_MODEL=$(MODEL_PLAY4)
FW_PRODUCT=$(PRODUCT_PLAY4)
GENERAL_FLAGS += -DBUILD_PLAY4
RELEASE_MODEL=$(PRODUCT_PLAY4)-A01
FW_RELEASE=$(VERSION)-$(HARDWARE_PLAY4)-*.bin
else
ifdef BUILD_IQ4
FW_NAME=$(VERSION)-$(HARDWARE_IQ4)-$(DATE_CURR)T$(BUILD_TIME)
FW_MODEL=$(MODEL_IQ4)
FW_PRODUCT=$(PRODUCT_IQ4)
GENERAL_FLAGS += -DBUILD_IQ4
RELEASE_MODEL=$(PRODUCT_IQ4)-A01
FW_RELEASE=$(VERSION)-$(HARDWARE_IQ4)-*.bin
else
BUILD_ERROR='Model not support'
endif
endif
