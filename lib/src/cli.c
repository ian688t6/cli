#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "cli.h"

static cli_s *gpst_cli;
static cli_func_s gst_func;
static uint8_t gauc_cli_buf[CLI_BUF_LEN] = {0};

static void print_arg(cli_type_e em_type, char *pc_arg_name, uint8_t *puc_arg)
{
	switch (em_type) {
	case CLI_TYPE_UINT8:
	break;
	case CLI_TYPE_UINT16:
	break;
	case CLI_TYPE_UINT32:
	break;
	case CLI_TYPE_UINT64:
	break;
	case CLI_TYPE_STRING:
	break;
	default:break;	
	}
	return;
}

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
	uint32_t ui_size = 0;
	cli_func_s *pst_func = &gst_func;
	cli_arg_s *pst_arg;
	cli_type_e em_type = CLI_TYPE_INVALID;
		
	INIT_LIST_HEAD(&pst_func->st_arg_list);
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
		pst_arg = (cli_arg_s *)malloc(sizeof(cli_arg_s));	
		strcpy(pst_arg->ac_arg_name, ac_arg_name);
		pst_arg->em_type = em_type;
		pst_arg->ui_size = ui_size;
		memcpy(pst_arg->auc_arg_buf, auc_arg_buf, ui_size);
		list_add_tail(&pst_arg->list, &pst_func->st_arg_list);
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

static int32_t parse_inputarg(const char *pc_arg, char *pc_arg_name, char *pc_arg_val)
{
	if (!pc_arg || !pc_arg_name || !pc_arg_val)
		return -1;
	
	sscanf(pc_arg, "%s=%s", pc_arg_name, pc_arg_val);
	return 0;
}

static cli_arg_s *lookup_arg(char *pc_arg_name)
{
	cli_func_s *pst_func = &gst_func;
	cli_arg_s *pst_node;
	cli_arg_s *pst_tmp_node;
	if (!list_empty(&pst_func->st_arg_list)) {
		list_for_each_entry_safe(pst_node, pst_tmp_node, &pst_func->st_arg_list, list) {
			if (!strcmp(pc_arg_name, pst_node->ac_arg_name))
				return pst_node;
		}
	}
	return NULL;
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
	int32_t i = 0;
	cli_func_s *pst_func = &gst_func;
	char ac_arg_name[CLI_ARG_NAMELEN] = {0};
	uint8_t	auc_arg_buf[CLI_ARG_BUFLEN] = {0};
	uint8_t *puc_ptr = gauc_cli_buf;	
	cli_arg_s *pst_node;
	cli_arg_s *pst_tmp_node;
	uint64_t ul_val = 0;

	for (i = 0; i < gpst_cli->i_argc; i ++) {
		parse_inputarg(gpst_cli->ppc_argv[i], ac_arg_name, (char *)auc_arg_buf);	
		pst_node = lookup_arg(ac_arg_name);	
		if (pst_node) {
			switch (pst_node->em_type) {
			case CLI_TYPE_UINT8:
			ul_val = strtoul((const char *)auc_arg_buf, 0, 0);	
			memcpy(pst_node->auc_arg_buf, (uint8_t *)&ul_val, sizeof(uint8_t));	
			break;
	
			case CLI_TYPE_UINT16:
			ul_val = strtoul((const char *)auc_arg_buf, 0, 0);	
			memcpy(pst_node->auc_arg_buf, (uint16_t *)&ul_val, sizeof(uint16_t));	
			break;
	
			case CLI_TYPE_UINT32:
			ul_val = strtoul((const char *)auc_arg_buf, 0, 0);	
			memcpy(pst_node->auc_arg_buf, (uint32_t *)&ul_val, sizeof(uint32_t));	
			break;
	
			case CLI_TYPE_UINT64:
			ul_val = strtoul((const char *)auc_arg_buf, 0, 0);	
			memcpy(pst_node->auc_arg_buf, (uint64_t *)&ul_val, sizeof(uint64_t));	
			break;
	
			case CLI_TYPE_STRING:
			strcpy((char *)pst_node->auc_arg_buf, (char *)auc_arg_buf);
			break;
			
			default: return -1;
			break;
			}	
		}	
	}
	
	if (!list_empty(&pst_func->st_arg_list)) {
		list_for_each_entry_safe(pst_node, pst_tmp_node, &pst_func->st_arg_list, list) {
			memcpy(puc_ptr, pst_node->auc_arg_buf, pst_node->ui_size);
			puc_ptr += pst_node->ui_size;
		}
	}
	puc_ptr = gauc_cli_buf;	
	if (0 != pst_func->pst_func->cli_func(puc_ptr)) {
		return -1;
	}

	return 0;
}

void cli_end(void)
{
	cli_func_s *pst_func = &gst_func;
	cli_arg_s *pst_node;
	cli_arg_s *pst_tmp_node;

	if (!list_empty(&pst_func->st_arg_list)) {
		list_for_each_entry_safe(pst_node, pst_tmp_node, &pst_func->st_arg_list, list) {
			print_arg(pst_node->em_type, pst_node->ac_arg_name, pst_node->auc_arg_buf);			
			list_del(&pst_node->list);
			free(pst_node);
		}	
	}	
	
	return;
}

