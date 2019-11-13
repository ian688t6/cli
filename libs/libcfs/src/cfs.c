/*
* @File  		:	cfs.c
* @Description	: 	Celfras external register control driver
* @Date			: 	2019.06.24	
*/
#include <stdint.h>
#include "cfs.h"

extern cfs_dev_s gst_cfs;
/**
* @function: cfs_read_reg
* @brief: cfs i2c read external register
* @param: us_reg input external register addr
* @param: *puc_val output external register value
* @return: 0 success or -1 fail
*/
int32_t cfs_read_reg(uint16_t us_reg, uint8_t *puc_val)
{
	int32_t i_ret = 0;
	uint8_t uc_len = 1;	
	uint8_t auc_data[CFS_DATA_MAXLEN] = {0};
	
	if (!gst_cfs.get)
		return -1;
	
	i_ret = gst_cfs.get(us_reg, auc_data, uc_len);
	if (0 != i_ret) {
		cfs_loge("cfs read fail");	
	}
	*puc_val = auc_data[0];	
	
	return i_ret;
}

/**
* @function: cfs_write_reg
* @brief: cfs i2c write external register
* @param: us_reg input external register addr
* @param: uc_val input external register value
* @return: 0 success or -1 fail
*/
int32_t cfs_write_reg(uint16_t us_reg, uint8_t uc_val)
{
	int32_t i_ret = 0;
	uint8_t uc_len = 1;	
	uint8_t auc_data[CFS_DATA_MAXLEN] = {0};

	if (!gst_cfs.set) 
		return -1;
	
	auc_data[0] = uc_val;
	i_ret = gst_cfs.set(us_reg, auc_data, uc_len);
	if (0 != i_ret) {
		cfs_loge("cfs write fail");	
	}

	return i_ret;
}

/**
* @function: cfs_get_chip_id
* @brief: Get cfs chip id
* @param: *pus_id output chip id
* @return: 0 success or -1 fail
*/
int32_t cfs_get_chip_id(uint16_t *pus_id)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;

	if (!pus_id)
		return -1;
	
	i_ret  = cfs_read_reg(REG_CFS_CHIPIDL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_CHIPIDH, &uc_h);
	if (0 != i_ret) {
		cfs_loge("read chipid fail");
	}	
	*pus_id = ((uc_h << 8) | (uc_l));

	return i_ret; 
}

/**
* @function: cfs_get_intr_status
* @brief: Get cfs intr status
* @param: *pst_stats output system status
* @return: 0 success or -1 fail
*/
int32_t cfs_get_intr_status(cfs_intr_s *pst_status)
{
	int32_t i_ret = 0;
	
	if (!pst_status) {
		return -1;	
	}

	i_ret  = cfs_read_reg(REG_CFS_INTSTATUS, &pst_status->uc_data);
	if (0 != i_ret) {
		cfs_loge("get intr status fail");
		return i_ret;	
	}
	
	return i_ret;
}

/**
* @function: cfs_get_intr
* @brief: Get cfs intr config
* @param: *pst_stats output system status
* @return: 0 success or -1 fail
*/
int32_t cfs_get_intr(cfs_intr_s *pst_intr)
{
	int32_t i_ret = 0;
	
	if (!pst_intr) {
		return -1;	
	}

	i_ret  = cfs_read_reg(REG_CFS_INTEN, &pst_intr->uc_data);
	if (0 != i_ret) {
		cfs_loge("get intr fail");
		return i_ret;	
	}
	
	return i_ret;
}

/**
* @function: cfs_set_intr
* @brief: Set cfs intr status
* @param: *pst_stats input system status
* @return: 0 success or -1 fail
*/
int32_t cfs_set_intr(cfs_intr_s *pst_intr)
{
	int32_t i_ret = 0;
	
	if (!pst_intr) {
		return -1;	
	}

	i_ret  = cfs_write_reg(REG_CFS_INTEN, pst_intr->uc_data);
	if (0 != i_ret) {
		cfs_loge("set intr fail");
		return i_ret;	
	}

	return i_ret;
}

