#include "SignalListeErzeuger.h"

using namespace std;

SignalListeErzeuger::SignalListeErzeuger()
{
	dateipfad = "";
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
	//ifstream datei(dateipfad);
	//string zeile;
	//while (getline(datei, zeile)){
	//	
	//}
	//datei.close();
	return NULL;
}

void SignalListeErzeuger::ausgabeSignalListe(){
	//erzeugeListe();
	cout << "-------------------------------" << endl;
	cout << "Signale:" << endl;
	//For...

}
