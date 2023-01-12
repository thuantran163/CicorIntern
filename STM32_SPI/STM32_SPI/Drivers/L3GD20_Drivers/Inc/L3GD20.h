/*
 * @file L3GD20.h
 * @brief L3GD20  three-axis digital gyroscope driver for stm32f411.h
 * @author Thuan Tran - Cicor Anam
 * @date 09.01.2023
 */
#ifndef __L3GD20_H__
#define __L3GD20_H__

#include <stdint.h>

/*________________________________________DEFINE________________________________________*/
/* Memory mapping*/
//#define RESERVED1_START_BASE 	    =	0x0000 0000UL	/* 8-bit registers address map*/
//#define RESERVED1_STOP_BASE 	    =	0x0000 000EUL	/* 8-bit registers address map*/
#define WHO_AM_I_BASE	     	0x0000000FUL	/* Readable register*/
//#define RESERVED2_START_BASE      = 	0x0000 0010FUL	/*Read-write register*/
//#define RESERVED2_STOP_BASE      = 	0x0000 001FUL	/*Read-write register*/
#define CTRL_REG1_BASE         	0x00000020UL	/*Read-write register*/
#define CTRL_REG2_BASE         	0x00000021UL	/*Read-write register*/
#define CTRL_REG3_BASE         	0x00000022UL	/*Read-write register*/
#define CTRL_REG4_BASE         	0x00000023UL	/*Read-write register*/
#define CTRL_REG5_BASE         	0x00000024UL	/*Read-write register*/
#define REFERENCE_BASE 	    	0x00000025UL	/*Read-write register*/
#define OUT_TEMP_BASE 	     	0x00000026UL	/* Readable register*/
#define STATUS_REG_BASE       	0x00000027UL	/* Readable register*/
#define OUT_X_L_BASE           	0x00000028UL 	/* Readable register*/
#define OUT_X_H_BASE         	0x00000029UL 	/* Readable register*/
#define OUT_Y_L_BASE           	0x0000002AUL	/* Readable register*/
#define OUT_Y_H_BASE           	0x0000002BUL	/* Readable register*/
#define OUT_Z_L_BASE 	       	0x0000002CUL	/* Readable register*/
#define OUT_Z_H_BASE           	0x0000002DUL	/* Readable register*/
#define FIFO_CTRL_REG_BASE 	 	0x0000002EUL	/*Read-write register*/
#define FIFO_SRC_REG_BASE		0x0000002FUL	/* Readable register*/
#define INT1_CFG_BASE			0x00000030UL	/*Read-write register*/
#define INT1_SRC_BASE			0x00000031UL	/* Readable register*/
#define INT1_TSH_XH_BASE       	0x00000032UL	/*Read-write register*/
#define INT1_TSH_XL_BASE       	0x00000033UL   /*Read-write register*/
#define INT1_TSH_YH_BASE       	0x00000034UL	/*Read-write register*/
#define INT1_TSH_YL_BASE       	0x00000035UL	/*Read-write register*/
#define INT1_TSH_ZH_BASE       	0x00000036UL 	/*Read-write register*/
#define INT1_TSH_ZL_BASE       	0x00000037UL	/*Read-write register*/
#define INT1_DURATION_BASE   	0x00000038UL 	/*Read-write register*/


/*________________________________________DEFAULT VALUE DECLARATIONS________________________________________*/
/* Default register configuration setting*/
typedef enum
{
	WHO_AM_I_DEFAULT 		= 0b11010100UL,
	CTRL_REG1_DEFAULT 		= 0b00000111UL,
	COMMON_DEFAULT_VALUE	= 0UL
}Register_DefaultValue;

/* DR and BW configuration setting*/
typedef enum
{
	ODR_CONF_95HZ  = 0x00,
	ODR_CONF_190HZ = 0x01,
	ODR_CONF_380HZ = 0x02,
	ODR_CONF_760HZ = 0x03,
}ODR_Configuration;

/* High-pass filter mode declarations*/
typedef enum
{
	HIGH_PASS_FILTER_NORMAL_MODE_RESET_READING  = 0x00,
	HIGH_PASS_FILTER_REFERENCE_SIGNAL_MODE 		= 0x01,
	HIGH_PASS_FILTER_NORMAL_MODE			    = 0x02,
	HIGH_PASS_FILTER_AUTORESET_MODE				= 0x03
}HighPassFilterMode_Configuration;

