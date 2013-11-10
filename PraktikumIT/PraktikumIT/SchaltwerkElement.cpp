#include "SchaltwerkElement.h"


SchaltwerkElement::SchaltwerkElement(void)
{
}


SchaltwerkElement::~SchaltwerkElement(void)
{
}

std::string getName()
{
	
}

/*GatterTyp* SchaltwerkElement::getTyp()
{
	
}
*/
double SchaltwerkElement::getLaufzeitEinzelgatter()
{
	
}

SchaltwerkElement SchaltwerkElement::getNachfolger(int pos)
{
	
}

int SchaltwerkElement::getAnzahlNachfolger()
{
	
}

short SchaltwerkElement::getAnzahlEingangssignale()
{
	
}

bool SchaltwerkElement::getIsEingangsElement()
{
	
}

bool SchaltwerkElement::getIsAusgangsElement()
{
	
}

void SchaltwerkElement::setName(std::string n)
{
	
}

void SchaltwerkElement::nachfolgerHinzufuegen(SchaltwerkElement schaltwerkElement, int pos)
{
	
}

void SchaltwerkElement::setAnzahlNachfolger(int anzahlN)
{
	
}

void SchaltwerkElement::setAnzahlEingangssignale(short anzahlE)
{
	
}

void SchaltwerkElement::setIsEingangsElement(bool isEingangsEl)
{
	
}

void SchaltwerkElement::setIsAusgangsElement(bool isAusgangsEl)
{
	
}

void SchaltwerkElement::setLaufzeitEinzelgatter(double lfz)
{
	
}