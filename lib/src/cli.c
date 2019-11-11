#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
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

static int32_t get_param_name(char *pc_src, char *pc_dst)
{
	char *pc_save = pc_dst;	
	
	pc_src += strlen(CLI_TAG_PARAM_NAME);
	while ('\0' != *pc_src) {
		if ('>' == *pc_src)
			break;
		*pc_dst ++ = *pc_src ++;
	}
	*pc_dst = '\0';

	return (('>' == *pc_src) && (pc_dst - pc_save)) ? 0 : -1;
}

static int32_t get_param_type(char *pc_src, cli_type_e *pem_type, uint32_t *pui_size)
{
	pc_src += strlen(CLI_TAG_PARAM_TYPE);
	
	if (strstr(pc_src, CLI_TAG_PARAM_UINT8)) {
		*pem_type = CLI_TYPE_UINT8;
		*pui_size = 1;	
		return 0;
	}

	if (strstr(pc_src, CLI_TAG_PARAM_UINT16)) {
		*pem_type = CLI_TYPE_UINT16;
		*pui_size = 2;
		return 0;
	}

	if (strstr(pc_src, CLI_TAG_PARAM_UINT32)) {
		*pem_type = CLI_TYPE_UINT32;
		*pui_size = 4;
		return 0;
	}

	if (strstr(pc_src, CLI_TAG_PARAM_UINT64)) {
		*pem_type = CLI_TYPE_UINT64;
		*pui_size = 8;
		return 0;
	}
	
	if (strstr(pc_src, CLI_TAG_PARAM_STRING)) {
		*pem_type = CLI_TYPE_STRING;
		pc_src += strlen(CLI_TAG_PARAM_STRING);
		*pui_size = strtoul(pc_src, NULL, 10);
		return 0;	
	}
	
	return -1;
}

static int32_t get_param_defval(char *pc_src, cli_type_e em_type, uint8_t *puc_val)
{
	uint64_t ul_val = 0;
	char *pc_tmp = NULL;
	
	pc_src += strlen(CLI_TAG_PARAM_DEFVAL);
	switch (em_type) {
	case CLI_TYPE_UINT8:
	ul_val = strtoul(pc_src, 0, 0);	
	memcpy(puc_val, (uint8_t *)&ul_val, sizeof(uint8_t));	
	break;
	
	case CLI_TYPE_UINT16:
	ul_val = strtoul(pc_src, 0, 0);	
	memcpy(puc_val, (uint16_t *)&ul_val, sizeof(uint16_t));	
	break;
	
	case CLI_TYPE_UINT32:
	ul_val = strtoul(pc_src, 0, 0);	
	memcpy(puc_val, (uint32_t *)&ul_val, sizeof(uint32_t));	
	break;
	
	case CLI_TYPE_UINT64:
	ul_val = strtoul(pc_src, 0, 0);	
	memcpy(puc_val, (uint64_t *)&ul_val, sizeof(uint64_t));	
	break;
	
	case CLI_TYPE_STRING:
	strcpy((char *)puc_val, pc_src);
	pc_tmp = strrchr((char *)puc_val, '>');
	*pc_tmp = '\0';
	break;
	
	default:
	return -1;	
	break;
	}

	return 0;
}

static int32_t parse_params(FILE *pf_file)
{
	int32_t i_ret = 0;
	char *pc_ptr = NULL;
	char ac_line[CLI_LINE_BUFLEN] = {0};
	char ac_arg_name[CLI_ARG_NAMELEN] = {0};
	uint8_t	auc_arg_buf[CLI_ARG_BUFLEN] = {0};
	uint32_t ui_size;
	cli_type_e em_type;

	while (fgets(ac_line, CLI_LINE_BUFLEN, pf_file)) {
		pc_ptr = strstr(ac_line, CLI_TAG_PARAM_NAME);
		if (pc_ptr) {
			if (0 != get_param_name(pc_ptr, ac_arg_name)) {
				return -1;
			}
		}
		
		pc_ptr = strstr(ac_line, CLI_TAG_PARAM_TYPE);
		if (pc_ptr) {
			if (0 != get_param_type(pc_ptr, &em_type, &ui_size)) {
				return -1;	
			}	
		}
		
		pc_ptr = strstr(ac_line, CLI_TAG_PARAM_DEFVAL);
		if (pc_ptr) {
			if (0 != get_param_defval(pc_ptr, em_type, auc_arg_buf)) {
				return -1;	
			}	
		}
		printf("%s %d %d\n", ac_arg_name, em_type, ui_size);	
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

