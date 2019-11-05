include config.mk

.PHONY: all clean cleanall

all:
	@echo "make cli"
	@make -C lib
	@make -C cli

clean: 
	@echo "make clean cli"
	@make clean -C lib
	@make clean -C cli

