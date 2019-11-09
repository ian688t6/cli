#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli.h"

int32_t main(int32_t i_argc, char *pc_argv[])
{
	const char *pc_script = NULL;
	
	if (i_argc < 2)
		printf("cli invalid params\n");
	
	pc_script = pc_argv[1];
	printf("script path: %s\n", pc_script);
	cli_begin(i_argc - 1, &pc_argv[1]);	

	return 0;
}

