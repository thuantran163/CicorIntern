/*
 * @file L3GD20_util.c
 * @brief All function for register assigned
 * @author ThuanTran Cicor
 * @date 11.01.2023
 *
 */
#include "L3GD20.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include "gpio.h"
#include "spi.h"


int Get_DataBlock(uint8_t assign_address, uint8_t *assign_value )
{
	MX_SPI1_Init();
	MX_GPIO_Init();
	uint8_t tx_data[2] = {assign_address | 0x80, 0};
	printf("\n transmit_address:  %x", tx_data[0]);
	printf("\n");
	uint8_t get_value[2];
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET); //-----------
	HAL_SPI_TransmitReceive(&hspi1, tx_data, get_value, 2, 1000);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);   //-----------
	printf("\n receive_data:  %x", get_value[0]);
	printf("\n receive_data:  %x", get_value[1]);
	printf("\n");
	*assign_value = get_value[1];
	return 1;
};
int Set_DataBlock(uint8_t assign_address, uint8_t assign_value)
{
	MX_GPIO_Init();
	MX_SPI1_Init();
	uint8_t tx_data[2] = {assign_address  , assign_value};
	uint8_t return_value[2];
	printf("\n transmit_address:  %x", tx_data[0]);
	printf("\n transmit_data:  %x", tx_data[1]);
	printf("\n");
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);   //-----------
	HAL_SPI_TransmitReceive(&hspi1, tx_data, return_value, 2, 1000);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);     //-----------
	return 1;
};

int L3GD20_Set_WhoAmIRegister(uint8_t assign_value);
int L3GD20_Read_WhoAmIRegister(uint8_t *return_value);
int L3GD20_CheckDefault_WhoAmIRegister(void);

int L3GD20_Set_WhoAmIRegister(uint8_t assign_value)
{
	uint8_t address = WHO_AM_I_BASE;
	Set_DataBlock(address, assign_value);
	return 1;
};

int L3GD20_Read_WhoAmIRegister(uint8_t *return_value)
{

	uint8_t address = WHO_AM_I_BASE;
	Get_DataBlock(address, return_value);
	return 1;
};

int L3GD20_CheckDefault_WhoAmIRegister(void)
{

	uint8_t check_value;
	L3GD20_Read_WhoAmIRegister(&check_value);

	if(check_value == WHO_AM_I_DEFAULT)
	{
		return 1;
	}
	else return 0;
};

int L3GD20_Set_CTRL_REG1(CTRL_REG1_TypeDef reg)
{
//	initialise_monitor_handles();
	uint8_t address = CTRL_REG1_BASE;
	uint8_t assign_value = 0;
	BFN_SET(assign_value,reg.Yen, CTRL_REG1_YEN);
	BFN_SET(assign_value,reg.Xen, CTRL_REG1_XEN);
	BFN_SET(assign_value,reg.Zen, CTRL_REG1_ZEN);
	BFN_SET(assign_value,reg.PD,  CTRL_REG1_PD);
	BFN_SET(assign_value,reg.DR,  CTRL_REG1_DR);
	BFN_SET(assign_value,reg.BW,  CTRL_REG1_BW);

		printf("\n data check: %x", reg.Xen);
		printf("\n data check: %x", reg.Yen);
		printf("\n data check: %x", reg.Zen);
		printf("\n data check: %x", reg.PD);
		printf("\n data check: %x", reg.BW);
		printf("\n data check: %x", reg.DR);
		printf("\n data check: %x", assign_value);


	Set_DataBlock(address, assign_value);
};
int L3GD20_Read_CTRL_REG1(CTRL_REG1_TypeDef *reg)
{
	uint8_t address = CTRL_REG1_BASE;
	uint8_t return_value = 0;
	Get_DataBlock(address, &return_value);
	reg->Xen = BFN_GET(return_value, CTRL_REG1_XEN);
	reg->Yen = BFN_GET(return_value, CTRL_REG1_YEN);
	reg->Zen = BFN_GET(return_value, CTRL_REG1_ZEN);
	reg->PD  = BFN_GET(return_value, CTRL_REG1_PD);
	reg->BW  = BFN_GET(return_value, CTRL_REG1_BW);
	reg->DR  = BFN_GET(return_value, CTRL_REG1_DR);
};

int L3GD20_Set_CTRL_REG1_OutputDataRate(ODR_Configuration Mode)
{
	uint8_t address = CTRL_REG1_BASE;
	uint8_t return_value = 0;
	Get_DataBlock(address, &return_value);
//	printf("\n Mode: %x", Mode);
	switch(Mode)
	{
	case ODR_CONF_95HZ:
		return_value  = BFN_SET(return_value, 0b00, CTRL_REG1_DR);
		break;
	case ODR_CONF_190HZ:
		return_value  = BFN_SET(return_value, 0b01, CTRL_REG1_DR);
		break;
	case ODR_CONF_380HZ:
		return_value  = BFN_SET(return_value, 0b10, CTRL_REG1_DR);
		break;
	case ODR_CONF_760HZ:
		return_value  = BFN_SET(return_value, 0b11, CTRL_REG1_DR);
		break;
	default:
		break;
	}
	Set_DataBlock(address, return_value);
};

