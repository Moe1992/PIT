#pragma once

#include <iostream>

class Faktoren
{
public:
	Faktoren(void);
	~Faktoren(void);
	double getSpannung();
	double getTemperatur();
	short getProzess();
	void getFaktoren(double& spgFaktor, double& tmpFaktor, double& przFaktor);
	void setSpannung(double spg);
	void setTemperatur(double temp);
	void setProzess(short prz);
	void ausgabeFaktoren();

private:
	double spannung;
	double temperatur;
	short prozess;
	double spannungFaktor;
	double temperaturFaktor;
	double prozessFaktor;

	bool berechneSpannungFaktor(double spg);
	bool berechneTemperaturFaktor(double temp);
	bool berechneProzessFaktor(short prz);
	double berechneFaktor(double wert, double arr[][2], int laenge);
};

