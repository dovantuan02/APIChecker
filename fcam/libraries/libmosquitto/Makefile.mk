CXXFLAGS += -Ilibraries/libmosquitto/include

LDFLAGS += -Llibraries/libmosquitto/lib

LDLIBS += -lmosquitto -lmosquittopp