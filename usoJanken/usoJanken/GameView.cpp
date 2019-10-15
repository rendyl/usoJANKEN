#include "GameView.h"

GameView::GameView()
{
	textureBG.loadFromFile("background.png");
	backGround = Sprite(textureBG);

	texWhite.loadFromFile("tileBG.png");
	whiteTile = Sprite(texWhite);

	texWhiteGlow.loadFromFile("tilewhiteglow1.png");
	whiteGlowTile = Sprite(texWhiteGlow);

	texPurple.loadFromFile("tilepurple.png");
	purpleTile = Sprite(texPurple);

	texBlue.loadFromFile("tileblue.png");
	blueTile = Sprite(texBlue);
	
	texRed.loadFromFile("tilered.png");
	redTile = Sprite(texRed);

	texGreen.loadFromFile("tilegreen.png");
	greenTile = Sprite(texGreen);

	texBlack.loadFromFile("tileblack.png");
	blackTile = Sprite(texBlack);

	texBrown.loadFromFile("tilebrown.png");
	brownTile = Sprite(texBrown);

	texGreenIsh.loadFromFile("tilegreenish.png");
	greenIshTile = Sprite(texGreenIsh);

	texGray.loadFromFile("tilegray.png");
	grayTile = Sprite(texGray);

	texJ0.loadFromFile("J0tile.png");
	J0Tile = Sprite(texJ0);

	texJ1.loadFromFile("J1tile.png");
	J1Tile = Sprite(texJ1);

	texChar.loadFromFile("tileWhite.png");
	charSprite = Sprite(texChar);

	texMove.loadFromFile("cursorMove.png");
	cursorMove = Sprite(texMove);

	texPierre.loadFromFile("cursorPierre.png");
	cursorPierre = Sprite(texPierre);

	texFeuille.loadFromFile("cursorFeuille.png");
	cursorFeuille = Sprite(texFeuille);

	texCiseaux.loadFromFile("cursorCiseaux.png");
	cursorCiseaux = Sprite(texCiseaux);

	MyFont.loadFromFile("bebas.otf");

	littleText = Text("", MyFont, 24);
	littleText.setFillColor(sf::Color(255, 255, 255));

	middleText = Text("", MyFont, 30);
	middleText.setFillColor(sf::Color(255, 255, 255));

	bigText = Text("", MyFont, 60);
	bigText.setFillColor(sf::Color(255, 255, 255));

	height = 720;
	width = 1280;

	atkToDisplay = false;
	wayToDisplay = false;
}

Vector2f GameView::getCoordfromISO(Vector2i v)
{
	Vector2f position;
	position.x = v.x * 53 - v.y * 53 + 1280 / 2 - 53;
	position.y = v.x * 30 + v.y * 30 - 360 + 30;
	return position;
}

Vector2f GameView::getCoordfromISO(Vector2f v)
{
	Vector2f position;
	position.x = v.x * 53 - v.y * 53 + 1280 / 2 - 53;
	position.y = v.x * 30 + v.y * 30 - 360 + 30;
	return position;
}

void GameView::displayMap(RenderWindow& window, int * map, int mapSize)
{
	for (int a = 0; a < mapSize; a++)
	{
		for (int b = 0; b < mapSize; b++)
		{
			Vector2f position = getCoordfromISO(Vector2i(a, b));

			if (map[a + mapSize * b] == 1) blackTile.setPosition(position), window.draw(blackTile);
			else whiteTile.setPosition(position), window.draw(whiteTile);
		}
	}
}

void GameView::drawTile(RenderWindow& window, Sprite& tile, int x, int y)
{
	Vector2f position = getCoordfromISO(Vector2i(x, y));
	tile.setPosition(position), window.draw(tile);
}

void GameView::displayAttaque(RenderWindow& window, Attaque atk, Vector2i posPlayer, Vector2i directionAtk, int* map)
{
	for (int i = 0; i < 3 + abs(directionAtk.x); i++)
	{
		for (int j = 0; j < 3 + abs(directionAtk.y); j++)
		{
			float xPosToDisplay = 0;
			float yPosToDisplay = 0;

			int indexPatternToCheck = 0;

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

			if (0 <= (int)xPosToDisplay && 0 <= (int)yPosToDisplay && (int)xPosToDisplay < 23 && (int)yPosToDisplay < 23)
			{
				//if (i == 0 && j == 0) drawTile(window, blueTile, xPosToDisplay, yPosToDisplay);
				//else if (i == 1 && j == 0) drawTile(window, blueTile, xPosToDisplay, yPosToDisplay);
				if (atk.patternAtk[indexPatternToCheck] > 0)
				{
					if (atk.type == "pierre") drawTile(window, brownTile, xPosToDisplay, yPosToDisplay);
					if (atk.type == "feuille") drawTile(window, greenIshTile, xPosToDisplay, yPosToDisplay);
					if (atk.type == "ciseaux") drawTile(window, grayTile, xPosToDisplay, yPosToDisplay);
				}
				// std::cout << "x : " << i << " y : " << j << " index : " << i + j * (3 + abs(directionAtk.y)) << std::endl;
			}
		}
	}
}

