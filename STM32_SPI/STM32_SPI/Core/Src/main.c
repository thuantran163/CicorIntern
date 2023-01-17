
#include "main.h"
#include "cmsis_os.h"
#include "L3GD20.h"
#include "gpio.h"

CRC_HandleTypeDef hcrc;
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

osThreadId defaultTaskHandle;

void SystemClock_Config(void);
//static void MX_SPI1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_CRC_Init(void);
void StartDefaultTask(void const * argument);

extern void initialise_monitor_handles(void);

int main(void)
{
  initialise_monitor_handles();
  HAL_Init();
  MX_GPIO_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_CRC_Init();
  L3GD20_Init();
  FIFO_SRC_REG_TypeDef fifo_src_reg;
  L3GD20_Read_FIFO_SRC_REG(fifo_src_reg);
  printf("\n data check FSS: %x",  	 fifo_src_reg.FSS);
  printf("\n data check EMPTY: %x",  fifo_src_reg.EMPTY);
  printf("\n data check OVRN: %x",   fifo_src_reg.OVRN);
  printf("\n data check WTM: %x",    fifo_src_reg.WTM);
  printf("\n");
  OutValue_TypeDef out_value;

  while (1)
  {
	  L3GD20_Read_Data(&out_value);
	  printf("\n data check OUT_X %X", out_value.OUT_X);
	  printf("\n data check OUT_Y %X", out_value.OUT_Y);
	  printf("\n data check OUT_Z %X", out_value.OUT_Z );
	  printf("\n");

  }
}



void L3GD20_Init(void)
{
  CTRL_REG1_TypeDef reg1 = {
				  .Xen = 1,
				  .Yen = 1,
				  .Zen = 1,
				  .PD =  1,
				  .BW = 0b11,
				  .DR = 0b11
		  };

  //  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
  L3GD20_Set_CTRL_REG1(reg1);

  CTRL_REG2_TypeDef reg2 = {
    .HPCF  = 0b1011,
	.HPM   = 0b00,
  };

  L3GD20_Set_CTRL_REG2(reg2);

  CTRL_REG3_TypeDef reg3 = {
 			  .I2_Empty = 0,
 			  .I2_ORun = 1,
 			  .I2_WTM = 1,
 			  .I2_DRDY = 1,
 			  .PP_OD = 1,
 			  .H_Lactive = 1,
 			  .I1_Boot = 1,
 			  .I1_Int1 = 1.
 	  };
  L3GD20_Set_CTRL_REG3(reg3);

  CTRL_REG4_TypeDef reg4 = {
  			.BDU = 0,
  			.BLE = 0,
  			.FS  = 0b11,
  			.SIM = 0
  	};
  L3GD20_Set_CTRL_REG4(reg4);

  CTRL_REG5_TypeDef reg5 = {
  				.Out_Sel  = 0b11,
  				.INT1_Sel = 0b11,
  				.HPen 	  = 1,
  				.FIFO_EN  = 1,
  				.BOOT     = 0
  		};
  L3GD20_Set_CTRL_REG5(reg5);

  FIFO_CTRL_REG_TypeDef fifo_ctrl_reg = {
		  .WTM = 0b1110,
		  .FM  = 0b001,
  };
  L3GD20_Set_FIFO_CTRL_REG(fifo_ctrl_reg);
};

void Test_CTRL_REG5(void)
{
	CTRL_REG5_TypeDef reg;
	CTRL_REG5_TypeDef reg5 = {
			.Out_Sel  = 0b11,
			.INT1_Sel = 0b10,
			.HPen 	  = 0,
			.FIFO_EN  = 1,
			.BOOT     = 0
	};
	L3GD20_Set_CTRL_REG5(reg5);
	L3GD20_Read_CTRL_REG5(&reg);
	  printf("\n data check OUT_SEL: %x",  	reg.Out_Sel);
	  printf("\n data check INT1_SEL: %x",  reg.INT1_Sel);
	  printf("\n data check HPEN: %x",  	reg.HPen);
	  printf("\n data check FIFO_EN: %x",   reg.FIFO_EN);
	  printf("\n data check BOOT %x",  		reg.BOOT);
	  printf("\n");

}

