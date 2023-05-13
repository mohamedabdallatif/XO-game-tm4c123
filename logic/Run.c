#include "../headers/tm4c123gh6pm.h"
#include "../headers/Nokia5110.h"
#include "../headers/TExaS.h"
#include "../headers/gpio_driver.h"
#include "../headers/draw.h"

int i,j,k;
char matrix[10]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
char turn = 'X';
int cursor = 1;

void drawGrid(void){
	k = 1;
	Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();
	for(i = 0 ;i < 8 ;i++){
		Nokia5110_SetCursor(i, 1);
		Nokia5110_OutString("-");
		Nokia5110_SetCursor(i, 3);
		Nokia5110_OutString("-");
}
	for(j = 0 ;j < 5 ;j+=2){
		Nokia5110_SetCursor(2, j);
		Nokia5110_OutString("|");
		Nokia5110_SetCursor(5, j);
		Nokia5110_OutString("|");	
		}
	for(i = 0 ;i < 5;i+=2) {
		for(j = 0 ;j < 8 ;j+=3){
			Nokia5110_SetCursor(j, i);
			Nokia5110_OutChar(matrix[k++]);
	}
	}
	Nokia5110_SetCursor(8,0);
	Nokia5110_OutString("Turn");
	Nokia5110_SetCursor(9,1);
	Nokia5110_OutChar(turn);
}

void Xo_Init(void){
	
}

