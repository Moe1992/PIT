#pragma once

#include "Signal.h"
#include <iostream>
#include <fstream>
#include <string>
#include <boost\lexical_cast.hpp>


class SignalListeErzeuger
{
public:
	SignalListeErzeuger();
	~SignalListeErzeuger();


	bool setPfad(std::string dateipfad);		//liefert true falls Datei existiert und geoeffnet weden kann
	std::string getPfad(){ return dateipfad; }
	void ausgabeDatei();
	Signal* erzeugeListe();					//liefert Zeiger auf Liste falls Datei gueltig, ansonsten NULL
	void ausgabeSignalListe();
	long getFrequenz(){
		return frequenz;
	}


private:
	Signal* signale;
	short anzahlSignale;
	std::string dateipfad;
	long frequenz;
	int sZaehlen(std::string zeile);
};