void Test_CTRL_REG4(void)
{
	CTRL_REG4_TypeDef reg;
	CTRL_REG4_TypeDef reg4 = {
			.BDU = 1,
			.BLE = 1,
			.FS  = 0b00,
			.SIM = 0
	};
	L3GD20_Set_CTRL_REG4(reg4);
	L3GD20_Read_CTRL_REG4(&reg);
	  printf("\n data check SIM: %x",  reg.SIM);
	  printf("\n data check FS: %x",   reg.FS);
	  printf("\n data check BLE: %x",  reg.BLE);
	  printf("\n data check BDU: %x",  reg.BDU);
	  printf("\n");
};
void Test_CTRL_REG3(void)
{
      CTRL_REG3_TypeDef reg;
	  CTRL_REG3_TypeDef reg3 = {
			  .I2_Empty = 0,
			  .I2_ORun = 1,
			  .I2_WTM = 1,
			  .I2_DRDY = 1,
			  .PP_OD = 1,
			  .H_Lactive = 0,
			  .I1_Boot = 1,
			  .I1_Int1 = 0.
	  };
	  L3GD20_Set_CTRL_REG3(reg3);
	  L3GD20_Read_CTRL_REG3(&reg);
		  printf("\n data check I2_Empty: %x", reg.I2_Empty);
		  printf("\n data check I2_ORun: %x", reg.I2_ORun);
		  printf("\n data check I2_WTM: %x",  reg.I2_WTM);
		  printf("\n data check I2_DRDY: %x", reg.I2_DRDY);
		  printf("\n data check PP_OD: %x",   reg.PP_OD);
		  printf("\n data check H_Lactive: %x", reg.H_Lactive);
		  printf("\n data check I1_Boot: %x", reg.I1_Boot);
		  printf("\n data check I1_Int1: %x", reg.I1_Int1);
		  printf("\n");
};

void Test_CTRL_REG2(void)
{
	  CTRL_REG2_TypeDef reg;
	  CTRL_REG2_TypeDef reg2 = {
			 .HPCF = 0b0101,
			 .HPM  = 0b10,
	  };

	//  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	  L3GD20_Set_CTRL_REG2(reg2);
	//  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	  L3GD20_Read_CTRL_REG2(&reg);

	  printf("\n data check HPCF: %x", reg.HPCF);
	  printf("\n data check HPM: %x", reg.HPM);
	  printf("\n");

	  L3GD20_Set_CTRL_REG2_HighPassFilterMode(HIGH_PASS_FILTER_AUTORESET_MODE);
	  L3GD20_Set_CTRL_REG2_HighPassFilter_CutOffFrequency(0b0111);
	  L3GD20_Read_CTRL_REG2(&reg);

	  printf("\n data check HPCF: %x", reg.HPCF);
	  printf("\n data check HPM: %x", reg.HPM);
	  printf("\n");
};

void Test_CTRL_REG1(void)
{
	  CTRL_REG1_TypeDef reg;
	  CTRL_REG1_TypeDef reg2 = {
			  .Xen = 1,
			  .Yen = 1,
			  .Zen = 0,
			  .PD =  1,
			  .BW = 0,
			  .DR = 2
	  };

	//  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	  L3GD20_Set_CTRL_REG1(reg2);
	//  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	  L3GD20_Read_CTRL_REG1(&reg);

		//  printf("\n data check Xen: %x", reg.Xen);
		//  printf("\n data check Yen: %x", reg.Yen);
		//  printf("\n data check Zen: %x", reg.Zen);
		//  printf("\n data check PD: %x", reg.PD);
		//  printf("\n data check BW: %x", reg.BW);
		//  printf("\n data check DR: %x", reg.DR);
		//  printf("\n");
	//  printf("\n who am i register");
	//  printf("\n");
	  uint8_t read_data;

	  L3GD20_Set_WhoAmIRegister(0b11001101);
	  L3GD20_Read_WhoAmIRegister(&read_data);

	//  printf("\n data check who_am_i %x", read_data);
	//  printf("\n");

	  uint8_t flags = L3GD20_CheckDefault_WhoAmIRegister();
	  if ( flags == 1) {
		  printf("\n WHO_AM_I_ register is default value");
		  printf("\n");
	  }

	//  uint8_t rate = ODR_CONF_760HZ;

	  L3GD20_Set_CTRL_REG1_OutputDataRate(ODR_CONF_760HZ);
	  uint8_t bandwidth = 0b11;
	  L3GD20_Set_CTRL_REG1_BandWidth(bandwidth);
	  L3GD20_Set_CTRL_REG1_PowerMode(POWER_DOWN);

	  L3GD20_Read_CTRL_REG1(&reg);
	  printf("\n data check Xen: %x", reg.Xen);
	  printf("\n data check Yen: %x", reg.Yen);
	  printf("\n data check Zen: %x", reg.Zen);
	  printf("\n data check PD: %x", reg.PD);
	  printf("\n data check BW: %x", reg.BW);
	  printf("\n data check DR: %x", reg.DR);
	  printf("\n");
};

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }

}



/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_TIM_MspPostInit(&htim2);

}

static void MX_TIM3_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_RESET;
  sSlaveConfig.InputTrigger = TIM_TS_TI2FP2;
  sSlaveConfig.TriggerPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sSlaveConfig.TriggerPrescaler = TIM_ICPSC_DIV1;
  sSlaveConfig.TriggerFilter = 0;
  if (HAL_TIM_SlaveConfigSynchro(&htim3, &sSlaveConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_INDIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  if (HAL_TIM_IC_ConfigChannel(&htim3, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
}


void StartDefaultTask(void const * argument)
{

  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END 5 */
}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
