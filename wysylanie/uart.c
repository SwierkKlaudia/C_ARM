#include <LPC210X.H>
#include "uart.h"
#include "string.h"

/************ UART ************/
// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   0x00000080
#define m8BIT_UART_WORD_LENGTH                     0x00000003

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE        0x00000001
#define mTHRE_INTERRUPT_ENABLE                     0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  0x0000000F
#define mTHRE_INTERRUPT_PENDING                    0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       0x00000004


#define mUART0_RX								   								 0x00000004
#define mUART0_TX																	 0x00000001

/************ Interrupts **********/
// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE                           0x00000020

#define NULL 0
#define TERMINATOR ';'

////////////// Zmienne globalne ////////////
char cOdebranyZnak;

struct RecieverBuffer sBuffer;

struct TransmiterBuffer sTransmiterBuffer;

///////////////////////////////////////////
__irq void UART0_Interrupt (void) {
   // jesli przerwanie z odbiornika (Rx)
   
   unsigned int uiCopyOfU0IIR=U0IIR; // odczyt U0IIR powoduje jego kasowanie wiec lepiej pracowac na kopii

   if      ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) // odebrano znak
   {
     cOdebranyZnak = U0RBR;
		 Reciever_PutCharacterToBuffer(cOdebranyZnak);
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)              // wyslano znak - nadajnik pusty 
   {
		 if(sTransmiterBuffer.eStatus == BUSY){
			 U0THR = Transmiter_GetCharacterFromBuffer();
		 }
   }

   VICVectAddr = 0; // Acknowledge Interrupt
}

////////////////////////////////////////////
void UART_InitWithInt(unsigned int uiBaudRate){

   // UART0
   PINSEL0 = PINSEL0 | mUART0_RX | mUART0_TX;                   // ustawic pina na odbiornik uart0
   U0LCR  |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT; // dlugosc slowa, DLAB = 1
   U0DLL   = ((15000000)/16)/uiBaudRate;                        // predkosc transmisji
   U0LCR  &= (~mDIVISOR_LATCH_ACCES_BIT);                       // DLAB = 0
   U0IER  |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE | mTHRE_INTERRUPT_ENABLE;               // aktywacja przerwan po odebraniu danych (RDA)

   // INT
   VICVectAddr1  = (unsigned long) UART0_Interrupt;             // set interrupt service routine address
   VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
}


void Reciever_PutCharacterToBuffer(char cCharacter){


	if(sBuffer.ucCharCtr == RECIEVER_SIZE ) {
		sBuffer.eStatus = OVERFLOW;
	} 
	else if (cCharacter == TERMINATOR) {
		sBuffer.cData[sBuffer.ucCharCtr] = NULL;
		sBuffer.eStatus = READY;
		sBuffer.ucCharCtr = 0;
	} 
	else {
		sBuffer.cData[sBuffer.ucCharCtr] = cCharacter;
		sBuffer.ucCharCtr++;
	}
	
}


enum eRecieverStatus eReciever_GetStatus(void){
	return sBuffer.eStatus;
	
}

void Reciever_GetStringCopy(char * ucDestination){
	CopyString(sBuffer.cData, ucDestination);
	sBuffer.eStatus = EMPTY;
	
}



char Transmiter_GetCharacterFromBuffer(void){
	unsigned char ucCurrentChar;
	
	ucCurrentChar = sTransmiterBuffer.cData[sTransmiterBuffer.cCharCtr];
	
	if(ucCurrentChar == NULL){
		if(sTransmiterBuffer.fLastCharacter == 0){
			sTransmiterBuffer.fLastCharacter = 1;
			return '\r';
		}
		else{
			sTransmiterBuffer.fLastCharacter = 0;
			sTransmiterBuffer.eStatus = FREE;
			return '\n';
		}
	}
	else{
		sTransmiterBuffer.cCharCtr++;
		return ucCurrentChar;
	}
}

void Transmiter_SendString(char cString[]){
	
	sTransmiterBuffer.eStatus = BUSY;
	sTransmiterBuffer.cCharCtr = 0;
	CopyString(cString,sTransmiterBuffer.cData);
	U0THR = Transmiter_GetCharacterFromBuffer();
}

enum eTransmiterStatus Transmiter_GetStatus(void){
	
	return sTransmiterBuffer.eStatus;
}