/**
* @function: cfs_clr_intr
* @brief: clear cfs intr
* @return: 0 success or -1 fail
*/
int32_t cfs_clr_intr(void)
{
	int32_t i_ret = 0;
	uint8_t uc_intr = 0;
	cfs_misc_s st_misc;

	i_ret  = cfs_write_reg(REG_CFS_INTSTATUS, uc_intr);
	if (0 != i_ret) {
		cfs_loge("clr intr status fail");
		return i_ret;	
	}

	i_ret = cfs_get_oper_misc(&st_misc);
	if (0 != i_ret) {
		cfs_loge("set misc fail");
		return i_ret;	
	}

	st_misc.uc_clr_intr = 1;
	i_ret = cfs_set_oper_misc(&st_misc);
	if (0 != i_ret) {
		cfs_loge("set misc fail");
	}
	
	return i_ret;	
}

/**
* @function: cfs_get_fw_ver
* @brief: get cfs firmware version
* @param: pus_major_ver output firmware major version
* @param: pus_minor_ver output firmware minor version
* @return: 0 success or -1 fail
*/
int32_t cfs_get_fw_ver(uint16_t *pus_major_ver, uint16_t *pus_minor_ver)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;
	
	if (!pus_major_ver || !pus_minor_ver)
		return -1;
	
	i_ret  = cfs_read_reg(REG_CFS_FW_MAJOR_VERL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_FW_MAJOR_VERH, &uc_h);
	if (0 != i_ret) {
		cfs_loge("read major fw fail");
		return i_ret;	
	}	
	*pus_major_ver = ((uc_h << 8) | uc_l);
	
	i_ret  = cfs_read_reg(REG_CFS_FW_MINOR_VERL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_FW_MINOR_VERH, &uc_h);
	if (0 != i_ret) {
		cfs_loge("read minor fw fail");
		return i_ret;	
	}	
	*pus_minor_ver = ((uc_h << 8) | uc_l);
	
	return i_ret;
}

/**
* @function: cfs_get_power_vrect
* @brief: get power information actual Vrect
* @param: pus_vrect output power info actual Vrect (unit:mV)
* @return: 0 success or -1 fail
*/
int32_t cfs_get_power_vrect(uint16_t *pus_vrect)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;
	
	if (!pus_vrect)
		return -1;

	i_ret  = cfs_read_reg(REG_CFS_PWR_INFO_VRECTL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_PWR_INFO_VRECTH, &uc_h);
	*pus_vrect = ((uc_h << 8) | uc_l);
	if (0 != i_ret) {
		cfs_loge("get vrect fail");
	}
	
	return i_ret;
}

/**
* @function: cfs_get_power_vout
* @brief: get power information actual Vout
* @param: pus_vout output power info actual Vout (unit:mV)
* @return: 0 success or -1 fail
*/
int32_t cfs_get_power_vout(uint16_t *pus_vout)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;
	
	if (!pus_vout)
		return -1;
	
	i_ret  = cfs_read_reg(REG_CFS_PWR_INFO_VOUTL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_PWR_INFO_VOUTH, &uc_h);
	*pus_vout = ((uc_h << 8) | uc_l);
	if (0 != i_ret) {
		cfs_loge("get vout fail");
	}
	
	return i_ret;
}

/**
* @function: cfs_get_power_iout
* @brief: get power information actual Iout
* @param: pus_iout output power info actual Iout (unit:mA)
* @return: 0 success or -1 fail
*/
int32_t cfs_get_power_iout(uint16_t *pus_iout)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;
	
	if (!pus_iout)
		return -1;
	
	i_ret  = cfs_read_reg(REG_CFS_PWR_INFO_IOUTL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_PWR_INFO_IOUTH, &uc_h);
	*pus_iout = ((uc_h << 8) | uc_l);
	if (0 != i_ret) {
		cfs_loge("get iout fail");
	}
	
	return i_ret;
}

