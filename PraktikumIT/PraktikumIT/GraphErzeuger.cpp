#include "GraphErzeuger.h"


GraphErzeuger::GraphErzeuger(void)
{
	startElement = NULL;
	endElement = NULL;
}


GraphErzeuger::~GraphErzeuger(void)
{
}

void GraphErzeuger::setBibliothek(Bibliothek* bib)
{
	bibliothek = bib;
}

void GraphErzeuger::setSignalListe(Signal* signalList)
{
	signale = signalList;
}

void GraphErzeuger::erzeugeVerketteteListe()
{
	if (signale != NULL)//Falls die Signalliste erzeugt wurde
	{
		zaehleSignale();
		for (int i = 0; i < anzahlSignale; i++)
		{
			if (signale[i].getSignalTyp() != eingang) //Handelt es sich nicht um ein Einganssignal, so gibt es ein Quellgatter
			{
				if (startElement == NULL)//Sind noch keine Elemente in der Liste enthalten, erstelle eine Liste
				{
					startElement = new ListenElement();
					endElement = startElement;
					startElement->setNextElement(NULL);
				}
				else
				{
					endElement->setNextElement(new ListenElement());
					endElement = endElement->getNextElement();
					endElement->setNextElement(NULL); 
				}
				endElement->setSchaltwerkElement(new SchaltwerkElement());
				GatterTyp* temp = bibliothek->getBibElement(signale[i].getQuellenTyp());//der Gattertyp muss später im Konstruktor von SchaltwerkElement
																						//übergeben werden.
			}
		}
	}
}

void GraphErzeuger::zaehleSignale()
{
	int i = 0;
	while (true)
	{
		if (signale[i].getSignalTyp() != eingang && signale[i].getSignalTyp() != intern && signale[i].getSignalTyp() != ausgang && signale[i].getSignalTyp() != unbekannt)
		{
			break;
		}
		else
		{
			i++;
		}
	}
	anzahlSignale = i;
}
