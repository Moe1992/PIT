#include "Menue.h"

using namespace std;

//Konstruktor zum Erzeugen von Objekten aller Klassen sowie Festlegen der Startwerte
Menue::Menue(void)
{
	meineFaktoren = Faktoren();
	meineBibliothek = Bibliothek("bib.txt");
	meinSignalListeErzeuger = SignalListeErzeuger();
	meinGraphErzeuger = GraphErzeuger();
	meinLaufzeitAnalysator = LaufzeitAnalysator();
	DevPtr = ItivDev_GetConfigByName("Global\\ITIV_WindowsDevice");
	debug = true;
}


Menue::~Menue(void){}

//Hauptmenue zur Navigation
void Menue::start()
{
	string input;
	if (DevPtr != 0) //Falls die Gerätesimulation gestartet ist, sollen die Werte gemessen werden
	{
		debug = false;
	}
	if(!debug) //Je nach dem ob debug aktiviert ist, werden nun die 3 Groessen gemessen
	{
		readValuesFromDevice();
	}	

	while (true)
	{
		//Ausgabe des Hauptmenüs
		system("cls");
		menueKopf();

		cout << "(1) \x8Eu\xE1" << "ere Faktoren" << endl;	
		cout << "    Spannung [Volt]:                     " << meineFaktoren.getSpannung() << endl;
		cout << "    Temperatur [Grad Celsius]:           " << meineFaktoren.getTemperatur() << endl;
		cout << "    Prozess (1=slow, 2=typical, 3=fast): " << meineFaktoren.getProzess() << endl << endl;

		cout << "(2) Bibliothek" << endl;	//oeffnet das Menue zum Einstellen der Bibliotheksdatei
		cout << "    Pfad zur Bibliotheksdatei: " << meineBibliothek.getPfad() << endl << endl;

		cout << "(3) Schaltwerk" << endl;	//oeffnet das Menue zum Einstellen der Schaltwerksdatei
		cout << "    Pfad zur Schaltwerksdatei: " << meinSignalListeErzeuger.getPfad() << endl << endl;

		cout << "(4) Starte Analyse" << endl << endl;	//startet die Analyse

		cout << "(5) Programm beenden" << endl << endl << endl;

		cout << "W\x84hle einen Men\x81punkt und best\x84tige mit Enter:\n";

		getline(cin, input);
		if(input.length() != 1)	//Falls der eingegebene Wert mehr als ein Zeichen besitzt, muss er schon falsch sein!
		{
			cout << "Bitte geben Sie eine g\x81ltige Zahl ein!" << endl;
			system("pause");
		}
		else
		{
			switch (input.at(0))
			{
			case '1':
				faktorenMenue();	//oeffnet das Menue zum Aendern der Faktoren
				break;
			case '2':
				bibliothekMenue();
				break;
			case '3':
				schaltwerkMenue();	//oeffnet das Menue zum Einstellen der Schaltwerksdatei
				break;
			case '4':
				analyse();
				break;
			case '5':
				goto ende;			//beendet das Programm
				break;
			default:
				cout << "Bitte geben Sie eine g\x81ltige Zahl ein!" << endl;
				system("pause");
				break;
			}
		}
	}
ende:
	if (DevPtr != 0) ItivDev_ReleaseDevice(DevPtr);
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
			cout << "Bitte gib eine g\x81ltige Zahl ein!" << endl;
			system("pause");
		}
		else
		{
			switch (input.at(0))
			{
			case '0':
				debugAendernMenue();	//oeffnet das Menue zum Aendern des debug-modes
				break;
			case '1':
				if(debug) spannungAendernMenue();	//oeffnet das Menue zum Aendern der Spannung
				break;
			case '2':
				if(debug) temperaturAendernMenue();	//oeffnet das Menue zum Aendern der Betriebstemperatur
				break;
			case '3':
				if(debug) prozessAendernMenue();	//oeffnet das Menue zum Aendern des Prozesses
				break;
			case '4':
				meineFaktoren.ausgabeFaktoren();	//lässt die Faktoren ausgeben
				break;
			case '5':
				goto ende;	//Kehrt zurück zum Hauptmenue
				break;
			default:
				cout << "Bitte gib eine g\x81ltige Zahl ein" << endl;
				system("pause");
				break;
			}
		}
	}
ende:;	//Springt hier her
}

void Menue::bibliothekMenue()
{
	string input;
	while (true)
	{
		system("cls");
		menueKopf();
		cout << "Men\x81 Bibliothek" << endl;
		cout << "(1) Pfad zur Bibliotheksdatei: " << meineBibliothek.getPfad() << endl;
		cout << "(2) Ausgabe der Bibliotheksdatei" << endl;
		cout << "(3) Hauptmen\x81" << endl;

		getline(cin, input);
		system("cls");
		menueKopf();

		if(input.length() != 1)
		{
			cout << "Bitte gib eine g\x81ltige Zahl ein!" << endl;
			system("pause");
		}
		else
		{
			switch (input.at(0))
			{
			case '1':
				bibliothekPfadAendernMenue();
				break;
			case '2':
				meineBibliothek.dateiAusgabe();
				meineBibliothek.dateiAuswerten();
				break;
			case '3':
				goto ende;
				break;
			default:
				break;
			}
		}
	}
ende:;
}

