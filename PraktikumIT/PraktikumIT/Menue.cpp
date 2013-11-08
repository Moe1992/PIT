#include "Menue.h"

using namespace std;

Menue::Menue(void)
{
	Faktoren* meineFaktoren = new Faktoren();
}


Menue::~Menue(void)
{
}

void Menue::start()
{
	char input;
	bool ending = false;
	while (true)
	{
		system("cls");
		menueKopf();
		cout << "(1) Aeussere Faktoren" << endl;
		//cout << "Spannung [Volt]: " << meineFaktoren->getSpannung() << endl;
		//cout << "Temperatur [Grad Celsius]: " << meineFaktoren->getTemperatur() << endl;
		//cout << "Prozess (1=slow, 2=typical, 3=fast): " << meineFaktoren->getProzess() << endl << endl;

		cout << "(2) Bibliothek" << endl;
		cout << "Pfad zur Bibliotheksdatei: " << endl << endl; //********Pfad ausgeben

		cout << "(3) Schaltwerk" << endl;
		cout << "Pfad zur Schaltwerksdatei: " << endl << endl; //*******Pfad ausgeben

		cout << "(4) Analyse starten" << endl << endl;

		cout << "(5) Programm beenden" << endl << endl << endl;

		cout << "Waehle einen Menuepunkt und bestaetige mit Enter: ";
		
		cin >> input;

		switch (input)
		{
		case '1':
			break;
		case '2':
			break;
		case '3':
			break;
		case '4':
			break;
		case '5':
			ending = true;
			//system("stop");
			break;
		default:
			break;
		}

		if(ending) break;
	}

}

void Menue::faktorenMenue()
{
	
}

void Menue::bibliothekMenue()
{
	
}

void Menue::schaltwerkMenue()
{
	
}

void Menue::analyse()
{
	
}

void Menue::menueKopf()
{
	cout << "********************************************\n";
	cout << "*     IT-Projektpraktikum WS2013/2014      *\n";
	cout << "*  Laufzeitanalyse synchroner Schaltwerke  *\n";
	cout << "********************************************\n" << endl;
}
