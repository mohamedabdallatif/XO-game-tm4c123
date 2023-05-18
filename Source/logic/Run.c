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
void result(){
		Nokia5110_ClearBuffer();
		Nokia5110_DisplayBuffer();
		Nokia5110_SetCursor(2, 2);
		Nokia5110_OutString("X-");
		Nokia5110_SetCursor(2, 3);
		Nokia5110_OutString("Y-");
		Nokia5110_SetCursor(6, 2);
		Nokia5110_OutUDec(scoreX);
		Nokia5110_SetCursor(6, 3);
		Nokia5110_OutUDec(scoreO);
		Timer2_Init(100);
		Nokia5110_DisplayBuffer();
		Timer2_Init(100);
}

void Xo_Init(void){
			Nokia5110_Clear();
	Nokia5110_SetCursor(4,1);
	Nokia5110_OutString("1.Kit");
	Nokia5110_SetCursor(4,2);
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
		Xo_Init();
  i = 0, j = 0, position = 1, current_cursor = 1;
	start=0;
	moves = 0;
	cursor=1;
	for (i = 0; i < 9; i++)
		matrix[i] = ' '; // erase all drawings in cells matrix
	turn = 'X';
	flag = 0;
}
void Print_Result(char turn){
	
	extern int flag ;
	flag = 3;
	Nokia5110_Clear();
	Nokia5110_SetCursor(0,0);
	if(turn == 'D')
	{
			Nokia5110_OutString("Draw!");
	}
	else if(turn == 'X')
	{
			Nokia5110_OutString("Player X Won");
	}
	else if(turn == 'O')
	{
			Nokia5110_OutString("Player O Won");
	}
	    Nokia5110_SetCursor(2,10);
			Nokia5110_OutString("Score X!");
	    Nokia5110_OutUDec(scoreX);

			Nokia5110_SetCursor(50,10);
			Nokia5110_OutString("Score Y!");
	    Nokia5110_OutUDec(scoreO);
		
			/*Timer2_Init(300);
			Nokia5110_Clear();
	
			Nokia5110_SetCursor(2,2);
			Nokia5110_OutString("Play Again?");
	    
			Nokia5110_SetCursor(50,2);
			Nokia5110_OutString("YES!");
	  

			Nokia5110_SetCursor(50,10);
			Nokia5110_OutString("NO!");
	*/
	}



