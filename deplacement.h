/* deplacement.h
------------------

date de création: 01/04/2017
*/

#ifndef __DEPLACEMENT_H__
#define __DEPLACEMENT_H__

#include "partie.h"

#define PROMOTION p->tablier[d.x][d.y].statut = PROMU

/* haut, bas, gauche, droite. */
#define HAUT (d.x == a.x + 1)
#define BAS (d.x == a.x - 1)
#define GAUCHE (d.y == a.y + 1)
#define DROITE (d.y == a.y - 1)

/* mouvements en diagonales. */
#define DIAGONALE_UP_LEFT (HAUT && GAUCHE)
#define DIAGONALE_UP_RIGHT (HAUT && DROITE)
#define DIAGONALE_DOWN_LEFT (BAS && GAUCHE)
#define DIAGONALE_DOWN_RIGHT (BAS && DROITE)

#define ALL_DIRECTIONS (HAUT || BAS || GAUCHE || DROITE)

/* mouvements du cavalier */
#define KNIGHT_UP_LEFT (d.x == a.x + 2 && GAUCHE)
#define KNIGHT_UP_RIGHT (d.x == a.x + 2 && DROITE)
#define KNIGHT_DOWN_LEFT (d.x == a.x - 2 && GAUCHE)
#define KNIGHT_DOWN_RIGHT (d.x == a.x - 2 && DROITE)

/* mouvements directionnels, ça sert pour la tour, la lance et le fou qui ont une portée illimité. */
#define HAUT_D (d.x > a.x)
#define BAS_D (d.x < a.x)
#define GAUCHE_D (d.y > a.y)
#define DROITE_D (d.y < a.y)
#define DIAGONALE_UP_LEFT_D HAUT_D && GAUCHE_D
#define DIAGONALE_UP_RIGHT_D HAUT_D && DROITE_D
#define DIAGONALE_DOWN_LEFT_D BAS_D && GAUCHE_D
#define DIAGONALE_DOWN_RIGHT_D BAS_D && DROITE_D
#define DIAGONALE_D (valeur_absolue(difference_x) == valeur_absolue(difference_y))

#define MEME_COLONNE (d.y == a.y)
#define MEME_LIGNE (d.x == a.x)
#define RESERVE_JOUEUR_1 (d.x == NB_LIGNE - 1 || d.y == NB_LIGNE - 1)
#define RESERVE_JOUEUR_2 (d.x == 0 || d.y == 0)
#define RESERVE (RESERVE_JOUEUR_1 || RESERVE_JOUEUR_2)
#define CASE_VIDE case_vide(p, a) == TRUE
#define CASE_NON_VIDE case_vide(p, c) == FALSE

#define SURPLACE (d.x == a.x && d.y == a.y)
#define TEAMKILL (p.tablier[a.x][a.y].joueur == p.tablier[d.x][d.y].joueur)
#define MIND_CONTROL (piece_joueur(p->tablier[d.x][d.y]) != p->joueur)
#define ONE_CASE (valeur_absolue(d.x - a.x) <= 1 && valeur_absolue(d.y - a.y) <= 1)
#define ZONE_PROMO_1 a.x <= 3
#define ZONE_PROMO_2 a.x >= 7


/* conditions de déplacements des pièces
1 -> joueur1
2 -> joueur2
P -> statut == PROMU
*/
#define CONDITION_PION_1 HAUT && MEME_COLONNE && statut == NON_PROMU            /* | */
#define CONDITION_PION_2 BAS && MEME_COLONNE && statut == NON_PROMU             /* P */

#define CONDITION_GOLD_1 (ALL_DIRECTIONS && !(DIAGONALE_DOWN_LEFT || DIAGONALE_DOWN_RIGHT))&& ONE_CASE
#define CONDITION_GOLD_2 (ALL_DIRECTIONS && !(DIAGONALE_UP_LEFT || DIAGONALE_UP_RIGHT))&& ONE_CASE
#define CONDITION_GOLD_1_P (CONDITION_GOLD_1) && statut == PROMU
#define CONDITION_GOLD_2_P (CONDITION_GOLD_2) && statut == PROMU