/**
* @function: cfs_get_power_freq
* @brief: get power information AC Frequency
* @param: pui_freq output power info AC Frequency (unit:Hz)
* @return: 0 success or -1 fail
*/
int32_t cfs_get_power_freq(uint32_t *pui_freq)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;
	
	if (!pui_freq)
		return -1;
	
	i_ret  = cfs_read_reg(REG_CFS_PWR_INFO_FREQL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_PWR_INFO_FREQH, &uc_h);
	*pui_freq = ((uc_h << 8) | uc_l) * 10;
	if (0 != i_ret) {
		cfs_loge("get freq fail");
	}
	
	return i_ret;
}

/**
* @function: cfs_get_power
* @brief: get power information actual received power
* @param: pus_power output power info actual received power (unit:mW)
* @return: 0 success or -1 fail
*/
int32_t cfs_get_power(uint16_t *pus_power)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;
	
	if (!pus_power)
		return -1;
	
	i_ret  = cfs_read_reg(REG_CFS_PWR_INFO_PWRL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_PWR_INFO_PWRH, &uc_h);
	*pus_power = ((uc_h << 8) | uc_l);
	if (0 != i_ret) {
		cfs_loge("get powe fail");
	}

	return i_ret;
}

/**
* @function: cfs_get_power_voset
* @brief: get power information actual target Vout
* @param: pus_voset output power info actual target Vout (unit:mV)
* @return: 0 success or -1 fail
*/
int32_t cfs_get_power_voset(uint16_t *pus_voset)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;
	
	if (!pus_voset)
		return -1;
	
	i_ret  = cfs_read_reg(REG_CFS_PWR_INFO_VOSETL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_PWR_INFO_VOSETH, &uc_h);
	*pus_voset = ((uc_h << 8) | uc_l);
	if (0 != i_ret) {
		cfs_loge("get target vout fail");
	}

	return i_ret;
}

/**
* @function: cfs_get_power_vrset
* @brief: get power information actual target Vrect
* @param: pus_vrset output power info actual target Vrect (unit:mV)
* @return: 0 success or -1 fail
*/
int32_t cfs_get_power_vrset(uint16_t *pus_vrset)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;
	
	if (!pus_vrset)
		return -1;
	
	i_ret  = cfs_read_reg(REG_CFS_PWR_INFO_VRSETL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_PWR_INFO_VRSETH, &uc_h);
	*pus_vrset = ((uc_h << 8) | uc_l);
	if (0 != i_ret) {
		cfs_loge("get target vrect fail");
	}

	return i_ret;
}

/**
* @function: cfs_set_ept
* @brief: set End power transfer packet value
* @param: em_ept if this value is not 0xff, the PRx will be sent End Power Transfer packet to PTx 
* @return: 0 success or -1 fail
*/
int32_t cfs_set_ept(cfs_ept_e em_ept)
{
	int32_t i_ret 	= 0;
	
	i_ret = cfs_write_reg(REG_CFS_EPT, em_ept);
	if (0 != i_ret) {
		cfs_loge("Set EPT fail");
	}

	return i_ret;
}

/**
* @function: cfs_get_oper_vout
* @brief: get operation infomation Vout value
* @param: pui_vout output Vout, Vout = 18 * reg_val / 4095 (unit:V) 
* @return: 0 success or -1 fail
*/
int32_t cfs_get_oper_vout(uint32_t *pui_vout)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;
	uint16_t us_vout = 0;

	if (!pui_vout)
		return -1;

	i_ret  = cfs_read_reg(REG_CFS_OPER_VOUTL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_OPER_VOUTH, &uc_h);
	if (0 != i_ret) {
		cfs_loge("get oper vout fail");
		return i_ret;	
	}
	us_vout = ((uc_h << 8) | uc_l);	
	*pui_vout = (us_vout * 18) / 4095;

	return i_ret;
}

