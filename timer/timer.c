#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE (1<<0)
#define COUNTER_RESET (1<<1)
#define MR0_RESET (1<<1)
#define MR0_INTERRUPT (1<<0)

void InitTimer0(void)
{
	T0TCR = (COUNTER_ENABLE | T0TCR);	//Enable na 1, wlaczenie Timer Counter
}

void WaitOnTimer0(unsigned int uiTime)
{
	T0TCR = (T0TCR | COUNTER_RESET);	//Reset na 1
	T0TCR = (T0TCR & ~COUNTER_RESET);	//reset Timer Counter i Reset na 0
	while(T0TC < (15*uiTime))	//poczekanie do osiagniecia przez Timer Counter wartosci podanej w wywolaniu funcji	(!= nie moze byc uzyte)
	{}	//1dodanie kolejnej wartosci do TimerCounter 2sprawdzenie czy wartosci sa rowne
}

void InitTimer0Match0(unsigned int iDelayTime)
{
	T0MR0 = (iDelayTime*15);	//ustawienie MR0 zeby miala wartosc podana w wywolaniu funcji
	T0MCR = (MR0_RESET | MR0_INTERRUPT | T0MCR);	// Reset on MR0 i Interrupt on MR0 na 1
	T0TCR = (COUNTER_ENABLE | COUNTER_RESET | T0TCR);	//Enable na 1, wlaczenie Timer Counter, Reset na 1
}

void WaitOnTimer0Match0(){
	T0TCR = (T0TCR & ~COUNTER_RESET);	//Reset na 0, reset Timer Counter
	while((T0IR & MR0_INTERRUPT) == 0){}	//poczekanie do osiagniecia przez Timer Counter wartosci jak w MR0, generacja Interrupt Register
	T0IR = MR0_INTERRUPT;	//wyzerowanie flagi przerywnika, jedynka zeruje Interupt Counter
}

