#pragma once

#include <iostream>
#include "Faktoren.h"
#include "SignalListeErzeuger.h"
#include <string>
#include <boost\lexical_cast.hpp>

class Menue
{
public:
	Menue(void);
	~Menue(void);
	void start();

private:
	Faktoren meineFaktoren;
	SignalListeErzeuger meinSignalListeErzeuger;
	bool debug;
	ItivDev_Config* DevPtr;

	void readValuesFromDevice();
	void faktorenMenue();
	void bibliothekMenue();
	void schaltwerkMenue();
	void debugAendernMenue();
	void spannungAendernMenue();
	void temperaturAendernMenue();
	void prozessAendernMenue();
	void schaltwerkPfadAendernMenue();
	void analyse();
	void menueKopf();
	bool isNumber(std::string arg1);
	bool isShort(std::string arg1);
};