int L3GD20_Set_CTRL_REG1_BandWidth (uint8_t BandWidth_Selection)
{
	uint8_t address = CTRL_REG1_BASE;
	uint8_t return_value = 0;
	Get_DataBlock(address, &return_value);
//	printf("\n BandWidth_Selection %x", BandWidth_Selection);
	BandWidth_Selection = _BF_PREP(BandWidth_Selection, 0, 2);
//	printf("\n BandWidth_Selection %x", BandWidth_Selection);
	return_value = BFN_SET(return_value, BandWidth_Selection, CTRL_REG1_BW);
//	printf("\n return value: %x", return_value);
	Set_DataBlock(address, return_value);
};

int L3GD20_Set_CTRL_REG1_PowerMode (PowerMode_Selection Mode)
{
	uint8_t return_value = 0;
	uint8_t address = CTRL_REG1_BASE;
	Get_DataBlock(address, &return_value);
	switch(Mode)
	{
		case POWER_DOWN:
			return_value = BFN_SET(return_value, 0b0, CTRL_REG1_PD);
			return_value = BFN_SET(return_value, 0b0, CTRL_REG1_XEN);
			return_value = BFN_SET(return_value, 0b0, CTRL_REG1_YEN);
			return_value = BFN_SET(return_value, 0b0, CTRL_REG1_ZEN);
			break;
		case POWER_SLEEP:
			return_value = BFN_SET(return_value, 0b1, CTRL_REG1_PD);
			return_value = BFN_SET(return_value, 0b0, CTRL_REG1_XEN);
			return_value = BFN_SET(return_value, 0b0, CTRL_REG1_YEN);
			return_value = BFN_SET(return_value, 0b0, CTRL_REG1_ZEN);
			break;
		case POWER_NORMAL:
			return_value = BFN_SET(return_value, 0b1, CTRL_REG1_PD);
			break;
	}
	Set_DataBlock(address, return_value);

};

int L3GD20_Set_CTRL_REG2(CTRL_REG2_TypeDef reg)
{
	uint8_t address = CTRL_REG2_BASE;
	uint8_t assign_value = 0;
	BFN_SET(assign_value,reg.HPCF, CTRL_REG2_HPCF);
	BFN_SET(assign_value,reg.HPM, CTRL_REG2_HPM);
	Set_DataBlock(address, assign_value);
};
int L3GD20_Read_CTRL_REG2(CTRL_REG2_TypeDef *reg)
{
	uint8_t address = CTRL_REG2_BASE;
	uint8_t return_value = 0;
	Get_DataBlock(address, &return_value);
	reg->HPCF = BFN_GET(return_value, CTRL_REG2_HPCF);
	reg->HPM  = BFN_GET(return_value, CTRL_REG2_HPM);
};

int L3GD20_Set_CTRL_REG2_HighPassFilterMode (HighPassFilterMode_Configuration  Mode)
{
	uint8_t return_value = 0;
	uint8_t address = CTRL_REG2_BASE;
	Get_DataBlock(address, &return_value);
	switch(Mode)
	{
		case HIGH_PASS_FILTER_NORMAL_MODE_RESET_READING:
			return_value = BFN_SET(return_value, 0b00, CTRL_REG2_HPM);
			break;
		case HIGH_PASS_FILTER_REFERENCE_SIGNAL_MODE:
			return_value = BFN_SET(return_value, 0b01, CTRL_REG2_HPM);
			break;
		case HIGH_PASS_FILTER_NORMAL_MODE:
			return_value = BFN_SET(return_value, 0b10, CTRL_REG2_HPM);
			break;
		case HIGH_PASS_FILTER_AUTORESET_MODE:
			return_value = BFN_SET(return_value, 0b11, CTRL_REG2_HPM);
			break;
	}
	Set_DataBlock(address, return_value);
};

int L3GD20_Set_CTRL_REG2_HighPassFilter_CutOffFrequency (uint8_t HPF_CutOff_Freq)
{
	uint8_t address = CTRL_REG2_BASE;
	uint8_t return_value = 0;
	Get_DataBlock(address, &return_value);
	HPF_CutOff_Freq = _BF_PREP(HPF_CutOff_Freq, 0, 4);
	return_value = BFN_SET(return_value, HPF_CutOff_Freq, CTRL_REG2_HPCF);
	Set_DataBlock(address, return_value);
};