/**
* @function: cfs_set_oper_vout
* @brief: set operation infomation Vout value
* @param: ui_vout input Vout, Vout = 18 * reg_val / 4095 (unit:V) 
* @return: 0 success or -1 fail
*/
int32_t cfs_set_oper_vout(uint32_t ui_vout)
{
	int32_t i_ret 	= 0;
	uint16_t us_vout = (ui_vout * 4095) / 18;

	i_ret  = cfs_write_reg(REG_CFS_OPER_VOUTH, (uint8_t)((us_vout >> 8) & 0xFF));
	i_ret |= cfs_write_reg(REG_CFS_OPER_VOUTL, (uint8_t)(us_vout & 0xFF));
	if (0 != i_ret) {
		cfs_loge("set oper vout fail");
		return i_ret;	
	}

	return i_ret;
}

/**
* @function: cfs_get_oper_vrect
* @brief: get operation infomation Vrect value
* @param: pui_vrect output Vrect, Vrect = 20 * reg_val / 4095 (unit:V) 
* @return: 0 success or -1 fail
*/
int32_t cfs_get_oper_vrect(uint32_t *pui_vrect)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;
	uint16_t us_vrect = 0;

	if (!pui_vrect)
		return -1;

	i_ret  = cfs_read_reg(REG_CFS_OPER_VRECTL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_OPER_VRECTH, &uc_h);
	if (0 != i_ret) {
		cfs_loge("get oper vrect fail");
		return i_ret;	
	}
	us_vrect = ((uc_h << 8) | uc_l);	
	*pui_vrect = (us_vrect * 20) / 4095;

	return i_ret;
}

/**
* @function: cfs_set_oper_vrect
* @brief: set operation infomation Vrect value
* @param: ui_vrect input Vrect, Vrect = 18 * reg_val / 4095 (unit:V) 
* @return: 0 success or -1 fail
*/
int32_t cfs_set_oper_vrect(uint32_t ui_vrect)
{
	int32_t i_ret 	= 0;
	uint16_t us_vrect = (ui_vrect * 4095) / 20;

	i_ret  = cfs_write_reg(REG_CFS_OPER_VRECTH, (uint8_t)((us_vrect >> 8) & 0xFF));
	i_ret |= cfs_write_reg(REG_CFS_OPER_VRECTL, (uint8_t)(us_vrect & 0xFF));
	if (0 != i_ret) {
		cfs_loge("set oper vrect fail");
		return i_ret;	
	}

	return i_ret;
}

/**
* @function: cfs_get_oper_iout
* @brief: get operation infomation Iout value
* @param: pui_iout output Iout, Iout = reg_val(adc val) 
* @return: 0 success or -1 fail
*/
int32_t cfs_get_oper_iout(uint16_t *pus_iout)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;

	if (!pus_iout)
		return -1;

	i_ret  = cfs_read_reg(REG_CFS_OPER_IOUTL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_OPER_IOUTH, &uc_h);
	if (0 != i_ret) {
		cfs_loge("get oper iout fail");
		return i_ret;	
	}
	*pus_iout = ((uc_h << 8) | uc_l);	

	return i_ret;
}

/**
* @function: cfs_set_oper_iout
* @brief: set operation infomation Iout value
* @param: ui_iout input Iout, Iout = reg_val(adc val) (unit:mA) 
* @return: 0 success or -1 fail
*/
int32_t cfs_set_oper_iout(uint16_t us_iout)
{
	int32_t i_ret 	= 0;

	i_ret  = cfs_write_reg(REG_CFS_OPER_IOUTH, (uint8_t)((us_iout >> 8) & 0xFF));
	i_ret |= cfs_write_reg(REG_CFS_OPER_IOUTL, (uint8_t)(us_iout & 0xFF));
	if (0 != i_ret) {
		cfs_loge("set oper iout fail");
		return i_ret;	
	}

	return i_ret;
}

