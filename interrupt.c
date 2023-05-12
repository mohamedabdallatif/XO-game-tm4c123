#include "..\\./headers/draw.h"



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
	//	moves++;
		
	//	theWinnerIs();
		
	}
		
}

}
