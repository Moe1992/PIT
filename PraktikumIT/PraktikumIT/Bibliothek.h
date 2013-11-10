#pragma once

#include <string>

class Bibliothek
{
public:
	Bibliothek(std::string pfad);
	~Bibliothek(void);
	std::string getPfad();
	//GatterTyp getBibElement(std::string typ)
	void dateiAusgabe();
	void dateiAuswerten();
	bool pfadEinlesen();
	
private:
	//vector<GatterTyp*> bibElemente
	std::string datei;
	void openError();
	void readError();
};

