#include "GameModel.h"

GameModel::GameModel()
{
	mapSize = 23;
	map = new int[23*23];
	buildMap();

	lastPosSouris = Vector2i(-1, -1);

	ciseaux = Attaque("ciseaux");
	pierre = Attaque("pierre");
	feuille = Attaque("feuille");
	none = Attaque("none");

	numTour = 0;
	numStage = 0;

	dmgATK = 30;
	nbCharacter = 2;
	tabChar = new Character[2];
	buildChar();
}

void GameModel::buildMap()
{
	// 0 : Libre
	for (int i = 0; i < mapSize; i++)
	{
		for (int j = 0; j < mapSize; j++)
		{
			map[mapSize * i + j] = 0;
		}
	}

	// 1 : Obstacle
	for (int i = 0; i <= 11; i++)
	{
		for (int j = 0; j < i; j++)
		{
			map[(i + 11) + mapSize * j] = 1;
			map[(11 - i) + mapSize * j] = 1;
			map[(i + 11) + mapSize * (22 - j)] = 1;
			map[(11 - i) + mapSize * (22 - j)] = 1;
		}
	}

	// Big Building
	/*
	map[0 + mapSize * 11] = 1;
	map[1 + mapSize * 10] = 1;
	map[1 + mapSize * 11] = 1;
	map[1 + mapSize * 12] = 1;

	map[2 + mapSize * 9 ] = 1;
	map[2 + mapSize * 10] = 1;
	map[2 + mapSize * 11] = 1;
	map[2 + mapSize * 12] = 1;
	map[2 + mapSize * 13] = 1;

	map[3 + mapSize * 8] = 1;
	map[3 + mapSize * 9] = 1;
	map[3 + mapSize * 10] = 1;
	map[3 + mapSize * 11] = 1;
	map[3 + mapSize * 12] = 1;
	map[3 + mapSize * 13] = 1;
	map[3 + mapSize * 14] = 1;

	map[4 + mapSize * 8] = 1;
	map[4 + mapSize * 9] = 1;
	map[4 + mapSize * 10] = 1;
	map[4 + mapSize * 11] = 1;
	map[4 + mapSize * 12] = 1;
	map[4 + mapSize * 13] = 1;
	map[4 + mapSize * 14] = 1;
	map[4 + mapSize * 15] = 1;

	map[5 + mapSize * 8] = 1;
	map[5 + mapSize * 9] = 1;
	map[5 + mapSize * 10] = 1;
	map[5 + mapSize * 11] = 1;
	map[5 + mapSize * 12] = 1;
	map[5 + mapSize * 13] = 1;
	map[5 + mapSize * 14] = 1;
	map[5 + mapSize * 15] = 1;
	*/

	// Mini Lake

	map[9 + mapSize * 10] = 1;
	map[10 + mapSize * 10] = 1;
	map[11 + mapSize * 10] = 1;

	map[9 + mapSize * 11] = 1;
	map[10 + mapSize * 11] = 1;
	map[11 + mapSize * 11] = 1;

	map[9 + mapSize * 12] = 1;
	map[10 + mapSize * 12] = 1;
	map[11 + mapSize * 12] = 1;

	map[10 + mapSize * 13] = 1;
	map[11 + mapSize * 13] = 1;

	// Big Lake

	map[9 + mapSize * 15] = 1;
	map[10 + mapSize * 15] = 1;
	map[11 + mapSize * 15] = 1;
	map[12 + mapSize * 15] = 1;
	map[13 + mapSize * 15] = 1;

	map[8 + mapSize * 16] = 1;
	map[9 + mapSize * 16] = 1;
	map[10 + mapSize * 16] = 1;
	map[11 + mapSize * 16] = 1;
	map[12 + mapSize * 16] = 1;
	map[13 + mapSize * 16] = 1;
	map[14 + mapSize * 16] = 1;

	map[8 + mapSize * 17] = 1;
	map[9 + mapSize * 17] = 1;
	map[10 + mapSize * 17] = 1;
	map[11 + mapSize * 17] = 1;
	map[12 + mapSize * 17] = 1;
	map[13 + mapSize * 17] = 1;
	map[14 + mapSize * 17] = 1;

	map[9 + mapSize * 18] = 1;
	map[10 + mapSize * 18] = 1;
	map[11 + mapSize * 18] = 1;
	map[12 + mapSize * 18] = 1;
	map[13 + mapSize * 18] = 1;

	map[10 + mapSize * 19] = 1;
	map[11 + mapSize * 19] = 1;
	map[12 + mapSize * 19] = 1;
}

