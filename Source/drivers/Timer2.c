#include "../headers/tm4c123gh6pm.h"
#include "../headers/Timer2.h"
unsigned long TimerCount;
unsigned long Semaphore;

void Timer2_Init(unsigned long period){ 
	int i;
  unsigned long volatile delay;
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  TimerCount = 0;
  Semaphore = 0;
  TIMER2_CTL_R |=0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R  = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = 1600000-1;    // 4) reload value
	TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_CTL_R |= 0x00000001;    // 10) enable timer2A
	 for(i = 0; i < period; i++) { while ((TIMER2_RIS_R & 0x1) == 0) ;      /* wait for TimerA timeout flag */
        TIMER2_ICR_R = 0x1;      /* clear the TimerA timeout flag */
  }
}
