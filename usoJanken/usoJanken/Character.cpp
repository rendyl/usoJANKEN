#include "Character.h"

Character::Character()
{
	nbHP = 200;
	nbPM = 5;
	canMove = false;
	noAtk = true;
	mode = "deplacement";
	orientation = sf::Vector2i(1, 0);
	valHit = 0;
}