/**
* @function: cfs_get_oper_temp
* @brief: get operation infomation temperature adc val
* @param: pus_temp output temperature value, pus_temp = reg_val(adc val) 
* @return: 0 success or -1 fail
*/
int32_t cfs_get_oper_temp(uint16_t *pus_temp)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;

	if (!pus_temp)
		return -1;

	i_ret  = cfs_read_reg(REG_CFS_OPER_TEMPL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_OPER_TEMPH, &uc_h);
	if (0 != i_ret) {
		cfs_loge("get oper temp fail");
		return i_ret;	
	}
	*pus_temp = ((uc_h << 8) | uc_l);	

	return i_ret;
}

/**
* @function: cfs_set_oper_temp
* @brief: set operation infomation temperature adc val
* @param: us_temp input temperature value, us_temp = reg_val(adc val) 
* @return: 0 success or -1 fail
*/
int32_t cfs_set_oper_temp(uint16_t us_temp)
{
	int32_t i_ret 	= 0;

	i_ret  = cfs_write_reg(REG_CFS_OPER_TEMPH, (uint8_t)((us_temp >> 8) & 0xFF));
	i_ret |= cfs_write_reg(REG_CFS_OPER_TEMPL, (uint8_t)(us_temp & 0xFF));
	if (0 != i_ret) {
		cfs_loge("set oper temp fail");
		return i_ret;	
	}

	return i_ret;
}

/**
* @function: cfs_get_oper_freq
* @brief: get operation infomation AC Frequency
* @param: pui_freq output AC Frequency, pui_freq = 15000000 * 32 / reg_val (unit:Hz)
* @return: 0 success or -1 fail
*/
int32_t cfs_get_oper_freq(uint32_t *pui_freq)
{
	int32_t i_ret 	= 0;
	uint8_t	uc_l 	= 0;
	uint8_t	uc_h 	= 0;
	uint16_t us_freq = 0;
	
	if (!pui_freq)
		return -1;

	i_ret  = cfs_read_reg(REG_CFS_OPER_FREQL, &uc_l);
	i_ret |= cfs_read_reg(REG_CFS_OPER_FREQH, &uc_h);
	if (0 != i_ret) {
		cfs_loge("get oper freq fail");
		return i_ret;	
	}
	us_freq = ((uc_h << 8) | uc_l);
	*pui_freq = (15000000 * 32) / us_freq;	

	return i_ret;
}

/**
* @function: cfs_set_oper_freq
* @brief: set operation infomation AC Frequency
* @param: ui_freq input AC Frequency, ui_freq = 15000000 * 32 / reg_val (unit:Hz)
* @return: 0 success or -1 fail
*/
int32_t cfs_set_oper_freq(uint32_t ui_freq)
{
	int32_t i_ret 	= 0;
	uint16_t us_freq = 0;

	us_freq = (15000000 * 32) / ui_freq;
	i_ret  = cfs_write_reg(REG_CFS_OPER_FREQH, (uint8_t)((us_freq >> 8) & 0xFF));
	i_ret |= cfs_write_reg(REG_CFS_OPER_FREQL, (uint8_t)(us_freq & 0xFF));
	if (0 != i_ret) {
		cfs_loge("set oper freq fail");
		return i_ret;	
	}

	return i_ret;
}

/**
* @function: cfs_get_oper_misc
* @brief: get oper misc  
* @param: pst_misc output misc status
* @return: 0 success or -1 fail
*/
int32_t cfs_get_oper_misc(cfs_misc_s *pst_misc)
{
	int32_t i_ret = 0;
	
	if (!pst_misc)
		return -1;

	i_ret = cfs_read_reg(REG_CFS_OPER_MISC, &pst_misc->uc_data);
	if (0 != i_ret) {
		cfs_loge("get MISC fail");
		return i_ret;	
	}
	
	return i_ret; 
}