void GameView::displayChemin(RenderWindow& window, std::vector<Util::Node> chemin, bool canMove, int* map)
{
	for (int i = 1; i < chemin.size(); i++)
	{
		if (Util::isValid(chemin[i].x, chemin[i].y, Vector2i(-1, -1), map))
		{
			if (canMove) drawTile(window, greenTile, chemin[i].x, chemin[i].y);
			else drawTile(window, redTile, chemin[i].x, chemin[i].y);
		}
	}
}

Vector2i GameView::getSourisInMatrix(Vector2i posSouris)
{
	// Conversion des coords en pixel en indices dans la matrice
	if (posSouris.x > 0 && posSouris.y > 0 && posSouris.y < height && posSouris.x < width)
	{
		float indiceSourisX = ((posSouris.x - offSetX) / 53 + (posSouris.y - offSetY) / 30) / 2;
		float indiceSourisY = ((posSouris.y - offSetY) / 30 - ((posSouris.x - offSetX) / 53)) / 2;
		indiceSourisY += 12;
		return Vector2i(indiceSourisX, indiceSourisY);
	}
	else return Vector2i(-1, -1);
}

void GameView::displayBG(RenderWindow& window)
{
	window.draw(backGround);
}

void GameView::drawCharacter(RenderWindow& window, GameModel gModel, int i, bool isPlayer)
{
	if(i == 0) drawTile(window, J0Tile, gModel.tabChar[i].posChar.x, gModel.tabChar[i].posChar.y);
	if(i == 1) drawTile(window, J1Tile, gModel.tabChar[i].posChar.x, gModel.tabChar[i].posChar.y);
	if (isPlayer) drawTile(window, whiteGlowTile, gModel.tabChar[i].posChar.x, gModel.tabChar[i].posChar.y);
}

void GameView::displayPrev(GameModel gModel, std::vector<Util::Node> chemin, RenderWindow& window, Vector2i indiceSouris, int i)
{
	if (wayToDisplay) displayChemin(window, chemin, gModel.tabChar[i].canMove, gModel.map);
	if (atkToDisplay) displayAttaque(window, gModel.tabChar[i].atkSelected, gModel.tabChar[i].posChar, Vector2i((int)indiceSouris.x - (int)gModel.tabChar[i].posChar.x, (int)indiceSouris.y - (int)gModel.tabChar[i].posChar.y), gModel.map);
}

void GameView::drawCursor(RenderWindow& window, std::string typeDisplay, Vector2i positionSouris)
{
	if (typeDisplay == "move") cursorMove.setPosition(positionSouris.x, positionSouris.y), window.draw(cursorMove);
	if (typeDisplay == "pierre") cursorPierre.setPosition(positionSouris.x, positionSouris.y), window.draw(cursorPierre);
	if (typeDisplay == "feuille") cursorFeuille.setPosition(positionSouris.x, positionSouris.y), window.draw(cursorFeuille);
	if (typeDisplay == "ciseaux") cursorCiseaux.setPosition(positionSouris.x, positionSouris.y), window.draw(cursorCiseaux);
	if (typeDisplay == "none");
}

void GameView::displayText(RenderWindow& window, std::string typeDisplay, Vector2f posToDisplay, String stringToDisplay)
{
	if (typeDisplay == "little") littleText.setString(stringToDisplay), littleText.setPosition(posToDisplay.x, posToDisplay.y), window.draw(littleText);
	if (typeDisplay == "middle") middleText.setString(stringToDisplay), middleText.setPosition(posToDisplay.x, posToDisplay.y), window.draw(middleText);
	if (typeDisplay == "big") bigText.setString(stringToDisplay), bigText.setPosition(posToDisplay.x, posToDisplay.y), window.draw(bigText);
}