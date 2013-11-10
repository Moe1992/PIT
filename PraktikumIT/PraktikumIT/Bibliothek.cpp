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