/* liste.c
----------------

date de cr�ation: 22/03/2107.
*/
#include "liste_coups.h"

/**
    D�clarer une variable coordonn�e c et l'initialise par les param�tres pass�s en entr�e.
    @param x le num�ro de colonne
    @param y le caract�re de la ligne
    @return c les coordonn�es
 */
coordonnees_t coordonnees_creer(int x, int y)
{
    coordonnees_t c;
    c.x = x;
    c.y = y;
    return c;
}

void coordonnees_afficher(coordonnees_t c)
{
    printf("(%d,%d)\n", c.x, c.y);
}

/**
    Allouer de la m�moire de la taille d'un coup.
    Affecter les valeurs pass�es en entr�es au maillon cr��.
    @param d les coordonn�es de d�part
    @param a les coordonn�es d'arriv�
    @param promo entier bool�en pour savoir si il y a promotion
    @param capture bool�en pour une �ventuelle capture
    @return un coup initialis�
 */
coup_t* coup_creer(coordonnees_t d, coordonnees_t a, int promo, int capture)
{
	coup_t *res =(coup_t*)malloc(sizeof(coup_t));
	res->depart = d;
	res->arrive = a;
	res->capture = capture;
	res->promo = promo;

    return res;
}

/**
    Liberer le coup
    @param coup un coup
 */
    void coup_detruire(coup_t *c)
{
	free(c);
}
/**
    Allouer de la m�moire de la taille d'un maillon.
    Allouer de la m�moire de la taille d'un coup du maillon.
    Affecter les valeurs pass�es en entr�es au maillon cr��.
    @param coup le coup du maillon
    @return un maillon initialis�
 */
maillon_t* maillon_creer(coup_t *c)
{
    maillon_t* res = (maillon_t*)malloc(sizeof(maillon_t));
 	res->coup = c;
	res->precedent = NULL;
    res->suivant = NULL;

    return res;
}

/**
    Liberer le coup du maillon puis liberer le maillon
    @param m un maillon
 */
void maillon_detruire(maillon_t* m)
{
	coup_detruire(m->coup);
	free(m);
}

/**
    Afficher le maillon pass� en entr�.
    @param m un maillon
 */
void maillon_afficher(maillon_t m)
{
    coordonnees_afficher(m.coup->depart);
    coordonnees_afficher(m.coup->arrive);

    printf("%d %d", m.coup->promo, m.coup->capture);
}

/**
    Allouer de la m�moire de la taille d'une liste.
    @return un pointeur sur la liste
 */
liste_t* liste_initialiser()
{
    liste_t* res = malloc(sizeof(liste_t));
    res->debut = NULL;
    res->fin = NULL;
    res->taille = 0;

    return res;
}

/**
        Tester si la taille de la liste est nulle
        @param l une liste
        @return TRUE si nulle, FALSE sinon
*/
int liste_vide(liste_t l)
{
    if(l.taille == 0)
        return TRUE;
    return FALSE;
}

/**
    Extraire un maillon qui se situe au debut de la liste si la liste n'est pas vide
    Remplacer le debut de liste par le maillon suivant du maillon extrait
    Decrementer la taille de la liste
        - Si la liste est encore non_vide, le precedent du nouveau maillon debut devient nul
        - Sinon la fin de la liste est vide
    @param l une liste
    @return le maillon extrait
*/
maillon_t* liste_extraire_debut(liste_t *l)
{
	maillon_t * res = l->debut;
	if(!liste_vide(*l))
	{
    	l->debut=res->suivant;
    	res->suivant=NULL;
    	l->taille--;
        if(!liste_vide(*l))
			l->debut->precedent=NULL;
        else l->fin = NULL;
	}
    return res;
}

maillon_t* liste_extraire_fin(liste_t *l)
{
	maillon_t* res = l->fin;
	if(!liste_vide(*l))
	{
		l->fin = res->precedent;
		res->precedent = NULL;
		l->taille--;
		if(!liste_vide(*l))
			l->fin->suivant = NULL;
		else l->debut = NULL;
	}
	
	return res;
}

/**
    Liberer les maillons de la liste tant que la liste n'est pas vide, puis liberer la liste
    @param l une liste
 */
void liste_detruire(liste_t *l)
{
    while(!liste_vide(*l))
	{
    		maillon_detruire(liste_extraire_debut(l));

	}
    free(l);
}

/**
    Ajouter un maillon au debut de la liste, le maillon devient le debut de la liste
    Incr�menter la taille de la liste
        - Si la liste est vide, la fin de la liste est le maillon ajout�
        - Sinon le maillon suivant du maillon ajout� et le ancien debut de la liste
          Le precedent du ancien debut de la liste est le maillon ajout�
    @param l une liste
    @param m un maillon
*/
void liste_ajouter_debut(liste_t *l, maillon_t *m)
{
	if(liste_vide(*l))
	{
		l->fin=m;
    }
	else
	{
	    m->suivant=l->debut;
		l->debut->precedent= m;
	}
	l->debut=m;
	l->taille++;
}

/**
    Ajouter un maillon au debut de la liste, le maillon devient le debut de la liste
    Incr�menter la taille de la liste
        - Si la liste est vide, la fin de la liste est le maillon ajout�
        - Sinon le maillon suivant du maillon ajout� et le ancien debut de la liste
          Le precedent du ancien debut de la liste est le maillon ajout�
    @param l une liste
    @param m un maillon
*/
void liste_ajouter_fin(liste_t *l, maillon_t *m)
{
	if(liste_vide(*l))
	{
		l->debut=m;
    }
	else
	{
	    m->precedent=l->fin;
		l->fin->suivant= m;
	}
	l->fin=m;
	l->taille++;
}

