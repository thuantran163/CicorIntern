/*
 * @file L3GD20.c
 * @brief All function for
 * @author ThuanTran Cicor
 * @date 11.01.2023
 *
 */
#include "../Inc/L3GD20.h"

#define SET(x,y)
#define GET(x,y)

int L3GD20_Set_WhoAmIRegister(uint8_t assign_value);
int L3GD20_Read_WhoAmIRegister(uint8_t *return_value);
int L3GD20_CheckDefault_WhoAmIRegister(void);



int L3GD20_Set_WhoAmIRegister(uint8_t assign_value)
{
	uint8_t address = WHO_AM_I_BASE;
	SET(address, assign_value);
	return 1;
};

int L3GD20_Read_WhoAmIRegister(uint8_t *return_value)
{

	uint8_t address = WHO_AM_I_BASE;
	GET(address, return_value);
	return 1;
}
int L3GD20_CheckDefault_WhoAmIRegister(void)
{
	uint8_t check_value;
	L3GD20_Read_WhoAmIRegister(&check_value);
	if(check_value == WHO_AM_I_DEFAULT)
	{
		return 1;
	}
	else return 0;
}

int L3GD20_Set_CTRL_REG1(CTRL_REG1_TypeDef reg)
{
	uint8_t address = CTRL_REG1_BASE;
	uint8_t assign_value = 0;
	BFN_SET(assign_value,reg.Yen, CTRL_REG1_YEN);
	BFN_SET(assign_value,reg.Xen, CTRL_REG1_XEN);
	BFN_SET(assign_value,reg.Zen, CTRL_REG1_ZEN);
	BFN_SET(assign_value,reg.PD, CTRL_REG1_PD);
	BFN_SET(assign_value,reg.DR, CTRL_REG1_DR);
	BFN_SET(assign_value,reg.BW, CTRL_REG1_DR);
	SET( CTRL_REG1_BASE, assign_value)
}
int L3GD20_Read_CTRL_REG1(CTRL_REG1_TypeDef *reg)
{
	uint8_t address = CTRL_REG1_BASE;
	uint8_t return_value = 0;
	GET(address, &return_value);
	reg->Xen = BFN_GET(return_value, CTRL_REG1_XEN);
	reg->Yen = BFN_GET(return_value, CTRL_REG1_YEN);
	reg->Zen = BFN_GET(return_value, CTRL_REG1_ZEN);
	reg->PD  = BFN_GET(return_value, CTRL_REG1_PD);
	reg->BW  = BFN_GET(return_value, CTRL_REG1_BW);
	reg->DR  = BFN_GET(return_value, CTRL_REG1_DR);
}

int L3GD20_Set_CTRL_REG1_OutputDataRate()
{

};










