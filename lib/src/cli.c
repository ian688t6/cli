#include <stdio.h>
#include <stdint.h>
#include <string.h>

int32_t cli_begin(int32_t i_argc, char *pc_argv[])
{
	int32_t i = 0;

	for (i = 0; i < i_argc; i ++) {
		printf("%s\n", pc_argv[i]);
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

