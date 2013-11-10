#include "Signal.h"

using namespace std;

Signal::Signal()
{
	signalTyp = unbekannt;
	quelle = "";
	quellenTyp = "";
	//ziele = NULL;
	anzahlZiele = 0;

}


Signal::~Signal()
{
}
