#ifndef __CLI_H__
#define __CLI_H__
#include "list.h"

#define LOG_EN	(1)
#ifdef LOG_EN
#define cli_logi(format, arg...) printf("INFOM: " format "\r\n", ##arg)
#define cli_logw(format, arg...) printf("WARN: " format "\r\n", ##arg)
#define cli_loge(format, arg...) printf("ERROR: " format "\r\n", ##arg)
#else
#define cli_logi(format, arg...)
#define cli_logw(format, arg...)
#define cli_loge(format, arg...)
#endif

#define CLI_ARG_BUFLEN		(256)
#define CLI_FUN_BUFLEN		(256)
#define CLI_ARG_NAMELEN		(32)
#define CLI_LINE_BUFLEN		(1024)
#define CLI_BUF_LEN			(2048)

#define CLI_TAG_FUNCTION		"[function]"
#define CLI_TAG_PARAMS			"[parameters]"
#define CLI_TAG_PARAM_NAME		"<name:"
#define CLI_TAG_PARAM_TYPE		"<type:"
#define CLI_TAG_PARAM_DEFVAL	"<defval:"
#define CLI_TAG_PARAM_UINT8		"uint8_t"
#define CLI_TAG_PARAM_UINT16	"uint16_t"
#define CLI_TAG_PARAM_UINT32	"uint32_t"
#define CLI_TAG_PARAM_UINT64	"uint64_t"
#define CLI_TAG_PARAM_STRING	"string"

typedef enum {
	CLI_TYPE_UINT8,
	CLI_TYPE_UINT16,
	CLI_TYPE_UINT32,
	CLI_TYPE_UINT64,
	CLI_TYPE_STRING,
	CLI_TYPE_INVALID,
} cli_type_e;

typedef struct {
	char ac_func_name[CLI_FUN_BUFLEN];
	uint32_t ui_args_size;
	int32_t (*cli_func)(void *pv_arg);	
} cli_func_tb_s;

typedef struct {
	const char	*pc_script;
	int32_t 	i_argc;	
	const char 	**ppc_argv;
	cli_func_tb_s *pst_tb;
} cli_s;

typedef struct {
	FILE *pf_file;	
	cli_func_tb_s *pst_func;
	struct list_head st_arg_list;	
} cli_func_s;

typedef struct {
	struct list_head list;	
	cli_type_e	em_type;
	char 		ac_arg_name[CLI_ARG_NAMELEN];	
	uint32_t	ui_size;
	uint8_t		auc_arg_buf[CLI_ARG_BUFLEN];
} cli_arg_s;

extern int32_t cli_begin(cli_s *pst_cli);

extern int32_t cli_exec(void);

extern void cli_end(void);

#endif

