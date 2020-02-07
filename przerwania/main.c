#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"
#include "timer.h"

void Automat(){
	
	enum LedState {LED_STOP, LED_RIGHT, LED_LEFT};
	enum LedState eLedState = LED_STOP;

	switch(eLedState){
		case LED_STOP:
			if(eKeyboardRead() == BUTTON_0){
				eLedState = LED_LEFT;
				LedStepLeft();
			}
			else if(eKeyboardRead() == BUTTON_2){
				eLedState = LED_RIGHT;
				LedStepRight();
			}				
			else{
				eLedState = LED_STOP;
			}
		break;
		case LED_RIGHT:
			if(eKeyboardRead() == BUTTON_1){
				eLedState = LED_STOP;
			}
			else{
				eLedState = LED_RIGHT;
				LedStepRight();
			}
		break;
		case LED_LEFT:
			if(eKeyboardRead() == BUTTON_1){
				eLedState = LED_STOP;
			}
			else{
				eLedState = LED_LEFT;
				LedStepLeft();
			}
		break;				
	}	
}


int main (){
	unsigned int iMainLoopCtr;
	LedInit();
	KeyboardInit();	
	//Timer0Interrupts_Init(20000, &Automat);		
	Timer1Interrupts_Init(20000, &Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}


