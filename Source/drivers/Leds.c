
#include "..\\./headers/tm4c123gh6pm.h"
#include "..\\./headers/Leds.h"
#include "..\\./headers/Timer2.h"

int l;
int idx;

// Turn on Specific led..
void Set_Led(int Led_Pin)
{
	GPIO_PORTE_DATA_R |= (1 << Led_Pin);
}

// Turn off Specific led..

void Clear_Led(int Led_Pin)
{
	GPIO_PORTE_DATA_R &= ~(1 << Led_Pin);
}

// using only when starting game or replay..
void Start_Game()
{
	Set_Led(0);
	Timer2_Init(15);
	Set_Led(2);
	Timer2_Init(15);
	Set_Led(3);
	Timer2_Init(15);
}

// used in Start_Game ---> Turn off all leds
void Clear_ALL(void)
{
	Clear_Led(2);
	Clear_Led(3);
	Clear_Led(4);
}

// Used when someone wins:
/*
if (x wins)								----> Flash Led 1
if (O wins)								----> Flash Led 2
if (someone plays in filled place)		----> Flash Led 3
*/
void Flash(int Led_Pin)
{
	for (idx = 0; idx < 5; idx++)
	{
		Set_Led(Led_Pin);
		Timer2_Init(10);
		Clear_Led(Led_Pin);
		Timer2_Init(10);
	}
}


// Turn off red led.
void Clear_Led_PF1()
{
	GPIO_PORTF_DATA_R &= ~(1 << 1);
}


