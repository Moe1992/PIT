#include "GraphErzeuger.h"

using namespace std;

GraphErzeuger::GraphErzeuger(void)
{
	startElement = NULL;
	endElement = NULL;
	anzahlElemente = 0;
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

bool GraphErzeuger::erzeugeVerketteteListe()
{
	if (signale != NULL)//Falls die Signalliste erzeugt wurde
	{
		loescheListe();
		erzeugeEingangsGatterString();
		for (int i = 0; i < anzahlSignale; i++) //Nach Durchlauf der Schleife ist die gesamte Liste erstellt. Es m�ssen aber nachtr�glich noch manche Attribute
												//der SchaltwerkElemente gesetzt werden.
		{
			if (signale[i].getSignalTyp() != eingang) //Handelt es sich nicht um ein Einganssignal, so gibt es ein Quellgatter
			{
				if (signale[i].getQuellenTyp() != "")// unbenutzetes Signal ausschlie�en
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

					anzahlElemente++;

					//GatterTyp* temp = bibliothek->getBibElement(signale[i].getQuellenTyp()); //der Gattertyp
					endElement->setSchaltwerkElement(new SchaltwerkElement(bibliothek->getBibElement(signale[i].getQuellenTyp())));	//wird direkt an den Konstruktor �bergeben

					//setzen der Attribute von SchaltwerkElement
					//Gattername wird gesetzt
					endElement->getSchaltwerkElement()->setName(signale[i].getQuelle());

					//isAusgangsElement und isEingangsElement setzen
					if (signale[i].getSignalTyp() == ausgang)
					{
						endElement->getSchaltwerkElement()->setIsAusgangsElement(true);
					}
					else
					{
						endElement->getSchaltwerkElement()->setIsAusgangsElement(false);
					}
					if (eingangsElemente.find(endElement->getSchaltwerkElement()->getName()) != std::string::npos)
					{
						endElement->getSchaltwerkElement()->setIsEingangsElement(true);
					}
					else
					{
						endElement->getSchaltwerkElement()->setIsEingangsElement(false);
					}
				}
				else
				{
					cout << "Fehler! Ein unbenutztes Signal wurde gefunden\n";
					system("pause");
					return false;
				}
			}
		}//ende for-Schleife
		return true;
	}
	return false;
}

void GraphErzeuger::loescheListe()
{
	if (startElement != NULL)
	{
		startElement = NULL;
		anzahlElemente = 0;
	}
}

bool GraphErzeuger::erzeugeGraph()
{
	if (erzeugeVerketteteListe())
	{
		for (int i = 0; i < anzahlSignale; i++) //alle Signale durchgehen
		{
			if (signale[i].getSignalTyp() != eingang) //handelt es sich nicht um ein Einganssignal, so gibt es ein Quellgatter
			{
				SchaltwerkElement* tempSWE = getSchaltwerkElementByName(signale[i].getQuelle());
				tempSWE->setAnzahlNachfolger(signale[i].getAnzahlZiele());
				for (int ziel = 0; ziel < signale[i].getAnzahlZiele(); ziel++)
				{
					tempSWE->nachfolgerHinzufuegen(getSchaltwerkElementByName(signale[i].getZiel(ziel)), ziel);
					tempSWE->getNachfolger(ziel)->incAnzahlEingangssignale();
				}
			}
			else
			{
				for (int ziel = 0; ziel < signale[i].getAnzahlZiele(); ziel ++)
				{
					getSchaltwerkElementByName(signale[i].getZiel(ziel))->incAnzahlEingangssignale();
				}
			}
		}
		//�berpr�fe ob AnzahlEingangssignale mit AnzahlEing�nge �bereinstimmt
		ListenElement* tempLE = startElement;
		short anzahlEingaenge, anzahlSignale;
		while (tempLE != NULL)
		{
			anzahlEingaenge = tempLE->getSchaltwerkElement()->getTyp()->getEingaenge();
			anzahlSignale = tempLE->getSchaltwerkElement()->getAnzahlEingangssignale();
			if (anzahlEingaenge != anzahlSignale)
			{
				cout << "Fehler!\n";
				cout << "Anzahl Eing\x84nge von " << tempLE->getSchaltwerkElement()->getName() << " laut Bibliothek: " << anzahlEingaenge << endl;
				cout << "Anzahl Eing\x84nge von " << tempLE->getSchaltwerkElement()->getName() << " laut Schaltwerk: " << anzahlSignale << endl;
				system("pause");
				return false;
			}
			tempLE = tempLE->getNextElement();
		}
		return true; 
	}
	cout << "Fehler beim Erzeugen des Graphen" << endl;
	system("pause");
	return false;
}

SchaltwerkElement* GraphErzeuger::getSchaltwerkElementByName(std::string quelle)
{
	ListenElement* tempLE = startElement;
	while (true)
	{
		if (quelle == tempLE->getSchaltwerkElement()->getName())
		{
			return tempLE->getSchaltwerkElement();
		}
		tempLE = tempLE->getNextElement();
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

void GraphErzeuger::erzeugeEingangsGatterString()
{
	zaehleSignale();
	eingangsElemente = "";
	for (int i = 0; i < anzahlSignale; i++)
	{
		if (signale[i].getSignalTyp() == eingang)
		{
			for (int j = 0; j < signale[i].getAnzahlZiele(); j++)
			{
				eingangsElemente += signale[i].getZiel(j);
			}
		}
	}
}
void GraphErzeuger::ausgabeGraphstruktur()
{
	ListenElement* tempLE = startElement;
	cout << "Graphstruktur" << endl;
	cout << "-------" << endl;
	for(int i = 0; i<anzahlElemente;i++)
	{
		int anzahlNachfolger = tempLE->getSchaltwerkElement()->getAnzahlNachfolger();
		cout << "Gattername: " << tempLE->getSchaltwerkElement()->getName() << endl;
		cout << "Gattertyp: " << tempLE->getSchaltwerkElement()->getTyp()->getName() << endl;
		cout << "--> Das Gatter hat " << anzahlNachfolger << (anzahlNachfolger == 1 ? " Ziel" : " Ziele") << endl;
		cout << "Angeschlossene Gatter:";
		for (int j = 0; j < anzahlNachfolger; j++)
		{
			cout << " " << tempLE->getSchaltwerkElement()->getNachfolger(j)->getName();
		}
		cout << endl << endl;

		tempLE = tempLE->getNextElement();
	}
	system("pause");
}

ListenElement* GraphErzeuger::getStartElement()
{
	return startElement;
}