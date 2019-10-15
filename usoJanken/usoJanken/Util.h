#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <assert.h>
#include <stack>
#include <array>
#include <windows.h>
#include <math.h>
#include <SFML/System/Vector2.hpp>

class Util
{
	public :

		// DIJKSTRA :

		struct my_comparator
		{
			bool operator()(std::vector<int> const& a, std::vector<int> const& b) const
			{
				assert(a.size() == 2);
				assert(b.size() == 2);
				return a[1] > b[1];
			}
		};

		using my_priority_queue = std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, my_comparator>;

		static int dijkstra()
		{
			const int nbSommets = 10;
			int noeud_depart = 0;
			int noeud_arrivee = 9;

			int graphe[nbSommets][nbSommets];

			for (int i = 0; i < nbSommets; i++)
			{
				for (int j = 0; j < nbSommets; j++)
				{
					graphe[i][j] = -1; // -1 = inf
				}
			}

			// Exemple du Cours : 10 sommets, 0 > 9

			graphe[0][1] = 85;		// A > B
			graphe[0][2] = 217;		// A > C
			graphe[0][4] = 173;		// A > E
			graphe[1][5] = 80;		// B > F
			graphe[2][7] = 103;		// C > H
			graphe[2][6] = 186;		// C > G
			graphe[3][7] = 183;		// D > H
			graphe[4][9] = 502;		// E > J
			graphe[5][8] = 250;		// F > I
			graphe[7][9] = 167;		// H > J
			graphe[8][9] = 84;		// I > J

			// Distance : 487, Chemin : 0 > 2 > 7 > 9


			// Autre exemple : 7 sommets, 0 > 6

			// graphe[0][1] = 9;
			// graphe[0][2] = 20;
			// graphe[0][3] = 17;
			// graphe[1][4] = 30;
			// graphe[2][5] = 40;
			// graphe[3][6] = 50;
			// graphe[4][5] = 2;
			// graphe[5][6] = 8;

			// Distance : 49, Chemin : 0 > 1 > 4 > 5 > 6

			bool noeuds_visites[nbSommets];
			int distanceMin[nbSommets];
			int predecesseur[nbSommets];

			for (int i = 0; i < nbSommets; i++)
			{
				distanceMin[i] = -1; // -1 = inf
				predecesseur[i] = -1;
				noeuds_visites[i] = false;
			}

			int noeud_courant;
			int distance = 0;

			// Affichage Graphe :
			for (int i = 0; i < nbSommets; i++)
			{
				for (int j = 0; j < nbSommets; j++)
				{
					std::cout << " " << graphe[i][j];
				}
				std::cout << std::endl;
			}


			my_priority_queue prio_queue;
			prio_queue.push({ noeud_depart, 0 });
			distanceMin[noeud_depart] = 0;
			std::vector<int> entrance;

			while (true)
			{
				if (prio_queue.empty())
				{
					break;
				}
				else
				{
					entrance = prio_queue.top();
					prio_queue.pop();

					noeud_courant = entrance[0];
					distance = entrance[1];
				}

				if (noeuds_visites[noeud_courant] == false)
				{
					noeuds_visites[noeud_courant] = true;
					if (noeud_courant == noeud_arrivee) break;

					for (int i = 0; i < nbSommets; i++)
					{
						if (graphe[noeud_courant][i] != -1)
						{
							// std::cout << "Pour le noeud courant : " << noeud_courant << " on check l'arc : (" << noeud_courant << ", " << i << ") > " << graphe[noeud_courant][i] << std::endl;

							int new_distance = distance + graphe[noeud_courant][i];
							int distance_min = distanceMin[i];

							if (new_distance < distanceMin[i] || distanceMin[i] == -1)
							{
								distanceMin[i] = new_distance;
								predecesseur[i] = noeud_courant;
								prio_queue.push({ i , new_distance });


								// Debug

								std::cout << "Prio Queue Insered : " << std::endl;
								std::cout << "0 : " << i << std::endl;
								std::cout << "1 : " << new_distance << std::endl;

							}
						}
					}
				}
			}

			distance = distanceMin[noeud_arrivee];

			std::stack<int> chemin;
			if (predecesseur[noeud_arrivee] != -1)
			{
				noeud_courant = noeud_arrivee;
				while (noeud_courant != -1)
				{
					chemin.push(noeud_courant);
					noeud_courant = predecesseur[noeud_courant];
				}
			}

			std::cout << "Chemin  : " << std::endl;
			while (!chemin.empty())
			{
				std::cout << chemin.top() << " ";
				chemin.pop();
			}
			std::cout << std::endl;



			// Debug

			std::cout << "Noeuds_Visites : " << std::endl;
			for (int i = 0; i < nbSommets; i++)
			{
				std::cout << noeuds_visites[i] << std::endl;
			}

			std::cout << "Predecesseur : " << std::endl;
			for (int i = 0; i < nbSommets; i++)
			{
				std::cout << predecesseur[i] << std::endl;
			}


			std::cout << "Distance : " << std::endl;
			std::cout << distanceMin[noeud_arrivee] << std::endl;
			std::cout << std::endl;

			return distanceMin[noeud_arrivee];
		}

		// A STAR :

		struct Node
		{
			int y;
			int x;
			int parentX;
			int parentY;
			float gCost;
			float hCost;
			float fCost;
		};

