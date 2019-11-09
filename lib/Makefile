LOC_INC = inc
LOC_SRC = src

SRC = $(wildcard ${LOC_SRC}/*.c)
OBJ = $(patsubst %.c,${LOC_SRC}/%.o,$(notdir ${SRC})) 

CFLAGS += -I$(LIBS)/inc
LDFLAG := -static -fdata-sections -ffunction-sections -Wl,-dn -L$(LIBS) -lcli -lm -lrt
TARGET = libcli.a

.PHONY: all clean cleanall

all: ${TARGET}
${TARGET}:${OBJ}
	@echo "make lib"
	@$(AR) rc $@ $^
%.o:%.c
	$(CC) $(CFLAGS) $(LDFLAG) -c $< -o $@

clean: 
	@echo "make clean lib"
	@rm -rf ${OBJ}
	@rm -rf *.a

