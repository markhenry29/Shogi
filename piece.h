/* piece.h
----------------
Par LE Richard

date de création: 21/03/2107.
*/
#ifndef __PIECE_H__
#define __PIECE_H__

#define JOUEUR_VIDE 0
#define JOUEUR_1 1
#define JOUEUR_2 2


#define NON_PROMU 0
#define PROMU 1

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>

/*
    Général d'or --> GOLD
    Général d'argent -->SILVER
    fou --> BISHOP
    tour --> ROOK
    cavalier --> KNIGHT
    pion --> PAWN
*/
enum
{
	PAWN, LANCE, KNIGHT, BISHOP, ROOK, SILVER, GOLD, KING, VIDE
};


struct piece_s
{
    int joueur;
    int type;
    int statut;
};
typedef struct piece_s piece_t;

piece_t piece_creer(int joueur, int type, int statut);
int piece_joueur(piece_t p);
piece_t piece_identifier(char c);
char piece_caractere(piece_t p);
void piece_afficher(piece_t p);
int cmp_piece(piece_t p1,piece_t p2);

#endif