int L3GD20_Set_CTRL_REG3(CTRL_REG3_TypeDef reg)
{
//	initialise_monitor_handles();
	uint8_t address = CTRL_REG3_BASE;
	uint8_t assign_value = 0;
	BFN_SET(assign_value,reg.I1_Int1,   CTRL_REG3_I1_INT1);
	BFN_SET(assign_value,reg.I1_Boot,   CTRL_REG3_I1_BOOT);
	BFN_SET(assign_value,reg.H_Lactive, CTRL_REG3_H_LACTIVE);
	BFN_SET(assign_value,reg.PP_OD,  	CTRL_REG3_PP_OD);
	BFN_SET(assign_value,reg.I2_DRDY,   CTRL_REG3_I2_DRDY);
	BFN_SET(assign_value,reg.I2_WTM,  	CTRL_REG3_I2_WTM);
	BFN_SET(assign_value,reg.I2_ORun, 	CTRL_REG3_I2_ORUN);
	BFN_SET(assign_value,reg.I2_Empty,  CTRL_REG3_I2_EMPTY);
	Set_DataBlock(address, assign_value);
};

int L3GD20_Read_CTRL_REG3(CTRL_REG3_TypeDef *reg)
{
	uint8_t address = CTRL_REG3_BASE;
	uint8_t return_value;
	Get_DataBlock(address, &return_value);
	reg->I2_Empty = BFN_GET(return_value, CTRL_REG3_I2_EMPTY);
	reg->I2_ORun  = BFN_GET(return_value, CTRL_REG3_I2_ORUN);
	reg->I2_WTM   = BFN_GET(return_value, CTRL_REG3_I2_WTM);
	reg->I2_DRDY  = BFN_GET(return_value, CTRL_REG3_I2_DRDY);
	reg->PP_OD    = BFN_GET(return_value, CTRL_REG3_PP_OD);
	reg->H_Lactive= BFN_GET(return_value, CTRL_REG3_H_LACTIVE);
	reg->I1_Boot  = BFN_GET(return_value, CTRL_REG3_I1_BOOT);
	reg->I1_Int1  = BFN_GET(return_value, CTRL_REG3_I1_INT1);
};

int L3GD20_Set_CTRL_REG4(CTRL_REG4_TypeDef reg)
{
	uint8_t address = CTRL_REG4_BASE;
	uint8_t assign_value = 0;
	BFN_SET(assign_value, reg.SIM,   CTRL_REG4_SIM);
	BFN_SET(assign_value, reg.FS,    CTRL_REG4_FS);
	BFN_SET(assign_value, reg.BLE, 	 CTRL_REG4_BLE);
	BFN_SET(assign_value, reg.BDU, 	 CTRL_REG4_BDU);
	Set_DataBlock(address, assign_value);
};

int L3GD20_Read_CTRL_REG4(CTRL_REG4_TypeDef *reg)
{
	uint8_t address = CTRL_REG4_BASE;
	uint8_t return_value = 0;
	Get_DataBlock(address, &return_value);
	reg->SIM = BFN_GET(return_value, CTRL_REG4_BDU);
	reg->FS  = BFN_GET(return_value, CTRL_REG4_FS);
	reg->BLE = BFN_GET(return_value, CTRL_REG4_BLE);
	reg->BDU = BFN_GET(return_value, CTRL_REG4_BDU);
};

int L3GD20_Set_CTRL_REG5(CTRL_REG5_TypeDef reg)
{
	uint8_t address = CTRL_REG5_BASE;
	uint8_t assign_value = 0;
	BFN_SET(assign_value, reg.Out_Sel,   CTRL_REG5_OUT_SEL);
	BFN_SET(assign_value, reg.INT1_Sel,  CTRL_REG5_INT_SEL);
	BFN_SET(assign_value, reg.HPen, 	 CTRL_REG5_HPEN);
	BFN_SET(assign_value, reg.FIFO_EN, 	 CTRL_REG5_FIFO_EN);
	BFN_SET(assign_value, reg.BOOT, 	 CTRL_REG5_BOOT);
	Set_DataBlock(address, assign_value);
};

int L3GD20_Read_CTRL_REG5(CTRL_REG5_TypeDef *reg)
{
	uint8_t address = CTRL_REG5_BASE;
	uint8_t return_value = 0;
	Get_DataBlock(address, &return_value);
	reg->Out_Sel  	= BFN_GET(return_value, CTRL_REG5_OUT_SEL);
	reg->INT1_Sel 	= BFN_GET(return_value, CTRL_REG5_INT_SEL);
	reg->HPen 		= BFN_GET(return_value, CTRL_REG5_HPEN);
	reg->FIFO_EN 	= BFN_GET(return_value, CTRL_REG5_FIFO_EN);
	reg->BOOT  		= BFN_GET(return_value, CTRL_REG5_BOOT);
};

