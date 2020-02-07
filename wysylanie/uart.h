
#define RECIEVER_SIZE 25
#define TRANSMITER_SIZE 25

enum eRecieverStatus {EMPTY, READY, OVERFLOW};
struct RecieverBuffer{
	char cData[RECIEVER_SIZE];			//przechowanie lancucha
	unsigned char ucCharCtr;				//iteracja po lancuchu
	enum eRecieverStatus eStatus;		//status bufora
};



enum eTransmiterStatus {FREE, BUSY};
struct TransmiterBuffer{
	char cData[TRANSMITER_SIZE];		//przechowanie lancucha
	enum eTransmiterStatus eStatus;	//status bufora
	unsigned char fLastCharacter;		//flaga ostatniego znaku(0,1)
	unsigned char cCharCtr;					//iteracja po lancuchu
};


void UART_InitWithInt(unsigned int uiBaudRate);
void Reciever_PutCharacterToBuffer(char cCharacter);
enum eRecieverStatus eReciever_GetStatus(void);
void Reciever_GetStringCopy(char * ucDestination);

char Transmiter_GetCharacterFromBuffer(void);
void Transmiter_SendString(char cString[]);
enum eTransmiterStatus Transmiter_GetStatus(void);

