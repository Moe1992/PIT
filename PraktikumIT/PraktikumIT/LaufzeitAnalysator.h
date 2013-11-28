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
	void starteAnalyse();
	void setFrequenz(long _frequenz);

private:
	Faktoren* faktoren;
	ListenElement* startElement;
	long frequenz;
	std::string uebergangspfad;
	std::string ausgangspfad;
	double laufzeitUebergangspfad;
	double laufzeitAusgangspfad;
	double spannungFaktor;
	double temperaturFaktor;
	double prozessFaktor;
	bool zyklus;

	struct DFS_Daten
	{
		SchaltwerkElement* VaterElement;
		double PfadLaufzeit;
	};
	std::map<SchaltwerkElement*, DFS_Daten> DFS_Zwischenspeicher;

	SchaltwerkElement* getSchaltwerkElementByName(std::string quelle);

	void EinzelLaufzeitenErmitteln(); //Berechnung der Laufzeit der einzelnen Gatter
	void dfs(ListenElement* startknoten);
	void dfs_visit(SchaltwerkElement* k, SchaltwerkElement* s);
	bool zyklensuche(SchaltwerkElement* sw);
	std::string pfad_erstellen(SchaltwerkElement* s, SchaltwerkElement* k, SchaltwerkElement* v);
	
};

