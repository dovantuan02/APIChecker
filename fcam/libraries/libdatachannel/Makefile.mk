CXXFLAGS += -Ilibraries/libdatachannel/include

LDLIBS +=\
        libraries/libdatachannel/lib/libdatachannel.a \
        libraries/libdatachannel/lib/libjuice.a \
        libraries/libdatachannel/lib/libsrtp2.a \
        libraries/libdatachannel/lib/libusrsctp.a
