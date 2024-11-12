CXXFLAGS += -Ilibraries/libanyka/include
CXXFLAGS += -Ilibanyka/include_3rd

LDFLAGS += -Llibraries/libanyka/lib

LDLIBS += $(addprefix -l, $(ANYKA_LIBS_DEP))
ANYKA_LIBS_DEP = plat_common plat_mem plat_thread plat_log plat_osal mpi_venc plat_dbg ak_object_filter \
                  plat_vi plat_isp_sdk plat_vpss plat_ao mpi_adec plat_vqe akaudiofilter plat_ai akaudiocodec mpi_aenc ak_mrd \
                  app_video app_its plat_timer mpi_osd app_osd_ex mpi_svp akv_cnn_dt akv_cnn_fas akv_cnn_re