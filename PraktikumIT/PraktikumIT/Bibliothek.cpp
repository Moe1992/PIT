#include "Bibliothek.h"

using namespace std;

//Konstruktor der Bibliotheksklasse mit Festlegung des Attributs "datei" (Speicherort der Bibliotheksdatei)
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

//Einfache Set/Get-Befehle sind Selbsterklärend
string Bibliothek::getPfad()
{
	return datei;
}


GatterTyp* Bibliothek::getBibElement(string typ)
{
	for(int i = 0 ; i < bibElemente.size(); i++) //Vector bibElemente wird nach dem gesuchten Element durchsucht und dessen Adresse wird zurück gegeben
	{
		if(typ == bibElemente.at(i)->getName())
		{
			return bibElemente.at(i);
		}
	}
	return NULL;
}

void Bibliothek::dateiAusgabe()
{
	ifstream bib(datei.c_str());
	if(bib)
	{
		int zeilenNr = 1;
		string zeile;
		while(getline(bib,zeile)) //Bibliotheksdatei wird zeilenweiße mit Zeilennummer ausgegeben
		{
			cout << zeilenNr << " " << zeile << endl;
			zeilenNr++;
		}
	} else {
		openError();
	}
	system("pause");
}

void Bibliothek::dateiAuswerten()
{
	ifstream bib(datei.c_str());
	bibElemente.clear();

	if(bib)
	{
		string zeile;
		while(getline(bib,zeile)) //Bibliotheksdatei wird zeilenweiße ausgelesen
		{
			if((zeile != "[[Bausteine]]") && (zeile.find("[") == 0)) //Die Zeile wird nach Namen und Eigenschaften durchsucht
			{
				int posEnd = zeile.find("]");
				string temp = zeile.substr(1,posEnd-1); //Wird ein Name gefunden, aber kein dff, wird ein GatterTyp-Element angelegt
				if(temp != "dff")                       //Wird ein dff im Namen gefunden wird ein Flipflop-Element angelegt
				{
					bibElemente.push_back(new GatterTyp);
				} else 
				{
					bibElemente.push_back(new Flipflop);
				}
				bibElemente.back()->setName(temp); //Wird eine Eigenschaft gefunden wird sie in das zuletzt erstellte Element gespeichert
			} else if(zeile.find("ei:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.back()->setEingaenge(atof(temp.c_str()));
			} else if(zeile.find("tpd0:") == 0)
			{
				string temp = zeile.substr(5);
				bibElemente.back()->setGrundLaufzeit(atof(temp.c_str()));
			} else if(zeile.find("kl:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.back()->setLastFaktor(atof(temp.c_str()));
			} else if(zeile.find("cl:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.back()->setLastKapazitaet(atof(temp.c_str()));
			} else if(zeile.find("tsetup:") == 0)
			{
				string temp = zeile.substr(7);
				bibElemente.back()->setSetupTime(atof(temp.c_str()));
			} else if(zeile.find("thold:") == 0)
			{
				string temp = zeile.substr(6);
				bibElemente.back()->setHoldTime(atof(temp.c_str()));
			} else if(zeile.find("ct:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.back()->setLastKapazitaetClock(atof(temp.c_str()));
			} else if(zeile.find("ed:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.back()->setEingaenge(atof(temp.c_str()));
			} else if(zeile.find("cd:") == 0)
			{
				string temp = zeile.substr(3);
				bibElemente.back()->setLastKapazitaet(atof(temp.c_str()));
			} else if(zeile.find("tpdt:") == 0)
			{
				string temp = zeile.substr(5);
				bibElemente.back()->setGrundLaufzeit(atof(temp.c_str()));
			}
			
		}
	}
	if(bibElemente.size() == 0) //Ist der vector nach der Abarbeitung leer wird ein Fehler ausgegeben
	{
		readError(); 
	}
	bib.close();
}

bool Bibliothek::pfadEinlesen(string pfad)
{
	string tempDatei = pfad;
	ifstream bib(tempDatei.c_str());
	if(bib) //Die Datei wird testweiße geöffnet und bei Erfolg wird der neue Pfad gespeichert
	{
		bib.close();
		datei = pfad;
		return 1;
	} else 
	{
		openError();
		return 0;
	}
}

//Fehlermeldungen beim Lesen oder Öffnen der Bibliotheksdatei
void Bibliothek::openError()
{
	cout << "Die Datei konnte nicht geoeffnet werden" << endl;
}

void Bibliothek::readError()
{
	cout << "Beim lesen der Datei ist ein Fehler aufgetreten" << endl;
}