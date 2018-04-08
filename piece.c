/* piece.c
----------------
Par LE Richard

date de création: 21/03/2107.
*/

#include "piece.h"

/**
    Déclare une piece et le renvoie initialisé par les valeurs passées en entrées.
    @param joueur un entier (type enum)
    @param type un entier (type enum)
    @param statut un entier (type enum)
    @return res une pièce initialisé
 */
piece_t piece_creer(int joueur, int type, int statut)
{
    piece_t res;
    res.joueur = joueur;
    res.type = type;
    res.statut = statut;
    return res;
}
/**
    Renvoie à quel joueur appartien la pièce.
    @param p une pièce
    @return p.joueur le numéro du joueur
 */
int piece_joueur(piece_t p)
{
    return p.joueur;
}
/**
    Déclare une pièce p, et l'initialise selon le caractère passé en entré.
    Par exemple si le caractère vaut 'b', alors la fonction renvoie un fou non promu qui appartient au joueur 1.
    @param c un caractère
    @return p une pièce initialisé
 */
piece_t piece_identifier(char c)
{
    piece_t p;
    switch(c)
    {
        /* piece identifié du joueur 1 */
        case 'p':
            p = piece_creer(JOUEUR_1, PAWN, NON_PROMU);
            return p;
            break;
        case 'l':
            p = piece_creer(JOUEUR_1, LANCE, NON_PROMU);
            return p;
            break;
        case 'n':
            p = piece_creer(JOUEUR_1, KNIGHT, NON_PROMU);
            return p;
            break;
        case 'b':
            p = piece_creer(JOUEUR_1, BISHOP, NON_PROMU);
            return p;
            break;
        case 'r':
            p = piece_creer(JOUEUR_1, ROOK, NON_PROMU);
            return p;
            break;
        case 's':
            p = piece_creer(JOUEUR_1, SILVER, NON_PROMU);
            return p;
            break;
        case 'g':
            p = piece_creer(JOUEUR_1, GOLD, NON_PROMU);
            return p;
            break;
        case 'k':
            p = piece_creer(JOUEUR_1, KING, NON_PROMU);
            return p;
            break;
        case 'd':
            p = piece_creer(JOUEUR_1, PAWN, PROMU);
            return p;
            break;
        case 'j':
            p = piece_creer(JOUEUR_1, LANCE, PROMU);
            return p;
            break;
        case 'c':
            p = piece_creer(JOUEUR_1, KNIGHT, PROMU);
            return p;
            break;
        case 'f':
            p = piece_creer(JOUEUR_1, BISHOP, PROMU);
            return p;
            break;
        case 't':
            p = piece_creer(JOUEUR_1, ROOK, PROMU);
            return p;
            break;
        case 'a':
            p = piece_creer(JOUEUR_1, SILVER, PROMU);
            return p;
            break;


        /* piece identifié du joueur 2 */
        case 'P':
            p = piece_creer(JOUEUR_2, PAWN, NON_PROMU);
            return p;
            break;
        case 'L':
            p = piece_creer(JOUEUR_2, LANCE, NON_PROMU);
            return p;
            break;
        case 'N':
            p = piece_creer(JOUEUR_2, KNIGHT, NON_PROMU);
            return p;
            break;
        case 'B':
            p = piece_creer(JOUEUR_2, BISHOP, NON_PROMU);
            return p;
            break;
        case 'R':
            p = piece_creer(JOUEUR_2, ROOK, NON_PROMU);
            return p;
            break;
        case 'S':
            p = piece_creer(JOUEUR_2, SILVER, NON_PROMU);
            return p;
            break;
        case 'G':
            p = piece_creer(JOUEUR_2, GOLD, NON_PROMU);
            return p;
            break;
        case 'K':
            p = piece_creer(JOUEUR_2, KING, NON_PROMU);
            return p;
            break;
        case 'D':
            p = piece_creer(JOUEUR_2, PAWN, PROMU);
            return p;
            break;
        case 'J':
            p = piece_creer(JOUEUR_2, LANCE, PROMU);
            return p;
            break;
        case 'C':
            p = piece_creer(JOUEUR_2, KNIGHT, PROMU);
            return p;
            break;
        case 'F':
            p = piece_creer(JOUEUR_2, BISHOP, PROMU);
            return p;
            break;
        case 'T':
            p = piece_creer(JOUEUR_2, ROOK, PROMU);
            return p;
            break;
        case 'A':
            p = piece_creer(JOUEUR_2, SILVER, PROMU);
            return p;
            break;
    }
	p = piece_creer(JOUEUR_VIDE, VIDE, NON_PROMU);
	return p;
}

