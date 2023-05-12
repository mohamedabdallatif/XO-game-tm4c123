#include "..\\./headers/draw.h"
#include "..\\./headers/check_winner.h"
#include "./tm4c123gh6pm.h"
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
