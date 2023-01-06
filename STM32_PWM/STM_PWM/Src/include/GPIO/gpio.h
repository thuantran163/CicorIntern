/*
 * @file gpio.h
 * @brief GPIO library for multiple functions
 * @author Thuan
 * @date 06-01-2023
 */

#ifndef __GPIO_H__
#define __GPIO_H__

#include "common.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
	 GPIO_PIN_0    = ((uint16_t)0x0001)        /*Pin 0 selected  */,
	 GPIO_PIN_1    = ((uint16_t)0x0002)        /*Pin 1 selected  */,
	 GPIO_PIN_2    = ((uint16_t)0x0004)        /*Pin 2 selected  */,
	 GPIO_PIN_3    = ((uint16_t)0x0008)        /*Pin 3 selected  */,
	 GPIO_PIN_4    = ((uint16_t)0x0010)        /*Pin 4 selected  */,
	 GPIO_PIN_5    = ((uint16_t)0x0020)        /*Pin 5 selected  */,
	 GPIO_PIN_6    = ((uint16_t)0x0040)        /*Pin 6 selected  */,
	 GPIO_PIN_7    = ((uint16_t)0x0080)        /*Pin 7 selected  */,
	 GPIO_PIN_8    = ((uint16_t)0x0100)        /*Pin 8 selected  */,
	 GPIO_PIN_9    = ((uint16_t)0x0200)        /*Pin 9 selected  */,
	 GPIO_PIN_10   = ((uint16_t)0x0400)        /*Pin 10 selected */,
	 GPIO_PIN_11   = ((uint16_t)0x0800)        /*Pin 11 selected */,
	 GPIO_PIN_12   = ((uint16_t)0x1000)        /*Pin 12 selected */,
	 GPIO_PIN_13   = ((uint16_t)0x2000)        /*Pin 13 selected */,
	 GPIO_PIN_14   = ((uint16_t)0x4000)  	   /*Pin 14 selected */,
	 GPIO_PIN_15   = ((uint16_t)0x8000)  	   /*Pin 15 selected */,
	 GPIO_PIN_All  = ((uint16_t)0xFFFF) 	   /*All pin selected*/,
	 GPIO_PIN_MASK = ((uint32_t)0x0000FFFFU)   /*PIN MASK*/
}GPIO_PinNumber;

#define GPIO_MODE_Pos                           0U
#define GPIO_MODE                               (0x3UL << GPIO_MODE_Pos)
#define MODE_INPUT                              (0x0UL << GPIO_MODE_Pos)
#define MODE_OUTPUT                             (0x1UL << GPIO_MODE_Pos)
#define MODE_AF                                 (0x2UL << GPIO_MODE_Pos)
#define MODE_ANALOG                             (0x3UL << GPIO_MODE_Pos)
#define OUTPUT_TYPE_Pos                         4U
#define OUTPUT_TYPE                             (0x1UL << OUTPUT_TYPE_Pos)
#define OUTPUT_PP                               (0x0UL << OUTPUT_TYPE_Pos)
#define OUTPUT_OD                               (0x1UL << OUTPUT_TYPE_Pos)
#define EXTI_MODE_Pos                           16U
#define EXTI_MODE                               (0x3UL << EXTI_MODE_Pos)
#define EXTI_IT                                 (0x1UL << EXTI_MODE_Pos)
#define EXTI_EVT                                (0x2UL << EXTI_MODE_Pos)
#define TRIGGER_MODE_Pos                         20U
#define TRIGGER_MODE                            (0x7UL << TRIGGER_MODE_Pos)
#define TRIGGER_RISING                          (0x1UL << TRIGGER_MODE_Pos)
#define TRIGGER_FALLING                         (0x2UL << TRIGGER_MODE_Pos)

