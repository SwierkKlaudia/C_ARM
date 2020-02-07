#include <LPC21xx.H>
#include "keyboard.h"

#define BUTT0_bm (1<<4)
#define BUTT1_bm (1<<6)
#define BUTT2_bm (1<<5)
#define BUTT3_bm (1<<7)

enum KeyboardState eKeyboardRead(){

	if((IO0PIN&BUTT0_bm) == 0){
		return BUTTON_0;
	}
	else if((IO0PIN&BUTT1_bm) == 0){
		return BUTTON_1;
	}
	else if((IO0PIN&BUTT2_bm) == 0){
		return BUTTON_2;
	}
	else if((IO0PIN&BUTT3_bm) == 0){
		return BUTTON_3;
	}
	else{
		return RELEASED;
	}
}

void KeyboardInit(){
		IO0DIR = IO0DIR & ~(BUTT0_bm | BUTT1_bm | BUTT2_bm | BUTT3_bm);
}

