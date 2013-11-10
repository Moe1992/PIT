#include "SchaltwerkElement.h"


SchaltwerkElement::SchaltwerkElement(void)
{
	name = "";
	laufzeitEinzelgatter = 0;
	nachfolgerElemente = NULL;
	anzahlNachfolger = 0;
	isEingangsElement = NULL;
	isAusgangsElement = NULL;
	anzahlEingangssignale = 0;
}


SchaltwerkElement::~SchaltwerkElement(void)
{
}

std::string SchaltwerkElement::getName()
{
	return name;
}

/*GatterTyp* SchaltwerkElement::getTyp()
{
	
}
*/
double SchaltwerkElement::getLaufzeitEinzelgatter()
{
	return laufzeitEinzelgatter;
}

SchaltwerkElement SchaltwerkElement::getNachfolger(int pos)
{
	
}

int SchaltwerkElement::getAnzahlNachfolger()
{
	return anzahlNachfolger;
}

short SchaltwerkElement::getAnzahlEingangssignale()
{
	return anzahlEingangssignale;
}

bool SchaltwerkElement::getIsEingangsElement()
{
	return isEingangsElement;
}

bool SchaltwerkElement::getIsAusgangsElement()
{
	return isAusgangsElement;
}

void SchaltwerkElement::setName(std::string n)
{
	name = n;
}

void SchaltwerkElement::nachfolgerHinzufuegen(SchaltwerkElement schaltwerkElement, int pos)
{
	
}

void SchaltwerkElement::setAnzahlNachfolger(int anzahlN)
{
	anzahlNachfolger = anzahlN;
}

void SchaltwerkElement::setAnzahlEingangssignale(short anzahlE)
{
	anzahlEingangssignale = anzahlE;
}

void SchaltwerkElement::setIsEingangsElement(bool isEingangsEl)
{
	isEingangsElement = isEingangsEl;
}

void SchaltwerkElement::setIsAusgangsElement(bool isAusgangsEl)
{
	isAusgangsElement = isAusgangsEl;
}

void SchaltwerkElement::setLaufzeitEinzelgatter(double lfz)
{
	laufzeitEinzelgatter = lfz;
}