typedef enum
{
	CONTINUOUS_UPDATE = 0x0,
	WAIT_READING 	 = 0x1
}BlockDataUpdate_Selection;

typedef enum
{
	LSB_ENDIAN = 0x0,
	MSB_ENDIAN = 0x1
}EndianData_Selection;

typedef enum
{
	FULL_SCALE_SELECTION_250DPS 	= 0x00,
	FULL_SCALE_SELECTION_500DPS		= 0x01,
	FULL_SCALE_SELECTION_1000DPS	= 0x02,
	FULL_SCALE_SELECTION_2000DPS	= 0x03
}FullScale_Selection;

typedef enum
{
	POWER_DOWN 	    = 	0x00,
	POWER_SLEEP 	= 	0x01,
	POWER_NORMAL    =  	0x02,
}PowerMode_Selection;

typedef enum
{
	INTERFACE_2_WIRE = 0x0,
	INTERFACE_3_WIRE = 0x1,
}SPI_Mode_Selection;

typedef enum
{
	NORMAL_MODE = 0x0,
	REBOOT_MODE = 0x1,
}RebootMemory_Content;

typedef enum
{
	FIFO_ENABALE = 0x0,
	FIFO_DISABLE = 0x1
}FIFO_Selection;

typedef enum
{
	HPF_ENABLE 		= 0x0,
	HPF_DISABLE		= 0x1
}HighPassFilter_Selection;

typedef enum
{
	LPF1_OUTPUT = 0x00,
	HPF_OUTPUT  = 0x01,
	LBF2_OUTPUT = 0x02
}INT1_Out_Selection;

typedef enum
{
	BYPASS_MODE = 0x00,
	FIFO_MODE 	= 0x01,
	STREAM_MODE = 0x02,
	STREAM_TO_FIFO_MODE   = 0x03,
	BYPASS_TO_STREAM_MODE =	0x04
}FIFO_Mode_Selection;



/*________________________________________DATA STRUCTURES________________________________________*/

typedef struct
{
	uint8_t DR   : 2; 		/* Output data rate selection*/
	uint8_t BW   : 2; 		/* Bandwidth selection*/
	uint8_t PD   : 1; 		/* Power-down mode enable - Default value: 0*/
	uint8_t Zen  : 1;  		/* Z axis enable*/
	uint8_t Xen  : 1;		/* X axis enable*/
	uint8_t Yen  : 1;		/* Y axis enable*/
}CTRL_REG1_TypeDef;

typedef struct
{
    uint8_t HPM  : 2;		/*High-pass filter mode selection*/
    uint8_t HPCF : 4; 		/*High-pass filter cut off frequency configuration*/
}CTRL_REG2_TypeDef;

typedef struct
{
	uint8_t I1_Int1		: 1;  		/*Interrupt Enable on INT1 pin*/
	uint8_t I1_Boot		: 1;  		/*Boot status available on INT1*/
	uint8_t H_Lactive	: 1; 		/*Interrupt active configuration on INT1*/
	uint8_t PP_OD		: 1; 		/*Push-pull / Open drain. Default value: 0. (0: push- pull; 1: open drain)*/
	uint8_t I2_DRDY		: 1; 		/*Data-ready on DRDY/INT2*/
	uint8_t I2_WTM		: 1;		/*FIFO watermark interrupt on DRDY/INT2*/
	uint8_t I2_ORun		: 1;		/* FIFO overrun interrupt on DRDY/INT2*/
	uint8_t I2_Empty	: 1;		/* FIFO empty interrupt on DRDY/INT2*/
}CTRL_REG3_TypeDef;

typedef struct
{
	uint8_t BDU		: 1;    /*Block data update - Bit 0: continuosly update; 1: output registers not updated until MSb and LSb reading*/
	uint8_t BLE		: 1;    /*Big/little endian data selection - Bit 0: Data LSb @ lower address; 1: Data MSb @ lower address*/
	uint8_t FS 		: 1;  	/*Full scale selection */
	uint8_t SIM		: 1;    /* SPI serial interface mode selection - Bit 0: 4-wire interface; 1: 3-wire interface */
}CTRL_REG4_TypeDef;

