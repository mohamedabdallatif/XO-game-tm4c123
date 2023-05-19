#include "../headers/tm4c123gh6pm.h"
#include "..\\./headers/UART.h"
#include "..\\./headers/Run.h"
#include "..\\./headers/Leds.h"
#include "..\\./headers/Timer2.h"
#include "..\\./headers/check_winner.h"
#include "..\\./headers/Nokia5110.h"

extern char matrix[10];
extern char turn;
extern int cursor;
extern int moves;
char won;
//------------UART_Init------------
// Initialize the UART for 115200 baud rate (assuming 80 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART_Init(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
//                 switching from PC5,PC4 to PA1,PA0
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART0; // activate UART0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // activate port A
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART0_IBRD_R = 43;                    // IBRD = int(80,000,000 / (16 * 115200)) = int(43.402778)
  UART0_FBRD_R = 26;                    // FBRD = round(0.402778 * 64) = 26
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTA_AFSEL_R |= 0x03;           // enable alt funct on PA1,PA0
  GPIO_PORTA_DEN_R |= 0x03;             // enable digital I/O on PA1,PA0
                                        // configure PA1,PA0 as UART0
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // disable analog functionality on PA1,PA0
}

//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
unsigned char UART_InChar(void){
// as part of Lab 11, modify this program to use UART0 instead of UART1
  while((UART0_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART0_DR_R&0xFF));
}

//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART_OutString(unsigned char* buffer){
// as part of Lab 11 implement this function
   while(*buffer){
	   UART_OutChar(*(buffer++));
	 }
}

void UART_OutChar(unsigned char data){ //print
// as part of Lab 11, modify this program to use UART0 instead of UART1
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
} 

void UART(void){
	char n;
	UART_OutString("Instructions:\nd-->left\na-->right\nw-->top\ns-->down\nspace-->Your Turn");
while(1){
	if (turn =='X') Set_Led(0);
	else Set_Led(2);
	UART_OutString("\n\rInput:");
	n = UART_InChar();
	UART_OutChar(n);
	UART_OutString("\n\r");
	switch(n){
		case 'd':
			Timer2_Init(20);
			cursor++;
			if(cursor>9) cursor=1;	
			drawGrid();
			break;
		case 'a':
			Timer2_Init(20);
			cursor--;
			if(cursor<1) cursor=9;
			drawGrid();
			break;
		case ' ':
			Timer2_Init(20);
			if(matrix[cursor]==' '){
					if (turn =='X'){
						matrix[cursor]='X';
						won = check_winner (matrix, turn);
						if (won == 1){
							Flash(0);//red led on
							Timer2_Init(100);
							Clear_Led(0);//red led off
							Print_Result(turn);
							return;
						}
						Clear_Led(0);
						turn='O';
					}
					else{ 
						matrix[cursor]='O';
						won = check_winner (matrix, turn);
						if (won == 1){
							Flash(2);//red led on
							Timer2_Init(50);
							Clear_Led(2);//red led off
							Print_Result(turn);
							return;
						}
						Clear_Led(2);
						turn='X';
					}
					moves++;
					if (!won && moves== 9){
					Flash(3);//red led on
					Timer2_Init(50);
					Clear_Led(3);//red led off
					Print_Result('D');
					return;
					}
				drawGrid();
			}
			break;	
		case 'w':
			Timer2_Init(10);
			if(cursor < 4 && cursor > 0)	cursor += 6;   //code up
			else	cursor -= 3;
			drawGrid();	
			break;
		case 's':
			Timer2_Init(10);
			if(cursor < 10 && cursor > 6)	cursor -= 6;   //code up
			else	cursor += 3;
			drawGrid();	
			break;
	}
}
}

