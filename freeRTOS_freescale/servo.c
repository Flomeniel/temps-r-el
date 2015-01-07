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

void servo_moteur_test(unsigned char tabValeur[128])
{
	uint32_t valeur_max=0;
	static uint32_t valeur_min=0;
	static	uint32_t index=17;
	uint32_t valeur_min_precedent=0;


	do
	{
		if( (tabValeur[index]+tabValeur[index+1]+tabValeur[index+2]+tabValeur[index+3] ) > (tabValeur[index+4]+tabValeur[index+5]+tabValeur[index+7]+tabValeur[index+6]))
		{
			valeur_max=1;
		}

		if(valeur_max==1)
		{
			if( (tabValeur[index]+tabValeur[index+1]+tabValeur[index+2]+tabValeur[index+3] ) < (tabValeur[index+4]+tabValeur[index+5]+tabValeur[index+7]+tabValeur[index+6]))
			{
				valeur_min=index;
			}

		}

		index++;
	}while(valeur_min==0);


	if(valeur_min!=valeur_min_precedent)
	{
		servo_moteur((valeur_min+83)/10);
	}
	valeur_min_precedent=valeur_min;
//	var++;

}
