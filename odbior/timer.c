#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE (1<<0)
#define COUNTER_RESET (1<<1)
#define MR0_RESET (1<<1)
#define MR0_INTERRUPT (1<<0)

void InitTimer0(void)
{
	T0TCR = (COUNTER_ENABLE | T0TCR);
}

void WaitOnTimer0(unsigned int uiTime)
{
	T0TCR = (T0TCR | COUNTER_RESET);
	T0TCR = (T0TCR & ~COUNTER_RESET);
	while(T0TC<(15*uiTime))
	{}
}

void InitTimer0Match0(unsigned int iDelayTime)
{
	T0MR0 = (iDelayTime*15);
	T0MCR = (MR0_RESET | MR0_INTERRUPT | T0MCR);	
	T0TCR = (COUNTER_ENABLE | COUNTER_RESET | T0TCR);
}

void WaitOnTimer0Match0(){
	T0TCR = (T0TCR & ~COUNTER_RESET);
	while((T0IR & MR0_INTERRUPT) == 0){}
	T0IR = MR0_INTERRUPT;	
}

