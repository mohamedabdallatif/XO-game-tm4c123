#include "../headers/Run.h"
#include "../headers/check_winner.h"
#include "../headers/tm4c123gh6pm.h"
#include "../headers/Timer2.h"

extern char matrix[10];
extern char turn;
extern int cursor;
extern int moves;

void GPIOPortF_Handler(void){
	if (GPIO_PORTF_RIS_R &(1<<4))  
	{
		Timer2_Init(25);
		GPIO_PORTF_ICR_R|= (1<<4);
		/*cursor--;
		while(matrix[cursor]!=' '){
			cursor--;
			if(cursor<1) cursor=9;
		}
		drawGrid();
		*/
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
	else if(GPIO_PORTF_RIS_R &(1<<0)){	
		Timer2_Init(20);
		GPIO_PORTF_ICR_R |= (1<<0);
		cursor++;
			while(matrix[cursor]!=' '){
				
				cursor++;
		if(cursor>9) cursor=1;
		}	
		drawGrid();		
	}
}

void GPIOPortE_Handler(void){
if(GPIO_PORTE_RIS_R &(1<<1)){
		Timer2_Init(25);
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

