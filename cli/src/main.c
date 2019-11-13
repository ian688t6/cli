#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"

typedef struct {
	char ac_stu_name[32];
	uint16_t us_score;
	uint32_t ui_age;
} __attribute__ ((packed))xxx_s;

static int32_t cli_xxx_set(void *pv_arg)
{
	xxx_s *pst_xxx = (xxx_s *)pv_arg;

	printf("xxx_set %s %d %d\n", pst_xxx->ac_stu_name, pst_xxx->us_score, pst_xxx->ui_age);	
				
	return 0;
}

static int32_t cli_xxx_get(void *pv_arg)
{
	xxx_s *pst_xxx = (xxx_s *)pv_arg;

	strcpy(pst_xxx->ac_stu_name, "YinJia");
	pst_xxx->us_score = 100;
	pst_xxx->ui_age = 32;

	return 0;
}

static cli_func_tb_s gast_fn_tb[] = {
	{ "xxx_set", sizeof(xxx_s), cli_xxx_set },
	{ "xxx_get", sizeof(xxx_s), cli_xxx_get },
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

