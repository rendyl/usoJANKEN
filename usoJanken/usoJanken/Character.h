#pragma once
#include <SFML/Graphics.hpp>
#include "Attaque.h"

class Character
{
	public :

		sf::Vector2i posChar;
		int numCharacter;
		int nbPM;
		int nbHP;
		int valHit;
		bool canMove;
		bool noAtk;
		sf::Vector2i orientation;
		Attaque atkSelected;
		Attaque atkHitWith;
		std::string mode;

		Character();
};