int L3GD20_Set_STATUS_REG(STATUS_REG_TypeDef reg)
{
	uint8_t address = STATUS_REG_BASE;
	uint8_t assign_value = 0;
	BFN_SET(assign_value, reg.XDA,   STATUS_REG_XDA  );
	BFN_SET(assign_value, reg.YDA,   STATUS_REG_YDA  );
	BFN_SET(assign_value, reg.ZDA,   STATUS_REG_ZDA  );
	BFN_SET(assign_value, reg.ZYXDA, STATUS_REG_ZYXDA);
	BFN_SET(assign_value, reg.XOR,   STATUS_REG_XOR  );
	BFN_SET(assign_value, reg.YOR,   STATUS_REG_YOR  );
	BFN_SET(assign_value, reg.ZOR,   STATUS_REG_ZOR  );
	BFN_SET(assign_value, reg.ZYXOR, STATUS_REG_ZYXOR);
	Set_DataBlock(address, assign_value);
};

int L3GD20_Read_STATUS_REG(STATUS_REG_TypeDef *reg)
{
	uint8_t address = STATUS_REG_BASE;
	uint8_t return_value = 0;
	Get_DataBlock(address, &return_value);
	reg->XDA   = BFN_GET(return_value, STATUS_REG_XDA  );
	reg->YDA   = BFN_GET(return_value, STATUS_REG_YDA  );
	reg->ZDA   = BFN_GET(return_value, STATUS_REG_ZDA  );
	reg->ZYXDA = BFN_GET(return_value, STATUS_REG_ZYXDA);
	reg->XOR   = BFN_GET(return_value, STATUS_REG_XOR  );
	reg->YOR   = BFN_GET(return_value, STATUS_REG_YOR  );
	reg->ZOR   = BFN_GET(return_value, STATUS_REG_ZOR  );
	reg->ZYXOR = BFN_GET(return_value, STATUS_REG_ZYXOR);
}

int L3GD20_Set_FIFO_CTRL_REG(FIFO_CTRL_REG_TypeDef reg)
{
	uint8_t address = FIFO_CTRL_REG_BASE;
	uint8_t assign_value = 0;
	BFN_SET(assign_value, reg.FM,    FIFO_CTRL_FM  );
	BFN_SET(assign_value, reg.WTM,   FIFO_CTRL_WTM );
	Set_DataBlock(address, assign_value);
};
int L3GD20_Read_FIFO_CTRL_REG(FIFO_CTRL_REG_TypeDef *reg)
{
	uint8_t address = FIFO_CTRL_REG_BASE;
	uint8_t return_value = 0;
	Get_DataBlock(address, &return_value);
	reg->FM    = BFN_GET(return_value, FIFO_CTRL_FM );
	reg->WTM   = BFN_GET(return_value, FIFO_CTRL_WTM);
};

int L3GD20_Read_FIFO_SRC_REG(FIFO_SRC_REG_TypeDef *reg)
{
	uint8_t address = FIFO_CTRL_REG_BASE;
	uint8_t return_value = 0;
	Get_DataBlock(address, &return_value);
	reg->EMPTY  = BFN_GET(return_value, FIFO_SRC_EMPTY );
	reg->FSS    = BFN_GET(return_value, FIFO_SRC_FSS);
	reg->OVRN	= BFN_GET(return_value, FIFO_SRC_OVRN);
	reg->WTM 	= BFN_GET(return_value, FIFO_SRC_WTM);
};
int L3GD20_Read_DATACAPTURE(uint8_t *data)
{
	uint8_t address = REFERENCE_BASE;
	Get_DataBlock(address, data);
};
int L3GD20_Read_OUTTEMP(uint8_t *data)
{
	uint8_t address = OUT_TEMP_BASE;
	Get_DataBlock(address, data);
};
int L3GD20_Read_Data(OutValue_TypeDef *outvalue)
{
	uint8_t data;
	uint8_t address = OUT_X_L_BASE;
	Get_DataBlock(address, &data);
	outvalue->OUT_X = _BF_PREP(data, 0, 8);
	address = OUT_X_H_BASE;
	Get_DataBlock(address, &data);
	outvalue->OUT_X |= _BF_PREP(data, 8, 8);

	address = OUT_Y_L_BASE;
	Get_DataBlock(address, &data);
	outvalue->OUT_Y = _BF_PREP(data, 0, 8);
	address = OUT_Y_H_BASE;
	Get_DataBlock(address, &data);
	outvalue->OUT_Y |= _BF_PREP(data, 8, 8);

	address = OUT_Z_L_BASE;
	Get_DataBlock(address, &data);
	outvalue->OUT_Z = _BF_PREP(data, 0, 8);
	address = OUT_Z_H_BASE;
	Get_DataBlock(address, &data);
	outvalue->OUT_Z |= _BF_PREP(data, 8, 8);
};




