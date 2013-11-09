#include "Menue.h"

using namespace std;

Menue::Menue(void)
{
	Faktoren meineFaktoren = Faktoren();
}


Menue::~Menue(void)
{
}

void Menue::start()
{
	string input;
	bool ending = false;
	while (true)
	{
		system("cls");
		menueKopf();
		cout << "(1) \x8Eu\xE1" << "ere Faktoren" << endl;
		cout << "Spannung [Volt]: " << meineFaktoren.getSpannung() << endl;
		cout << "Temperatur [Grad Celsius]: " << meineFaktoren.getTemperatur() << endl;
		cout << "Prozess (1=slow, 2=typical, 3=fast): " << meineFaktoren.getProzess() << endl << endl;

		cout << "(2) Bibliothek" << endl;
		cout << "Pfad zur Bibliotheksdatei: " << endl << endl; //********Pfad ausgeben

		cout << "(3) Schaltwerk" << endl;
		cout << "Pfad zur Schaltwerksdatei: " << endl << endl; //*******Pfad ausgeben

		cout << "(4) Analyse starten" << endl << endl;

		cout << "(5) Programm beenden" << endl << endl << endl;

		cout << "W\x84hle einen Men\x81punkt und best\x84tige mit Enter:\n";

		getline(cin, input);
		if(input.length() != 1)
		{
			cout << "Bitte geben Sie eine g\x81ltige Zahl ein!" << endl;
			system("pause");
		}
		else
		{
			switch (input.at(0))
			{
			case '1':
				faktorenMenue();
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
				cout << "Bitte geben Sie eine g\x81ltige Zahl ein!" << endl;
				system("pause");
			break;
			}
		}
		if(ending) break;
	}

}

void Menue::faktorenMenue()
{
	string input;
	bool ending = false;
	while (true)
	{
		system("cls");
		menueKopf();
		cout << "\x8Eu\xE1" << "ere Faktoren einstellen" << endl;
		cout << "(1) Spannung [Volt]: " << meineFaktoren.getSpannung() << endl;
		cout << "(2) Temperatur [Grad Celsius]: " << meineFaktoren.getTemperatur() << endl;
		cout << "(3) Prozess (1=slow, 2=typical, 3=fast): " << meineFaktoren.getProzess() << endl;
		cout << "(4) Ausgabe errechneter Faktoren" << endl;
		cout << "(5) Hauptmen\x81" << endl << endl;
		cout << "W\x84hle einen Men\x81punkt und best\x84tige mit Enter:\n";

		getline(cin, input);
		system("cls");
		menueKopf();

		if(input.length() != 1)
		{
			cout << "Bitte geben Sie eine gueltige Zahl ein!" << endl;
			system("pause");
		}
		else
		{
			switch (input.at(0))
			{
			case '1':
				spannungAendernMenue();
			break;
			case '2':
				temperaturAendernMenue();
			break;
			case '3':
				prozessAendernMenue();
			break;
			case '4':
				meineFaktoren.ausgabeFaktoren();
			break;
			case '5':
			ending = true;
			break;
			default:
				cout << "Bitte geben Sie eine gueltige Zahl ein" << endl;
				system("pause");
			break;
			}
		}
		if(ending) break;
	}
}

void Menue::bibliothekMenue()
{
	
}

void Menue::schaltwerkMenue()
{
	
}

void Menue::spannungAendernMenue()
{
	while (true)
	{
		string input;
		system("cls");
		menueKopf();
		cout << "Bitte gib die Betriebsspannung an\n";
		getline(cin, input);
		if (isNumber(input))
		{
			meineFaktoren.setSpannung(boost::lexical_cast<double>(input));
			break;
		}
		else
		{
			cout << "Bitte gib einen g\x81ltigen Wert an\n";
			system("pause");
		} 
	}
}

void Menue::temperaturAendernMenue()
{
	while (true)
	{
		string input;
		system("cls");
		menueKopf();
		cout << "Bitte gib die Bauteiltemperatur an\n";
		getline(cin, input);
		if (isNumber(input))
		{
			meineFaktoren.setTemperatur(boost::lexical_cast<double>(input));
			break;
		}
		else
		{
			cout << "Bitte gib einen g\x81ltigen Wert an\n";
			system("pause");
		} 
	}
}

void Menue::prozessAendernMenue()
{
	while (true)
	{
		string input;
		cout << "Bitte gib die Bauteiltemperatur an\n";
		getline(cin, input);
		if (isShort(input))
		{
			meineFaktoren.setProzess(boost::lexical_cast<short>(input));
			break;
		}
		else
		{
			cout << "Bitte gib einen g\x81ltigen Wert an\n";
			system("pause");
		} 
	}
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

bool Menue::isNumber(string arg1)
{
	try
	{
		boost::lexical_cast<double>(arg1);
		return true;
	}catch(boost::bad_lexical_cast const&)
	{
		return false;
	}
	return false;
}

bool Menue::isShort(string arg1)
{
	try
	{
		boost::lexical_cast<short>(arg1);
		return true;
	}catch(boost::bad_lexical_cast const&)
	{
		return false;
	}
	return false;
}