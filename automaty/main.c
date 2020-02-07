#include "keyboard.h"
#include "led.h"


void delay(int iDelayTime){
	int i;
	
	for(i=0; i<(5455*iDelayTime); i++){
	}
}


/*
///CWICZENIE1
int main()
{
	enum LedState {LED_LEFT, LED_RIGHT};
	enum LedState eLedState = LED_LEFT;

	LedInit();
	KeyboardInit();

	while(1){	
		switch(eLedState){
			case LED_LEFT:
				eLedState = LED_RIGHT;
				LedStepRight();
			break;
			case LED_RIGHT:
				eLedState = LED_LEFT;
				LedStepLeft();
			break;
		}
		delay(250);				
	}	
}
*/
/*
/////CWICZENIE2
int main()
{
	enum LedState {STATE0_L, STATE1_L, STATE2_L, STATE3_R, STATE4_R, STATE5_R};
	enum LedState eLedState = STATE5_R;

	LedInit();
	KeyboardInit();

	while(1){	
		switch(eLedState){
			case STATE0_L:
				eLedState = STATE1_L;
				LedStepLeft();
			break;
			case STATE1_L:
				eLedState = STATE2_L;
				LedStepLeft();
			break;
			case STATE2_L:
				eLedState = STATE3_R;
				LedStepRight();
			break;
			case STATE3_R:
				eLedState = STATE4_R;
				LedStepRight();
			break;			
			case STATE4_R:
				eLedState = STATE5_R;
				LedStepRight();
			break;
			case STATE5_R:
				eLedState = STATE0_L;
				LedStepLeft();
			break;			
		}
		delay(250);			
	}	
}
*/
/*
///////CWICZENIE3
int main()
{
	enum LedState {LED_LEFT, LED_RIGHT};
	enum LedState eLedState = LED_LEFT;
	
	unsigned char ucStepCounter = 0;

	LedInit();
	KeyboardInit();

	while(1){
		switch(eLedState){
			case LED_LEFT:
				if(ucStepCounter == 2){
					ucStepCounter = 0;
					eLedState = LED_RIGHT;
					LedStepRight();
				}
				else{
					eLedState = LED_LEFT;
					ucStepCounter++;
					LedStepLeft();
				}
			break;
			case LED_RIGHT:
				if(ucStepCounter == 2){
					ucStepCounter = 0;
					eLedState = LED_LEFT;
					LedStepLeft();
				}
				else{
					eLedState = LED_RIGHT;
					ucStepCounter++;
					LedStepRight();
				}
			break;
		}
		delay(250);			
	}
}
*/

/*
///////CWICZENIE4
int main()
{
	enum LedState {LED_STOP, LED_RIGHT};
	enum LedState eLedState = LED_STOP;
	
	unsigned char ucStepCounter = 0;

	LedInit();
	KeyboardInit();

	while(1){
		switch(eLedState){
			case LED_STOP:
				if(eKeyboardRead() == BUTTON_0){
					ucStepCounter = 0;
					eLedState = LED_RIGHT;
					LedStepRight();
				}
				else{
					eLedState = LED_STOP;
				}
			break;
			case LED_RIGHT:
				if(ucStepCounter == 2){
					eLedState = LED_STOP;
				}
				else{
					eLedState = LED_RIGHT;
					ucStepCounter++;
					LedStepRight();
				}
			break;
		}
		delay(250);			
	}
}
*/

/*
/////////CWICZENIE5
int main()
{
	enum LedState {LED_STOP, LED_RIGHT};
	enum LedState eLedState = LED_RIGHT;

	LedInit();
	KeyboardInit();

	while(1){
		switch(eLedState){
			case LED_STOP:
				if(eKeyboardRead() == BUTTON_1){
					eLedState = LED_RIGHT;
					LedStepRight();
				}
				else{
					eLedState = LED_STOP;
				}
			break;
			case LED_RIGHT:
				if(eKeyboardRead() == BUTTON_0){
					eLedState = LED_STOP;
				}
				else{
					eLedState = LED_RIGHT;
					LedStepRight();
				}
			break;
		}
		delay(250);			
	}
}
*/

/*
///////////CWICZENIE6
int main()
{
	enum LedState {LED_STOP, LED_RIGHT, LED_LEFT};
	enum LedState eLedState = LED_STOP;

	LedInit();
	KeyboardInit();

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
					eLedState = LED_STOP;
				}
			break;
			case LED_RIGHT:
				if(eKeyboardRead() == BUTTON_2){
					eLedState = LED_STOP;
				}
				else{
					eLedState = LED_RIGHT;
					LedStepRight();
				}
			break;
			case LED_LEFT:
				if(eKeyboardRead() == BUTTON_2){
					eLedState = LED_STOP;
				}
				else{
					eLedState = LED_LEFT;
					LedStepLeft();
				}
			break;				
		}
		delay(100);			
	}
}
*/

///////////CWICZENIE
int main()
{
	enum LedState {LED_STOP, LED_RIGHT, LED_LEFT, LED_DELAY};
	enum LedState eLedState = LED_STOP;
	unsigned char ucStepCounter = 0; 

	LedInit();
	KeyboardInit();

	while(1){
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
				else if(eKeyboardRead() == BUTTON_2){
					eLedState = LED_DELAY;
				}
				else{
					eLedState = LED_LEFT;
					LedStepLeft();
				}
			break;	
			case LED_DELAY:
				if(ucStepCounter == 9){
					eLedState = LED_RIGHT;
					LedStepRight();
					ucStepCounter = 0;
				}
				else{
					eLedState = LED_DELAY;
					ucStepCounter++;
					LedStepLeft();
				}
			break;				
		}
		delay(100);			
	}
}





