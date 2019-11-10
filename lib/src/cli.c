#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "cli.h"

static cli_func_s gst_func;

static int32_t parse_script(FILE *pf_file)
{
	int32_t i_ret = 0;

	return i_ret;
}

int32_t cli_begin(cli_s *pst_cli)
{
	//int32_t i = 0;
	cli_func_s *pst_func = &gst_func;

	printf("script: %s\n", pst_cli->pc_script);
	pst_func->pf_file = fopen(pst_cli->pc_script, "r");
	if (!pst_func->pf_file) {
		printf("fopen %s fail\n", pst_cli->pc_script);
		return -1;
	}
	
	//for (i = 0; i < pst_cli->i_argc; i ++) {
	//	printf("%s\n", pst_cli->ppc_argv[i]);
	//}
	parse_script(pst_func->pst_file);

	if (!pst_func->pf_file)
		fclose(pst_func->pf_file);
	
	return 0;
}

int32_t cli_exec(void)
{
	return 0;
}

void cli_end(void)
{
	
	return;
}

