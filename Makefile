include config.mk

.PHONY: all clean cleanall

all:
	@echo "make cli"
	@make -C libs
	@make -C cli

clean: 
	@echo "make clean cli"
	@make clean -C libs
	@make clean -C cli

