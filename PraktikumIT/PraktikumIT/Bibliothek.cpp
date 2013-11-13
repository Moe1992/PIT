#include "Bibliothek.h"

using namespace std;

Bibliothek::Bibliothek(string pfad)
{
	datei = pfad;
}


Bibliothek::~Bibliothek(void)
{
}

string Bibliothek::getPfad()
{
	return datei;
}

/*GatterTyp* Bibliothek::getBibElement(string typ)
{

}*/

void Bibliothek::dateiAusgabe()
{
	ifstream bib(datei.c_str());
	if(bib)
	{
		int zeilenNr = 1;
		string zeile;
		while(!bib.eof())
		{
			getline(bib,zeile);
			cout << zeilenNr << " " << zeile << endl;
			zeilenNr++;
		}
	} else {
		openError();
	}
}

void Bibliothek::dateiAuswerten()
{

}

bool Bibliothek::pfadEinlesen(string pfad)
{
	datei = pfad;
	return 1; //nicht final
}

void Bibliothek::openError()
{
	cout << "Die Datei konnte nicht geoeffnet werden" << endl;
}

void Bibliothek::readError()
{
	cout << "Beim lesen der Datei ist ein Fehler aufgetreten" << endl;
}