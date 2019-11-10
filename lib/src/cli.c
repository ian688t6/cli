#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "cli.h"

static cli_s *gpst_cli;
static cli_func_s gst_func;

static int32_t parse_function(FILE *pf_file)
{
	int32_t i_ret = -1;
	int32_t i = 0;
	char ac_line[CLI_LINE_BUFLEN] = {0};
	
	while (fgets(ac_line, CLI_LINE_BUFLEN, pf_file)) {
		for (i = 0; gpst_cli->pst_tb[i].cli_func; i ++) {
			if (strstr(ac_line, gpst_cli->pst_tb[i].ac_func_name)) {
				printf("find func: %s\n", gpst_cli->pst_tb[i].ac_func_name);	
				gst_func.pst_func = &gpst_cli->pst_tb[i];
				return 0;
			}	
		}	
	}

	return i_ret;
}

static int32_t parse_params(FILE *pf_file)
{
	int32_t i_ret = 0;
	char ac_line[CLI_LINE_BUFLEN] = {0};
	
	while (fgets(ac_line, CLI_LINE_BUFLEN, pf_file)) {
		if (strstr(ac_line, CLI_TAG_PARAM_NAME)) {
		}

		if (strstr(ac_line, CLI_TAG_PARAM_TYPE)) {
		}

		if (strstr(ac_line, CLI_TAG_PARAM_DEFVAL)) {
		}
	}

	return i_ret;
}

static int32_t parse_script(FILE *pf_file)
{
	int32_t i_ret = 0;
	char ac_line[CLI_LINE_BUFLEN] = {0};
	
	if (!pf_file)
		return -1;

	while (fgets(ac_line, CLI_LINE_BUFLEN, pf_file)) {
		if (strstr(ac_line, CLI_TAG_FUNCTION)) {
			if (0 != parse_function(pf_file)) {
				return -1;
			}
		}
	
		if (strstr(ac_line, CLI_TAG_PARAMS)) {
			if (0 != parse_params(pf_file)) {
				return -1;
			}
		}
	}

	return i_ret;
}

int32_t cli_begin(cli_s *pst_cli)
{
	//int32_t i = 0;
	cli_func_s *pst_func = &gst_func;
	gpst_cli = pst_cli;
	
	printf("script: %s\n", pst_cli->pc_script);
	pst_func->pf_file = fopen(pst_cli->pc_script, "r");
	if (!pst_func->pf_file) {
		printf("fopen %s fail\n", pst_cli->pc_script);
		return -1;
	}
	
	parse_script(pst_func->pf_file);

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

