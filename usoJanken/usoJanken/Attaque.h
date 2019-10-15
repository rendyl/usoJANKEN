#pragma once
#include <iostream>

class Attaque
{
	public :

		std::string type;
		int * patternAtk;

		Attaque(std::string type);
		Attaque();

		bool operator == (Attaque a2);
		bool operator < (Attaque a2);
};