typedef struct
{
	uint8_t BOOT		: 1;
	uint8_t FIFO_EN		: 1;
	uint8_t HPen		: 1;
	uint8_t INT1_Sel	: 2;
	uint8_t Out_Sel		: 2;
}CTRL_REG5_TypeDef;

typedef struct
{
	uint8_t ZYXOR	: 1;
	uint8_t ZOR		: 1;
	uint8_t YOR		: 1;
	uint8_t XOR		: 1;
	uint8_t ZYXDA	: 1;
	uint8_t ZDA		: 1;
	uint8_t YDA		: 1;
	uint8_t XDA		: 1;
} STATUS_REG_TypeDef;

typedef struct
{
	uint8_t WTM		: 4;
	uint8_t FM		: 3;
}FIFO_CTRL_REG_TypeDef;

typedef struct
{
	uint8_t FSS		: 5;
	uint8_t EMPTY	: 1;
	uint8_t OVRN 	: 1;
	uint8_t WTM		: 1;
}FIFO_SRC_REF_TypeDef;

typedef struct
{
	uint8_t XLIE 	: 1;
	uint8_t XHIE	: 1;
	uint8_t YLIE	: 1;
	uint8_t YHIE	: 1;
	uint8_t ZLIE	: 1;
	uint8_t ZHIE	: 1;
	uint8_t LIR		: 1;
	uint8_t AND_OR  : 1;
}INT1_CFG_TypdeDef;

typedef struct
{
	uint8_t XL       : 1;
	uint8_t XH       : 1;
	uint8_t YL       : 1;
	uint8_t YH       : 1;
	uint8_t ZL       : 1;
	uint8_t ZH       : 1;
}INT1_SRC_TypeDef;

typedef struct
{
	uint16_t  	THS_X 	: 15;
	uint16_t	THS_y	: 15;
	uint16_t	THS_Z	: 15;
}INT1_THS_VALUE;

typedef struct
{
	uint8_t WAIT		: 1;
	uint8_t DURATION 	: 7;
}INT1_DURATION;



///* Peripheral_declaration*/
//#define CTRL_REG1  ((CTRL_REG1_TypeDef*) CTRL_REG1_BASE)

#define BIT(n)                  ( 1<<(n) )
#define BTI_SHIF(a,n)			((a)<<(n))
#define BIT_SET(y, mask)        ( y |=  (mask) )
#define BIT_CLEAR(y, mask)      ( y &= ~(mask) )
#define BIT_FLIP(y, mask)       ( y ^=  (mask) )
#define BIT_EQ(y,flag) =  (((y)&(flag))==(flag))


//! Create a bitmask of length \a len.
#define BIT_MASK(len)           ( BIT(len)-1 )

//! Create a bitfield mask of length \a starting at bit \a start.
#define BF_MASK(start, len)     ( BIT_MASK(len)<<(start) )

//! Prepare a bitmask for insertion or combining.
#define _BF_PREP(x, start, len)  ( ((x)&BIT_MASK(len)) << (start) )

//! Extract a bitfield of length \a len starting at bit \a start from \a y.
#define _BF_GET(y, start, len)   ( ((y)>>(start)) & BIT_MASK(len) )

//! Insert a new bitfield value \a x into \a y.
#define _BF_SET(y, x, start, len)    \
    ( y= ((y) &~ BF_MASK(start, len)) | BF_PREP(x, start, len) )

//Prepare a named bit-field for for insterion or combination.
#define BFN_PREP(x, name) (((x)<<name##_Pos)&name##_Msk)

//Get the value of a named bitfield from y. Equivalent to (var=) y.name.
#define BFN_GET(y, name)   ( ((y) & name##_Msk)>>name##_Pos )

//Set a named bitfield in y to x. Equivalent to y.name= x.
#define 	BFN_SET(y, x, name)   (y = ((y)&~name##_Msk) | BFN_PREP(x,name) )

//Compare a named bitfield to named literal x.
#define 	BFN_CMP(y, x, name)   ( ((y)&name##_Msk) == (x) )