typedef enum
{
   GPIO_MODE_INPUT               =   MODE_INPUT                                                , /*!< Input Floating Mode                   */
   GPIO_MODE_OUTPUT_PP           =   (MODE_OUTPUT | OUTPUT_PP)                                 , /*!< Output Push Pull Mode                 */
   GPIO_MODE_OUTPUT_OD           =   (MODE_OUTPUT | OUTPUT_OD)                                 , /*!< Output Open Drain Mode                */
   GPIO_MODE_AF_PP               =   (MODE_AF | OUTPUT_PP)                                     , /*!< Alternate Function Push Pull Mode     */
   GPIO_MODE_AF_OD               =   (MODE_AF | OUTPUT_OD)                                     , /*!< Alternate Function Open Drain Mode    */
   GPIO_MODE_ANALOG              =   MODE_ANALOG                                               , /*!< Analog Mode  */
   GPIO_MODE_IT_RISING           =   (MODE_INPUT | EXTI_IT | TRIGGER_RISING)                   , /*!< External Interrupt Mode with Rising edge trigger detection          */
   GPIO_MODE_IT_FALLING          =   (MODE_INPUT | EXTI_IT | TRIGGER_FALLING)                  , /*!< External Interrupt Mode with Falling edge trigger detection         */
   GPIO_MODE_IT_RISING_FALLING   =   (MODE_INPUT | EXTI_IT | TRIGGER_RISING | TRIGGER_FALLING) , /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */
   GPIO_MODE_EVT_RISING          =   (MODE_INPUT | EXTI_EVT | TRIGGER_RISING)                  ,  /*!< External Event Mode with Rising edge trigger detection             */
   GPIO_MODE_EVT_FALLING         =   (MODE_INPUT | EXTI_EVT | TRIGGER_FALLING)                 ,  /*!< External Event Mode with Falling edge trigger detection            */
   GPIO_MODE_EVT_RISING_FALLING  =   (MODE_INPUT | EXTI_EVT | TRIGGER_RISING | TRIGGER_FALLING)  /*!< External Event Mode with Rising/Falling edge trigger detection     */
} GPIO_PinMode;


typedef enum
{
   GPIO_NOPULL     =  0x00000000U,  /*!< No Pull-up or Pull-down activation  */
   GPIO_PULLUP     =  0x00000001U,  /*!< Pull-up activation                  */
   GPIO_PULLDOWN   =  0x00000002U
}GPIO_Pull;


typedef enum
{
   GPIO_SPEED_FREQ_LOW       =  0x00000000U,  /*!< IO works at 2 MHz, please refer to the product datasheet */
   GPIO_SPEED_FREQ_MEDIUM    =  0x00000001U,  /*!< range 12,5 MHz to 50 MHz, please refer to the product datasheet */
   GPIO_SPEED_FREQ_HIGH      =  0x00000002U,  /*!< range 25 MHz to 100 MHz, please refer to the product datasheet  */
   GPIO_SPEED_FREQ_VERY_HIGH =  0x00000003U
}GPIO_Speed;



typedef struct
{
	GPIO_PinNumber Pin;
	GPIO_PinMode Mode;
	GPIO_Pull Pull;
	GPIO_Speed Speed;
	uint32_t Alternate;
}GPIO_InitTypeDef;

typedef enum
{
	GPIO_PIN_RESET = 0,
	GPIO_PIN_SET = 1
}GPIO_PinState;



#define IS_GPIO_PIN_ACTION(ACTION) (((ACTION) == GPIO_PIN_RESET) || ((ACTION) == GPIO_PIN_SET))
#define IS_GPIO_PIN(PIN)           (((((uint32_t)PIN) & GPIO_PIN_MASK ) != 0x00U) && ((((uint32_t)PIN) & ~GPIO_PIN_MASK) == 0x00U))
#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_MODE_INPUT)              ||\
                            ((MODE) == GPIO_MODE_OUTPUT_PP)          ||\
                            ((MODE) == GPIO_MODE_OUTPUT_OD)          ||\
                            ((MODE) == GPIO_MODE_AF_PP)              ||\
                            ((MODE) == GPIO_MODE_AF_OD)              ||\
                            ((MODE) == GPIO_MODE_IT_RISING)          ||\
                            ((MODE) == GPIO_MODE_IT_FALLING)         ||\
                            ((MODE) == GPIO_MODE_IT_RISING_FALLING)  ||\
                            ((MODE) == GPIO_MODE_EVT_RISING)         ||\
                            ((MODE) == GPIO_MODE_EVT_FALLING)        ||\
                            ((MODE) == GPIO_MODE_EVT_RISING_FALLING) ||\
                            ((MODE) == GPIO_MODE_ANALOG))
#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_SPEED_FREQ_LOW)  || ((SPEED) == GPIO_SPEED_FREQ_MEDIUM) || \
                              ((SPEED) == GPIO_SPEED_FREQ_HIGH) || ((SPEED) == GPIO_SPEED_FREQ_VERY_HIGH))
#define IS_GPIO_PULL(PULL) (((PULL) == GPIO_NOPULL) || ((PULL) == GPIO_PULLUP) || \
                            ((PULL) == GPIO_PULLDOWN))



#define __GPIO_EXTI_GET_FLAG(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))
#define __GPIO_EXTI_CLEAR_FLAG(__EXTI_LINE__) (EXTI->PR = (__EXTI_LINE__))
#define __GPIO_EXTI_GET_IT(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))
#define __GPIO_EXTI_CLEAR_IT(__EXTI_LINE__) (EXTI->PR = (__EXTI_LINE__))
#define __GPIO_EXTI_GENERATE_SWIT(__EXTI_LINE__) (EXTI->SWIER |= (__EXTI_LINE__))


void GPIO_init(void);


#ifdef __cplusplus
}
#endif



#endif /*GPIO_H*/
