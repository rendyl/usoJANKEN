#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Attaque.h"
#include "Character.h"
#include "Util.h"

using namespace sf;

class GameModel
{
	public :

		int * map;
		int mapSize;

		Attaque ciseaux;
		Attaque pierre;
		Attaque feuille;
		Attaque none;

		int numTour;
		int numStage;

		int dmgATK;
		int nbCharacter;
		Character * tabChar;

		Vector2i lastPosSouris;

		// int nbPM;
		// Vector2i posChar;
		// bool canMove;
		// bool noAtk;
		// Attaque atkSelected;
		// std::string mode;

		GameModel();

		void buildMap();
		void buildChar();
		std::vector<Util::Node> useAStarToGetChemin(int indexToPlay, Vector2i departv, Vector2i objectifv);
		int useAttack(Attaque atk, int indexPlayer, Vector2i posPlayer, Vector2i directionAtk);
};