//Massage x for use in bitfield name with pre-shifted x.
#define 	BFN_PREP2(x, name)   ( (x) & name##_Msk )

//Get the value of bitfield name from y, but don't down-shift.
#define 	BFN_GET2(y, name)   ( (y) & name##_Msk )

//Set bitfield name from y to x with pre-shifted x.
#define 	BFN_SET2(y, x, name)   ( y = ((y)&~name##_Msk) | BFN_PREP2(x,name) )

//CTRL_REG1_YEN
//CTRL_REG1_YEN
//CTRL_REG1_XEN
//CTRL_REG1_XEN
//CTRL_REG1_ZEN
//CTRL_REG1_ZEN
//CTRL_REG1_PD
//CTRL_REG1_PD
//CTRL_REG1_BW
//CTRL_REG1_BW
//CTRL_REG1_DR
//CTRL_REG1_DR
#define CTRL_REG1_YEN_Pos 		0
#define CTRL_REG1_YEN_Msk 		BF_MASK(CTRL_REG1_YEN_Pos, 1)
#define CTRL_REG1_XEN_Pos		1
#define CTRL_REG1_XEN_Msk   	BF_MASK(CTRL_REG1_XEN_Pos, 1)
#define CTRL_REG1_ZEN_Pos		2
#define CTRL_REG1_ZEN_Msk 		BF_MASK(CTRL_REG1_ZEN_Pos, 1)
#define CTRL_REG1_PD_Pos		3
#define CTRL_REG1_PD_Msk 		BF_MASK(CTRL_REG1_PD_Pos, 1)
#define CTRL_REG1_BW_Pos		4
#define CTRL_REG1_BW_Msk		BF_MASK(CTRL_REG1_BW_Pos, 2)
#define CTRL_REG1_DR_Pos		6
#define CTRL_REG1_DR_Msk		BF_MASK(CTRL_REG1_DR_Pos, 2)
//CTRL_REG2_HPCF
//CTRL_REG2_HPCF
//CTRL_REG2_HPM
//CTRL_REG2_HPM
#define CTRL_REG2_HPCF_Pos		0
#define CTRL_REG2_HPCF_Msk		BF_MASK(CTRL_REG2_HPCF_POS, 4)
#define CTRL_REG2_HPM_Pos		4
#define CTRL_REG2_HPM_Msk		BF_MASK(CTRL_REG2_HPM_POS, 2)
//CTRL_REG3_I2_EMPTY
//CTRL_REG3_I2_ORUN
//CTRL_REG3_I2_WTM
//CTRL_REG3_I2_DRDY
//CTRL_REG3_PP_OD
//CTRL_REG3_H_LACTIVE
//CTRL_REG3_I1_BOOT
//CTRL_REG3_I1_INT1
#define CTRL_REG3_I2_EMPTY_Pos			0
#define CTRL_REG3_I2_EMPTY_Msk 			BK_MASK(CTRL_REG3_I2_EMPTY_Pos, 1)
#define CTRL_REG3_I2_ORUN_Pos			1
#define CTRL_REG3_I2_ORUN_Msk			BF_MASK(CTRL_REG3_I2_ORUN_Pos, 1)
#define CTRL_REG3_I2_WTM_Pos			2
#define CTRL_REG3_I2_WTM_Msk			BF_MASK(CTRL_REG3_I2_WTM_Pos, 1)
#define CTRL_REG3_I2_DRDY_Pos			3
#define CTRL_REG3_I2_DRDY_Msk			BF_MASK(CTRL_REG3_I2_DRDY_Pos, 1)
#define CTRL_REG3_PP_OD_Pos				4
#define CTRL_REG3_PP_OD_Msk				BF_MASK(CTRL_REG3_PP_OD_Pos, 1)
#define CTRL_REG3_H_LACTIVE_Pos			5
#define CTRL_REG3_H_LACTIVE_Msk			BF_MASK(CTRL_REG3_H_LACTIVE_Pos, 1)
#define CTRL_REG3_I1_BOOT_Pos			6
#define CTRL_REG3_I1_BOOT_Msk			BF_MASK(CTRL_REG3_I1_BOOT_Pos, 1)
#define CTRL_REG3_I1_INT1_Pos			7
#define CTRL_REG3_I1_INT1_Msk			BF_MASK(CTRL_REG3_I1_INT1_Pos, 1)
//CTRL_REG4_SIM
//CTRL_REG4_FS
//CTRL_REG4_BLE
//CTRL_REG4_BDUz
#define CTRL_REG4_SIM_Pos	0
#define CTRL_REG4_SIM_Msk 	BF_MASK(CTRL_REG4_SIM_Pos, 1)
#define CTRL_REG4_FS_Pos	4
#define CTRL_REG4_FS_Msk	BF_MASK(CTRL_REG4_FS_Pos, 2)
#define CTRL_REG4_BLE_Pos	6
#define CTRL_REG4_BLE_Msk	BF_MASK(CTRL_REG4_BLE_Pos, 1)
#define CTRL_REG4_BDU_Pos	7
#define CTRL_REG4_BDU_Msk	BF_MASK(CTRL_REG4_BDU_Pos, 1)
//CTRL_REG5_OUT_SEL
//CTRL_REG5_INT_SEL
//CTRL_REG5_HPEN
//CTRL_REG5_FIFO_EN
//CTRL_REG5_BOOT
#define CTRL_REG5_OUT_SEL_Pos		0
#define CTRL_REG5_OUT_SEL_Msk		BF_MASK(CTRL_REG5_OUT_SEL_Pos, 2)
#define CTRL_REG5_INT_SEL_Pos 		2
#define CTRL_REG5_INT_SEL_Msk		BF_MASK(CTRL_REG5_INT_SEL_Pos, 2)
#define CTRL_REG5_HPEN_Pos			5
#define CTRL_REG5_HPEN_Msk 			BF_MASK( CTRL_REG5_HPEN_Pos, 1)
#define CTRL_REG5_FIFO_EN_Pos		6
#define CTRL_REG5_FIFO_EN_Msk		BF_MASK(CTRL_REG5_FIFO_EN, 1)
#define CTRL_REG5_BOOT_Pos			7
#define CTRL_REG5_BOOT_Msk			BF_MASK(CTRL_REG5_BOOT_Pos, 1)

