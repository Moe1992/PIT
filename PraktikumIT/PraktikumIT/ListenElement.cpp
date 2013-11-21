#include "ListenElement.h"


ListenElement::ListenElement(void)
{
}


ListenElement::~ListenElement(void)
{
}

SchaltwerkElement* ListenElement::getSchaltwerkElement()
{
	return schaltwerkElement;
}

ListenElement* ListenElement::getNextElement()
{
	return next;
}

void ListenElement::setSchaltwerkElement(SchaltwerkElement* schaltwerkEl)
{
	schaltwerkElement = schaltwerkEl;
}

void ListenElement::setNextElement(ListenElement* nextEl)
{
	next = nextEl;
}