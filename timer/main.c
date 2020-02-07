#include "keyboard.h"
#include "led.h"
#include "timer.h"


int main()
{
	enum LedState {LED_STOP, LED_RIGHT, LED_LEFT};
	enum LedState eLedState = LED_STOP;

	LedInit();
	KeyboardInit();
	InitTimer0();
	//InitTimer0Match0(100000);

	while(1){
		switch(eLedState){
			case LED_STOP:
				if(eKeyboardRead() == BUTTON_1){
					eLedState = LED_LEFT;
					LedStepLeft();
				}
				else if(eKeyboardRead() == BUTTON_3){
					eLedState = LED_RIGHT;
					LedStepRight();
				}				
				else{
				}
			break;
			case LED_RIGHT:
				if(eKeyboardRead() == BUTTON_2){
					eLedState = LED_STOP;
				}
				else{
					LedStepRight();
				}
			break;
			case LED_LEFT:
				if(eKeyboardRead() == BUTTON_2){
					eLedState = LED_STOP;
				}
				else{
					LedStepLeft();
				}
			break;				
		}
		WaitOnTimer0(100000);
		//WaitOnTimer0Match0();			
	}
}





