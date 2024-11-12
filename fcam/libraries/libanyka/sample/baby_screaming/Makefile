# Project name

PROJ = ak_baby_screaming_sample

LIB_DEP = plat_ai plat_common plat_vqe plat_log plat_thread pthread plat_mem akaudiofilter m plat_dbg plat_osal
LIB_DEP += dl

ifeq ($(CHIP_SERIES), AK3918AV100)
ifeq  ($(OS_TYPE), 0)
LIB_DEP += ak_nne plat_npu akAIcrydetect
endif
endif


ifneq ($(OS_TYPE), 0)
    TARGET = lib$(PROJ).a
else
    TARGET = $(PROJ)
endif

LIBS = $(addprefix -l, $(LIB_DEP))


TOPDIR 	?= $(shell pwd)/../..

# Flags

INCLUDE    =	-I. \
		-I../../include_inner \
		-I../../include \
		-I../include \
		-I$(EXT_LIB_DIR)/include \

#Locations

SRCDIR += .

CSRCS += $(foreach d, $(SRCDIR), $(wildcard $d/*.c))

COBJS += $(patsubst %.c, %.o, $(CSRCS))

LIB_DIR = $(TOPDIR)/lib

LD_FLAGS = -Xlinker "-(" $(LIBS) -Xlinker "-)"  -L$(LIB_DIR)

ifeq ($(OS_TYPE), 0)
LD_FLAGS += -L$(EXT_LIB_DIR)
endif

#build rule
.PHONY: all target install clean

all: $(COBJS)
ifneq ($(OS_TYPE), 0)
	$(AR) -rsv $(TARGET)  $(COBJS)
	@cp -r $(TARGET) $(TOPDIR)/lib
else
	$(CC) $(COBJS) $(LD_FLAGS) -o $(TARGET)
	$(STRIP) $(TARGET)
endif

install:
ifeq ($(OS_TYPE), 0)
	@cp -f $(TARGET) $(SAMPLE_INSTALL_DIR)
else
	@cp -f $(TARGET) $(PLATFORM_INSTALL_DIR)/lib
endif

clean : 
	$(RM) $(COBJS) $(TARGET)

ifndef RULES_MK_FILE
RULES_MK_FILE=$(TOPDIR)/../../rules.mk
endif


# Rules
include $(RULES_MK_FILE)
