#include "../headers/Run.h"
#include "../headers/check_winner.h"
#include "../headers/tm4c123gh6pm.h"
#include "../headers/Timer2.h"
#include "../headers/Nokia5110.h"
#include "../headers/gpio_driver.h"
#include "../headers/UART.h"

extern char matrix[10];
extern char turn;
extern int cursor;
extern int moves;
char win ;
int flag =0;

void GPIOPortF_Handler(void){
	if(GPIO_PORTF_RIS_R &(1<<4) && flag==0){
	   PortE_Init();
	   PortB_Init();
     drawGrid();
		flag =1;
	}
	else if(GPIO_PORTF_RIS_R &(1<<0) && flag==0){
		 drawGrid();
		 flag=1;
	   UART();
	} 
	else if (GPIO_PORTF_RIS_R &(1<<4) && flag!=0)  
	{
		Timer2_Init(20);
		GPIO_PORTF_ICR_R|= (1<<4);
		cursor--;
		if(cursor<1) cursor=9;
		drawGrid();
		}
		
	else if(GPIO_PORTF_RIS_R &(1<<0) && flag!=0){	
		Timer2_Init(20);
		GPIO_PORTF_ICR_R |= (1<<0);
		cursor++;
		if(cursor>9) cursor=1;
		}	
		drawGrid();		
	}

void GPIOPortB_Handler(void){
	if (GPIO_PORTB_RIS_R &(1<<0) && flag!=0)  
	{
		Timer2_Init(20);
		GPIO_PORTB_ICR_R|= (1<<0);
		if(cursor < 4 && cursor > 0)	cursor += 6;   //code up
		else	cursor -= 3;
		drawGrid();	
		}
	
	else if(GPIO_PORTB_RIS_R &(1<<1) && flag !=0){	
		Timer2_Init(20);
		GPIO_PORTB_ICR_R |= (1<<1);
		if(cursor < 10 && cursor > 6)	cursor -= 6;   //code down
		else	cursor += 3;
		drawGrid();		
	}
}

void GPIOPortE_Handler(void){
if (GPIO_PORTE_RIS_R &(1<<1) && flag!=0)  
	{
		Timer2_Init(20);
		GPIO_PORTE_ICR_R|= (1<<1);
		if(matrix[cursor]==' '){
			if (turn =='X'){
				matrix[cursor]='X';
				win = check_winner (matrix, turn);
				if (win == 1){
					//led red blink for a while then
					Timer2_Init(25);
					Nokia5110_Clear();
					Nokia5110_SetCursor(2,2);
					Nokia5110_OutString("X Win!");
				}
				turn='O';
			}
			else{ 
			matrix[cursor]='O';
			check_winner (matrix, turn);
		  turn='X';
			}
			drawGrid();
			moves++;
		}
	}			
}

