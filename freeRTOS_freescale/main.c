
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_exti.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx_adc.h>
#include <stm32f4xx_syscfg.h>
#include <stm32f4xx.h>
#include <misc.h>
#include <FreeRTOS.h>
#include <task.h>

#include "interruption.h"
#include "camera.h"
#include "adc.h"


#define LED_TASK_PRIO	(tskIDLE_PRIORITY + 1)


unsigned char ucCompteur=0;

void vApplicationIdleHook(void){

	__WFI();
}

int main(void)
{

	SystemInit();
	SystemCoreClockUpdate();

	/*************Initialisation***************/
		GPIO_Config_Camera_Adc1_PA1();
		ADC1_CH1_Config_Camera();

		vClockCamera_Timer4_CH1_PB6();
		vSICameraGpio_PB7();

		EXTILine6_Config_PB6();

	xTaskCreate( SIcamera,	(signed char*)"SI", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, NULL);
	xTaskCreate( AoAdc,		(signed char*)"AO", configMINIMAL_STACK_SIZE, NULL, LED_TASK_PRIO, NULL);

	vTaskStartScheduler();

	while(1)
	{
	}
}
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
	{
		ucCompteur++;
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}
