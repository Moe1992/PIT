#include "Faktoren.h"

using namespace std;

Faktoren::Faktoren(void)
{
}


Faktoren::~Faktoren(void)
{
}

double Faktoren::getSpannung()
{
	return spannung;
}

double Faktoren::getTemperatur()
{
	return temperatur;
}

short Faktoren::getProzess()
{
	return prozess;
}

void Faktoren::getFaktoren(double& spgFaktor, double& tmpFaktor, double& przFaktor)
{
	
}

void Faktoren::setSpannung(double spg)
{
	spannung = spg;
}

void Faktoren::setTemperatur(double temp)
{
	temperatur = temp;
}

void Faktoren::setProzess(short prz)
{
	prozess = prz;
}

void Faktoren::ausgabeFaktoren()
{
	
}

bool Faktoren::berechneSpannungFaktor(double spg)
{
	
}

bool Faktoren::berechneTemperaturFaktor(double temp)
{
	
}

bool Faktoren::berechneProzessFaktor(short prz)
{
	
}

double Faktoren::berechneFaktor(double wert, double arr[][2], int laenge)
{
	
}
