#pragma once

#include <iostream>
#include "Faktoren.h"

class Menue
{
public:
	Menue(void);
	~Menue(void);
	void start();

private:
	void faktorenMenue();
	void bibliothekMenue();
	void schaltwerkMenue();
	void analyse();
	void menueKopf();


};

