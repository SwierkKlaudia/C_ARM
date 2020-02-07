#include "servo.h"
#include "keyboard.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"

#define TERMINATOR ';'

extern char cOdebranyZnak;
unsigned char ucRotationCouter = 1;
char cDestination[RECIEVER_SIZE];
unsigned char ucOffset = 0;

extern struct RecieverBuffer sBuffer;
extern struct Token asToken[];
extern unsigned char ucTokenNr;

int main (){
	
	UART_InitWithInt(9600);
	KeyboardInit();	
	
	/*
//Zakladamy, ze RECIEVER_SIZE równa sie 4
Reciever_PutCharacterToBuffer ('k');
Reciever_PutCharacterToBuffer ('o');
Reciever_PutCharacterToBuffer ('d');
Reciever_PutCharacterToBuffer (TERMINATOR);
// w buforze powinien znalezc sie lancuch znakowy “kod\0”,
// status powinien równac sie READY, a cCharCtr 0.
sBuffer.eStatus = EMPTY;
Reciever_PutCharacterToBuffer ('k');
Reciever_PutCharacterToBuffer ('o');
Reciever_PutCharacterToBuffer ('d');
Reciever_PutCharacterToBuffer ('1');
Reciever_PutCharacterToBuffer (TERMINATOR);
// status powinien równac sie OVERFLOW
	*/
	
	
	
	ServoInit(50);
	
	
			
	while(1){
		
		
		/* CWICZENIE 2
		
		if(eReciever_GetStatus() == READY){
			Reciever_GetStringCopy(cDestination);
			
			if(eCompareString(cDestination, "callib")== EQUAL){
				ServoCallib();
			}
			else if(eCompareString(cDestination, "left")== EQUAL){
				ServoGoTo(50);
			}
			else if(eCompareString(cDestination, "right")== EQUAL){
				ServoGoTo(150);
			}
			else{}
		}

		*/
	
		if(eReciever_GetStatus() == READY){
			Reciever_GetStringCopy(cDestination);
			DecodeMsg(cDestination);
			
			if((ucTokenNr > 0) && (asToken[0].eType == KEYWORD)){
				switch(asToken[0].uValue.eKeyword){
					case CAL:
						ServoCallib();
						ucOffset = 0;
					break;
					case GOTO:
						if(ucTokenNr > 1){
							ucOffset = asToken[1].uValue.uiNumber;
							ServoGoTo(asToken[1].uValue.uiNumber);
						}
						else{}
					break;
					case SHIFT:
						if(ucTokenNr > 1){
							ucOffset = ucOffset + asToken[1].uValue.uiNumber;
							ServoGoTo(ucOffset);
						}
						else{}		
					break;
					default:
					break;
				}
			}
			else{}
		}
	}
}

