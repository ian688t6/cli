export TOP:= $(shell pwd)
export CROSS_COMPILE ?=
export CC := $(CROSS_COMPILE)gcc
export AR := $(CROSS_COMPILE)ar
export OD := $(CROSS_COMPILE)objdump
export NM := $(CROSS_COMPILE)nm
export STRIP := $(CROSS_COMPILE)strip
export CFLAGS = -Os -Wall -Werror

