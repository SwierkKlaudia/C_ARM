#include "command_decoder.h"
#include "string.h"

struct Token asToken[MAX_TOKEN_NR];
unsigned char ucTokenNr;

struct Keyword asKeywordList[MAX_KEYWORD_NR]={
{CAL,"callib"},
{GOTO, "goto" },
{SHIFT, "shift" },
{CALC, "calc"},
{LED, "led"},
{BUT, "but"},
{DET, "det"},
{ID, "id"}
};



unsigned char ucFindTokensInString (char *pcString)
{
	unsigned char ucTokenNr = 0;
	unsigned char ucCharacterCounter;
	unsigned char ucCurrentCharacter;
	enum Stan eStan = DELIMITER;
	
	for(ucCharacterCounter = 0;; ucCharacterCounter++){
		ucCurrentCharacter = pcString[ucCharacterCounter];
		switch(eStan){
			case TOKEN:
			{
				if(ucCurrentCharacter == DELIMITER_CHAR){
					eStan = DELIMITER;
				}
				else if(ucTokenNr == MAX_TOKEN_NR){
					return ucTokenNr;
				}
				else if(ucCurrentCharacter == NULL){
					return ucTokenNr;
				}
				else{
					eStan = TOKEN;
				}
			}
			break;
			case DELIMITER:
			{
				if((ucCurrentCharacter != DELIMITER_CHAR) && (ucCurrentCharacter != NULL)){
					eStan = TOKEN;
					asToken[ucTokenNr].uValue.pcString=pcString+ucCharacterCounter;
					ucTokenNr = ucTokenNr+1;
				}
				else if(ucCurrentCharacter == NULL){
					return ucTokenNr;
				}
				else{
					eStan = DELIMITER;
				}						
			}
		}		
	}
}


enum Result eStringToKeyword (char pcStr[], enum KeywordCode *peKeywordCode){
	
	unsigned char ucKeywordCounter;
	
	for(ucKeywordCounter = 0; (ucKeywordCounter < MAX_KEYWORD_NR); ucKeywordCounter++){
		if(EQUAL == eCompareString(asKeywordList[ucKeywordCounter].cString, pcStr)){
			*peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
			return OK;
		}
	}
	return ERROR;
}

void DecodeTokens()
{
	struct Token *psCurrentToken;
	unsigned int uiTokenValue;
	enum KeywordCode eTokenCode;
	unsigned char ucTokenCounter;
	
	for(ucTokenCounter = 0; ucTokenCounter < ucTokenNr; ucTokenCounter++){
		psCurrentToken = &asToken[ucTokenCounter];
		if(OK == eHexStringToUInt(psCurrentToken->uValue.pcString, &uiTokenValue)){
			psCurrentToken->eType = NUMBER;
			psCurrentToken->uValue.uiNumber = uiTokenValue;
		}
		else if(OK == eStringToKeyword(psCurrentToken->uValue.pcString, &eTokenCode)){
			psCurrentToken->eType = KEYWORD;
			psCurrentToken->uValue.eKeyword = eTokenCode;
		}
		else{
			psCurrentToken->eType = STRING;
		}
	}
}
	
void DecodeMsg(char *pcString){

	ucTokenNr = ucFindTokensInString(pcString);
	ReplaceCharactersInString(pcString,	DELIMITER_CHAR, NULL);
	DecodeTokens();
}

