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

bool berechneSpannungFaktor(double spg);
	double spannungFaktor;

private:
	double spannung;
	double temperatur;
	short prozess;
	double temperaturFaktor;
	double prozessFaktor;
	double spannungListe[7][2];
	double temperaturListe[15][2];
	double prozessListe[3];

	
	bool berechneTemperaturFaktor(double temp);
	bool berechneProzessFaktor(short prz);
	double berechneFaktor(double wert, double arr[][2], int laenge);
	double interpolation(double wert, double x1, double y1, double x2, double y2);
};