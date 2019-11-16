/*
* @File  		:	cfs.h
* @Description	: 	Celfras external register control driver
* @Date			: 	2019.06.24	
*/
#ifndef __CFS_H__
#define __CFS_H__

/** Celfras Log define */
#ifdef CFS_LOG_ENABLE
#define cfs_logi(format, arg...) printf("INFOM: " format "\r\n", ##arg)
#define cfs_logw(format, arg...) printf("WARN: " format "\r\n", ##arg)
#define cfs_loge(format, arg...) printf("ERROR: " format "\r\n", ##arg)
#else
#define cfs_logi(format, arg...) do{}while(0)
#define cfs_logw(format, arg...) do{}while(0)
#define cfs_loge(format, arg...) do{}while(0)
#endif

/** Celfras slave addr */
#define CFS_SLAVE_ADDR					(0x24 << 1)

/** Celfras slave addr */
#define CFS_DATA_MAXLEN					(0x04)

/** Celfras external register define */
#define REG_CFS_CHIPIDL                 (0x0000)  /** Chip ID.L (Read Only) */
#define REG_CFS_CHIPIDH                 (0x0001)  /** Chip ID.H (Read Only) */
#define REG_CFS_HW_VER					(0x0002)  /** Hardware Version */
#define REG_CFS_CUSTOMER_ID				(0x0003)  /** Customer ID */
#define REG_CFS_FW_MAJOR_VERL           (0x0004)  /** Firmware major version.L (Read Only) */
#define REG_CFS_FW_MAJOR_VERH           (0x0005)  /** Firmware major version.H (Read Only) */
#define REG_CFS_FW_MINOR_VERL           (0x0006)  /** Firmware minor version.L (Read Only) */
#define REG_CFS_FW_MINOR_VERH           (0x0007)  /** Firmware minor version.H (Read Only) */
#define REG_CFS_PWR_INFO_VRECTL         (0x0010)  /** Power Information.Vrect.L (Read Only) */
#define REG_CFS_PWR_INFO_VRECTH         (0x0011)  /** Power Information.Vrect.H (Read Only) */
#define REG_CFS_PWR_INFO_VOUTL          (0x0012)  /** Power Information.Vout.L (Read Only) */
#define REG_CFS_PWR_INFO_VOUTH          (0x0013)  /** Power Information.Vout.H (Read Only) */
#define REG_CFS_PWR_INFO_IOUTL          (0x0014)  /** Power Information.Iout.L (Read Only) */
#define REG_CFS_PWR_INFO_IOUTH          (0x0015)  /** Power Information.Iout.H (Read Only) */
#define REG_CFS_PWR_INFO_FREQL          (0x0016)  /** Power Information.Freq.L (Read Only) */
#define REG_CFS_PWR_INFO_FREQH          (0x0017)  /** Power Information.Freq.H (Read Only) */
#define REG_CFS_PWR_INFO_PWRL           (0x0018)  /** Power Information.Power.L (Read Only) */
#define REG_CFS_PWR_INFO_PWRH           (0x0019)  /** Power Information.Power.H (Read Only) */
#define REG_CFS_PWR_INFO_VOSETL			(0x001A)  /** Power Information.Target Vout.L */
#define REG_CFS_PWR_INFO_VOSETH			(0x001B)  /** Power Information.Target Vout.H */
#define REG_CFS_PWR_INFO_VRSETL			(0x001C)  /** Power Information.Target Vrect.L */
#define REG_CFS_PWR_INFO_VRSETH			(0x001D)  /** Power Information.Target Vrect.H */
#define REG_CFS_CTRL_ERR				(0x0020)  /** Control Error Counter */
#define REG_CFS_RPP						(0x0024)  /** Received Power Packet */
#define REG_CFS_TRIM_CONFIG_MODE        (0x002D)  /** Trim configuration.Mode */
#define REG_CFS_TRIM_CONFIG_JUDGEMENT   (0x0022)  /** Trim configuration.Judgement */
#define REG_CFS_TRIM_CONFIG_TEST_VOUTL  (0x0028)  /** Trim configuration.Test Vout.L */
#define REG_CFS_TRIM_CONFIG_TEST_VOUTH  (0x0029)  /** Trim configuration.Test Vout.H */
#define REG_CFS_STATUS					(0x0034)  /** Status */
#define REG_CFS_INTSTATUS				(0x0036)  /** Interrupt Register */
#define REG_CFS_INTEN					(0x0038)  /** Interrupt Enable Register */
#define REG_CFS_CHG_VAL					(0x003A)  /** Battery Charge Status */
#define REG_CFS_EPT                     (0x003B)  /** End Power Transfer Packet Configure */
#define REG_CFS_OPER_VOUTL              (0x003C)  /** Operation information.Vout.L */
#define REG_CFS_OPER_VOUTH              (0x003D)  /** Operation information.Vout.H */
#define REG_CFS_OPER_VRECTL             (0x0040)  /** Operation information.Vrect.L */
#define REG_CFS_OPER_VRECTH             (0x0041)  /** Operation information.Vrect.H */
#define REG_CFS_OPER_IOUTL              (0x0044)  /** Operation information.Iout.L */
#define REG_CFS_OPER_IOUTH              (0x0045)  /** Operation information.Iout.H */
#define REG_CFS_OPER_TEMPL              (0x0046)  /** Operation information.Temp.L */
#define REG_CFS_OPER_TEMPH              (0x0047)  /** Operation information.Temp.H */
#define REG_CFS_OPER_FREQL              (0x0048)  /** Operation information.Freq.L */
#define REG_CFS_OPER_FREQH              (0x0049)  /** Operation information.Freq.H */
#define REG_CFS_XALIGN					(0x004B)  /** Align X */
#define REG_CFS_YALIGN					(0x004C)  /** Align Y */
#define REG_CFS_OPER_MISC				(0x004E)  /** Operation misc information */
#define REG_CFS_CTRL_P2H                (0x0080)  /** Control.Passive To Half */
#define REG_CFS_CTRL_H2P                (0x0081)  /** Control.Half To Passive */
#define REG_CFS_CTRL_H2F                (0x0082)  /** Control.Half To Full */
#define REG_CFS_CTRL_F2H                (0x0083)  /** Control.Full To Half */
#define REG_CFS_CTRL_RECTIFIER_MODE     (0x0084)  /** Control.Rectifier mode */
#define REG_CFS_CTRL_RECTIFIER_STATE    (0x0085)  /** Control.Rectifier state */
#define REG_CFS_CTRL_VRECT_OFS0P00      (0x0088)  /** Control.Vrect offset 0.00 */
#define REG_CFS_CTRL_VRECT_OFS0P01      (0x0089)  /** Control.Vrect offset 0.01 */
#define REG_CFS_CTRL_VRECT_OFS0P02      (0x008A)  /** Control.Vrect offset 0.02 */
#define REG_CFS_CTRL_VRECT_OFS0P03      (0x008B)  /** Control.Vrect offset 0.03 */
#define REG_CFS_CTRL_VRECT_OFS0P04      (0x008C)  /** Control.Vrect offset 0.04 */
#define REG_CFS_CTRL_VRECT_OFS0P05      (0x008D)  /** Control.Vrect offset 0.05 */
#define REG_CFS_CTRL_VRECT_OFS0P06      (0x008E)  /** Control.Vrect offset 0.06 */
#define REG_CFS_CTRL_VRECT_OFS0P07      (0x008F)  /** Control.Vrect offset 0.07 */
#define REG_CFS_CTRL_VRECT_OFS0P08      (0x0090)  /** Control.Vrect offset 0.08 */
#define REG_CFS_CTRL_VRECT_OFS0P09      (0x0091)  /** Control.Vrect offset 0.09 */
#define REG_CFS_CTRL_VRECT_OFS0P10      (0x0092)  /** Control.Vrect offset 0.10 */
#define REG_CFS_CTRL_VRECT_OFS0P11      (0x0093)  /** Control.Vrect offset 0.11 */
#define REG_CFS_DUMMY_LOAD				(0x3864)  /** Lit.Control Dummy Load */
#define REG_CFS_WPC_MLDO				(0x3860)  /** WPC.Control MLDO 0 */
#define REG_CFS_TXMSG					(0x9000)  /** Send Msgdata*/