#define REFERENCE_REGISTER_Pos		0
#define REFERENCE_REGISTER_Msk 		BF_MASK(REFERENCE_REGISTER_Pos, 8)
#define OUT_TEMP_Pos				0
#define OUT_TEMP_Msk				BF_MASK(OUT_TEMP_Pos, 8)
//STATUS_REG_XDA
//STATUS_REG_YDA
//STATUS_REG_ZDA
//STATUS_REG_ZYXDA
//STATUS_REG_XOR
//STATUS_REG_YOR
//STATUS_REG_ZOR
//STATUS_REG_ZYXOR
#define STATUS_REG_XDA_Pos			0
#define STATUS_REG_XDA_Msk			BF_MASK(STATUS_REG_XDA_Pos, 1)
#define STATUS_REG_YDA_Pos			1
#define STATUS_REG_YDA_Msk 			BF_MASK(STATUS_REG_YDA_Pos, 1)
#define STATUS_REG_ZDA_Pos			2
#define STATUS_REG_ZDA_Msk			BF_MASK(STATUS_REG_ZDA_Pos, 1)
#define STATUS_REG_ZYXDA_Pos		3
#define STATUS_REG_ZYXDA_Msk		BF_MASK(STATUS_REG_ZYXDA_Pos, 1)
#define STATUS_REG_XOR_Pos 			4
#define STATUS_REG_XOR_Msk			BF_MASK(STATUS_REG_ZYXDA_Pos, 1)
#define STATUS_REG_YOR_Pos			5
#define STATUS_REG_YOR_Msk			BF_MASK(STATUS_REF_YOR_Pos, 1)
#define STATUS_REG_ZOR_Pos			6
#define STATUS_REG_ZOR_Msk 			BF_MASK(STATUS_REG_ZOR_Pos, 1)
#define STATUS_REG_ZYXOR_Pos		7
#define STATUS_REG_ZYXOR_Msk		BF_MASK(STATUS_REG_ZYXOR_Pos, 1)

