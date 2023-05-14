
#include "..\\./headers/tm4c123gh6pm.h"
#include "..\\./headers/Leds.h"
#include "..\\./headers/Timer2.h"

// Turn on Specific led..
void Set_Led(int Led_Pin){
	GPIO_PORTE_DATA_R |= (1 << Led_Pin);
}

// Turn off Specific led..
void Clear_Led(int Led_Pin){
	GPIO_PORTE_DATA_R &= ~(1 << Led_Pin);
}

// using only when starting game or replay..
void Start_Game(int Led_Pin){
	Set_Led(2);
	Timer2_Init(15);
	Set_Led(3);
	Timer2_Init(15);
	Set_Led(4);
	Timer2_Init(15);
	Clear_ALL();
}

// used in Start_Game ---> Turn off all leds
void Clear_ALL(void){
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
void Flash(int Led_Pin){
	int i;
	for (i = 0; i < 3; i++){
		Set_Led(Led_Pin);
		Timer2_Init(25);
		Clear_Led(Led_Pin);
		Timer2_Init(25);
	}
}


