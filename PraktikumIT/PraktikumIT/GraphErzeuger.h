#pragma once
#include "Bibliothek.h"
#include "ListenElement.h"
#include "SignalListeErzeuger.h"
#include <string>

class GraphErzeuger
{
public:
	GraphErzeuger(void);
	~GraphErzeuger(void);
	void setBibliothek(Bibliothek* bib);
	void setSignalListe(Signal* signalList);
	void erzeugeVerketteteListe();
	void erzeugeGraph();
	ListenElement* getStartElement();
	void ausgabeGraphstruktur();
	void erzeugeEingangsGatterString();

private:
	void zaehleSignale();
	SchaltwerkElement* getSchaltwerkElementByName(std::string quelle);

	Bibliothek* bibliothek;
	ListenElement* startElement;
	ListenElement* endElement;
	Signal* signale;
	std::string eingangsElemente;
	short anzahlSignale;
	short anzahlElemente;
};