/**
* @function: cfs_set_oper_misc
* @brief: get oper misc  
* @param: pst_misc output misc status
* @return: 0 success or -1 fail
*/
int32_t cfs_set_oper_misc(cfs_misc_s *pst_misc)
{
	int32_t i_ret = 0;
	
	if (!pst_misc)
		return -1;

	i_ret = cfs_write_reg(REG_CFS_OPER_MISC, pst_misc->uc_data);
	if (0 != i_ret) {
		cfs_loge("set MISC fail");
		return i_ret;	
	}
	
	return i_ret; 
}

/**
* @function: cfs_get_oper_align
* @brief: get rx align status  
* @param: pst_align output align x and y
* @return: 0 success or -1 fail
*/
int32_t cfs_get_oper_align(cfs_align_s *pst_align)
{
	int32_t i_ret = 0;
	
	if (!pst_align)
		return -1;

	i_ret  = cfs_read_reg(REG_CFS_XALIGN, (uint8_t *)&pst_align->c_x);
	i_ret |= cfs_read_reg(REG_CFS_YALIGN, (uint8_t *)&pst_align->c_y);
	if (0 != i_ret) {
		cfs_loge("get align fail");
		return i_ret;	
	}
	
	return i_ret; 
} 

/** 
* @function: cfs_get_recf_mode * @brief: get rectifier control mode
* @param: pem_mode output rectifier control mode (cfs_recf_mode_e) 
* @return: 0 success or -1 fail
*/
int32_t cfs_get_recf_mode(cfs_recf_mode_e *pem_mode)
{
	int32_t i_ret = 0;

	if (!pem_mode)
		return -1;

	i_ret = cfs_read_reg(REG_CFS_CTRL_RECTIFIER_MODE, (uint8_t *)pem_mode);
	if (0 != i_ret) {
		cfs_loge("get rectifier mode fail");
		return i_ret;	
	}

	return i_ret;
}

/**
* @function: cfs_get_recf_mode
* @brief: set rectifier control mode
* @param: em_mode input rectifier control mode (cfs_recf_mode_e) 
* @return: 0 success or -1 fail
*/
int32_t cfs_set_recf_mode(cfs_recf_mode_e em_mode)
{
	int32_t i_ret = 0;

	i_ret = cfs_write_reg(REG_CFS_CTRL_RECTIFIER_MODE, em_mode);
	if (0 != i_ret) {
		cfs_loge("set rectifier mode fail");
		return i_ret;	
	}
	
	return i_ret;
}

/**
* @function: cfs_set_recf_iout
* @brief: set rectifier Iout where the rectifier control mode changed.
* @param: us_reg reg addr 
* @param: us_iout input recf Iout (unit:mA) 
* @return: 0 success or -1 fail
*/
int32_t cfs_set_recf_iout(uint16_t us_reg, uint16_t us_iout)
{
	int32_t i_ret = -1;
	
	i_ret = cfs_write_reg(us_reg, us_iout / 10); 	
	if (0 != i_ret) {
		cfs_loge("set rectifier chg current fail");
		return i_ret;	
	}
	
	return i_ret;
}

