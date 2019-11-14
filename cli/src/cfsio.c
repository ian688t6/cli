#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cfsio.h"
#include "cfs.h"
#include "cli.h"

static int32_t cfsio_get(uint16_t us_reg, uint8_t *puc_val, uint8_t uc_len)
{
	int32_t i_ret = 0;

	return i_ret;
}

static int32_t cfsio_set(uint16_t us_reg, uint8_t *puc_val, uint8_t uc_len)
{
	int32_t i_ret = 0;

	return i_ret;
}

CFS_DEVICE_DEF(cfsio_set, cfsio_get)

int32_t cfsio_reg_get(void *pv_arg)
{
	int32_t i_ret = 0;
	return i_ret;
}

int32_t cfsio_reg_set(void *pv_arg)
{
	int32_t i_ret = 0;
	return i_ret;
}

int32_t cfsio_versid_get(void *pv_arg)
{
	int32_t i_ret = 0;
	return i_ret;
}

int32_t cfsio_pwrinfo_get(void *pv_arg)
{
	int32_t i_ret = 0;
	return i_ret;
}

void cfsio_init(void)
{
	return;
}

