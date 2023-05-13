#include "../headers/tm4c123gh6pm.h"
#include "../headers/gpio_driver.h"

int delay;
void PortE_Init(void){
	SYSCTL_RCGC2_R  |= (1<<4);        //port E clock
  delay = 0;                        // delay   
  GPIO_PORTE_LOCK_R = 0x4C4F434B;   // 2) unlock PortE
  GPIO_PORTE_CR_R = (1<<0)|(1<<1)|(1<<2)|(1<<3);           // allow changes to PE0,PE1    
  GPIO_PORTE_AMSEL_R = 0x00;        //  disable analog function
  GPIO_PORTE_PCTL_R = 0x00000000;   // GPIO clear bit PCTL  
  GPIO_PORTE_DIR_R = 0x0D;          //  PE0 OUTPUT PE1 INPUT 
  GPIO_PORTE_AFSEL_R = 0x02;        //  no alternate function
  GPIO_PORTE_DEN_R =0x0F;        //  enable digital pins PE0,PE1  
	GPIO_PORTF_PUR_R |= 0x00;  	   		//enable pullup resistors on PE1
	GPIO_PORTE_IS_R &= ~(1<<1);             //EDGE SENSE
	GPIO_PORTE_IBE_R &= ~0x02;       //SINGLE EDGE
  GPIO_PORTE_IEV_R &= ~0x02;          //FAILING EDGE
  GPIO_PORTE_ICR_R = 0x2;          // CLEAR FLAGS ON PF0,PF4
	GPIO_PORTE_IM_R |= (1<<1);			// ARM INTERRUPT PE1
	NVIC_PRI1_R =(5<<5);             //PRIORITY 5
	NVIC_EN0_R =(1<<4);          //ENABLE INTERRUPT 4
	EnableInterrupts();
}


void PortF_Init(void){                                               
	//configue PF0, PF4 as Input PINS and rising edge sensing 
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x11;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x00;          // 5) PF4,PF0, PF1 as input   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_DEN_R = 0x11;          // 7) enable digital pins PF5,PF0, PF1       
	GPIO_PORTF_PUR_R |= 0x11;         // enable pullup resistors on PF0,PF4, PF1       
  GPIO_PORTF_IS_R &= ~0x11;        	//EDGE SENSE
  GPIO_PORTF_IBE_R &= ~0x11;       	//SINGLE EDGE
  GPIO_PORTF_IEV_R &= ~0x11;        //FAILING EDGE for PF0, PF4
  GPIO_PORTF_ICR_R = 0x11;          // CLEAR FLAGS ON PF0,PF4
  GPIO_PORTF_IM_R |= 0x11;    		 	// ARM INTERRUPT PF0,PF4
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000;  //PRIORITY 5
  NVIC_EN0_R = 0x40000000;          //ENABLE INTERRUPT 30
	EnableInterrupts();          
}

