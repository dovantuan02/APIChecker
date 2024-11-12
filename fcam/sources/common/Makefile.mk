CXXFLAGS	+= -I./sources/common

VPATH += sources/common

OBJ += $(OBJ_DIR)/cmd_line.o
OBJ += $(OBJ_DIR)/jsmn.o
OBJ += $(OBJ_DIR)/firmware.o
OBJ += $(OBJ_DIR)/utils.o
OBJ += $(OBJ_DIR)/fifo.o
# OBJ += $(OBJ_DIR)/STUNExternalIP.o
OBJ += $(OBJ_DIR)/g711.o
# OBJ += $(OBJ_DIR)/h26xparsec.o TODO wait new g++ 
