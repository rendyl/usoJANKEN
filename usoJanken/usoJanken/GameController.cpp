#ifndef MAIN
#define MAIN

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Util.h"
#include "GameView.h"
#include "GameModel.h"
#include "Attaque.h"
#include "Animation.h"
#include <sstream>

using namespace sf;

int main()
{
	int a = Util::dijkstra();

	// Window setup
	RenderWindow window(VideoMode(1280, 720), "usoJANKEN", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	window.setMouseCursorVisible(false);
	Event event;
	Image icon;
	icon.loadFromFile("icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	sf::RectangleShape player(sf::Vector2f(70, 70));
	player.setPosition(200, 200);
	sf::Texture playerTexture;
	playerTexture.loadFromFile("sprite.png");
	player.setTexture(&playerTexture);
	Animation animation(&playerTexture, sf::Vector2u(8, 9), 0.1f);
	bool play = true;
	
	float deltaTime = 0;
	sf::Clock clock;
	std::vector<Util::Node> chemin;

	GameModel gModel;
	GameView gView;

	int indexToPlay = 0;
	std::cout << "TOUR NUMERO " << gModel.numTour << std::endl;
	std::cout << "HP J0 : " << gModel.tabChar[0].nbHP << std::endl;
	std::cout << "HP J1 : " << gModel.tabChar[1].nbHP << std::endl;

	bool animationMoveToPlay = false;
	Vector2i indiceSouris;

	while (window.isOpen())
	{
		// EVENEMENTS

		while (window.pollEvent(event))
		{
			// Fermeture de la fenêtre
			if (event.type == Event::Closed) window.close();

			// Debug ::Changement de Mode
			// if (Keyboard::isKeyPressed(Keyboard::Q)) gView.atkToDisplay = false, gModel.tabChar[indexToPlay].mode = "deplacement";
			// if (Keyboard::isKeyPressed(Keyboard::S)) gView.wayToDisplay = false, gModel.tabChar[indexToPlay].atkSelected = gModel.none, gModel.tabChar[indexToPlay].noAtk = true, gModel.tabChar[0].mode = "attaque";

			// Select Attack
			if (gModel.tabChar[indexToPlay].mode == "attaque")
			{
				if (Keyboard::isKeyPressed(Keyboard::A)) gModel.tabChar[indexToPlay].atkSelected = gModel.pierre, gModel.tabChar[indexToPlay].noAtk = false;
				if (Keyboard::isKeyPressed(Keyboard::Z)) gModel.tabChar[indexToPlay].atkSelected = gModel.feuille, gModel.tabChar[indexToPlay].noAtk = false;
				if (Keyboard::isKeyPressed(Keyboard::E)) gModel.tabChar[indexToPlay].atkSelected = gModel.ciseaux, gModel.tabChar[indexToPlay].noAtk = false;
				if (Keyboard::isKeyPressed(Keyboard::Escape)) gModel.tabChar[indexToPlay].atkSelected = gModel.none, gModel.tabChar[indexToPlay].noAtk = true;
			}

			// Souris
			indiceSouris = gView.getSourisInMatrix(Mouse::getPosition(window));

			// OnHover
			if (gModel.lastPosSouris.x != (int)indiceSouris.x || gModel.lastPosSouris.y != (int)indiceSouris.y || gModel.tabChar[indexToPlay].mode == "attaque" && gView.atkToDisplay == false || gModel.tabChar[indexToPlay].mode == "deplacement" && gView.wayToDisplay == false)
			{
				if (gModel.tabChar[indexToPlay].mode == "deplacement" && indiceSouris.x != -1 && indiceSouris.y != -1)
				{
					gModel.lastPosSouris = Vector2i((int)indiceSouris.x, (int)indiceSouris.y);
					// Utilisation de A* pour le plus court chemin
					chemin = gModel.useAStarToGetChemin(indexToPlay, gModel.tabChar[indexToPlay].posChar, gModel.lastPosSouris);
					gView.wayToDisplay = true;

					// Previsualisation Mouvement
					if (chemin.size() > gModel.tabChar[indexToPlay].nbPM + 1) gModel.tabChar[indexToPlay].canMove = false;
					else gModel.tabChar[indexToPlay].canMove = true;
				}
				else gModel.tabChar[indexToPlay].canMove = false;

				if (gModel.tabChar[indexToPlay].mode == "attaque")
				{
					if ((abs((int)indiceSouris.x - gModel.tabChar[indexToPlay].posChar.x)) + (abs((int)indiceSouris.y - gModel.tabChar[indexToPlay].posChar.y)) == 1) gView.atkToDisplay = true;
					if (!(Util::isValid(abs((int)indiceSouris.x), abs((int)indiceSouris.y), Vector2i(-1, -1), gModel.map))) gView.atkToDisplay = false;
				}
			}

			// OnClick
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (gModel.tabChar[indexToPlay].mode == "deplacement")
				{
					if (Util::isValid(indiceSouris.x, indiceSouris.y, gModel.tabChar[(indexToPlay + 1) % 2].posChar, gModel.map))
					{
						// Deplacement
						if (gModel.tabChar[indexToPlay].canMove)
						{
							std::cout << "JOUEUR " << indexToPlay << " se deplace" << std::endl;
							if (chemin.size() >= 2) gModel.tabChar[indexToPlay].orientation = Vector2i(-chemin[chemin.size() - 2].x + chemin[chemin.size() - 1].x, chemin[chemin.size() - 2].y - chemin[chemin.size() - 1].y);
							// std::cout << "(" << gModel.tabChar[indexToPlay].orientation.x << ", " << gModel.tabChar[indexToPlay].orientation.y << ")" << std::endl;

							animationMoveToPlay = true;

							std::cout << "animationMoveToPlay " << animationMoveToPlay << std::endl;

							gView.wayToDisplay = false;
							gModel.tabChar[indexToPlay].posChar = Vector2i((int)(indiceSouris.x), (int)(indiceSouris.y));
							gModel.tabChar[indexToPlay].canMove = false;
							gModel.numStage++;
						}
					}
				}
				else if (gModel.tabChar[indexToPlay].mode == "attaque")
				{
					if (Util::isValid(indiceSouris.x, indiceSouris.y, Vector2i(-1, -1), gModel.map))
					{
						// Attaque
						if ((abs((int)indiceSouris.x - gModel.tabChar[indexToPlay].posChar.x)) + (abs((int)indiceSouris.y - gModel.tabChar[indexToPlay].posChar.y)) == 1)
						{
							if (!gModel.tabChar[indexToPlay].noAtk)
							{
								gModel.tabChar[indexToPlay].orientation = Vector2i((int)indiceSouris.x - (int)gModel.tabChar[indexToPlay].posChar.x, - (int)indiceSouris.y + (int)gModel.tabChar[indexToPlay].posChar.y);
								// std::cout << "(" << gModel.tabChar[indexToPlay].orientation.x << ", " << gModel.tabChar[indexToPlay].orientation.y << ")" << std::endl;
								std::cout << "JOUEUR " << indexToPlay << " utilise attaque : " << gModel.tabChar[indexToPlay].atkSelected.type << std::endl;

								gModel.tabChar[(indexToPlay + 1) % 2].atkHitWith = gModel.none;
								gModel.tabChar[(indexToPlay + 1) % 2].valHit = gModel.useAttack(gModel.tabChar[indexToPlay].atkSelected, indexToPlay, gModel.tabChar[indexToPlay].posChar, Vector2i((int)indiceSouris.x - (int)gModel.tabChar[indexToPlay].posChar.x, (int)indiceSouris.y - (int)gModel.tabChar[indexToPlay].posChar.y));
								gModel.tabChar[(indexToPlay + 1) % 2].atkHitWith = gModel.tabChar[indexToPlay].atkSelected;

								gView.atkToDisplay = false; 
								gModel.tabChar[indexToPlay].noAtk = true;
								gModel.numStage++;
							}	
						}
					}	
				}
			}

			// Select Player to Play
			// Nb de tours toussa stages MAJ
			indexToPlay = (gModel.numTour + gModel.numStage) % 2;

			if (gModel.numStage <= 1) gModel.tabChar[indexToPlay].mode = "deplacement";
			if (gModel.numStage > 1) gModel.tabChar[indexToPlay].mode = "attaque";
			if (gModel.numStage == 4)
			{
				bool ableToTakeDmg0 = true;
				bool ableToTakeDmg1 = true;

				if (gModel.tabChar[0].atkSelected == gModel.tabChar[1].atkSelected)
				{
					gModel.tabChar[0].nbHP -= gModel.tabChar[0].valHit * gModel.dmgATK;
					gModel.tabChar[1].nbHP -= gModel.tabChar[1].valHit * gModel.dmgATK;
				}
				else if (gModel.tabChar[0].atkSelected < gModel.tabChar[1].atkSelected)
				{
					gModel.tabChar[0].nbHP -= 1 * gModel.tabChar[1].valHit * gModel.dmgATK;
					gModel.tabChar[0].nbHP -= 1 * gModel.tabChar[0].valHit * gModel.dmgATK;
				}
				else if (gModel.tabChar[1].atkSelected < gModel.tabChar[0].atkSelected)
				{
					gModel.tabChar[1].nbHP -= 1 * gModel.tabChar[0].valHit * gModel.dmgATK;
					gModel.tabChar[1].nbHP -= 1 * gModel.tabChar[1].valHit * gModel.dmgATK;
				}

				gModel.tabChar[0].atkSelected = gModel.none;
				gModel.tabChar[1].atkSelected = gModel.none;

				gModel.numStage = 0;
				gModel.numTour++;

				std::cout << "TOUR NUMERO " << gModel.numTour << std::endl;
				std::cout << "HP J0 : " << gModel.tabChar[0].nbHP << std::endl;
				std::cout << "HP J1 : " << gModel.tabChar[1].nbHP << std::endl;

				if (gModel.tabChar[0].nbHP < 0) std::cout << "J1 GAGNE" << std::endl, window.close();
				if (gModel.tabChar[1].nbHP < 0) std::cout << "J0 GAGNE" << std::endl, window.close();
			}
		}
		
		// AFFICHAGE DES ELEMENTS
		
		int iterAffichage = 1;

		float nbFramesMove = 8;
		if (animationMoveToPlay) iterAffichage = nbFramesMove *(chemin.size()-1);

		Vector2f posPlayer;

		deltaTime = clock.restart().asSeconds();

		int j = 0;
		for (int k = 0; k < iterAffichage; k++)
		{
			// Affiche le BG
			gView.displayBG(window);

			// Map + Obstacles
			gView.displayMap(window, gModel.map, gModel.mapSize);

			// Previsualisation Attaque Portee
			if (gModel.tabChar[indexToPlay].mode == "attaque" && gModel.tabChar[indexToPlay].atkSelected.type != "none")
			{
				if (Util::isValid(gModel.tabChar[indexToPlay].posChar.x + 1, gModel.tabChar[indexToPlay].posChar.y, Vector2i(-1, -1), gModel.map)) gView.drawTile(window, gView.blueTile, gModel.tabChar[indexToPlay].posChar.x + 1, gModel.tabChar[indexToPlay].posChar.y);
				if (Util::isValid(gModel.tabChar[indexToPlay].posChar.x - 1, gModel.tabChar[indexToPlay].posChar.y, Vector2i(-1, -1), gModel.map)) gView.drawTile(window, gView.blueTile, gModel.tabChar[indexToPlay].posChar.x - 1, gModel.tabChar[indexToPlay].posChar.y);
				if (Util::isValid(gModel.tabChar[indexToPlay].posChar.x, gModel.tabChar[indexToPlay].posChar.y + 1, Vector2i(-1, -1), gModel.map)) gView.drawTile(window, gView.blueTile, gModel.tabChar[indexToPlay].posChar.x, gModel.tabChar[indexToPlay].posChar.y + 1);
				if (Util::isValid(gModel.tabChar[indexToPlay].posChar.x, gModel.tabChar[indexToPlay].posChar.y - 1, Vector2i(-1, -1), gModel.map)) gView.drawTile(window, gView.blueTile, gModel.tabChar[indexToPlay].posChar.x, gModel.tabChar[indexToPlay].posChar.y - 1);
			}

			// Affichage des cases sous les persos
			for(int i = 0; i < 2; i++) 
			{ 
				if (animationMoveToPlay)
				{
					if (i == indexToPlay)
					{
						gView.drawCharacter(window, gModel, i, indexToPlay == i);
					}
				}
				else
				{
					gView.drawCharacter(window, gModel, i, indexToPlay == i);
				}
			}
				

			// Affiche Previsualisation
			gView.displayPrev(gModel, chemin, window, indiceSouris, indexToPlay);

			// Affiche Personnage

			// if (gModel.tabChar[0].orientation == Vector2i(1, 0)) animation.Update(6, deltaTime);
			// if (gModel.tabChar[0].orientation == Vector2i(-1, 0)) animation.Update(8, deltaTime);
			// if (gModel.tabChar[0].orientation == Vector2i(0, 1)) animation.Update(7, deltaTime);
			// if (gModel.tabChar[0].orientation == Vector2i(0, -1)) animation.Update(5, deltaTime);

			// Affichage des Personnages selon leur orientation

			sf::IntRect uvRect;
			uvRect.width = playerTexture.getSize().x / float(8);
			uvRect.height = playerTexture.getSize().y / float(9);
			uvRect.top = 0 * uvRect.height;

			if (animationMoveToPlay)
			{
				if (k % (int)nbFramesMove == 0 && k != 0) j++;

				Vector2i direction;
				if (Vector2i(chemin[j + 1].x - chemin[j].x, chemin[j].y - chemin[j + 1].y) == Vector2i(1, 0)) animation.Update(6, deltaTime), direction = Vector2i(1, 0);
				if (Vector2i(chemin[j + 1].x - chemin[j].x, chemin[j].y - chemin[j + 1].y) == Vector2i(-1, 0)) animation.Update(8, deltaTime), direction = Vector2i(-1, 0);
				if (Vector2i(chemin[j + 1].x - chemin[j].x, chemin[j].y - chemin[j + 1].y) == Vector2i(0, 1)) animation.Update(7, deltaTime), direction = Vector2i(0, 1);
				if (Vector2i(chemin[j + 1].x - chemin[j].x, chemin[j].y - chemin[j + 1].y) == Vector2i(0, -1)) animation.Update(5, deltaTime), direction = Vector2i(0, -1);
				//uvRect.left = 4 * uvRect.width;

				posPlayer = gView.getCoordfromISO(Vector2f(chemin[j].x + (1/ nbFramesMove)*(k% (int)nbFramesMove)*direction.x, chemin[j].y - (1 / nbFramesMove) *(k % (int)nbFramesMove)*direction.y));
				player.setPosition(posPlayer.x + 18, posPlayer.y - 25);
				player.setTextureRect(animation.uvRect);
				window.draw(player);
			}

			for (int i = 0; i < 2; i++)
			{
				if (animationMoveToPlay)
				{
					if (i == indexToPlay)
					{
						if (gModel.tabChar[i].orientation == Vector2i(1, 0)) uvRect.left = 4 * uvRect.width;
						if (gModel.tabChar[i].orientation == Vector2i(-1, 0)) uvRect.left = 0 * uvRect.width;
						if (gModel.tabChar[i].orientation == Vector2i(0, 1)) uvRect.left = 2 * uvRect.width;
						if (gModel.tabChar[i].orientation == Vector2i(0, -1)) uvRect.left = 6 * uvRect.width;

						player.setPosition(gView.getCoordfromISO(gModel.tabChar[i].posChar).x + 18, gView.getCoordfromISO(gModel.tabChar[i].posChar).y - 25);
						player.setTextureRect(uvRect);
						window.draw(player);
					}
				}
				else
				{
					if (gModel.tabChar[i].orientation == Vector2i(1, 0)) uvRect.left = 4 * uvRect.width;
					if (gModel.tabChar[i].orientation == Vector2i(-1, 0)) uvRect.left = 0 * uvRect.width;
					if (gModel.tabChar[i].orientation == Vector2i(0, 1)) uvRect.left = 2 * uvRect.width;
					if (gModel.tabChar[i].orientation == Vector2i(0, -1)) uvRect.left = 6 * uvRect.width;

					player.setPosition(gView.getCoordfromISO(gModel.tabChar[i].posChar).x + 18, gView.getCoordfromISO(gModel.tabChar[i].posChar).y - 25);
					player.setTextureRect(uvRect);
					window.draw(player);
				}
			}


			// Affichage Texte : HP

			for (int i = 0; i < 2; i++)
			{
				if (animationMoveToPlay)
				{
					if (i == indexToPlay)
					{
						Vector2f posChar = gView.getCoordfromISO(gModel.tabChar[i].posChar);
						std::stringstream s;
						s << gModel.tabChar[i].nbHP;
						std::string s2 = s.str();
						float offset = (s2.length() - 1) * 6;
						gView.displayText(window, "little", Vector2f(posChar.x + 49 - offset, posChar.y - 50), s.str());
					}
					else
					{
						Vector2f posChar = posPlayer;
						std::stringstream s;
						s << gModel.tabChar[i].nbHP;
						std::string s2 = s.str();
						float offset = (s2.length() - 1) * 6;
						gView.displayText(window, "little", Vector2f(posChar.x + 49 - offset, posChar.y - 50), s.str());
					}
				}
				else
				{
					Vector2f posChar = gView.getCoordfromISO(gModel.tabChar[i].posChar);
					std::stringstream s;
					s << gModel.tabChar[i].nbHP;
					std::string s2 = s.str();
					float offset = (s2.length() - 1) * 6;
					gView.displayText(window, "little", Vector2f(posChar.x + 49 - offset, posChar.y - 50), s.str());
				}
			}

			// Affichage Texte : Mode + Raccourcis

			std::stringstream s2;
			s2 << gModel.tabChar[indexToPlay].mode << " " << indexToPlay;
			gView.displayText(window, "big", Vector2f(10, 650), s2.str());

			if (gModel.tabChar[indexToPlay].mode == "attaque")
			{
				gView.displayText(window, "middle", Vector2f(11, 550), "A : PIERRE");
				gView.displayText(window, "middle", Vector2f(11, 580), "Z : FEUILLE");
				gView.displayText(window, "middle", Vector2f(11, 610), "E : CISEAUX");
			}

			// Affichage Texte : Tour 

			std::stringstream s3;
			s3 << "TOUR " << gModel.numTour;
			gView.displayText(window, "big", Vector2f(10, -5), s3.str());

			// Affichage du curseur

			if (gModel.tabChar[indexToPlay].mode == "deplacement") gView.drawCursor(window, "move", Mouse::getPosition(window));
			if (gModel.tabChar[indexToPlay].mode == "attaque") gView.drawCursor(window, gModel.tabChar[indexToPlay].atkSelected.type, Mouse::getPosition(window));

			window.display();

			if (animationMoveToPlay)
			{
				while (clock.getElapsedTime().asMilliseconds() < 40)
				{

				}
				deltaTime = clock.restart().asSeconds();
			}
			
		}
		animationMoveToPlay = false;
	}

	return 0;
}
#endif