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


private:
	Signal* signale;
	short anzahlSignale;
	std::string dateipfad;
	long frequenz;
};

