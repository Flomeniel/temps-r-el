#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_syscfg.h>
#include <stm32f4xx.h>

#include "interruption.h"
#include "camera.h"
#include "adc.h"
#include "servo.h"

unsigned char ADCResult[128];

void AoAdc(void * pvParameters)
{
	unsigned char ADCResult_temp[128];									/* a changer!!!!!!!!!!!!*/

	static unsigned char ucCompteurPrecedent=2;
	for(;;)
	{
		if(ucCompteurPrecedent=!ucCompteur)
		{
			ADC_SoftwareStartConv(ADC1);
			ADCResult[ucCompteur]= ADC_GetConversionValue(ADC1);

			ADCResult_temp[ucCompteur]=ADCResult[ucCompteur];				/* a changer!!!!!!! */
		}
		else
		{
			ucCompteurPrecedent=ucCompteur;
		}

		/* Trés trés probablement a changer!!!!!*/
		if(ucCompteur==128)													/* a changer!!!!!!! */
		{
			servo_moteur_test(ADCResult_temp[128]);							/* a changer!!!!!!! */
		}

	}
}



void GPIO_Config_Camera_Adc1_PA1(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_StructInit(&GPIO_InitStructure);
  //for ADC1 on PC0 using IN10

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);				//
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  //for ADC1 on PC0 using IN10

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 ;							//CHANGE
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void ADC1_CH1_Config_Camera(void)
{
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  ADC_InitTypeDef       ADC_InitStructure;

  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;

  ADC_CommonInit(&ADC_CommonInitStructure);

  ADC_InitStructure.ADC_Resolution = ADC_Resolution_6b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;


  ADC_StructInit(&ADC_InitStructure);

  ADC_Init(ADC1, &ADC_InitStructure);

  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_3Cycles);
  ADC_EOCOnEachRegularChannelCmd(ADC1, ENABLE);

  ADC_Cmd(ADC1, ENABLE);    //The ADC is powered on by setting the ADON bit in the ADC_CR2 register.
  //When the ADON bit is set for the first time, it wakes up the ADC from the Power-down mode.
}
