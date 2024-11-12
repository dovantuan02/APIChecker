CXXFLAGS += -Ilibraries/libpsl/include

LDFLAGS += -Llibraries/libpsl/lib

# lib VIVOTEK SDK
LDLIBS	+= -lpsl