/** EPT code define */
typedef enum {
	CFS_EPT_UNKNOWN			= 0x00,		/** EPT Code Unknown */
	CFS_EPT_CHGCOMP			= 0x01,		/** EPT Code Charge Complete */
	CFS_EPT_FAULT			= 0x02,		/** EPT Code Internal Fault */
	CFS_EPT_OTP				= 0x03,		/** EPT Code Over Temperature Protect */
	CFS_EPT_OVP				= 0x04,		/** EPT Code Over Voltage Protect */
	CFS_EPT_OCP				= 0x05,		/** EPT Code Over Current Protect */
	CFS_EPT_BATFAIL			= 0x06,		/** EPT Code Battery Fail */
	CFS_EPT_NORESP			= 0x08,		/** EPT Code No Response */
	CFS_EPT_NEGFAIL			= 0x0A,		/** EPT Code Nego Fail */
	CFS_EPT_RESTART			= 0x0B,		/** EPT Code Restart */
	CFS_EPT_DEFAULT			= 0xFF,
} cfs_ept_e;

/** Rectifier Mode define */
typedef enum {
	CFS_RECF_MODE_FW		= 0x00,
	CFS_RECF_MODE_HW		= 0x01,
	CFS_RECF_MODE_PASSIVE	= 0x02,
	CFS_RECF_MODE_HALF		= 0x03,
	CFS_RECF_MODE_FULL		= 0x04,
} cfs_recf_mode_e;

