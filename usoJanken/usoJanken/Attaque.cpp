#include "Attaque.h"

Attaque::Attaque(std::string type2)
{
	type = type2;
	patternAtk = new int[12];
	int pattern[12];

	if (type == "pierre")
	{
		int pattern[12] =
		{
			0, 0, 1, 0,
			0, 2, 1, 1,
			0, 0, 1, 0
		};
		for (int i = 0; i < 12; i++) std::cout << pattern[i] << "i" << std::endl;
	}

	if (type == "feuille")
	{
		int pattern[12] =
		{
			0, 0, 0, 1,
			0, 2, 1, 1,
			0, 0, 0, 1
		};
		for (int i = 0; i < 12; i++) std::cout << pattern[i] << "i" << std::endl;
	}

	if (type == "ciseaux")
	{
		int pattern[12] =
		{
			1, 0, 1, 1,
			0, 2, 0, 0,
			1, 0, 1, 1
		};
		for (int i = 0; i < 12; i++) std::cout << pattern[i] << "i" << std::endl;
	}

	if (type == "none")
	{
		int pattern[12] =
		{
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		};
		for (int i = 0; i < 12; i++) std::cout << pattern[i] << "i" << std::endl;
	}

	for (int i = 0; i < 12; i++)
	{
		patternAtk[i] = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			patternAtk[j * 4 + i] = pattern[j * 4 + i];
		}
	}
}

Attaque::Attaque()
{

}

bool Attaque::operator == (Attaque a2)
{
	if (type == a2.type) return true;
	if (type == "none" || a2.type == "none") return true;
	return false;
}

bool Attaque::operator < (Attaque a2)
{
	if (type == "feuille" && a2.type == "ciseaux") return true;
	if (type == "ciseaux" && a2.type == "pierre") return true;
	if (type == "pierre" && a2.type == "feuille") return true;
	return false;
}