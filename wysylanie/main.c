#include "servo.h"
#include "keyboard.h"
#include "led.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"
#include "timer_interrupts.h"

#define TERMINATOR ';'

extern char cOdebranyZnak;
unsigned char ucRotationCouter = 1;
char cDestination[RECIEVER_SIZE];
unsigned char ucOffset = 0;

extern struct RecieverBuffer sBuffer;
extern struct Token asToken[];
extern unsigned char ucTokenNr;

extern struct TransmiterBuffer sTransmiterBuffer;

/*//TEST4
unsigned int uiNmber = 0;
char cHexString[6] = "";
char cMsgStr[14] = "";
*/

struct Watch {

	unsigned char ucMinutes, ucSecconds;
	unsigned char fSeccondsValueChanged, fMinutesValueChanged;
};

struct Watch sWatch;


struct Calc {
	
	unsigned char fCalcCommand;
	
};

struct Calc sCalc;

void WatchUpdate(){
	
	sWatch.ucSecconds++;
	sWatch.fSeccondsValueChanged=1;
	if(sWatch.ucSecconds >=60) {
		sWatch.ucSecconds=0;
		sWatch.ucMinutes++;
		sWatch.fMinutesValueChanged=1;
	}
	if(sWatch.ucMinutes >= 60){
		sWatch.ucMinutes=0;
	}
}

char cTab[TRANSMITER_SIZE];
char cRecStr[RECIEVER_SIZE];



struct Python{
	
	unsigned char fRecBut, fRecDet, fRecID;

};

struct Python sPython;


int main (){
	
	//LedInit();
	KeyboardInit();		
	//DetectorInit();
	UART_InitWithInt(9600);
	//Timer0Interrupts_Init(1000000,&WatchUpdate);

	ServoInit(50);
	
			
	while(1){
		
		if(eReciever_GetStatus() == READY){
			Reciever_GetStringCopy(cRecStr);
			DecodeMsg(cRecStr);
			
			if((ucTokenNr > 0) && (asToken[0].eType == KEYWORD)){
				switch(asToken[0].uValue.eKeyword){
					case LED:
						LedOn(asToken[1].uValue.uiNumber);
					break;
					case BUT:
						sPython.fRecBut = 1;
					break;
					case DET:
						sPython.fRecDet = 1;
					break;
					case ID:
						sPython.fRecID = 1;
					default:
					break;
				}
			}
		}
			
		if (Transmiter_GetStatus() == FREE){
			if(sPython.fRecBut==1){
				sPython.fRecBut=0;
				switch(eKeyboardRead()){
					case BUTTON_0:
						Transmiter_SendString("BUT 0");
					break;
					case BUTTON_1:
						Transmiter_SendString("BUT 1");
					break;
					case BUTTON_2:
						Transmiter_SendString("BUT 2");
					break;
					case BUTTON_3:
						Transmiter_SendString("BUT 3");
					break;
					default:
						Transmiter_SendString("BUT -1");
					break;
				}
			}
			else if(sPython.fRecDet==1){
					sPython.fRecDet=0;
				switch(eReadDetector()){
					case ACTIVE:
						Transmiter_SendString("DETECT 1");
					break;				
					default:
						Transmiter_SendString("DETECT 0");
					break;
				}
			}
			else if(sPython.fRecID==1){
				sPython.fRecID = 0;
				Transmiter_SendString("ID myUART");
				break;
			}
	}
			
		/*TEST 6
		
		if(eReciever_GetStatus() == READY){
			Reciever_GetStringCopy(cRecStr);
			DecodeMsg(cRecStr);
			
			if ((ucTokenNr > 0) && (asToken[0].uValue.eKeyword == CALC)){
				sCalc.fCalcCommand=1;
			}
			else{}
		}
		
		
		
		if (Transmiter_GetStatus() == FREE){
			if(sWatch.fSeccondsValueChanged==1){
			
				sWatch.fSeccondsValueChanged=0;
				CopyString("sec ",cTab);
				AppendUIntToString(sWatch.ucSecconds,cTab);
				Transmiter_SendString(cTab);
			}
			else if(sWatch.fMinutesValueChanged==1){
			
				sWatch.fMinutesValueChanged=0;
				CopyString("min ",cTab);
				AppendUIntToString(sWatch.ucMinutes,cTab);
				Transmiter_SendString(cTab);
			}
			else if(sCalc.fCalcCommand == 1){
					sCalc.fCalcCommand=0;
					CopyString("calc ",cTab);
					AppendUIntToString((asToken[1].uValue.uiNumber)*2, cTab);
					Transmiter_SendString(cTab);
				
			}
		}
		*/
				
		/*
		//TEST3
		if(Transmiter_GetStatus()==FREE){
			Transmiter_SendString("test123");
		}
		*/
		
		/*
		//TEST4
		if(Transmiter_GetStatus()==FREE){
			UIntToHexStr(uiNmber,cHexString);
			CopyString("licznik ",cMsgStr);
			AppendString(cHexString,cMsgStr);
			Transmiter_SendString(cMsgStr);
			uiNmber++;
		}
		*/
	
	
		/*
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
		*/
	}
}

