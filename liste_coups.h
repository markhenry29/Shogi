/* liste.h
----------------

Ici il y a les structs permettant la manipulation des maillons et des listes.

date de création: 21/03/2107.
*/
#ifndef __LISTE_H__
#define __LISTE_H__

#include "piece.h"


struct coordonnees_s{
    int x;
    int y;
};
typedef struct coordonnees_s coordonnees_t;

struct coup_s{
    piece_t piece;
    coordonnees_t depart;
    coordonnees_t arrive;
    int capture;
    int promo;
};
typedef struct coup_s coup_t;

struct maillon_s
{
    coup_t * coup;
    struct maillon_s *precedent;
    struct maillon_s *suivant;
};
typedef struct maillon_s maillon_t;


struct liste_s
{
    maillon_t* debut;
    maillon_t* fin;
    int taille;
};
typedef struct liste_s liste_t;

/* prototypes des fonctions coup */
coordonnees_t coordonnees_creer(int x, int y);
coup_t* coup_creer(coordonnees_t d, coordonnees_t a, int promo, int capture);
void coup_detruire(coup_t *c);
void coordonnees_afficher(coordonnees_t c);


/* prototypes des fonctions maillon */
maillon_t* maillon_creer(coup_t *c);
void maillon_detruire(maillon_t* m);
void maillon_afficher(maillon_t m);

/* prototypes des fonctions liste */
liste_t* liste_initialiser();
int liste_vide(liste_t l);
maillon_t* liste_extraire_debut(liste_t *l);
maillon_t* liste_extraire_fin(liste_t *l);
void liste_detruire(liste_t *l);
void liste_ajouter_debut(liste_t *l, maillon_t *m);
void liste_ajouter_fin(liste_t *l, maillon_t *m);

#endif