/** Vrect offset define */
typedef enum {
	CFS_VRECT_OFS0P00		= 0x00,
	CFS_VRECT_OFS0P01		= 0x01,
	CFS_VRECT_OFS0P02		= 0x02,
	CFS_VRECT_OFS0P03		= 0x03,
	CFS_VRECT_OFS0P04		= 0x04,
	CFS_VRECT_OFS0P05		= 0x05,
	CFS_VRECT_OFS0P06		= 0x06,
	CFS_VRECT_OFS0P07		= 0x07,
	CFS_VRECT_OFS0P08		= 0x08,
	CFS_VRECT_OFS0P09		= 0x09,
	CFS_VRECT_OFS0P10		= 0x0A,
	CFS_VRECT_OFS0P11		= 0x0B,
}  cfs_vrect_offset_e;

/** System status Struct define */
typedef union {
	uint8_t	uc_data;
	struct {
		uint8_t uc_ocp				:1; /** OVER_CURRENT */
		uint8_t uc_ovp				:1; /** OVER_VOLTAGE */	
		uint8_t uc_otp				:1; /** OVER_TEMP */
		uint8_t uc_ready			:1; /** RX Ready */
		uint8_t uc_vout_on			:1; /** RX Vout on */
		uint8_t uc_vout_chg			:1; /** RX Vout Changed */
		uint8_t uc_resv				:2;	/** Reservation */	
	};
} cfs_status_s;

/** Intr status Struct define */
typedef cfs_status_s cfs_intr_s;

/** Align Status Struct define */
typedef struct {
	int8_t	c_x;
	int8_t	c_y;
} cfs_align_s;

typedef union {
	uint8_t	uc_data;
	struct {
		uint8_t uc_resv0		:1;
		uint8_t uc_toggle_ldo	:1;	
		uint8_t uc_resv1		:1;
		uint8_t uc_snd_ept		:1;
		uint8_t uc_snd_csp		:1;
		uint8_t uc_clr_intr		:1;
		uint8_t uc_resv2		:2;
	};
} cfs_misc_s;

