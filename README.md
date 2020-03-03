# usoJANKEN
Gamagora 2019 - AI  - usoJANKEN (A* / Dijkstra)

## Histoire

*Jeu inspiré de Dofus, c'était un petit challenge personnel d'essayer de réimplémenter le système de combat.*<br>
*Le jeu a été entièrement codé en C++ avec SFML en partant de rien.*

## Illustration

![usoJANKEN](Capture.PNG)

## Fiche technique du jeu
Le but était de créer un jeu isométrique (iso) de combat tour à tour basé sur le JANKEN (Pierre Feuille Ciseaux) :

Le jeu se déroule en tours, chaque tour contient 4 phases :

- Le premier joueur se déplace<br>
- Le deuxième joueur se déplace<br>
- Le premier joueur choisit une attaque entre Pierre Feuille et Ciseaux (selon le placement du joueur il est possible de toucher avec certaines attaques et pas d'autres)<br>
- Le deuxième joueur choisit une attaque entre Pierre Feuille et Ciseaux (ne sachant pas ce que le premier joueur a choisi)

Les dégats sont appliqués selon le choix des joueurs :
- S'il y a égalité, les dégats sont appliqués aux deux joueurs (x1)<br>
- Si l'un domine, il inflige des dégats doublés (x2) à l'autre joueur qui lui ne lui inflige pas de dégats<br>
- Il est possible de rater son attaque et de ne pas toucher le joueur (les attaques ont des patterns)<br>

A chaque tour l'ordre des joueurs est inversé, exemple :<br>
> Tour 1 :
- J1 move
- J2 move
- J1 attack
- J2 attack<br>
> Tour 2 : <br>
- J2 move
- J1 move
- J2 attack
- J1 attack

On se déplace en utilisant la souris et en cliquant sur la case où on veut se déplacer (il y a une limite de distance qu'un joueur peut parcourir par tour de 6 cases).
On choisit l'attaque que l'on veut utiliser avec A Z E pour respectivement choisir Pierre Feuille et Ciseaux, et on l'utilise en cliquant sur une des cases bleues autour du personnage qui indiquent la portée d'attaque.

## Video Youtube :
