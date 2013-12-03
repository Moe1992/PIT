#include "SignalListeErzeuger.h"

using namespace std;

SignalListeErzeuger::SignalListeErzeuger()
{
	dateipfad = "csd.txt";
}


SignalListeErzeuger::~SignalListeErzeuger()
{
}

bool SignalListeErzeuger::setPfad(string _dateipfad){			//liefert true falls Datei existiert und geoeffnet weden kann
	ifstream datei(_dateipfad);
	if (datei){
		dateipfad = _dateipfad;
		datei.close();
		return true;
	}
	else{ return false; }
}

void SignalListeErzeuger::ausgabeDatei(){
	ifstream datei(dateipfad);
	string zeile;
	while (getline(datei, zeile)){
		cout << zeile << endl;
	}
	datei.close();
}

Signal* SignalListeErzeuger::erzeugeListe(){					//liefert Zeiger auf Liste falls Datei gueltig, ansonsten NULL
	anzahlSignale = 0;
	ifstream datei(dateipfad);
	string zeile, eing, ausg, internal;

	while (getline(datei, zeile)){
		if (zeile.find("ENTITY") != string::npos){
			//Anzahl bestimmen
			getline(datei, eing);
			anzahlSignale += sZaehlen(eing.substr(6));
			getline(datei, ausg);
			anzahlSignale += sZaehlen(ausg.substr(7));
			getline(datei, internal);
			anzahlSignale += sZaehlen(internal.substr(8));
			signale = new Signal[anzahlSignale];
			//Frequenz bestimmen
			getline(datei, zeile);
			zeile = zeile.substr(zeile.find(",") + 1);
			if (zeile.find("MHz") != string::npos){
				frequenz = 1000000 * strtol(zeile.c_str(), NULL, 0);
			}
			else if (zeile.find("kHz") != string::npos){
				frequenz = 1000 * strtol(zeile.c_str(), NULL, 0);
			}
			else{ frequenz = strtol(zeile.c_str(), NULL, 0); }
			//Signaltyp zuordnen
			while (eing.find("s") != string::npos){
				eing = eing.substr(eing.find("s") + 1);
				signale[atoi(eing.c_str()) - 1].setSignalTyp(eingang);
			}
			while (ausg.find("s") != string::npos){
				ausg = ausg.substr(ausg.find("s") + 1);
				signale[atoi(ausg.c_str()) - 1].setSignalTyp(ausgang);
			}
			while (internal.find("s") != string::npos){
				internal = internal.substr(internal.find("s") + 1);
				signale[atoi(internal.c_str()) - 1].setSignalTyp(intern);
			}


		}
		else if (zeile.find("BEGIN") != string::npos){
			getline(datei, zeile);
			//Gatteranalyse
			while (zeile.find("END") == string::npos){
				int doppelP = zeile.find(":");
				int klammer = zeile.find("(");
				int posAusgangssignal = zeile.rfind("s"); //Ausgangssignal sollte immer vorhanden sein

				string gatterName = zeile.substr(0, 4);
				string gatterTyp = zeile.substr(doppelP + 1, klammer - doppelP - 1);

				//Ausgangssignal des Gatters verarbeiten
				int a1 = atoi(zeile.substr(posAusgangssignal + 1).c_str());
				//Kurzschluss pruefen
				if (signale[a1 - 1].getQuelle() != ""){
					cout << endl << "Kurzschluss bei Signal s";
					printf("%03d", a1);
					cout << endl;
					return NULL;
				}
				signale[a1 - 1].setQuelle(gatterName);
				signale[a1 - 1].setQuellenTyp(gatterTyp);
				zeile = zeile.substr(klammer + 1, posAusgangssignal - klammer - 1);//String enhaelt danach nur noch max zwei Eingangssignale

				//Eingangssignale des Gatters verarbeiten
				if (int pos1 = zeile.find("s") != string::npos){
					int e1 = atoi(zeile.substr(pos1+1).c_str());
					zeile = zeile.substr(pos1+3);		//String kuerzen
					signale[e1 - 1].zielHinzufuegen(gatterName, signale[e1 - 1].getAnzahlZiele());
					signale[e1 - 1].incAnzahlZiele();
				}
				if (int pos2 = zeile.find("s") != string::npos){
					int e2 = atoi(zeile.substr(pos2 + 1).c_str());
					signale[e2 - 1].zielHinzufuegen(gatterName, signale[e2 - 1].getAnzahlZiele());
					signale[e2 - 1].incAnzahlZiele();
				}
				
				getline(datei, zeile);
			}
			//Gatteranalyse Ende
			break;
		}


	}

	datei.close();

	return signale;
}

void SignalListeErzeuger::ausgabeSignalListe(){
	if (erzeugeListe() != NULL)
	{
		cout << "--------------------" << endl;
		cout << "Signale:" << endl;
		for (int i = 0; i < anzahlSignale; i++){
			cout << "-----" << endl;
			cout << "Signalname: s";
			printf("%03d", i + 1);		//setprecision fuer fuehrende Nullen erforderlich
			cout << endl << "Signaltyp: ";
			switch (signale[i].getSignalTyp()){
			case 0: cout << "Eingangssignal"; break;
			case 1: cout << "internes Signal"; break;
			case 2: cout << "Ausgangssignal"; break;
			case 3: cout << "unbekanntes Signal"; break;
			}

			cout << endl << "Signalquelle: " << signale[i].getQuelle() << endl;
			cout << "Quellentyp: " << signale[i].getQuellenTyp() << endl;
			cout << "-->Das Signal hat " << signale[i].getAnzahlZiele() << (signale[i].getAnzahlZiele() == 1 ? " Ziel" : " Ziele") << endl;
			cout << "Ziel-Gatter : ";
			for (int j = 0; j < 5; j++){
				cout << signale[i].getZiel(j) << " ";
			}
			cout << endl;
		}
	}

}

int SignalListeErzeuger::sZaehlen(string zeile){
	int n = 0;
	while (true){

		if (zeile.find("s") != string::npos){
			n++;
			zeile = zeile.substr(zeile.find("s") + 1);
		}
		else{
			break;
		}
	}
	return n;
}
