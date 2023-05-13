#include "..\\./headers/draw.h"
#include "..\\./headers/check_winner.h"
#include "../headers/tm4c123gh6pm.h"

extern char matrix[];
extern char turn;
extern int cursor;
int moves=0;
void GPIOPortE_Handler (void){
	
	if(GPIO_PORTE_RIS_R &(1<<1)){
	
		GPIO_PORTE_ICR_R =(1<<1);
		 
		if(matrix[cursor]==' '){
		if (turn =='X'){
			matrix[cursor]='X';
			turn='O';
		}
		else{ 
			matrix[cursor]='O';
		  turn='X';
		
		}
			 drawGrid();
		moves++;
		
		check_winner(turn);
		
	}
		
}

}

void GPIOPortF_Handler(void)
	{
	if (GPIO_PORTF_RIS_R &(1<<4))  
	{
	//	Delay100ms(5);
		
	
		GPIO_PORTF_ICR_R|= (1<<4);

		cursor--;
		while(matrix[cursor]!=' '){
			
		cursor--;
		if(cursor<1) cursor=9;
		}
		
		drawGrid();
		
		
	}
	 else if(GPIO_PORTF_RIS_R &(1<<0)){
				
//Delay100ms(5);
		 GPIO_PORTF_ICR_R |= (1<<0);
		 cursor++;
		while(matrix[cursor]!=' '){
			
			cursor++;
		if(cursor>9) cursor=1;
		}
		
		drawGrid();
		
		
	}
}
