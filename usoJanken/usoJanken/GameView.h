#pragma once
#include <SFML/Graphics.hpp>
#include "Attaque.h"
#include "Util.h"
#include "GameModel.h"

using namespace sf;

class GameView
{
	public :

		// Textures
		Texture textureBG;
		Texture texWhite;
		Texture texWhiteGlow;
		Texture texPurple;
		Texture texBlue;
		Texture texRed;
		Texture texGreen;
		Texture texBlack;
		Texture texJ0;
		Texture texJ1;
		Texture texChar;
		Texture texGreenIsh;
		Texture texBrown;
		Texture texGray;

		Texture texMove;
		Texture texPierre;
		Texture texFeuille;
		Texture texCiseaux;

		// Sprites
		Sprite backGround;
		Sprite whiteTile;
		Sprite whiteGlowTile;
		Sprite purpleTile;
		Sprite blueTile;
		Sprite redTile;
		Sprite greenTile;
		Sprite blackTile;
		Sprite J0Tile;
		Sprite J1Tile;
		Sprite charSprite;
		Sprite greenIshTile;
		Sprite brownTile;
		Sprite grayTile;

		Sprite cursorMove;
		Sprite cursorPierre;
		Sprite cursorFeuille;
		Sprite cursorCiseaux;

		Font MyFont;
		Text littleText;
		Text middleText;
		Text bigText; 

		// Decalage de la premiere tuile sur l'écran 
		const float offSetX = 5;
		const float offSetY = 29;

		int width;
		int height;

		bool atkToDisplay;
		bool wayToDisplay;

		GameView();
		
		void displayMap(RenderWindow& window, int* map, int mapSize);
		void drawTile(RenderWindow& window, Sprite& tile, int x, int y);
		void displayAttaque(RenderWindow& window, Attaque atk, Vector2i posPlayer, Vector2i directionAtk, int* map);
		void displayChemin(RenderWindow& window, std::vector<Util::Node> chemin, bool canMove, int* map);
		void displayBG(RenderWindow& window);
		void drawCharacter(RenderWindow& window, GameModel gModel, int i, bool isPlayer);
		void displayPrev(GameModel gModel, std::vector<Util::Node> chemin, RenderWindow& window, Vector2i indiceSouris, int i);
		void drawCursor(RenderWindow& window, std::string typeDisplay, Vector2i positionSouris);
		void displayText(RenderWindow& window, std::string typeDisplay, Vector2f posToDisplay, String stringToDisplay);


		Vector2f getCoordfromISO(Vector2i v);
		Vector2f getCoordfromISO(Vector2f v);
		Vector2i getSourisInMatrix(Vector2i posSouris);
};