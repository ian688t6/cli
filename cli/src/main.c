#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"
#include "cfsio.h"

static cli_func_tb_s gast_fn_tb[] = {
	{ "reg_get", 	sizeof(cfsio_reg_s), cfsio_reg_get },
	{ "reg_set", 	sizeof(cfsio_reg_s), cfsio_reg_set },
	{ "versid_get", sizeof(cfsio_versid_s), cfsio_versid_get },
	{ "pwrinfo_get", sizeof(cfsio_pwrinfo_s), cfsio_pwrinfo_get },
	{ "", 0, 0 },
};

int32_t main(int32_t i_argc, const char **ppc_argv)
{
	int32_t i_ret = 0;

	cli_s st_cli;

	if (i_argc < 2)
		printf("cli invalid params\n");
	
	st_cli.pc_script 	= ppc_argv[1];
	st_cli.i_argc		= i_argc - 2;
	st_cli.ppc_argv		= &ppc_argv[2];	
	st_cli.pst_tb		= gast_fn_tb;
	i_ret = cli_begin(&st_cli);	
	if (0 != i_ret) {
		goto end;
	}	
	cli_exec();
end:	
	cli_end();
	
	return 0;
}

