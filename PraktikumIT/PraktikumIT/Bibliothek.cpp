#include "Bibliothek.h"

using namespace std;

Bibliothek::Bibliothek(string pfad)
{
	datei = pfad;
}

Bibliothek::Bibliothek()
{

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
		while(getline(bib,zeile))
		{
			cout << zeilenNr << " " << zeile << endl;
			zeilenNr++;
		}
	} else {
		openError();
	}
}

void Bibliothek::dateiAuswerten()
{
	ifstream bib(datei.c_str());
	if(bib)
	{
		string zeile;
		while(getline(bib,zeile))
		{
			int gatterNr = 0;
			if((zeile != "[[Bausteine]]") && (zeile.find("[") == 0))
			{
				int posEnd = zeile.find("]");
				string temp = zeile.substr(1,posEnd-1);
				if(temp != "dff")
				{
					bibElemente.push_back(new GatterTyp);
				} else 
				{
					bibElemente.push_back(new Flipflop);
				}
				bibElemente.at(gatterNr)->setName(temp);
			} else if(zeile.find("ei:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.at(gatterNr)->setEingaenge(atof(temp.c_str()));
			} else if(zeile.find("tpd0:") == 0)
			{
				string temp = zeile.substr(5);
				bibElemente.at(gatterNr)->setGrundLaufzeit(atof(temp.c_str()));
			} else if(zeile.find("kl:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.at(gatterNr)->setLastFaktor(atof(temp.c_str()));
			} else if(zeile.find("cl:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.at(gatterNr)->setLastKapazitaet(atof(temp.c_str()));
				gatterNr++;
			} else if(zeile.find("tsetup:") == 0)
			{
				string temp = zeile.substr(7);
				bibElemente.at(gatterNr)->setSetupTime(atof(temp.c_str()));
			} else if(zeile.find("thold:") == 0)
			{
				string temp = zeile.substr(6);
				bibElemente.at(gatterNr)->setHoldTime(atof(temp.c_str()));
			} else if(zeile.find("ct:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.at(gatterNr)->setLastKapazitaetClock(atof(temp.c_str()));
				gatterNr++;
			}
		}
	}
	
}

bool Bibliothek::pfadEinlesen(string pfad)
{
	datei = pfad;
	ifstream bib(datei.c_str());
	if(bib)
	{
		return 1;
	} else 
	{
		return 0;
	}
}

void Bibliothek::openError()
{
	cout << "Die Datei konnte nicht geoeffnet werden" << endl;
}

void Bibliothek::readError()
{
	cout << "Beim lesen der Datei ist ein Fehler aufgetreten" << endl;
}