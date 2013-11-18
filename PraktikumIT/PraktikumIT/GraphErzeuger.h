#pragma once
#include "Bibliothek.h"
#include "ListenElement.h"
#include "SignalListeErzeuger.h"

class GraphErzeuger
{
public:
	GraphErzeuger(void);
	~GraphErzeuger(void);
	void setBibliothek(Bibliothek* bib);
	void setSignalListe(Signal* signalList);
	void erzeugeVerketteteListe();

private:
	void zaehleSignale();

	Bibliothek* bibliothek;
	ListenElement* startElement;
	ListenElement* endElement;
	Signal* signale;
	short anzahlSignale;
};

