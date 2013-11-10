#pragma once
#include "SchaltwerkElement.h"

class ListenElement
{
public:
	ListenElement(void);
	~ListenElement(void);
	SchaltwerkElement getSchaltwerkElement();
	ListenElement getNextElement();
	void setSchaltwerkElement(SchaltwerkElement schaltwerkEl);
	void setNextElement(ListenElement nextEl);

private:
	SchaltwerkElement* schaltwerkElement;
	ListenElement* next;
};

