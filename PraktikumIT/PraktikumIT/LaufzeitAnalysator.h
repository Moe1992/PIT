#pragma once
#include "Faktoren.h"
#include "ListenElement.h"
#include <map>

class LaufzeitAnalysator
{
public:
	LaufzeitAnalysator(void);
	~LaufzeitAnalysator(void);
	void setFaktoren(Faktoren* fakt);
	void setStartElement(ListenElement* start);

private:
	Faktoren* faktoren;
	ListenElement* startElement;
	long frequenz;
	std::string uebergangspfad;
	std::string ausgangspfad;
	double laufzeitUebergangspfad;
	double laufzeitAusgangspfad;
	struct DFS_Daten
	{
		SchaltwerkElement* VaterElement;
		double PfadLaufzeit;
	};
	std::map<SchaltwerkElement*, DFS_Daten> DFS_Zwischenspeicher;
	void EinzelLaufzeit(); //Berechnung der Laufzeit der einzelnen Gatter

};