/**
    La fonction regarde d'abord à quel joueur appartient la pièce, puis le statut(si il est promu ou pas) et enfin le type.
    Elle renvoie donc le caractère qui correspond à la pièce décrit par les paramètres énumérés si dessus.
    @param p une pièce
    @return un caractère
 */
char piece_caractere(piece_t p)
{
    switch(p.joueur)
    {
        /* -- Joueur 1 -- */
        case JOUEUR_1:
            switch(p.statut)
            {
                /* Si la pièce n'est pas promu... */
                case NON_PROMU:
                    switch(p.type)
                    {
                        case PAWN:
                            return 'p';
                            break;
                        case LANCE:
                            return 'l';
                            break;
                        case KNIGHT:
                            return 'n';
                            break;
                        case BISHOP:
                            return 'b';
                            break;
                        case ROOK:
                            return 'r';
                            break;
                        case SILVER:
                            return 's';
                            break;
                        case GOLD:
                            return 'g';
                            break;
                        case KING:
                            return 'k';
                            break;
                    }
                break;

                /* Si la pièce est promu... */
                case PROMU:
                    switch(p.type)
                    {
                        case PAWN:
                            return 'd';
                            break;
                        case LANCE:
                            return 'j';
                            break;
                        case KNIGHT:
                            return 'c';
                            break;
                        case BISHOP:
                            return 'f';
                            break;
                        case ROOK:
                            return 't';
                            break;
                        case SILVER:
                            return 'a';
                            break;
                    }
                break;
            }
        break;


        /* -- Joueur 2 -- */
        case JOUEUR_2:
            switch(p.statut)
            {
                /* Si la pièce n'est pas promu... */
                case NON_PROMU:
                    switch(p.type)
                    {
                        case PAWN:
                            return 'P';
                            break;
                        case LANCE:
                            return 'L';
                            break;
                        case KNIGHT:
                            return 'N';
                            break;
                        case BISHOP:
                            return 'B';
                            break;
                        case ROOK:
                            return 'R';
                            break;
                        case SILVER:
                            return 'S';
                            break;
                        case GOLD:
                            return 'G';
                            break;
                        case KING:
                            return 'K';
                            break;
                    }
                break;

                /* Si la pièce est promu... */
                case PROMU:
                    switch(p.type)
                    {
                        case PAWN:
                            return 'D';
                            break;
                        case LANCE:
                            return 'J';
                            break;
                        case KNIGHT:
                            return 'C';
                            break;
                        case BISHOP:
                            return 'F';
                            break;
                        case ROOK:
                            return 'T';
                            break;
                        case SILVER:
                            return 'A';
                            break;
                    }
                break;
            }
        break;
    }

    /* Si il n'y a pas de pièce */
		return '.';
}

void piece_afficher(piece_t p)
{
	 char c = piece_caractere(p);
	 printf("%c",c);
}

/**
    Retourne TRUE si il s'agit de la meme pièce et FALSE sinon.
    @param p1 une pièce
    @param p2 une pièce
    @return un booléen TRUE or FALSE
 */
int cmp_piece(piece_t p1,piece_t p2)
{
	if(piece_joueur(p1)==piece_joueur(p2) && p1.type == p2.type && p1.statut == p2.statut)
		return TRUE;
	return FALSE;
}