/** Dummy Load Struct define */
typedef union {
	uint8_t	uc_data;
	struct {
		uint8_t	uc_lit_mode	:1;	/** Enter the lit mode */	
		uint8_t	uc_reserv	:3; /** Reservation */	
		uint8_t	uc_lit_cont	:4; /** LIT_MODE current settings */	
	};
} cfs_dummy_load_s;

/** MLDO Control Struct define */
typedef union {
	uint8_t	uc_data;
	struct {
		uint8_t uc_pen_ldo		:1; /** PEN LDO*/	
		uint8_t uc_is_pen		:1; /** IS PEN */	
		uint8_t uc_ocl_pen		:1; /** OCL PEN */	
		uint8_t uc_soft_wdt		:1; /** Soft WDT */	
		uint8_t uc_trim_rfeed	:4; /** Trim Rfeed */	
	};
} cfs_mldo_s;

/** Msg data Struct define */
typedef union {
	uint32_t 	ui_data;
	uint8_t		auc_byte[4];
} cfs_msg_s;

/** cfs driver device define */
typedef struct {
	/** 
	* @description: set callback implement cfs dev i2c set 
	* @param: us_reg input cfs external register address	
	* @param: uc_val input cfs external register value	
	* @param: uc_len input data len	
	* @return: 0 success or -1 fail
	*/	
	int32_t (*set) (uint16_t us_reg, uint8_t *puc_val, uint8_t uc_len);
	/** 
	* @description: set callback implement cfs dev i2c get 
	* @param: us_reg input cfs external register address	
	* @param: puc_val output cfs external register value	
	* @param: uc_len input data len	
	* @return: 0 success or -1 fail
	*/	
	int32_t (*get) (uint16_t us_reg, uint8_t *puc_val, uint8_t uc_len);
} cfs_dev_s;

#define CFS_DEVICE_DEF(cfs_set, cfs_get) \
cfs_dev_s gst_cfs = {.set = cfs_set, .get = cfs_get };

/**
* @function: cfs_read_reg
* @brief: cfs i2c read external register
* @param: us_reg input external register addr
* @param: *puc_val output external register value
* @return: 0 success or -1 fail
*/
extern int32_t cfs_read_reg(uint16_t us_reg, uint8_t *puc_val);

/**
* @function: cfs_write_reg
* @brief: cfs i2c write external register
* @param: us_reg input external register addr
* @param: uc_val input external register value
* @return: 0 success or -1 fail
*/
extern int32_t cfs_write_reg(uint16_t us_reg, uint8_t uc_val);

/**
* @function: cfs_get_chip_id
* @brief: Get cfs chip id
* @param: *pus_id output chip id
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_chip_id(uint16_t *pus_id);

/**
* @function: cfs_get_fw_ver
* @brief: get cfs firmware version
* @param: pus_major_ver output firmware major version
* @param: pus_minor_ver output firmware minor version
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_fw_ver(uint16_t *pus_major_ver, uint16_t *pus_minor_ver);

/**
* @function: cfs_get_intr_status
* @brief: Get cfs intr status
* @param: *pst_stats output system status
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_intr_status(cfs_intr_s *pst_status);

/**
* @function: cfs_get_intr
* @brief: Get cfs intr config
* @param: *pst_stats output system status
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_intr(cfs_intr_s *pst_intr);

/**
* @function: cfs_set_intr
* @brief: Set cfs intr config
* @param: *pst_stats input system status
* @return: 0 success or -1 fail
*/
extern int32_t cfs_set_intr(cfs_intr_s *pst_intr);

/**
* @function: cfs_clr_intr
* @brief: clear cfs intr
* @return: 0 success or -1 fail
*/
extern int32_t cfs_clr_intr(void);

