#include "../headers/Run.h"
#include "../headers/check_winner.h"
#include "../headers/tm4c123gh6pm.h"
#include "../headers/Timer2.h"
#include "../headers/Nokia5110.h"
#include "../headers/gpio_driver.h"
#include "../headers/UART.h"
#include "../headers/Leds.h"

extern char matrix[10];
extern char turn;
extern int cursor;
int moves;
char win ;
int flag =0;

void GPIOPortF_Handler(void){
	if(GPIO_PORTF_RIS_R &(1<<0) && flag==0){
			 Timer2_Init(10);
			 drawGrid();
			 flag =1;
	}
	else if(GPIO_PORTF_RIS_R &(1<<4) && flag==0){
				Timer2_Init(10);	
				drawGrid();
				flag=2;
				UART();
	} 
	else if (GPIO_PORTF_RIS_R &(1<<4) && flag==1)  {
		if (turn =='X') Set_Led(0);
		else Set_Led(2);
		
		Timer2_Init(10);
		GPIO_PORTF_ICR_R|= (1<<4);
		//Timer2_Init(15);
			if(matrix[cursor]==' '){
					if (turn =='X'){
						matrix[cursor]='X';
						win = check_winner (matrix, turn);
						if (win == 1){
							drawGrid();
							Flash(0);//red led on
							Timer2_Init(100);
							Clear_Led(0);//red led off
							Print_Result(turn);
							return;
						}
						Clear_Led(0);
						turn='O';
						if (turn =='X') Set_Led(0);
						else Set_Led(2);
					}
				else{ 
					matrix[cursor]='O';
					win = check_winner (matrix, turn);
					if (win == 1){
						drawGrid();
						Flash(2);//red led on
						Timer2_Init(100);
						Clear_Led(2);//red led off
						Print_Result(turn);
						return;
					}						
					Clear_Led(2);
					turn='X';
					if (turn =='X') Set_Led(0);
					else Set_Led(2);
				}
			moves++;
			if (!win && moves == 9){
					drawGrid();
					Clear_Led(0);
					Clear_Led(2);
					Flash(3);//yellow led on
					Timer2_Init(50);
					Clear_Led(3);//yellow led off
					Print_Result('D');
					Timer2_Init(100);
					return;
			}
			drawGrid();
		}
	}

	else if(GPIO_PORTF_RIS_R &(1<<0) && flag==1){
			Timer2_Init(10);
      GPIO_PORTF_ICR_R |= (1<<0);		
			//Timer2_Init(15);
			cursor++;
			if(cursor>9) cursor=1;
			drawGrid();
			}	
			
	}


void GPIOPortB_Handler(void){
	
	if(GPIO_PORTB_RIS_R &(1<<0) && flag ==3){
		// user chooses yes to play again
			Play_Again();
			Timer2_Init(10);

	}
	if(GPIO_PORTB_RIS_R & (1<<1) && flag ==3){
	  	// user choose not to play again
			Bye();
	}
	
	if (GPIO_PORTB_RIS_R &(1<<0) && flag==1)  
		{
			Timer2_Init(10);
			GPIO_PORTB_ICR_R|= (1<<0);
			if(cursor < 4 && cursor > 0)	cursor += 6;   //code up
			else	cursor -= 3;
			drawGrid();	
			}
		
	else if(GPIO_PORTB_RIS_R &(1<<1) && flag ==1){	
			Timer2_Init(10);
			GPIO_PORTB_ICR_R |= (1<<1);
			if(cursor < 10 && cursor > 6)	cursor -= 6;   //code down
			else	cursor += 3;
			drawGrid();		
		}	
}

void GPIOPortE_Handler(void){
			Timer2_Init(10);
if (GPIO_PORTE_RIS_R &(1<<1) && flag==1)  
	{
			GPIO_PORTE_ICR_R|= (1<<1);
			cursor--;
			if(cursor<1) cursor=9;
			drawGrid();
		
	}			
}
