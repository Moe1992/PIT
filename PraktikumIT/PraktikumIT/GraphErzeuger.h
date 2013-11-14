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

private:
	Bibliothek* bibliothek;
	ListenElement* startElement;
	ListenElement* endElement;
	Signal* signale;
	short anzahlSignale;
};

