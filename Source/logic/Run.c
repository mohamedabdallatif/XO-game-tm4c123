#include "../headers/tm4c123gh6pm.h"
#include "../headers/Nokia5110.h"
#include "../headers/TExaS.h"
#include "../headers/gpio_driver.h"
#include "../headers/UART.h"
#include "../headers/Timer2.h"
#include "../headers/Leds.h"


int i = 0, j = 0, position = 1, current_cursor = 1, start;
char matrix[10]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};
char turn = 'X';
int scoreX = 0, scoreO = 0, cursor = 1;
extern int flag ;
extern int moves;

void drawGrid(void){
	if(start==0){
		Start_Game();
		Clear_ALL();
		start++;
	}
	Clear_Led_PF1();
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
		Timer2_Init(25);
		Nokia5110_Clear();
		Nokia5110_SetCursor(3,1);
		Nokia5110_OutString("1.Kit");
		Nokia5110_SetCursor(3,2);
		Nokia5110_OutString("2.UART");
}
void Bye(void)
{		
	  Nokia5110_Clear();
		Nokia5110_SetCursor(2,2);
		Nokia5110_OutString("Bye Bye!");
		while(1){
		}
}
void Play_Again(void)
{
		Nokia5110_Clear();
		Timer2_Init(25);
		i = 0, j = 0, position = 1, current_cursor = 1;
		start=0;
		moves = 0;
		cursor=1;
		flag = 0;
		for (i = 0; i < 10; i++) matrix[i] = ' '; // erase all drawings in cells matri
		Xo_Init();
}
void Print_Result(char turn){
		extern int flag ;
		flag = 3;
		Nokia5110_Clear();
		Nokia5110_SetCursor(0,0);
		if(turn == 'D')
		{
				Nokia5110_ClearBuffer();
				Nokia5110_DisplayBuffer();
				Nokia5110_SetCursor(1, 1);
				Nokia5110_OutString("NO");
				Timer2_Init(40);
				Nokia5110_DisplayBuffer();
				Timer2_Init(40);
				Nokia5110_SetCursor(3, 2);
				Nokia5110_OutString("ONE");
				Timer2_Init(40);
				Nokia5110_DisplayBuffer();
				Timer2_Init(40);
				Nokia5110_SetCursor(6, 3);
				Nokia5110_OutString("WIN!");
				Timer2_Init(100);
				Nokia5110_DisplayBuffer();
		}
		else if(turn == 'X')
		{	
				Nokia5110_ClearBuffer();
				Nokia5110_DisplayBuffer();
				Nokia5110_SetCursor(1, 1);
				Nokia5110_OutString("PlayerX Won");
		}
		else if(turn == 'O')
		{
				Nokia5110_ClearBuffer();
				Nokia5110_DisplayBuffer();
				Nokia5110_SetCursor(1, 1);
				Nokia5110_OutString("PlayerO Won");
		}
				Nokia5110_SetCursor(1,2);
				Nokia5110_OutString("ScoreX:");
				Nokia5110_SetCursor(6,2);
				Nokia5110_OutUDec(scoreX);

				Nokia5110_SetCursor(1,3);
				Nokia5110_OutString("ScoreO:");
				Nokia5110_SetCursor(6,3);
				Nokia5110_OutUDec(scoreO);
				//Play_Again();
}



