#include "servo.h"
#include "keyboard.h"
#include "uart.h"

extern char cOdebranyZnak;
unsigned char ucRotationCouter = 1;

int main (){
	
	UART_InitWithInt(9600);
	KeyboardInit();
	ServoInit(50);
	
	
			
	while(1){
		
		switch(eKeyboardRead()){
			case BUTTON_0:
				ServoCallib();
			break;
			case BUTTON_1:
				ServoGoTo(12);
			break;
			case BUTTON_2:
				ServoGoTo(24);
			break;
			case BUTTON_3:
				ServoGoTo(36);
			break;
			default:
			break;
		}
		
		switch( cOdebranyZnak ) {
			case 'c':
				cOdebranyZnak = '\0';
				ucRotationCouter = 1;
				ServoCallib();
			break;
			case '1':
				cOdebranyZnak = '\0';
				ServoGoTo(12*ucRotationCouter);
				ucRotationCouter++;
			break;
			default:
			break;
		}
	}
}

