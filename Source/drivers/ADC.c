#include "../headers/tm4c123gh6pm.h"

	volatile int z;

void ADC_Init(void)
{

	// ADC 0 , SEQ 3 , PE2 (AN1)
	// ENABLE THE ADC CLOCK USING RCGCADC REG (302)
	SYSCTL_RCGCADC_R |= 1; //ENABLE ADC MODULE 0 
	z=4;
	// ENABLE CLOCK TO THE APPROPRIATE GPIO MODULE VIA RCGCGPIO MOD
	SYSCTL_RCGCGPIO_R|=(1<<4) | (1 <<5) ; // ENABLE PORT E / F
			z=5;
	// ENABLE AF FOR PE2
	GPIO_PORTE_AFSEL_R |= (1<<2);
	// CHOOSING THE FUNCTION USING PORT CONTROL REG.
	// THIS IS BY DEF USED AD AN
	
	// DISABLE DIG. FUNCT
	GPIO_PORTE_DEN_R &= ~(1<<2);
	
	// ENABLE ANALOG FUNC IN PE2
	GPIO_PORTE_AMSEL_R |= (1<<2);
	
	////////////////////////
	//////////////////////
	
	// DISABLE SAMPLE SEQ(3) FIRST 
	ADC0_ACTSS_R &= ~(1<<3);
	
	//sample seq 3 is always running ( continusally sampling)
	ADC0_EMUX_R = (0xf <<12);
	
	// for each  sample in the sample seq , configure the sample control bits in the  adcsstln
	// we have 1 sample so..
	// since we get input from an2 so we will put 2 
	// SAMPLE SEQ 3 READS FROM AIN2 (PE1) (INPUT SOURCE)
		ADC0_SSMUX3_R = (1<<2);
	
	 // SAMPLE CONTROL (END BIT AND INTERRUPT)
	 
	 ADC0_SSCTL3_R = (1<<1)  // END BIT 
									| (1<<2); // ENABLE INTERRUPT FOR SS3
	 
  // ENABLE IM FOR SS3
	ADC0_IM_R |= (1<<3);
	
	// CLEAR I STATUS FOR SS3 
	ADC0_RIS_R |= (1<<3);
	
	// SS3 IS ENABLED
		ADC0_ACTSS_R |= (1<<3);
		
	// ENABLE IRQ FOR ADC1SS3
	
	 NVIC_EN1_R |= (1<<1);
	
}
