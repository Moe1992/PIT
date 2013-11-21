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
				string gatterName = zeile.substr(0, 4);
				string gatterTyp = zeile.substr(doppelP + 1, klammer - doppelP - 1);
				//Gatter die nur zwei Eingangssignale haben(inv oder clock-Anschluss) 
				if ((gatterTyp.find("inv") != string::npos) || (zeile.find("clk") != string::npos)){
					zeile = zeile.substr(klammer + 2);
					int e1;
					if (zeile.substr(0, 2) == "lk"){
						zeile = zeile.substr(zeile.find(",") + 2);
						e1 = atoi(zeile.c_str());
					}
					else{
						e1 = atoi(zeile.c_str());
					}
					zeile = zeile.substr(zeile.rfind(",") + 2);
					int a1 = atoi(zeile.c_str());

					signale[e1 - 1].zielHinzufuegen(gatterName, signale[e1 - 1].getAnzahlZiele());
					signale[e1 - 1].incAnzahlZiele();
					//Kurzschluss pruefen
					if (signale[a1 - 1].getQuelle() != ""){
						cout << endl << "Kurzschluss bei Signal s";
						printf("%03d", a1);
						cout << endl;
					}
					signale[a1 - 1].setQuelle(gatterName);
					signale[a1 - 1].setQuellenTyp(gatterTyp);
				}
				//alle anderen Gatter
				else{
					zeile = zeile.substr(klammer + 2);
					int e1 = atoi(zeile.c_str());
					zeile = zeile.substr(zeile.find(",") + 2);
					int e2 = atoi(zeile.c_str());
					zeile = zeile.substr(zeile.find(",") + 2);
					int a1 = atoi(zeile.c_str());


					signale[e1 - 1].zielHinzufuegen(gatterName, signale[e1 - 1].getAnzahlZiele());
					signale[e1 - 1].incAnzahlZiele();
					signale[e2 - 1].zielHinzufuegen(gatterName, signale[e2 - 1].getAnzahlZiele());
					signale[e2 - 1].incAnzahlZiele();
					//Kurzschluss pruefen
					if (signale[a1 - 1].getQuelle() != ""){
						cout << endl << "Kurzschluss bei Signal s";
							printf("%03d", a1); 
						cout << endl;
					}
					signale[a1 - 1].setQuelle(gatterName);
					signale[a1 - 1].setQuellenTyp(gatterTyp);
				}
				getline(datei, zeile);
			}
			//Gatteranalyse Ende
			break;
		}


	}

	datei.close();

	cout << "Testausgabe AnzahlSignale: " << anzahlSignale << " Frequenz: " << frequenz << endl;			//zu entfernen

	return signale;
}

void SignalListeErzeuger::ausgabeSignalListe(){
	erzeugeListe();
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