void GameModel::buildChar()
{
	for (int i = 0; i < nbCharacter; i++)
	{
		tabChar[i].numCharacter = i;
		tabChar[i].atkSelected = none;
		tabChar[i].atkHitWith = none;
	}

	tabChar[0].posChar = Vector2i(14, 11);
	tabChar[1].posChar = Vector2i(15, 11);
}

std::vector<Util::Node> GameModel::useAStarToGetChemin(int indexToPlay, Vector2i departv, Vector2i objectifv)
{
	Util::Node depart;
	depart.x = departv.x;
	depart.y = departv.y;

	Util::Node objectif;
	objectif.x = objectifv.x;
	objectif.y = objectifv.y;
	return Util::aStar(depart, objectif, tabChar[(indexToPlay+1)%2].posChar, map);
}

int GameModel::useAttack(Attaque atk, int indexPlayer, Vector2i posPlayer, Vector2i directionAtk)
{
	for (int i = 0; i < 3 + abs(directionAtk.x); i++)
	{
		for (int j = 0; j < 3 + abs(directionAtk.y); j++)
		{
			// std::cout << "heeeeeeeey" << std::endl;
			float xPosToDisplay;
			float yPosToDisplay;

			int indexPatternToCheck;

			if (directionAtk == Vector2i(1, 0))
			{
				// Decalage ds l'espace pr placer le pattern correctement
				xPosToDisplay = (posPlayer.x + i), yPosToDisplay = (posPlayer.y - 1 + j);
				// Rotation Pattern
				indexPatternToCheck = i + j * (3 + abs(directionAtk.x));
			}
			if (directionAtk == Vector2i(-1, 0))
			{
				// Decalage ds l'espace pr placer le pattern correctement
				xPosToDisplay = (posPlayer.x - (2 + abs(directionAtk.x)) + i), yPosToDisplay = (posPlayer.y + 1 - j);
				// Rotation Pattern
				indexPatternToCheck = (2 + abs(directionAtk.x) - i) + j * (3 + abs(directionAtk.x));
			}
			if (directionAtk == Vector2i(0, 1))
			{
				// Decalage ds l'espace pr placer le pattern correctement
				xPosToDisplay = (posPlayer.x + +1 - i), yPosToDisplay = (posPlayer.y + j);
				// Rotation Pattern
				indexPatternToCheck = j + i * (3 + abs(directionAtk.y));
			}
			if (directionAtk == Vector2i(0, -1))
			{
				// Decalage ds l'espace pr placer le pattern correctement
				xPosToDisplay = (posPlayer.x + -1 + i), yPosToDisplay = (posPlayer.y - (2 + abs(directionAtk.y)) + j);
				// Rotation Pattern
				indexPatternToCheck = (2 + abs(directionAtk.y) - j) + i * (3 + abs(directionAtk.y));
			}

			if (Util::isValid((int)xPosToDisplay, (int)yPosToDisplay, Vector2i(-1, -1), map))
			{
				//if (i == 0 && j == 0) drawTile(window, blueTile, xPosToDisplay, yPosToDisplay);
				//else if (i == 1 && j == 0) drawTile(window, blueTile, xPosToDisplay, yPosToDisplay);
				if (atk.patternAtk[indexPatternToCheck] > 0 && (xPosToDisplay == tabChar[(indexPlayer + 1) % 2].posChar.x) && (yPosToDisplay == tabChar[(indexPlayer + 1) % 2].posChar.y))
					return atk.patternAtk[indexPatternToCheck];
					// std::cout << "Joueur " << indexPlayer << "hit " << (indexPlayer + 1) % 2 << std::endl;

				// std::cout << "x : " << i << " y : " << j << " index : " << i + j * (3 + abs(directionAtk.y)) << std::endl;
			}
		}
	}
	return 0;
}