/**
* @function: cfs_get_vrect_ofs
* @brief: get Vrect offset value
* @param: em_offs input Vrect offset level (cfs_vrect_offset_e) 
* @param: pui_vrect_offs output Vrect offset (unit: mV) 
* @return: 0 success or -1 fail
*/
int32_t cfs_get_vrect_ofs(cfs_vrect_offset_e em_offs, uint32_t *pui_vrect_offs)
{
	int32_t i_ret = 0;	
	uint8_t uc_vrect_offs = 0;	

	switch(em_offs) {
	case CFS_VRECT_OFS0P00:
	i_ret = cfs_read_reg(REG_CFS_CTRL_VRECT_OFS0P00, &uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P01:
	i_ret = cfs_read_reg(REG_CFS_CTRL_VRECT_OFS0P01, &uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P02:
	i_ret = cfs_read_reg(REG_CFS_CTRL_VRECT_OFS0P02, &uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P03:
	i_ret = cfs_read_reg(REG_CFS_CTRL_VRECT_OFS0P03, &uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P04:
	i_ret = cfs_read_reg(REG_CFS_CTRL_VRECT_OFS0P04, &uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P05:
	i_ret = cfs_read_reg(REG_CFS_CTRL_VRECT_OFS0P05, &uc_vrect_offs);	
	break;

	case CFS_VRECT_OFS0P06:
	i_ret = cfs_read_reg(REG_CFS_CTRL_VRECT_OFS0P06, &uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P07:
	i_ret = cfs_read_reg(REG_CFS_CTRL_VRECT_OFS0P07, &uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P08:
	i_ret = cfs_read_reg(REG_CFS_CTRL_VRECT_OFS0P08, &uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P09:
	i_ret = cfs_read_reg(REG_CFS_CTRL_VRECT_OFS0P09, &uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P10:
	i_ret = cfs_read_reg(REG_CFS_CTRL_VRECT_OFS0P10, &uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P11:
	i_ret = cfs_read_reg(REG_CFS_CTRL_VRECT_OFS0P11, &uc_vrect_offs);	
	break;
	
	default:
	break;
	}
	
	if (0 != i_ret) {
		cfs_loge("get vrect offset fail");
		return i_ret;	
	}
	*pui_vrect_offs = uc_vrect_offs * 20;	

	return i_ret;
}

/**
* @function: cfs_set_vrect_ofs
* @brief: set Vrect offset value
* @param: em_offs input Vrect offset level (cfs_vrect_offset_e) 
* @param: ui_vrect_offs input Vrect offset (unit: mV) 
* @return: 0 success or -1 fail
*/
int32_t cfs_set_vrect_ofs(cfs_vrect_offset_e em_offs, uint32_t ui_vrect_offs)
{
	int32_t i_ret = 0;	
	uint8_t uc_vrect_offs = ui_vrect_offs / 20;	
		
	switch(em_offs) {
	case CFS_VRECT_OFS0P00:
	i_ret = cfs_write_reg(REG_CFS_CTRL_VRECT_OFS0P00, uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P01:
	i_ret = cfs_write_reg(REG_CFS_CTRL_VRECT_OFS0P01, uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P02:
	i_ret = cfs_write_reg(REG_CFS_CTRL_VRECT_OFS0P02, uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P03:
	i_ret = cfs_write_reg(REG_CFS_CTRL_VRECT_OFS0P03, uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P04:
	i_ret = cfs_write_reg(REG_CFS_CTRL_VRECT_OFS0P04, uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P05:
	i_ret = cfs_write_reg(REG_CFS_CTRL_VRECT_OFS0P05, uc_vrect_offs);	
	break;

	case CFS_VRECT_OFS0P06:
	i_ret = cfs_write_reg(REG_CFS_CTRL_VRECT_OFS0P06, uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P07:
	i_ret = cfs_write_reg(REG_CFS_CTRL_VRECT_OFS0P07, uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P08:
	i_ret = cfs_write_reg(REG_CFS_CTRL_VRECT_OFS0P08, uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P09:
	i_ret = cfs_write_reg(REG_CFS_CTRL_VRECT_OFS0P09, uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P10:
	i_ret = cfs_write_reg(REG_CFS_CTRL_VRECT_OFS0P10, uc_vrect_offs);	
	break;
	
	case CFS_VRECT_OFS0P11:
	i_ret = cfs_write_reg(REG_CFS_CTRL_VRECT_OFS0P11, uc_vrect_offs);	
	break;
	
	default:
	break;
	}
	
	if (0 != i_ret) {
		cfs_loge("set vrect offset fail");
		return i_ret;	
	}

	return i_ret;
}

/**
* @function: cfs_get_dummy_load
* @brief: get dummy load configuraion
* @param: pst_dummy_load output dummy load configuration (cfs_dummy_load_s) 
* @return: 0 success or -1 fail
*/
int32_t cfs_get_dummy_load(cfs_dummy_load_s *pst_dummy_load)
{
	int32_t i_ret = 0;
	
	if (!pst_dummy_load)
		return -1;
	
	i_ret = cfs_read_reg(REG_CFS_DUMMY_LOAD, &pst_dummy_load->uc_data);
	if (0 != i_ret) {
		cfs_loge("get dummy load fail");
	}

	return i_ret;
}

/**
* @function: cfs_set_dummy_load
* @brief: set dummy load configuraion
* @param: pst_dummy_load input dummy load configuration (cfs_dummy_load_s);
*			if cfs_dummy_load_s.uc_lit_mode=1 dummy_load -> on;
*			if cfs_dummy_load_s.uc_lit_mode=0 dummy_load -> off;
*			dummy load current = (cfs_dummy_load_s.uc_lit_cont * 25) mA; 
* @return: 0 success or -1 fail
*/
int32_t cfs_set_dummy_load(cfs_dummy_load_s *pst_dummy_load)
{
	int32_t i_ret = 0;
	
	if (!pst_dummy_load)
		return -1;
	
	i_ret = cfs_write_reg(REG_CFS_DUMMY_LOAD, pst_dummy_load->uc_data);
	if (0 != i_ret) {
		cfs_loge("get dummy load fail");
	}

	return i_ret;
}

/**
* @function: cfs_get_mldo0
* @brief: get MLDO 0 control configuraion
* @param: pst_mldo output MLDO 0 configuration (cfs_mldo_s) 
* @return: 0 success or -1 fail
*/
int32_t cfs_get_mldo0(cfs_mldo_s *pst_mldo)
{
	int32_t i_ret = 0;
	
	if (!pst_mldo)
		return -1;

	i_ret = cfs_read_reg(REG_CFS_WPC_MLDO, &pst_mldo->uc_data);
	if (0 != i_ret) {
		cfs_loge("get mldo fail");
	}
	
	return i_ret;
}

/**
* @function: cfs_set_mldo0
* @brief: set MLDO 0 control configuraion
* @param: pst_mldo input MLDO 0 configuration (cfs_mldo_s); 
* 			if cfs_mldo_s.uc_pen_ldo=1 && cfs_mldo_s.uc_soft_wdt = 1 LDO -> on;   
* 			if cfs_mldo_s.uc_pen_ldo=0 && cfs_mldo_s.uc_soft_wdt = 0 LDO -> off;   
* @return: 0 success or -1 fail
*/
int32_t cfs_set_mldo0(cfs_mldo_s *pst_mldo)
{
	int32_t i_ret = 0;
	
	if (!pst_mldo)
		return -1;

	i_ret = cfs_write_reg(REG_CFS_WPC_MLDO, pst_mldo->uc_data);
	if (0 != i_ret) {
		cfs_loge("set mldo fail");
	}
	
	return i_ret;
}

/**
* @function: cfs_snd_msg
* @brief: MCU send msg to RX
* @param: pst_msg input msg data 
* @return: 0 success or -1 fail
*/
int32_t cfs_snd_msg(cfs_msg_s *pst_msg)
{
	int32_t i_ret = 0;
	
	if (!pst_msg)
		return -1;

	if (!gst_cfs.set) 
		return -1; 	
	
	i_ret = gst_cfs.set(REG_CFS_TXMSG, pst_msg->auc_byte, sizeof(cfs_msg_s));
	if (0 != i_ret) {
		cfs_loge("cfs send msg fail");	
	}

	return i_ret;
}

/**
* @function: cfs_rcv_msg
* @brief: MCU receive msg from RX
* @param: pst_msg output msg data 
* @return: 0 success or -1 fail
*/
int32_t cfs_rcv_msg(cfs_msg_s *pst_msg)
{
	int32_t i_ret = 0;
	
	if (!pst_msg)
		return -1;

	if (!gst_cfs.get) 
		return -1; 	
	
	i_ret = gst_cfs.get(REG_CFS_TXMSG, pst_msg->auc_byte, sizeof(cfs_msg_s));
	if (0 != i_ret) {
		cfs_loge("cfs recv msg fail");	
	}

	return i_ret;
}

