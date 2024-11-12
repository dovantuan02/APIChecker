CXXFLAGS += -Ilibraries/libopenssl/include
LDFLAGS += -Llibraries/libopenssl/lib

LDLIBS += -lcrypto -lssl


