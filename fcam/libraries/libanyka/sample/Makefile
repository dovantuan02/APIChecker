include config.mk

dir_y:=

ifeq ($(AI), y)
	dir_y += ai
	dir_y += ai_resample
	dir_y += vqe
endif

ifeq ($(AO), y)
	dir_y += ao
endif

ifeq ($(AENC), y)
	dir_y += aenc
endif

ifeq ($(ADEC), y)
	dir_y += adec
endif

ifeq ($(VAD), y)
	dir_y += vad
	dir_y += baby_screaming
endif

ifeq ($(VENC), y)
	dir_y += venc
endif

ifeq ($(VDEC), y)
	dir_y += vdec
endif

ifeq ($(OSD), y)
	dir_y += osd
endif

ifeq ($(OSD_EX), y)
	dir_y += osd_ex
endif

ifeq ($(VO), y)
	dir_y += vo
endif

ifeq ($(TDE), y)
	dir_y += tde
endif

ifeq ($(MUX), y)
	dir_y += mux
endif

ifeq ($(DEMUX), y)
	dir_y += demux
endif

ifeq ($(VPSS), y)
	dir_y += vpss
endif

ifeq ($(VI), y)
	dir_y += vi
	dir_y += vi_draw_box
endif

ifeq ($(TIMER), y)
	dir_y += timer
endif

ifeq ($(MD), y)
	dir_y += md
endif

ifeq ($(DRV), y)
	dir_y += drv
endif

ifeq ($(MT), y)
	dir_y += mt
	dir_y += mt_math
endif

ifeq ($(VIBE), y)
	dir_y += vibe
endif

ifeq ($(IR), y)
	dir_y += ir
endif

ifeq ($(PS_IR), y)
	dir_y += ps_ir
endif

ifeq ($(MEM_EX), y)
	dir_y += mem_ex
endif

ifeq ($(VIDEO), y)
	dir_y += video
endif

ifeq ($(DUAL_CIS), y)
	dir_y += dual_cis
endif

ifeq ($(VAD), y)
    dir_y += baby_screaming
	dir_y += vad
endif

ifeq ($(UUID),y)
	dir_y += uuid
endif

ifeq ($(SVP), y)
	dir_y += svp
endif

ifeq ($(SVP2), y)
	dir_y += svp2
endif

all:
	@for i in $(dir_y); \
	do \
		$(MAKE) -C $$i; \
		if [ $$? -ne 0 ];then exit 1; fi \
	done

install:
	@for i in $(dir_y); \
	do \
		$(MAKE) -C $$i install; \
	done

clean:
	@for i in $(dir_y); \
	do \
		$(MAKE) -C $$i clean; \
	done

demo:
	$(MAKE) -C demo


.PHONY: all install clean image demo
