#include "Flipflop.h"


Flipflop::Flipflop(void)
{
}


Flipflop::~Flipflop(void)
{
}

//Einfache Set/Get-Befehle sind Selbsterkl�rend
bool Flipflop::getIsFlipflop()
{
	return 1;
}

short Flipflop::getSetupTime()
{
	return setupTime;
}

short Flipflop::getHoldTime()
{
	return holdTime;
}

short Flipflop::getLastKapazitaetClock()
{
	return lastKapazitaetClock;
}

void Flipflop::setSetupTime(short st)
{
	setupTime = st;
}

void Flipflop::setHoldTime(short ht)
{
	holdTime = ht;
}

void Flipflop::setLastKapazitaetClock(short lkc)
{
	lastKapazitaetClock = lkc;
}
