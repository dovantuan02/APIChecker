CXXFLAGS += -Ilibraries/libcurl/include

LDFLAGS += -Llibraries/libcurl/lib

# lib VIVOTEK SDK
LDLIBS	+= -lcurl
