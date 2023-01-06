#include "gpio.h"

void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
	assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
}
