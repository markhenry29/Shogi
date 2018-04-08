/* partie.h
---------------


date de création: 21/03/2017.
*/
#ifndef __PARTIE_H__
#define __PARTIE_H__

/* inclusion de piece.h, liste_coups.h et reserve.h */
#include "piece.h"
#include "liste_coups.h"
#include "reserve.h"
#include <string.h>

/* définition des constantes utilisateurs */
#define NB_LIGNE 11
#define NB_COLONNE 11

#define OPTION_DEBUT 0
#define OPTION_JOUER 1
#define OPTION_ANNULER 2
#define OPTION_QUITTER 3

#define INVALIDE 3
#define ECHEC 2
#define MAT 4

#define CONDITION_ECHEC_ROI_2 deplacement_valide(p, c, r2, p.tablier[c.x][c.y].type,\
                                                p.tablier[c.x][c.y].statut) == TRUE && piece_joueur(p.tablier[c.x][c.y]) == JOUEUR_1
#define CONDITION_ECHEC_ROI_1 deplacement_valide(p, c, r1, p.tablier[c.x][c.y].type,\
                                                p.tablier[c.x][c.y].statut) == TRUE && piece_joueur(p.tablier[c.x][c.y]) == JOUEUR_2
/* structure partie */
struct partie_s
{
    piece_t **tablier;
    liste_t *CoupsJoues;
    reserve_t *reserve_joueur_1;
    reserve_t * reserve_joueur_2;
    int joueur;
};
typedef struct partie_s partie_t;

/* inclusion de deplacement.h (deplacement.h dépend de partie.h, on est obligé de l'inclure ici)*/
#include "deplacement.h"

int case_vide(partie_t p, coordonnees_t c);
void modifier_case(partie_t *p, piece_t piece, coordonnees_t c);
void changer_joueur(partie_t *p);
void afficher_plateau(partie_t *p);

coordonnees_t saisie_case();
partie_t * partie_creer();
void init_tablier(partie_t * partie);
void partie_jouer(partie_t *p);
void partie_detruire(partie_t *p);
void afficher_reserve(partie_t *p);
void partie_sauvegarder(partie_t *p, char* nom_du_fichier);
int partie_echec(partie_t p);
int partie_mat(partie_t p);
coordonnees_t coordonnees_roi(partie_t p, int joueur);

void ajouter_reserve_chargement(partie_t* res);
partie_t* partie_charger(char* s);
partie_t* partie_nouvelle();
void replay_sauvegarder(partie_t *p, char *s);
liste_t* replay_charger(char* s);
void replay_jouer(partie_t *p,char *s);
#endif
