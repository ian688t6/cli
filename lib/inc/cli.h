#ifndef __CLI_H__
#define __CLI_H__

typedef struct {
	const char	*pc_script;
	int32_t 	i_argc;	
	const char 	**ppc_argv;
} cli_s;

extern int32_t cli_begin(cli_s *pst_cli);

extern int32_t cli_exec(void);

extern void cli_end(void);

#endif

