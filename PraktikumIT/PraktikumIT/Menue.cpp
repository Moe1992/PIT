#include "Menue.h"

using namespace std;

Menue::Menue(void)
{
	Faktoren meineFaktoren = Faktoren();
	DevPtr = ItivDev_GetConfigByName("Global\\ITIV_WindowsDevice");
	debug = false;
}


Menue::~Menue(void)
{
}

void Menue::start()
{
	string input;
	while (true)
	{
		system("cls");
		menueKopf();
		if(!debug)
		{
			readValuesFromDevice();
		}
		cout << "(1) \x8Eu\xE1" << "ere Faktoren" << endl;
		cout << "    Spannung [Volt]:                     " << meineFaktoren.getSpannung() << endl;
		cout << "    Temperatur [Grad Celsius]:           " << meineFaktoren.getTemperatur() << endl;
		cout << "    Prozess (1=slow, 2=typical, 3=fast): " << meineFaktoren.getProzess() << endl << endl;

		cout << "(2) Bibliothek" << endl;
		cout << "    Pfad zur Bibliotheksdatei: " << endl << endl; //********Pfad ausgeben

		cout << "(3) Schaltwerk" << endl;
		cout << "    Pfad zur Schaltwerksdatei: " << endl << endl; //*******Pfad ausgeben

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
				goto ende;
				break;
			default:
				cout << "Bitte geben Sie eine g\x81ltige Zahl ein!" << endl;
				system("pause");
				break;
			}
		}
	}
ende:;
}

void Menue::faktorenMenue()
{
	string input;
	while (true)
	{
		system("cls");
		menueKopf();
		cout << "\x8Eu\xE1" << "ere Faktoren einstellen" << endl;
		cout << "(0) Debug-Modus aktiviert: ";
			if(debug) cout << "ja\n"; else cout << "nein\n";
		if(debug) cout << "(1) "; else cout << "    "; 
		cout << "Spannung [Volt]:                     " << meineFaktoren.getSpannung() << endl;
		if(debug) cout << "(2) ";  else cout << "    "; 
		cout << "Temperatur [Grad Celsius]:           " << meineFaktoren.getTemperatur() << endl;
		if(debug) cout << "(3) ";  else cout << "    "; 
		cout << "Prozess (1=slow, 2=typical, 3=fast): " << meineFaktoren.getProzess() << endl;
		cout << "(4) Ausgabe errechneter Faktoren" << endl;
		cout << "(5) Hauptmen\x81" << endl << endl;
		cout << "W\x84hle einen Men\x81punkt und best\x84tige mit Enter:\n";

		getline(cin, input);
		system("cls");
		menueKopf();

		if(input.length() != 1)
		{
			cout << "Bitte geben Sie eine g\x81ltige Zahl ein!" << endl;
			system("pause");
		}
		else
		{
			switch (input.at(0))
			{
			case '0':
				debugAendernMenue();
				break;
			case '1':
				if(debug) spannungAendernMenue();
				break;
			case '2':
				if(debug) temperaturAendernMenue();
				break;
			case '3':
				if(debug) prozessAendernMenue();
				break;
			case '4':
				meineFaktoren.ausgabeFaktoren();
				break;
			case '5':
				goto ende;
				break;
			default:
				cout << "Bitte geben Sie eine g\x81ltige Zahl ein" << endl;
				system("pause");
			break;
			}
		}
	}
ende:;
}

void Menue::bibliothekMenue()
{
	
}

void Menue::schaltwerkMenue()
{
	
}

void Menue::debugAendernMenue()
{
	while (true)
	{
		string input;
		system("cls");
		menueKopf();
		cout << "Debug-Modus aktivieren? j/n:\n";
		getline(cin, input);
		if (input.length() != 1)
		{
			cout << "Bitte geben Sie 'j' oder 'n' ein" << endl;
			system("pause");
		}
		else
		{
			switch (input.at(0))
			{
			case 'j':
				debug = true;
				goto ende;
				break;
			case 'n':
				debug = false;
				goto ende;
				break;
			default:
				cout << "Bitte geben Sie 'j' oder 'n' ein" << endl;
				system("pause");
				break;
			}
		}
	}
ende:;
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
		system("cls");
		menueKopf();
		cout << "Bitte gib den Prozess an\n(1=slow, 2=typical, 3=fast)\n";
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

void Menue::readValuesFromDevice()
{
	volatile uint8_t* device = DevPtr->BaseAddress;
}