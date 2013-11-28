#include "LaufzeitAnalysator.h"

using namespace std;

LaufzeitAnalysator::LaufzeitAnalysator(void)
{
}


LaufzeitAnalysator::~LaufzeitAnalysator(void)
{
}

void LaufzeitAnalysator::setFaktoren(Faktoren* fakt)
{
	faktoren = fakt;
}
void LaufzeitAnalysator::setFrequenz(long _frequenz){
	frequenz = _frequenz;
}

void LaufzeitAnalysator::setStartElement(ListenElement* start)
{
	startElement = start;
}

void LaufzeitAnalysator::starteAnalyse()
{
	EinzelLaufzeitenErmitteln();
	laufzeitUebergangspfad = 0;
	uebergangspfad = "";
	zyklus = false;
	ListenElement* tempLE = startElement;
	//alle Eingangsgatter und FFs werden einmal als Startknoten betrachtet
	do{			//
		if (tempLE->getSchaltwerkElement()->getIsEingangsElement() || tempLE->getSchaltwerkElement()->getTyp()->getIsFlipflop()){
			dfs(tempLE);
		}
		tempLE = tempLE->getNextElement();
	} while (tempLE != NULL);

	if(zyklus)
	{
		system("pause");
		return;
	}
	
	double setuptime = 0;

	if (uebergangspfad != "")
	{
		string name = uebergangspfad.substr(uebergangspfad.rfind("g"),4);
		double setuptime = (double) getSchaltwerkElementByName(name)->getTyp()->getSetupTime(); 
	}

	double maxFreq = ((laufzeitUebergangspfad != 0) ? (1 / (laufzeitUebergangspfad + setuptime)) : -1); //[f]=[1/ps]

	//Ausgabe
	system("cls");
	
	if (maxFreq != -1)
	{
		cout << "L\x84ngster Pfad im \x9A" << "berf\x81hrungsschaltnetz: " << endl;
		cout << uebergangspfad; 
		cout << endl << "Maximale Laufzeit der Pfade im \x9A" << "berf\x81hrungsschaltnetz: " << laufzeitUebergangspfad << " ps" << endl << endl; 
	}

	cout << "L\x84ngster Pfad im Ausgangsschaltnetz: " << endl;
	cout << ausgangspfad; 
	cout << endl << "Maximale Laufzeit der Pfade im Ausgangsschaltnetz: " << laufzeitAusgangspfad << " ps" << endl << endl;

	cout << "------------------------------------" << endl << endl;
	
	
	if (maxFreq != -1)
	{
		cout << "Die maximal zul\x84ssige Frequenz f\x81r das Schaltnetz / -werk betr\x84gt: " << maxFreq*1000000 << " MHz" << endl << endl;
	}
	
	cout << "Bedingung f\x81r die Taktfrequenz vom Schaltnetz / -werk ist" << ((frequenz/1000000000000 < maxFreq || maxFreq == -1) ? "" : " nicht") << " erf\x81llt!" << endl;
	cout << "Die Taktfrequenz " << frequenz / 1000000 << " MHz ist ";
	if (frequenz / 1000000000000 < maxFreq || maxFreq == -1) cout << "kleiner";
	else cout << "gr\x94\xE1" << "er";
	cout << " als die maximale Frequenz!" << endl;
	cout << endl << "------------------------------------" << endl;
	system("pause");
}

void LaufzeitAnalysator::EinzelLaufzeitenErmitteln()
{
	ListenElement* tempListenElement = startElement;
	SchaltwerkElement* tempSchaltwerkElement;
	GatterTyp* tempGatterTyp;
	faktoren->getFaktoren(spannungFaktor, temperaturFaktor, prozessFaktor);
	double tpd0;
	double tpdactual;
	double tlast;
	do
	{
		tempSchaltwerkElement = tempListenElement->getSchaltwerkElement();
		tempGatterTyp = tempSchaltwerkElement->getTyp();
		tlast = 0;
		tpd0 = tempGatterTyp->getGrundLaufzeit();

		for (int i = 0; i < tempSchaltwerkElement->getAnzahlNachfolger(); i++)
		{
			tlast += tempSchaltwerkElement->getNachfolger(i)->getTyp()->getLastKapazitaet(); //Zuerst die Lastkapazitäten addieren. Noch handelt es sich um Kapazitäten
		}
		//Nachdem die Lastkapazitäten summiert sind, können sie mit dem Lastfaktor multipliziert werden, um tlast zu bekommen
		tlast = tlast * tempSchaltwerkElement->getTyp()->getLastFaktor() / 1000; //Umrechnung in ps
		//Jetzt wird die gesamte Gatterlaufzeit anhand der Formel berechnet: tpd,actual = (tpd0 + tlast) * KT * KV * KP
		tpdactual = (tpd0 + tlast) * spannungFaktor * temperaturFaktor * prozessFaktor;
		tempSchaltwerkElement->setLaufzeitEinzelgatter(tpdactual);

		tempListenElement = tempListenElement->getNextElement();
	} while (tempListenElement != NULL);
}