/**
* @function: cfs_get_power_vrect
* @brief: get power information Vrect
* @param: pus_vrect output power info actual Vrect (unit:mV)
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_power_vrect(uint16_t *pus_vrect);

/**
* @function: cfs_get_power_vout
* @brief: get power information Vout
* @param: pus_vout output power info actual Vout (unit:mV)
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_power_vout(uint16_t *pus_vout);

/**
* @function: cfs_get_power_iout
* @brief: get power information Iout
* @param: pus_iout output power info actual Iout (unit:mA)
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_power_iout(uint16_t *pus_iout);

/**
* @function: cfs_get_power_freq
* @brief: get power information AC Frequency
* @param: pui_freq output power info AC Frequency (unit:Hz)
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_power_freq(uint32_t *pui_freq);

/**
* @function: cfs_get_power
* @brief: get power information received power
* @param: pus_power output power info actual received power (unit:mW)
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_power(uint16_t *pus_power);

/**
* @function: cfs_get_power_voset
* @brief: get power information target Vout
* @param: pus_voset output power info target actual Vout (unit:mV)
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_power_voset(uint16_t *pus_voset);

/**
* @function: cfs_get_power_vrset
* @brief: get power information target Vrect
* @param: pus_vrset output power info target actual Vrect (unit:mV)
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_power_vrset(uint16_t *pus_vrset);

/**
* @function: cfs_set_ept
* @brief: set End power transfer packet value
* @param: em_ept if this value is not 0xff, the PRx will be sent End Power Transfer packet to PTx 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_set_ept(cfs_ept_e em_ept);

/**
* @function: cfs_get_oper_vout
* @brief: get operation infomation Vout value
* @param: pui_vout output Vout, Vout = 18 * reg_val / 4095 (unit:V) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_oper_vout(uint32_t *pui_vout);

/**
* @function: cfs_set_oper_vout
* @brief: set operation infomation Vout value
* @param: ui_vout input Vout, Vout = 18 * reg_val / 4095 (unit:V) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_set_oper_vout(uint32_t ui_vout);

/**
* @function: cfs_get_oper_vrect
* @brief: get operation infomation Vrect value
* @param: pui_vrect output Vrect, Vrect = 20 * reg_val / 4095 (unit:V) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_oper_vrect(uint32_t *pui_vrect);

/**
* @function: cfs_set_oper_vrect
* @brief: set operation infomation Vrect value
* @param: ui_vrect input Vrect, Vrect = 18 * reg_val / 4095 (unit:V) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_set_oper_vrect(uint32_t ui_vrect);

/**
* @function: cfs_get_oper_iout
* @brief: get operation infomation Iout value
* @param: pui_iout output Iout, Iout = reg_val(adc val) (unit:mA) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_oper_iout(uint16_t *pus_iout);

/**
* @function: cfs_set_oper_iout
* @brief: set operation infomation Iout value
* @param: ui_iout input Iout, Iout = reg_val(adc val) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_set_oper_iout(uint16_t us_iout);

/**
* @function: cfs_get_oper_temp
* @brief: get operation infomation temperature adc val
* @param: pus_temp output temperature value, pus_temp = reg_val(adc val) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_oper_temp(uint16_t *pus_temp);

/**
* @function: cfs_set_oper_temp
* @brief: set operation infomation temperature adc val
* @param: us_temp input temperature value, us_temp = reg_val(adc val) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_set_oper_temp(uint16_t us_temp);

/**
* @function: cfs_get_oper_freq
* @brief: get operation infomation AC Frequency
* @param: pui_freq output AC Frequency, pui_freq = 15000000 * 32 / reg_val (unit:Hz)
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_oper_freq(uint32_t *pui_freq);

/**
* @function: cfs_set_oper_freq
* @brief: set operation infomation AC Frequency
* @param: ui_freq input AC Frequency, ui_freq = 15000000 * 32 / reg_val (unit:Hz)
* @return: 0 success or -1 fail
*/
extern int32_t cfs_set_oper_freq(uint32_t ui_freq);

