#include "LaufzeitAnalysator.h"

using namespace std;

LaufzeitAnalysator::LaufzeitAnalysator(void)
{
}


LaufzeitAnalysator::~LaufzeitAnalysator(void)
{
}

void LaufzeitAnalysator::setFaktoren(Faktoren* fakt)
{
	faktoren = fakt;
}

void LaufzeitAnalysator::setStartElement(ListenElement* start)
{
	startElement = start;
}

void LaufzeitAnalysator::starteAnalyse()
{
	EinzelLaufzeitenErmitteln();
}

void LaufzeitAnalysator::EinzelLaufzeitenErmitteln()
{
	ListenElement* tempListenElement = startElement;
	SchaltwerkElement* tempSchaltwerkElement;
	GatterTyp* tempGatterTyp;
	faktoren->getFaktoren(spannungFaktor, temperaturFaktor, prozessFaktor);
	double tpd0;
	double tpdactual;
	double tlast;
	do
	{
		tempSchaltwerkElement = tempListenElement->getSchaltwerkElement();
		tempGatterTyp = tempSchaltwerkElement->getTyp();
		tlast = 0;
		tpd0 = tempGatterTyp->getGrundLaufzeit();

		for(int i = 0; i < tempSchaltwerkElement->getAnzahlNachfolger(); i++)
		{
			tlast += tempSchaltwerkElement->getNachfolger(i)->getTyp()->getLastKapazitaet(); //Zuerst die Lastkapazitäten addieren. Noch handelt es sich um Kapazitäten
		}
		//Nachdem die Lastkapazitäten summiert sind, können sie mit dem Lastfaktor multipliziert werden, um tlast zu bekommen
		tlast = tlast * tempSchaltwerkElement->getTyp()->getLastFaktor() / 1000; //Umrechnung in ps
		//Jetzt wird die gesamte Gatterlaufzeit anhand der Formel berechnet: tpd,actual = (tpd0 + tlast) * KT * KV * KP
		tpdactual = (tpd0 + tlast) * spannungFaktor * temperaturFaktor * prozessFaktor;
		tempSchaltwerkElement->setLaufzeitEinzelgatter(tpdactual);

		tempListenElement = tempListenElement->getNextElement();
	} while ( tempListenElement != NULL );
}