#define CONDITION_SILVER_1 (HAUT || DIAGONALE_DOWN_LEFT || DIAGONALE_DOWN_RIGHT\
               	 			|| DIAGONALE_UP_LEFT || DIAGONALE_UP_RIGHT)&& ONE_CASE && statut == NON_PROMU
#define CONDITION_SILVER_2 (BAS || DIAGONALE_DOWN_LEFT || DIAGONALE_DOWN_RIGHT\
               	 			|| DIAGONALE_UP_LEFT || DIAGONALE_UP_RIGHT)&& ONE_CASE && statut == NON_PROMU
#define CONDITION_TOUR (MEME_COLONNE || MEME_LIGNE)&& piece_sur_chemin_tour(p, d, a) == FALSE
#define CONDITION_TOUR_P (MEME_COLONNE || MEME_LIGNE || (ALL_DIRECTIONS && ONE_CASE))\
			  			  && piece_sur_chemin_tour(p, d, a) == FALSE && statut == PROMU

#define CONDITION_FOU DIAGONALE_D && piece_sur_chemin_fou(p, d, a) == FALSE && statut == NON_PROMU
#define CONDITION_FOU_P (DIAGONALE_D || (ALL_DIRECTIONS && ONE_CASE))&& piece_sur_chemin_fou(p, d, a) == FALSE && statut == PROMU

#define CONDITION_LANCE_1 MEME_COLONNE && piece_sur_chemin_lance(p, d ,a) == FALSE && !BAS_D && statut == NON_PROMU
#define CONDITION_LANCE_2 MEME_COLONNE && piece_sur_chemin_lance(p, d, a) == FALSE && !HAUT_D && statut == NON_PROMU

#define CONDITION_CAVALIER_1 (KNIGHT_UP_LEFT || KNIGHT_UP_RIGHT )&& statut == NON_PROMU
#define CONDITION_CAVALIER_2 (KNIGHT_DOWN_LEFT || KNIGHT_DOWN_RIGHT) && statut == NON_PROMU


/* Prototypes fonctions de deplacement */
void deplacement(partie_t *p, coordonnees_t d, coordonnees_t a);
void annuler_deplacement(partie_t *partie);
int deplacement_valide_pion(partie_t p, coordonnees_t d, coordonnees_t a, int statut);
int deplacement_valide_silver(partie_t p, coordonnees_t d, coordonnees_t a, int statut);
int deplacement_valide_gold(partie_t p, coordonnees_t d, coordonnees_t a, int statut);
int deplacement_valide_roi(coordonnees_t d, coordonnees_t a, int statut);
int deplacement_valide_cavalier(partie_t p , coordonnees_t d, coordonnees_t a, int statut);
int deplacement_valide_lance(partie_t p, coordonnees_t d, coordonnees_t a, int statut);
int deplacement_valide_fou(partie_t p, coordonnees_t d, coordonnees_t a, int statut);
int deplacement_valide(partie_t p, coordonnees_t d, coordonnees_t a, int type, int statut);

/* Prototypes aide aux fonctions déplacement */
int arrive_valide(coordonnees_t arrive);
int pion_colonne_joueur(partie_t p, coordonnees_t arrive);
int derniere_ligne(partie_t p, coordonnees_t arrive);
int deux_derniere_ligne(partie_t p, coordonnees_t a);
int piece_sur_chemin_tour(partie_t p, coordonnees_t d, coordonnees_t a);
int piece_sur_chemin_lance(partie_t p, coordonnees_t d, coordonnees_t a);
int piece_sur_chemin_fou(partie_t p, coordonnees_t d, coordonnees_t a);
int valeur_absolue(int a);

#endif
