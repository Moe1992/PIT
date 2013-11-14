#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "GatterTyp.h"

class Bibliothek
{
public:
	Bibliothek(std::string pfad);
	Bibliothek();
	~Bibliothek(void);
	std::string getPfad();
	GatterTyp* getBibElement(std::string typ);
	void dateiAusgabe();
	void dateiAuswerten();
	bool pfadEinlesen(std::string pfad);
	
private:
	//vector<GatterTyp> bibElemente;
	std::string datei;
	void openError();
	void readError();
};