void Menue::schaltwerkMenue()
{
	string input;
	while (true)
	{
		system("cls");
		menueKopf();
		cout << "Men\x81 Schaltwerk" << endl;
		cout << "(1) Pfad zur Schaltwerksdatei: " << meinSignalListeErzeuger.getPfad() << endl;
		cout << "(2) Ausgabe der Schaltwerksdatei" << endl;
		cout << "(3) Ausgabe der Signale" << endl;
		cout << "(4) Ausgabe der Graphstruktur" << endl;
		cout << "(5) Hauptmen\x81" << endl;
		cout << "W\x84hle einen Men\x81punkt und best\x84tige mit Enter:\n";

		getline(cin, input);
		system("cls");
		menueKopf();

		if(input.length() != 1)
		{
			cout << "Bitte gib eine g\x81ltige Zahl ein!" << endl;
			system("pause");
		}
		else
		{
			switch (input.at(0))
			{
			case '1':
				schaltwerkPfadAendernMenue();	//oeffnet das Menue zum Aendern des Pfades zur Schaltwerksdatei
				break;
			case '2':
				meinSignalListeErzeuger.ausgabeDatei();	//Gibt den Inhalt der Schaltwerksdatei aus
				system("pause");
				break;
			case '3':
				meinSignalListeErzeuger.ausgabeSignalListe(); //Gibt alle Signale mit Details aus
				system("pause");
				break;
			case '4':
				//Übergebe den Grapherzeuger die Signalliste und die Bibliothek
				meinGraphErzeuger.setSignalListe(meinSignalListeErzeuger.erzeugeListe());
				meineBibliothek.dateiAuswerten();
				meinGraphErzeuger.setBibliothek(&meineBibliothek);
				//Nur wenn es ein gültiger Graph ist, wird er ausgegeben
				if (meinGraphErzeuger.erzeugeGraph())
				{
					meinGraphErzeuger.ausgabeGraphstruktur();
				}else
				{

				}
				break;
			case '5':
				goto ende;	//Kehrt zurueck zum Hauptmenue
				break;
			default:
				break;
			}
		}
	}
ende:;
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
				if (readValuesFromDevice())
				{
					debug = false;
				}
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

void Menue::schaltwerkPfadAendernMenue()
{
	string input;
	while (true)
	{
		system("cls");
		menueKopf();
		cout << "Bitte gib den Pfad zur Schaltwerksdatei an oder schreibe 'exit' um zur\x81" << "ck zu gehen:\n";
		getline(cin, input);
		if(input == "exit") goto ende;
		if (meinSignalListeErzeuger.setPfad(input))
		{
			goto ende;
		}
		else
		{
			cout << "Bitte gib einen g\x81ltigen Pfad an." << endl;
			system("pause");
		}
	}
ende:;
}

void Menue::bibliothekPfadAendernMenue()
{
	string input;
	while (true)
	{
		system("cls");
		menueKopf();
		cout << "Bitte gib den Pfad zur Bibliotheksdatei an oder schreibe 'exit' um zur\x81" << "ck zu gehen:\n";
		getline(cin, input);
		if(input == "exit") goto ende;
		if (meineBibliothek.pfadEinlesen(input))
		{
			goto ende;
		}
		else
		{
			cout << "Bitte gib einen g\x81ltigen Pfad an." << endl;
			system("pause");
		}
	}
ende:;
}

void Menue::analyse()
{
	meinGraphErzeuger.setSignalListe(meinSignalListeErzeuger.erzeugeListe());
	meineBibliothek.dateiAuswerten();
	meinGraphErzeuger.setBibliothek(&meineBibliothek);
	//Nur wenn ein gültiger Graph erzeugt werden kann, soll die Analyse ausgeführt werden
	if (meinGraphErzeuger.erzeugeGraph())
	{
		meinLaufzeitAnalysator.setFaktoren(&meineFaktoren);
		meinLaufzeitAnalysator.setStartElement(meinGraphErzeuger.getStartElement());
		meinLaufzeitAnalysator.setFrequenz(meinSignalListeErzeuger.getFrequenz());
		meinLaufzeitAnalysator.starteAnalyse();
	}
}

void Menue::menueKopf()
{
	cout << "********************************************\n";
	cout << "*     IT-Projektpraktikum WS2013/2014      *\n";
	cout << "*  Laufzeitanalyse synchroner Schaltwerke  *\n";
	cout << "********************************************\n" << endl;
}

bool Menue::isNumber(string arg1)//Prüft, ob das Argument ein gültiger double ist
{
	try
	{
		boost::lexical_cast<double>(arg1);//Wandelt arg1 in einen double um. Dabei kann es zu einem Fehler kommen, wenn der string kein gültiger double ist
		return true;
	}catch(boost::bad_lexical_cast const&)//Nutzt die exception von boost, die geworfen wird, wenn lexical_cast nicht möglich ist
	{
		return false;
	}
	return false;
}

bool Menue::isShort(string arg1)//Prüft, ob das Argument ein gültiger short ist
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

bool Menue::readValuesFromDevice()//Versucht die Werte vom ITIV-Device zu lesen
{
	if (DevPtr != 0)//Ist das ITIV-Dev gestartet?
	{
		//Spannung messen
		do
		{
			*((int*)(DevPtr->BaseAddress + CTRL_REG)) = 0x00000001;	//Channel setzen
			while (*((int*)(DevPtr->BaseAddress + STAT_REG)) != 0x01000000)	//Prüfe Bereitschaft des Gerätes
			{
				cout << *((int*)DevPtr->BaseAddress + STAT_REG) << " Geraet nicht bereit\n";
			}
			*((int*)(DevPtr->BaseAddress + CTRL_REG)) = 0x00000101;	//starten mit gesetztem Channel
			while (*((int*)(DevPtr->BaseAddress + STAT_REG)) == 0x00000100)//Warten bis es nicht mehr busy ist
			{ 
				cout << "Geraet misst gerade\n"; 
			} 
		} while (*((int*)(DevPtr->BaseAddress + STAT_REG)) == 0x00010001);//Die Messung wird solange wiederholt, wie es einen Fehler bei der Messung gibt
		while (*((int*)(DevPtr->BaseAddress + STAT_REG)) != 0x00010000){} //nötig, da sonst zu schnell der Wert ausgelesen wird
		meineFaktoren.setSpannung( *((double*)(DevPtr->BaseAddress + DATA_REG)) );//Speichere den ermittelten Wert in den Variablen der Faktorenklasse

		//Temperatur messsen
		do
		{
			*((int*)(DevPtr->BaseAddress + CTRL_REG)) = 0x00000002;//channel setzen
			while (*((int*)(DevPtr->BaseAddress + STAT_REG)) != 0x01000000)//Prüfe Bereitschaft des Gerätes
			{
				cout << *((int*)DevPtr->BaseAddress + STAT_REG) << " Geraet nicht bereit\n";
			}
			*((int*)(DevPtr->BaseAddress + CTRL_REG)) = 0x00000102;//starten mit gesetztem Channel
			while (*((int*)(DevPtr->BaseAddress + STAT_REG)) == 0x00000100)//Warten bis es nicht mehr busy ist
			{
				cout << "Geraet misst gerade\n"; 
			} 
		} while (*((int*)(DevPtr->BaseAddress + STAT_REG)) == 0x00010001);//Die Messung wird solange wiederholt, wie es einen Fehler bei der Messung gibt
		while (*((int*)(DevPtr->BaseAddress + STAT_REG)) != 0x00010000){}//nötig, da sonst zu schnell der Wert ausgelesen wird
		meineFaktoren.setTemperatur( *((int*)(DevPtr->BaseAddress + DATA_REG)) );//Speichere den ermittelten Wert in den Variablen der Faktorenklasse

		//Prozess messen
		do
		{
			*((int*)(DevPtr->BaseAddress + CTRL_REG)) = 0x00000003;//channel setzen
			while (*((int*)(DevPtr->BaseAddress + STAT_REG)) != 0x01000000)//Prüfe Bereitschaft des Gerätes
			{
				cout << *((int*)DevPtr->BaseAddress + STAT_REG) << " Geraet nicht bereit\n";
			}
			*((int*)(DevPtr->BaseAddress + CTRL_REG)) = 0x00000103;//starten mit gesetztem Channel
			while (*((int*)(DevPtr->BaseAddress + STAT_REG)) == 0x00000100)//Warten bis es nicht mehr busy ist
			{
				cout << "Geraet misst gerade\n"; 
			} 
		} while (*((int*)(DevPtr->BaseAddress + STAT_REG)) == 0x00010001);//Die Messung wird solange wiederholt, wie es einen Fehler bei der Messung gibt
		while (*((int*)(DevPtr->BaseAddress + STAT_REG)) != 0x00010000){}//nötig, da sonst zu schnell der Wert ausgelesen wird
		meineFaktoren.setProzess( *((int*)(DevPtr->BaseAddress + DATA_REG)) + 1 );//Speichere den ermittelten Wert in den Variablen der Faktorenklasse

		return true;
	}//Ende if-Geraet-angeschaltet
	else
	{
		cout << "Die Ger\x84tesimulation ist noch nicht gestartet.\n";
		system("pause");
		return false;
	}

}