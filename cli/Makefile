LOC_INC = inc
LOC_SRC = src

SRC = $(wildcard ${LOC_SRC}/*.c)
OBJ = $(patsubst %.c,${LOC_SRC}/%.o,$(notdir ${SRC})) 

CFLAGS += -I$(LIBS)/libcli/inc
CFLAGS += -I$(LIBS)/libcfs/inc
LDFLAG := -static -fdata-sections -ffunction-sections -Wl,-dn -L$(LIBS)/libcli -lcli -L$(LIBS)/libcfs -lcfs -lm -lrt
TARGET = cli

.PHONY: all clean cleanall
all: ${TARGET}
${TARGET}:${OBJ}	
	@echo "make bin"
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAG)

${LOC_SRC}/%.o:${LOC_SRC}/%.c
	$(CC) -c -I$(LOC_INC) $(CFLAGS) $< -o $@ 

clean: 
	@echo "make clean bin"
	@rm -rf $(LOC_SRC)/*.o
	@rm -rf $(TARGET)