void LaufzeitAnalysator::dfs(ListenElement* startknoten){
	ListenElement* tempLE = startElement;
	DFS_Daten init;
	init.VaterElement = NULL;
	init.PfadLaufzeit = 0;
	//alle Laufzeiten auf 0, Vaterknoten auf NULL setzen
	do{
		DFS_Zwischenspeicher[tempLE->getSchaltwerkElement()] = init;
		tempLE = tempLE->getNextElement();
	} while (tempLE != NULL);
	dfs_visit(startknoten->getSchaltwerkElement(), startknoten->getSchaltwerkElement());
}

void LaufzeitAnalysator::dfs_visit(SchaltwerkElement* k, SchaltwerkElement* s){
	SchaltwerkElement* v = NULL;
	if(zyklus) return;

	for (int i = 0; i < k->getAnzahlNachfolger(); i++){
		v = k->getNachfolger(i);
		if (v->getTyp()->getIsFlipflop()){			//Ist Folgeknoten ein FF, so ist Endelement des Uebergangspfades gefunden
			if (laufzeitUebergangspfad < (DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter())){
				laufzeitUebergangspfad = (DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter());
				uebergangspfad = pfad_erstellen(s, k, v);  //String der besuchten Gatter
			}
		}
		else if (DFS_Zwischenspeicher[v].PfadLaufzeit < (DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter())){
			if (((DFS_Zwischenspeicher[v].PfadLaufzeit != 0) || (v == s)) && (DFS_Zwischenspeicher[v].VaterElement != k)){
				SchaltwerkElement* temp = DFS_Zwischenspeicher[v].VaterElement;
				DFS_Zwischenspeicher[v].VaterElement = k;

				if (zyklensuche(v)){		//zyklensuche
					//fehler_wegen_zyklus();
					cout << "Zyklus gefunden" << endl;
					zyklus = true;
					if (temp != NULL){
						DFS_Zwischenspeicher[v].VaterElement = temp;	//?
					}
					break;
				}
			}
			DFS_Zwischenspeicher[v].PfadLaufzeit = DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter();
			DFS_Zwischenspeicher[v].VaterElement = k;
			dfs_visit(v, s);
		}
	}

	if ((k->getIsAusgangsElement()) && (laufzeitAusgangspfad < (DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter()))){
		laufzeitAusgangspfad = DFS_Zwischenspeicher[k].PfadLaufzeit + k->getLaufzeitEinzelgatter();
		ausgangspfad = pfad_erstellen(s, k, v);
	}
}

bool LaufzeitAnalysator::zyklensuche(SchaltwerkElement* sw){
	SchaltwerkElement* temp = sw;
	while (temp != NULL){
		temp = DFS_Zwischenspeicher[temp].VaterElement;
		if (temp == sw){
			return true;
		}
	}
	return false;
}

string LaufzeitAnalysator::pfad_erstellen(SchaltwerkElement* s, SchaltwerkElement* k, SchaltwerkElement* v){
	string pfad = "";

	SchaltwerkElement* temp = k;

	//Pfad vom Startelement rekonstruieren
	while (temp != s){
		pfad.insert(0, temp->getName() + "->");
		temp = DFS_Zwischenspeicher.find(temp)->second.VaterElement;
	}
	pfad.insert(0, "->" + s->getName() + "->");
	if (v != NULL){
		pfad = pfad + v->getName() + "->";

	}


	return pfad;
}

SchaltwerkElement* LaufzeitAnalysator::getSchaltwerkElementByName(std::string quelle)
{
	ListenElement* tempLE = startElement;
	while (true)
	{
		if (quelle == tempLE->getSchaltwerkElement()->getName())
		{
			return tempLE->getSchaltwerkElement();
		}
		tempLE = tempLE->getNextElement();
	}
}