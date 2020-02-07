#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"

#define PinDetector (1<<10)
//#define OFFSET 12

void DetectorInit(){
	IO0DIR = (IO0DIR & ~PinDetector);
}



enum DetectorState eReadDetector(){
	if((IO0PIN & PinDetector)==0)
		{
			return ACTIVE;
		}
	else
	{
		return INACTIVE;
	}
}



struct Servo
{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
};

struct Servo sServo;
	


void Automat(){
		
	switch (sServo.eState){	
		case CALLIB:
			if(eReadDetector()==ACTIVE){
				sServo.uiCurrentPosition=0;
				sServo.uiDesiredPosition=0;
				sServo.eState=IDLE;								
			}
			else{
				LedStepLeft();
				sServo.eState=CALLIB;
			}
		break;
		case IDLE:
			if(sServo.uiCurrentPosition!=sServo.uiDesiredPosition)
			{
				sServo.eState=IN_PROGRESS;
			}
			else
			{
				sServo.eState=IDLE;
			}		
		break;
		case IN_PROGRESS:
			if(sServo.uiCurrentPosition==sServo.uiDesiredPosition)
			{
				sServo.eState=IDLE;
			}
			else if(sServo.uiCurrentPosition>sServo.uiDesiredPosition)
			{
				LedStepLeft();
				sServo.uiCurrentPosition--;
				sServo.eState=IN_PROGRESS;
			}
			else if(sServo.uiCurrentPosition<sServo.uiDesiredPosition)
			{
				LedStepRight();
				sServo.uiCurrentPosition++;
				sServo.eState=IN_PROGRESS;
			}
			else{
				sServo.eState=IN_PROGRESS;
			}
		break;
	}
}

void ServoInit(unsigned int uiServoFrequency){
	LedInit();
	DetectorInit();
	Timer0Interrupts_Init(1000000/uiServoFrequency, &Automat);
	ServoCallib();
}

void ServoCallib(void){
	sServo.eState=CALLIB;
	while(sServo.eState==CALLIB){};
	ServoGoTo(0);
	
}

void ServoGoTo(unsigned int uiPosition){
	sServo.eState=IN_PROGRESS;
	sServo.uiDesiredPosition=(uiPosition);	//sServo.uiDesiredPosition=(uiPosition+OFFSET);
	while(sServo.eState==IN_PROGRESS){};
}

