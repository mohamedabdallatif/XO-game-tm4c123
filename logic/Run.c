#include "../headers/tm4c123gh6pm.h"
#include "../headers/Nokia5110.h"
#include "../headers/TExaS.h"
#include "../headers/gpio_driver.h"
#include "../headers/UART.h"
#include "../headers/Timer2.h"

int i = 0, j = 0, position = 1, current_cursor = 1, moves=0;
char matrix[10]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
char turn = 'X', x = 'X', o = 'O';
int scoreX = 0, scoreO = 0, cursor = 1;

void drawGrid(void){
	Nokia5110_ClearBuffer();
	Nokia5110_DisplayBuffer();
	current_cursor=1,position=1;
	
	// Horizontal borders
	for(i = 0 ;i < 8 ;i++){
		Nokia5110_SetCursor(i, 1);
		Nokia5110_OutString("-");
		Nokia5110_SetCursor(i, 3);
		Nokia5110_OutString("-");
	}

	// Vertical borders
	for(j = 0 ;j < 5 ;j+=2){
		Nokia5110_SetCursor(2, j);
		Nokia5110_OutString("|");
		Nokia5110_SetCursor(5, j);
		Nokia5110_OutString("|");	
	}

// arrayay values
 for(i = 0 ;i < 5;i+=2) {
	for(j = 0 ;j < 8 ;j+=3){
			Nokia5110_SetCursor(j, i);
			Nokia5110_OutChar(matrix[position++]);
	}
}
 
// Displaying cursor
 for(i = 0 ;i < 5;i+=2) {
	for(j = 1 ;j < 8 ;j+=3){
		if(current_cursor == cursor){
			Nokia5110_SetCursor(j, i);
			Nokia5110_OutChar('.');
		}
		current_cursor++;
		}
}

// 	Display Trun
			Nokia5110_SetCursor(8,0);
			Nokia5110_OutString("Turn");
			Nokia5110_SetCursor(9,1);
			Nokia5110_OutChar(turn);
}

void Xo_Init(void){
	
}
int n;
void UART(){
    while(1){
			UART_OutString("\n\rInput:");
     n = UART_InChar();
   UART_OutChar(n);
		UART_OutString("\n\r");
			switch(n){
				case 'd':
				Timer2_Init(20);
				cursor++;
			while(matrix[cursor]!=' '){
				cursor++;
		if(cursor>9) cursor=1;
		}	
		drawGrid();
			}
		}
}

