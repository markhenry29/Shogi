#include <stdio.h>
#include <stdlib.h>
#include "reserve.h"

/**
    Allouer de la mémoire de la reserve
    Allouer de la mémoire du tableau de piece de taille TAILLE_MAX
    Definir nb_piece nombre de pieces (0) dans le tableau vide
 */
reserve_t * creer_tab_reserve()
{
	int i;
	piece_t p = piece_creer(JOUEUR_VIDE,VIDE,NON_PROMU);
	reserve_t * res = malloc(sizeof(reserve_t));
	res->tab_reserve=malloc(TAILLE_MAX*sizeof(piece_t));
	for(i=0;i<TAILLE_MAX;i++)
	{
		res->tab_reserve[i]=p;
	}
	res->nb_piece = 0;

	return res;
}

/**
    Tester nb_piece dans la reserve
    @param r une reserve
    @return TRUE si nb_piece=0, FALSE sinon
 */

int tab_reserve_vide(reserve_t * r)
{
    if (r->nb_piece==0)
       return TRUE;
      else return FALSE;
}

/**
    Liberer le tableau de piece puis liberer la reserve
    @param r une reserve
 */
void detruire_tab_reserve(reserve_t * r)
{
	free(r->tab_reserve);
	free(r);
}

/**
    Ajouter une piece au tableau si le nombre de piece dans le tableau ne depasse pas TAILLE_MAX
    Incrémenter le nombre de piece dans le tableau
    @param r une reserve
    @param p une piece
 */
void tab_reserve_ajouter(reserve_t * r, piece_t p)
{
    int i;
    int ajout = TRUE;
	if(r->nb_piece <= TAILLE_MAX)
    {
        for(i=0;i<TAILLE_MAX;i++)
        {
            if(r->tab_reserve[i].type==VIDE && ajout == TRUE)
            {
                r->tab_reserve[i] = p;
                ajout = FALSE;
            }
        }

	r->nb_piece++;
    }
}

/**
    Supprimer une piece au tableau en decalant la position des pieces qui succèdent la piece supprimée
    Decrémenter le nombre de piece dans le tableau
    @param r une reserve
    @param p une piece


 */
void tab_reserve_supprimer(reserve_t * r, piece_t p)
{
	int i;
	int booleen = TRUE;
	for(i=0;i<r->nb_piece;i++)
	{
		if(cmp_piece(r->tab_reserve[i],p)==TRUE&& booleen == TRUE)
		{
			r->tab_reserve[i]=piece_creer(JOUEUR_VIDE,VIDE,NON_PROMU);
			r->nb_piece--;
			booleen = FALSE;
		}
	}
}

piece_t tab_reserve_extraire(reserve_t * r)
{
	piece_t res = r->tab_reserve[r->nb_piece-1];
	piece_t piece_vide = piece_creer(JOUEUR_VIDE,VIDE,NON_PROMU);
	r->tab_reserve[r->nb_piece-1] = piece_vide;
	r->nb_piece--;
	return res;
}

int tab_reserve_appartient(reserve_t * r, piece_t p)
{
    int i;
    if(tab_reserve_vide(r) == FALSE)
    {
        for(i = 0; i < r->nb_piece; i++)
        {
            if(cmp_piece(r->tab_reserve[i], p) == TRUE)
                return TRUE;
        }
    }

    return FALSE;
}
