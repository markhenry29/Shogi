#ifndef RESERVE_H_INCLUDED
#define RESERVE_H_INCLUDED
#define TAILLE_MAX 19
#include "piece.h"


struct reserve_s
{
 	piece_t * tab_reserve;
 	int nb_piece;
};
typedef struct reserve_s reserve_t;

reserve_t * creer_tab_reserve();
int tab_reserve_vide(reserve_t * r);
void detruire_tab_reserve(reserve_t * r);
void tab_reserve_ajouter(reserve_t * l, piece_t p);
piece_t tab_reserve_extraire(reserve_t * r);
void tab_reserve_supprimer(reserve_t * r, piece_t p);
int tab_reserve_appartient(reserve_t * r, piece_t p);


#endif
