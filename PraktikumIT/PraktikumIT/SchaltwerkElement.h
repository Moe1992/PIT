#pragma once
#include <iostream>
#include <string>

class SchaltwerkElement
{
public:
	SchaltwerkElement(void);
	~SchaltwerkElement(void);
	std::string getName();
	//******GatterTyp* getTyp();
	double getLaufzeitEinzelgatter();
	SchaltwerkElement getNachfolger(int pos);
	int getAnzahlNachfolger();
	short getAnzahlEingangssignale();
	bool getIsEingangsElement();
	bool getIsAusgangsElement();
	void setName(std::string n);
	void nachfolgerHinzufuegen(SchaltwerkElement schaltwerkElement, int pos);
	void setAnzahlNachfolger(int anzahlN);
	void setAnzahlEingangssignale(short anzahlE);
	void setIsEingangsElement(bool isEingangsEl);
	void setIsAusgangsElement(bool isAusgangsEl);
	void setLaufzeitEinzelgatter(double lfz);

private:
	std::string name;
	//GatterTyp* typ;
	double laufzeitEinzelgatter;
	SchaltwerkElement* nachfolgerElement;
	int anzahlNachfolger;
	bool isEingangsElement;
	bool isAusgangsElement;
	short anzahlEingangssignale;
};

