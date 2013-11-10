#pragma once

#include<string>

class GatterTyp
{
public:
	GatterTyp(void);
	~GatterTyp(void);
	std::string getName();
	double getGrundLaufzeit();
	short getLastFaktor();
	short getLastKapazitaet();
	short getEingaenge();
	bool getIsFlipflop();
	void setName(std::string n);
	void setGrundLaufzeit(double gl);
	void setLastFaktor(short lf);
	void setLastKapazitaet(short lk);
	void setEingaenge(short ei);

protected:
	std::string name;
	double grundLaufzeit;
	short lastFaktor;
	short lastKapazitaet;
	short eingaenge;
};

