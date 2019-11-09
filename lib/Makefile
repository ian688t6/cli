LOC_INC = inc
LOC_SRC = src

SRC = $(wildcard ${LOC_SRC}/*.c)
OBJ = $(patsubst %.c,${LOC_SRC}/%.o,$(notdir ${SRC})) 

CFLAGS += -I$(LIB)/inc
LDFLAG := -static -fdata-sections -ffunction-sections -Wl,-dn -L$(LIB) -lcli -lm -lrt
TARGET = libcli

.PHONY: all clean cleanall

all: ${TARGET}
${TARGET}:${OBJ}
	@echo "make lib"

clean: 
	@echo "make clean lib"