		// Pour savoir si un noeud est atteignable (dans la map / pas sur un joueur / pas sur un obstacle)
		static bool isValid(int x, int y, sf::Vector2i posPlayerToDodge, int* map2)
		{
			// Noeud HORS DE LA MAP OU OBSTACLE(map2[x + y*23] == 1) OU JOUEUR ADVERSE(posPlayerToDodge)
			if (x < 0 || y < 0 || x >= 23 || y >= 23 || (map2[x + y * 23] == 1) || (sf::Vector2i(x, y) == posPlayerToDodge)) return false;
			return true;
		};

		// Pour savoir si un noeud est la destination finale
		static bool estObjectif(int x, int y, Node objectif)
		{
			if (x == objectif.x && y == objectif.y) return true;
			return false;
		};

		static double getHeuristique(int x, int y, Node destination)
		{
			double heuristique = (sqrt((x - destination.x) * (x - destination.x) + (y - destination.y) * (y - destination.y)));
			return heuristique;
		};

		static std::vector<Node> makePath(std::array<std::array<Node, 23>, 23> map, Node dest)
		{
			// std::cout << "Chemin Trouve ss" << std::endl;
			int x = dest.x;
			int y = dest.y;
			std::stack<Node> path;
			std::vector<Node> usablePath;

			while (!(map[x][y].parentX == x && map[x][y].parentY == y) && map[x][y].x != -1 && map[x][y].y != -1)
			{
				path.push(map[x][y]);
				int tempX = map[x][y].parentX;
				int tempY = map[x][y].parentY;
				x = tempX;
				y = tempY;
			}
			path.push(map[x][y]);

			while (!path.empty())
			{
				Node top = path.top();
				path.pop();
				usablePath.emplace_back(top);
			}
			return usablePath;
		};

		static std::vector<Node> aStar(Node player, Node dest, sf::Vector2i posPlayerToDodge, int* map2)
		{
			std::vector<Node> empty;
			if (isValid(dest.x, dest.y, posPlayerToDodge, map2) == false)
			{
				// std::cout << "La destination est un obstacle" << std::endl;
				return empty;
			}
			if (estObjectif(player.x, player.y, dest))
			{
				// std::cout << "Tu as clique sur toi meme" << std::endl;
				return empty;
			}
			bool closedList[23][23];

			std::array<std::array < Node, 23>, 23> allMap;
			for (int x = 0; x < 23; x++)
			{
				for (int y = 0; y < 23; y++)
				{
					allMap[x][y].fCost = FLT_MAX;
					allMap[x][y].gCost = FLT_MAX;
					allMap[x][y].hCost = FLT_MAX;
					allMap[x][y].parentX = -1;
					allMap[x][y].parentY = -1;
					allMap[x][y].x = x;
					allMap[x][y].y = y;

					closedList[x][y] = false;
				}
			}

			// Initialisation
			int x = player.x;
			int y = player.y;
			allMap[x][y].fCost = 0.0;
			allMap[x][y].gCost = 0.0;
			allMap[x][y].hCost = 0.0;
			allMap[x][y].parentX = x;
			allMap[x][y].parentY = y;

			std::vector<Node> openList;
			openList.emplace_back(allMap[x][y]);
			bool objectifAtteint = false;

			while (!openList.empty() && openList.size() < 23 * 23)
			{
				Node node;
				do
				{
					float temp = FLT_MAX;
					std::vector<Node>::iterator itNode;
					for (std::vector<Node>::iterator it = openList.begin(); it != openList.end(); it = next(it))
					{
						Node n = *it;
						if (n.fCost < temp)
						{
							temp = n.fCost;
							itNode = it;
						}
					}
					node = *itNode;
					openList.erase(itNode);
				} while (isValid(node.x, node.y, posPlayerToDodge, map2) == false);

				x = node.x;
				y = node.y;
				closedList[x][y] = true;

				// On regarde les voisins
				for (int newX = -1; newX <= 1; newX++)
				{
					for (int newY = -1; newY <= 1; newY++)
					{
						// Pas de deplacement en diagonale
						if (newX == 0 || newY == 0)
						{
							double gNew, hNew, fNew;
							if (isValid(x + newX, y + newY, posPlayerToDodge, map2)) 
							{
								if (estObjectif(x + newX, y + newY, dest))
								{
									// Si on trouve la destination on fait le chemin
									allMap[x + newX][y + newY].parentX = x;
									allMap[x + newX][y + newY].parentY = y;
									objectifAtteint = true;
									return makePath(allMap, dest);
								}
								else if (closedList[x + newX][y + newY] == false)
								{
									gNew = node.gCost + 1.0;
									hNew = getHeuristique(x + newX, y + newY, dest);
									fNew = gNew + hNew;
									// On regarde si ce chemin est meilleur que l'ancien
									if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
										allMap[x + newX][y + newY].fCost > fNew)
									{
										// On modifie les details du Noeud
										allMap[x + newX][y + newY].fCost = fNew;
										allMap[x + newX][y + newY].gCost = gNew;
										allMap[x + newX][y + newY].hCost = hNew;
										allMap[x + newX][y + newY].parentX = x;
										allMap[x + newX][y + newY].parentY = y;
										openList.emplace_back(allMap[x + newX][y + newY]);
									}
								}
							}
						}
					}
				}
			}

			if (objectifAtteint == false)
			{
				// std::cout << "OBjectif non atteint" << std::endl;
				return empty;
			}
		};
};

