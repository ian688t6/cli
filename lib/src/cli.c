#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "cli.h"

int32_t cli_begin(cli_s *pst_cli)
{
	int32_t i = 0;

	printf("script: %s\n", pst_cli->pc_script);
	for (i = 0; i < pst_cli->i_argc; i ++) {
		printf("%s\n", pst_cli->ppc_argv[i]);
	}

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