#define OUT_X_H_Pos			0
#define OUT_X_H_Msk		 	BF_MASK(OUT_X_H_Pos, 8)
#define OUT_Y_H_Pos			0
#define OUT_Y_H_Msk      	BF_MASK(OUT_Y_H_Pos, 8)
#define OUT_Z_H_Pos			0
#define OUT_Z_H_Msk      	BF_MASK(OUT_Z_H_Pos, 8)
#define OUT_X_L_Pos			0
#define OUT_X_L_Msk      	BF_MASK(OUT_X_L_Pos, 8)
#define OUT_Y_L_Pos			0
#define OUT_Y_L_Msk      	BF_MASK(OUT_Y_L_Pos, 8)
#define OUT_Z_L_Pos			0
#define OUT_Z_L_Msk      	BF_MASK(OUT_Z_L_Pos, 8)

#define FIFO_CTRL_WTM_Pos		0
#define FIFO_CTRL_WTM_Msk		BF_MASK(FIFO_CTRL_WTM_Pos, 5)
#define FIFO_CTRL_FM_Pos		6
#define FIFO_CTRL_FM_Msk		BF_MASK(FIFO_CTRL_FM_Pos, 3)

#define FIFO_SRC_FSS_Pos		0
#define FIFO_SRC_FSS_Msk 		BF_MASK(FIFO_SRC_FSS_Pos, 5)
#define FIFO_SRC_EMPTY_Pos		5
#define FIFO_SRC_EMPTY_Msk		BF_MASK(FIFO_SRC_EMPTY_Pos, 1)
#define FIFO_SRC_OVRN_Pos		6
#define FIFO_SRC_OVRN_Msk		BF_MASK(FIFO_SRC_OVRN_Pos, 1)
#define FIFO_SRC_WTM_Pos		7
#define FIFO_SRC_WTM_Msk		BF_MASK(FIFO_SRC_WTM_Pos, 1)

#define INT1_CFG_XLIE_Pos 			0
#define INT1_CFG_XLIE_Msk			BF_MASK(INT1_CFG_XLIE_Pos, 1)
#define INT1_CFG_XHIE_Pos       	1
#define INT1_CFG_XHIE_Msk       	BF_MASK(INT1_CFG_XHIE_Pos, 1)
#define INT1_CFG_YLIE_Pos       	2
#define INT1_CFG_YLIE_Msk       	BF_MASK(INT1_CFG_YLIE_Pos, 1)
#define INT1_CFG_YHIE_Pos       	3
#define INT1_CFG_YHIE_Msk       	BF_MASK(INT1_CFG_YHIE_Pos, 1)
#define INT1_CFG_ZLIE_Pos       	4
#define INT1_CFG_ZLIE_Msk      		BF_MASK(INT1_CFG_ZLIE_Pos, 1)
#define INT1_CFG_ZHIE_Pos       	5
#define INT1_CFG_ZHIE_Msk   		BF_MASK(INT1_CFG_ZHIE_Pos, 1)
#define INT1_CFG_LIR_Pos       		6
#define INT1_CFG_LIR_Msk       		BF_MASK(INT1_CFG_LIR_Pos, 1)
#define INT1_CFG_AND_OR_Pos			7
#define INT1_CFG_AND_OR_Msk	    	BF_MASK(INT1_CFG_AND_OR_Pos, 1)

#define INT1_SRC_XL_Pos         0
#define INT1_SRC_XL_Msk         BF_MASK(INT1_SRC_XL_Pos,1)
#define INT1_SRC_XH_Pos         1
#define INT1_SRC_XH_Msk         BF_MASK(INT1_SRC_XH_Pos,1)
#define INT1_SRC_YL_Pos         2
#define INT1_SRC_YL_Msk         BF_MASK(INT1_SRC_YL_Pos,1)
#define INT1_SRC_YH_Pos         3
#define INT1_SRC_YH_Msk         BF_MASK(INT1_SRC_YH_Pos,1)
#define INT1_SRC_ZL_Pos         4
#define INT1_SRC_ZL_Msk         BF_MASK(INT1_SRC_ZL_Pos,1)
#define INT1_SRC_ZH_Pos         5
#define INT1_SRC_ZH_Msk         BF_MASK(INT1_SRC_ZH_Pos,1)
#define INT1_SRC_IA_Pos         6
#define INT1_SRC_IA_Msk         BF_MASK(INT1_SRC_IA_Pos,1)

