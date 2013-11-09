#pragma once

#include <iostream>
#include "Faktoren.h"
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

	void faktorenMenue();
	void bibliothekMenue();
	void schaltwerkMenue();
	void spannungAendernMenue();
	void temperaturAendernMenue();
	void prozessAendernMenue();
	void analyse();
	void menueKopf();
	bool isNumber(std::string arg1);
	bool isShort(std::string arg1);
};

