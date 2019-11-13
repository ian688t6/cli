#ifndef __CFSIO_H__
#define __CFSIO_H__

typedef struct {
	uint16_t 	us_reg;
	uint8_t		uc_val;
} __attribute__ ((packed)) cfsio_reg_s;

typedef struct {
	uint16_t	us_chip_id;
	uint16_t	us_major_vers;
	uint16_t	us_minor_vers;
} __attribute__ ((packed)) cfsio_versid_s;

extern void cfsio_init(void);

extern int32_t cfsio_reg_get(void *pv_arg);

extern int32_t cfsio_reg_set(void *pv_arg);

extern int32_t cfsio_versid_get(void *pv_arg);

#endif

