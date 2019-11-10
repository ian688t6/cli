#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"

static int32_t cli_xxx_set(void *pv_arg)
{
	printf("xxx_set\n");	
	return 0;
}

static cli_func_tb_s gast_fn_tb[] = {
	{ "xxx_set", sizeof(uint32_t), cli_xxx_set },
	{ "", 0, 0 },
};

int32_t main(int32_t i_argc, const char **ppc_argv)
{
	cli_s st_cli;

	if (i_argc < 2)
		printf("cli invalid params\n");
	
	st_cli.pc_script 	= ppc_argv[1];
	st_cli.i_argc		= i_argc - 2;
	st_cli.ppc_argv		= &ppc_argv[2];	
	st_cli.pst_tb		= gast_fn_tb;
	cli_begin(&st_cli);	
	cli_exec();
	cli_end();
	return 0;
}

