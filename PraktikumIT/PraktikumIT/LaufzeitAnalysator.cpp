#include "LaufzeitAnalysator.h"

using namespace std;

LaufzeitAnalysator::LaufzeitAnalysator(void)
{
}


LaufzeitAnalysator::~LaufzeitAnalysator(void)
{
}

void LaufzeitAnalysator::EinzelLaufzeit()
{
	ListenElement* tempListenElement = startElement;
	SchaltwerkElement* tempSchaltwerkElement;
	GatterTyp* tempGatterTyp;
	double tpd0;
	double cLast;
	do
	{
		tempSchaltwerkElement = tempListenElement->getSchaltwerkElement();
		tempGatterTyp = tempSchaltwerkElement->getTyp();
		tpd0 = tempGatterTyp->getGrundLaufzeit();
		for(int i = 0; i < tempSchaltwerkElement->getAnzahlNachfolger(); i++)
		{

		}
	} while ( tempListenElement->getNextElement() != NULL );
}