/**
* @function: cfs_get_oper_align
* @brief: get rx align status  
* @param: pst_align output align x and y
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_oper_align(cfs_align_s *pst_align);

/**
* @function: cfs_get_oper_misc
* @brief: get oper misc  
* @param: pst_misc output misc status
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_oper_misc(cfs_misc_s *pst_misc);

/**
* @function: cfs_set_oper_misc
* @brief: set oper misc  
* @param: pst_misc output misc status
* @return: 0 success or -1 fail
*/
extern int32_t cfs_set_oper_misc(cfs_misc_s *pst_misc);

/**
* @function: cfs_get_recf_mode
* @brief: get rectifier control mode
* @param: pem_mode output rectifier control mode (cfs_recf_mode_e) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_recf_mode(cfs_recf_mode_e *pem_mode);

/**
* @function: cfs_get_recf_mode
* @brief: set rectifier control mode
* @param: em_mode input rectifier control mode (cfs_recf_mode_e) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_set_recf_mode(cfs_recf_mode_e em_mode);

/**
* @function: cfs_set_recf_iout
* @brief: set rectifier Iout where the rectifier control mode changed.
* @param: us_reg reg addr 
* @param: us_iout input recf Iout (unit:mA) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_set_recf_iout(uint16_t us_reg, uint16_t us_iout);

/**
* @function: cfs_get_vrect_ofs
* @brief: get Vrect offset value
* @param: em_offs input Vrect offset level (cfs_vrect_offset_e) 
* @param: pui_vrect_offs output Vrect offset (unit: mV) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_vrect_ofs(cfs_vrect_offset_e em_offs, uint32_t *pui_vrect_offs);

/**
* @function: cfs_set_vrect_ofs
* @brief: set Vrect offset value
* @param: em_offs input Vrect offset level (cfs_vrect_offset_e) 
* @param: ui_vrect_offs input Vrect offset (unit: mV) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_set_vrect_ofs(cfs_vrect_offset_e em_offs, uint32_t ui_vrect_offs);

/**
* @function: cfs_get_dummy_load
* @brief: get dummy load configuraion
* @param: pst_dummy_load output dummy load configuration (cfs_dummy_load_s) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_dummy_load(cfs_dummy_load_s *pst_dummy_load);

/**
* @function: cfs_set_dummy_load
* @brief: set dummy load configuraion
* @param: pst_dummy_load input dummy load configuration (cfs_dummy_load_s);
*			if cfs_dummy_load_s.uc_lit_mode=1 dummy_load -> on;
*			if cfs_dummy_load_s.uc_lit_mode=0 dummy_load -> off;
*			dummy load current = (cfs_dummy_load_s.uc_lit_cont * 25) mA; 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_set_dummy_load(cfs_dummy_load_s *pst_dummy_load);

/**
* @function: cfs_get_mldo0
* @brief: get MLDO 0 control configuraion
* @param: pst_mldo output MLDO 0 configuration (cfs_mldo_s) 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_get_mldo0(cfs_mldo_s *pst_mldo);

/**
* @function: cfs_set_mldo0
* @brief: set MLDO 0 control configuraion
* @param: pst_mldo input MLDO 0 configuration (cfs_mldo_s); 
* 			if cfs_mldo_s.uc_pen_ldo=1 && cfs_mldo_s.uc_soft_wdt = 1 LDO -> on;   
* 			if cfs_mldo_s.uc_pen_ldo=0 && cfs_mldo_s.uc_soft_wdt = 0 LDO -> off;   
* @return: 0 success or -1 fail
*/
extern int32_t cfs_set_mldo0(cfs_mldo_s *pst_mldo);

/**
* @function: cfs_snd_msg
* @brief: MCU send msg to RX
* @param: pst_msg input msg data 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_snd_msg(cfs_msg_s *pst_msg);

/**
* @function: cfs_rcv_msg
* @brief: MCU receive msg from RX
* @param: pst_msg output msg data 
* @return: 0 success or -1 fail
*/
extern int32_t cfs_rcv_msg(cfs_msg_s *pst_msg);

#endif

