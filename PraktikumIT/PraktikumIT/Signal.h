#pragma once

#include <string>

enum signalTypen { eingang, intern, ausgang, unbekannt };

class Signal
{
public:
	Signal();
	~Signal();
	int getAnzahlZiele(){
		return anzahlZiele;
	}
	signalTypen getSignalTyp(){
		return signalTyp;
	}
	std::string getQuelle(){
		return quelle;
	}
	std::string getQuellenTyp(){
		return quellenTyp;
	}
	std::string getZiel(int pos){
		return ziele[pos];
	}
	void setAnzahlZiele(int nZiele){
		anzahlZiele = nZiele;
	}
	void incAnzahlZiele(){
		anzahlZiele++;
	}
	void setSignalTyp(signalTypen sigTyp){
		signalTyp = sigTyp;
	}
	void setQuelle(std::string gatterName){
		quelle = gatterName;
	}
	void setQuellenTyp(std::string gatterTyp){
		quellenTyp = gatterTyp;
	}
	void zielHinzufuegen(std::string gatterName, int pos)
	{
		ziele[pos] = gatterName;
	}

private:
	signalTypen signalTyp;
	std::string quelle, quellenTyp;
	std::string ziele[5];									//dynamisches Array verwenden? max 5 Ziele laut Aufgabe
	int anzahlZiele;



};

