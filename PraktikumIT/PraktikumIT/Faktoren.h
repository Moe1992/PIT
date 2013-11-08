#pragma once
class Faktoren
{
public:
	Faktoren(void);
	~Faktoren(void);
	double getSpannung();
	double getTemperatur();
	short getProzess();
	void getFaktoren(double& spgFaktor, double& tmpFaktor, double& przFaktor);
	double setSpannung(double spannung);
	double setTemperatur(double temperatur);
	double setProzess(short prozess);

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