#define INT1_THS_XH_Pos 		0
#define INT1_THS_XH_Msk 		BF_MASK(INT1_THS_XH_Pos, 7)
#define INT1_THS_XL_Pos			0
#define INT1_THS_XL_Msk			BF_MASK(INT1_THS_XL_Pos, 8)
#define INT1_THS_YH_Pos 		0
#define INT1_THS_YH_Msk 		BF_MASK(INT1_THS_YH_Pos, 7)
#define INT1_THS_YL_Pos			0
#define INT1_THS_YL_Msk			BF_MASK(INT1_THS_YL_Pos, 8)
#define INT1_THS_ZH_Pos 		0
#define INT1_THS_ZH_Msk 		BF_MASK(INT1_THS_ZH_Pos, 7)
#define INT1_THS_ZL_Pos			0
#define INT1_THS_ZL_Msk			BF_MASK(INT1_THS_ZL_Pos, 8)

#define INT1_DURATION_D_Pos			0
#define INT1_DURATION_D_Msk			BF_MASK(INT1_DURATION_D_Pos, 7)
#define INT1_DURATION_WAIT_Pos		8
#define INT1_DURATION_WAIT_Msk 		BF_MASK(INT1_DURATION_WAIT_Pos, 1)



#endif /*END OF __L3GD20_H__*/

#ifdef BIT_OPERATOR_SAMPLE
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))

/* Use of CMSIS compiler intrinsics for register exclusive access */
/* Atomic 32-bit register access macro to set one or several bits */
#define ATOMIC_SET_BIT(REG, BIT)                             \
  do {                                                       \
    uint32_t val;                                            \
    do {                                                     \
      val = __LDREXW((__IO uint32_t *)&(REG)) | (BIT);       \
    } while ((__STREXW(val,(__IO uint32_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 32-bit register access macro to clear one or several bits */
#define ATOMIC_CLEAR_BIT(REG, BIT)                           \
  do {                                                       \
    uint32_t val;                                            \
    do {                                                     \
      val = __LDREXW((__IO uint32_t *)&(REG)) & ~(BIT);      \
    } while ((__STREXW(val,(__IO uint32_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 32-bit register access macro to clear and set one or several bits */
#define ATOMIC_MODIFY_REG(REG, CLEARMSK, SETMASK)                          \
  do {                                                                     \
    uint32_t val;                                                          \
    do {                                                                   \
      val = (__LDREXW((__IO uint32_t *)&(REG)) & ~(CLEARMSK)) | (SETMASK); \
    } while ((__STREXW(val,(__IO uint32_t *)&(REG))) != 0U);               \
  } while(0)

/* Atomic 16-bit register access macro to set one or several bits */
#define ATOMIC_SETH_BIT(REG, BIT)                            \
  do {                                                       \
    uint16_t val;                                            \
    do {                                                     \
      val = __LDREXH((__IO uint16_t *)&(REG)) | (BIT);       \
    } while ((__STREXH(val,(__IO uint16_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 16-bit register access macro to clear one or several bits */
#define ATOMIC_CLEARH_BIT(REG, BIT)                          \
  do {                                                       \
    uint16_t val;                                            \
    do {                                                     \
      val = __LDREXH((__IO uint16_t *)&(REG)) & ~(BIT);      \
    } while ((__STREXH(val,(__IO uint16_t *)&(REG))) != 0U); \
  } while(0)

/* Atomic 16-bit register access macro to clear and set one or several bits */
#define ATOMIC_MODIFYH_REG(REG, CLEARMSK, SETMASK)                         \
  do {                                                                     \
    uint16_t val;                                                          \
    do {                                                                   \
      val = (__LDREXH((__IO uint16_t *)&(REG)) & ~(CLEARMSK)) | (SETMASK); \
    } while ((__STREXH(val,(__IO uint16_t *)&(REG))) != 0U);               \
  } while(0)

#endif



