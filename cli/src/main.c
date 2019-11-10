#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"

int32_t main(int32_t i_argc, const char **ppc_argv)
{
	cli_s st_cli;

	if (i_argc < 2)
		printf("cli invalid params\n");
	
	st_cli.pc_script 	= ppc_argv[1];
	st_cli.i_argc		= i_argc - 2;
	st_cli.ppc_argv		= &ppc_argv[2];	
	cli_begin(&st_cli);	
	cli_exec();
	cli_end();
	return 0;
}

