/* deplacement.c

date de création: 01/04/2017
*/

#include "deplacement.h"

/**
    On vérifie il s'agit de quel joueur, si il a capturé une piece ou non et si il y a promotion.
    Pour chaque cas, on stock dans notre liste le coups joué.
    On met dans sa réserve la pièce éventuellemnt capturé.

    @param *p un pointeur sur une partie
    @param d les coordonnées de départ
    @param a les coordonnées d'arrivé
 */
void deplacement(partie_t *p, coordonnees_t d, coordonnees_t a)
{
	/* SI LE COUP PROVIENT DE LA RESERVE */
	if(RESERVE)
	{
		liste_ajouter_debut(p->CoupsJoues, maillon_creer(coup_creer(d, a, NON_PROMU, FALSE)));

		/* on va supprimer la piece de la réserve */
		if(p->joueur == JOUEUR_1)
			tab_reserve_supprimer(p->reserve_joueur_1, p->tablier[d.x][d.y]);
		else
			tab_reserve_supprimer(p->reserve_joueur_2, p->tablier[d.x][d.y]);
		p->tablier[d.x][d.y].statut = NON_PROMU;
	}

	/* ICI ON GERE LES PROMOTIONS */
	if(case_vide(*p, a) == TRUE)
	{
		if(!RESERVE)
		{
			/* si il est dans la zone de promo du joueur 1 et c'est le joueur 1 qui joue, la pièce est promu. idem pour le joueur 2 */
			if(((ZONE_PROMO_1 && p->joueur == JOUEUR_1) || (ZONE_PROMO_2 && p->joueur == JOUEUR_2))
                && p->tablier[d.x][d.y].statut == NON_PROMU)
			{
					liste_ajouter_debut(p->CoupsJoues, maillon_creer(coup_creer(d, a, PROMU, FALSE)));
					PROMOTION;
			}
			else
				liste_ajouter_debut(p->CoupsJoues, maillon_creer(coup_creer(d, a, NON_PROMU, FALSE)));
		}
	}

	/* ICI ON GERE LES CAPTURES */
	else if(case_vide(*p, a) == FALSE)
	{
		/* On ajoute la pièce dans la réserve */
		if(p->joueur == JOUEUR_1)
		{
			p->tablier[a.x][a.y].joueur = JOUEUR_1;
			tab_reserve_ajouter(p->reserve_joueur_1, p->tablier[a.x][a.y]);
		}
		else
		{
		    p->tablier[a.x][a.y].joueur = JOUEUR_2;
			tab_reserve_ajouter(p->reserve_joueur_2, p->tablier[a.x][a.y]);
		}
		/* Meme chose sauf que capture vaut TRUE. */
		if(((ZONE_PROMO_1 && p->joueur == JOUEUR_1) || (ZONE_PROMO_2 && p->joueur == JOUEUR_2))
             && p->tablier[d.x][d.y].statut == NON_PROMU)
		{

				liste_ajouter_debut(p->CoupsJoues, maillon_creer(coup_creer(d, a, PROMU, TRUE)));
				PROMOTION;
		}
		else
			liste_ajouter_debut(p->CoupsJoues, maillon_creer(coup_creer(d, a, NON_PROMU, TRUE)));

	}
    /* on modifie le tablier */
    modifier_case(p, p->tablier[d.x][d.y], a);
    p->tablier[d.x][d.y] = piece_creer(JOUEUR_VIDE, VIDE, NON_PROMU);
}


/**
	Annule le coup précédent.

	D'abord on extrait le dernier coup.
	Si il y avait capture le coup précédent, on remet la pièce capturé sur le terrain. Sinon on a juste à placer une pièce vide sur la coordoonnée d'arrivé.
	Si le coup était un parachutage, alors on lui retire sa promotion ou pas après vérification de son statut.
 */
void annuler_deplacement(partie_t *partie)
{
  /* Si la liste de coups est vide */
  if(!liste_vide(*partie->CoupsJoues))
  {
    maillon_t *m = liste_extraire_debut(partie->CoupsJoues);
	/* Si le coup d'avant était un drop du joueur 1, on la remet dans sa reserve */
	if(m->coup->depart.x == 10 || m->coup->arrive.y == 0)
	{
		if(m->coup->piece.statut == PROMU)
			partie->tablier[m->coup->arrive.x][m->coup->arrive.y].statut = PROMU;
		tab_reserve_ajouter(partie->reserve_joueur_1, partie->tablier[m->coup->arrive.x][m->coup->arrive.y]);

	}
	/* Si le coup était un dop du joueur 2, idem */
	else if(m->coup->depart.x == 0 || m->coup->arrive.y == 10)
	{
		if(m->coup->piece.statut == PROMU)
			partie->tablier[m->coup->arrive.x][m->coup->arrive.y].statut = PROMU;
		tab_reserve_ajouter(partie->reserve_joueur_2, partie->tablier[m->coup->arrive.x][m->coup->arrive.y]);
	}

	/* Si la pièce a été PROMU le coup précédent, alors on le retire sa promo. */
	if(m->coup->promo == PROMU)
		partie->tablier[m->coup->arrive.x][m->coup->arrive.y].statut = NON_PROMU;

    modifier_case(partie, partie->tablier[m->coup->arrive.x][m->coup->arrive.y], m->coup->depart);
	/* Si il n'y a pas de capture */
    if(m->coup->capture == FALSE)
    	partie->tablier[m->coup->arrive.x][m->coup->arrive.y] = piece_creer(JOUEUR_VIDE, VIDE, NON_PROMU);
	/* Si il y a capture */
    else
	{
		if(partie->joueur == JOUEUR_1)
		{
			 partie->tablier[m->coup->arrive.x][m->coup->arrive.y] = tab_reserve_extraire(partie->reserve_joueur_2);
			 partie->tablier[m->coup->arrive.x][m->coup->arrive.y].joueur = JOUEUR_1;
		}
		else
		{

			 partie->tablier[m->coup->arrive.x][m->coup->arrive.y] = tab_reserve_extraire(partie->reserve_joueur_1);
			 partie->tablier[m->coup->arrive.x][m->coup->arrive.y].joueur = JOUEUR_2;
		}
    }
     changer_joueur(partie);
	 maillon_detruire(m);
  }
  else
    printf("Il n'y a pas de coup precedent!\n");

}

/**
    Vérifie si le déplacement du PION est valide selon le joueur.
    Le pion ne peut que avancer d'une case à la verticale.
    Si le joueur parachute un pion, on vérifie que la case est vide et
    qu'il n'y a pas d'autres pions sur la meme colonne et que ça n'est pas la dernière ligne.
	(Selon les règles du Shogi)

    @param *p un pointeur sur une partie
    @param d coordonnées de départ
    @param a coordonnées d'arrivée
    @param statut PROMU ou NON_PROMU
    @return TRUE si valide FALSE sinon
 */
int deplacement_valide_pion(partie_t p, coordonnees_t d, coordonnees_t a, int statut)
{
    switch(p.joueur)
    {
        /* si c'est le joueur 1 qui joue */
        case JOUEUR_1:
                /* si le pion est parachuté, il y a beaucoup de conditions */
                if(RESERVE_JOUEUR_1 && CASE_VIDE && pion_colonne_joueur(p, a) == FALSE && derniere_ligne(p, a) == FALSE)
                    return TRUE;
                /* si le pion avance d'une case, et si il est NON_PROMU, on renvoie TRUE */
                if(CONDITION_PION_1)
                    return TRUE;
                /* Si le pion est promu, il se déplace comme un GOLD */
                if(CONDITION_GOLD_1_P)
                    return TRUE;
        break;

        /* si il s'agit du joueur 2 */
        case JOUEUR_2:
                if(RESERVE_JOUEUR_2 && CASE_VIDE && pion_colonne_joueur(p, a) == FALSE && derniere_ligne(p, a) == FALSE)
                    return TRUE;
                if(CONDITION_PION_2)
                    return TRUE;
                if(CONDITION_GOLD_2_P)
                    return TRUE;
        break;
    }
    /* Dans tout les autres cas ça n'est pas valide */
    return FALSE;
}

/**
    Vérifie le déplacement du SILVER selon le joueur.
    Le silver peut se déplacer devant, et sur toute les diagonales mais d'une seul case.
    Ne peut pas se déplacer sur les cotés ou derrière lui.
    @param p une partie
    @param d les coordonnées de départ
    @param a les coordonnées d'arrivées
    @param statut un entier booléen PROMU ou NON_PROMU
    @return TRUE si valide FALSE sinon
 */
int deplacement_valide_silver(partie_t p, coordonnees_t d, coordonnees_t a, int statut)
{
    switch(p.joueur)
    {
        case JOUEUR_1:
            /* drop */
            if(RESERVE_JOUEUR_1 && CASE_VIDE)
                return TRUE;
            /* regular déplacement */
            if(CONDITION_SILVER_1)
                return TRUE;
            if(CONDITION_GOLD_1_P)
                return TRUE;
        break;

        case JOUEUR_2:
            /* drop */
            if(RESERVE_JOUEUR_2 && CASE_VIDE)
                return TRUE;
            /* regular déplacement */
            if(CONDITION_SILVER_2)
                return TRUE;
            if(CONDITION_GOLD_2_P)
                return TRUE;

        break;
    }
    return FALSE;
}

/**
    Vérifie la validité d'un déplacement d'un GOLD.
    Se déplace dans toutes les directions sauf les 2 diagonales en arrières.
    Ne peut pas être promu.
    @param p une partie
    @param d coordonnées de départ
    @param a coordonnées d'arrivées
    @param statut un entier PROMU ou NON_PROMU
    @return TRUE si valide et FALSE sinon

 */
int deplacement_valide_gold(partie_t p, coordonnees_t d, coordonnees_t a, int statut)
{
    switch(p.joueur)
    {
        case JOUEUR_1:
            /* drop */
            if(RESERVE_JOUEUR_1 && CASE_VIDE)
                return TRUE;
            /* regular déplacement */
            if(CONDITION_GOLD_1)
            {
                return TRUE;
            }
        break;
        case JOUEUR_2:
            /* drop */
            if(RESERVE_JOUEUR_2 && CASE_VIDE)
                return TRUE;
            /* regular déplacement */
            if(CONDITION_GOLD_2)
                return TRUE;
        break;
    }
    return FALSE;
}


/**
    Vérifie le déplacement d'un ROI.
    Un roi ne peut pas être promu ni drop.
    Le roi peut se déplacer dans toutes les directions d'une seul case.
    @param d coordonnees de départ
    @param a coordonnees d'arrivées
    @return TRUE si valide FALSE sinon
 */
int deplacement_valide_roi(coordonnees_t d, coordonnees_t a, int statut)
{
    if(ALL_DIRECTIONS && ONE_CASE)
        return TRUE;
    return FALSE;
}
/**
    Vérifie le déplacement du cavalier.
    Le cavalier se déplace seulement DEVANT LUI EN L.
    Peut sauter par dessus les pièces.
    @param p une partie
    @param d coordonnées de départ
    @param a coordonnées d'arrivées
    @return TRUE si valide FALSE sinon
 */
int deplacement_valide_cavalier(partie_t p , coordonnees_t d, coordonnees_t a, int statut)
{
    switch(p.joueur)
    {
        case JOUEUR_1:
            /* drop */
            if(RESERVE_JOUEUR_1 && CASE_VIDE && deux_derniere_ligne(p, a) == FALSE)
                return TRUE;
            /* regular déplacement */
            if(CONDITION_CAVALIER_1)
                return TRUE;
            if(CONDITION_GOLD_1_P)
                return TRUE;
        break;
        case JOUEUR_2:
            /* drop */
            if(RESERVE_JOUEUR_2 && CASE_VIDE && deux_derniere_ligne(p, a) == FALSE)
                return TRUE;
            /* regular déplacement */
            if(CONDITION_CAVALIER_2)
                return TRUE;
            if(CONDITION_GOLD_2_P)
                return TRUE;
        break;
    }
    return FALSE;
}

/**
    Vérifie le déplacement de la tour.
    La tour peut se déplacer sur les lignes et colonnes du tablier sans problème.
    Une fois PROMU, comme le fou il garde ces capacités et peut se déplacer comme le roi.
    Cela fait de la tour la pièce la plus puissante et utile du jeu.
    Ne peut pas traverser les pièces.
    @param p une partie
    @param d coordonnées de départ
    @param a coordonnées d'arrivées
    @return TRUE si valide FALSE sinon
 */
int deplacement_valide_tour(partie_t p, coordonnees_t d, coordonnees_t a, int statut)
{
    switch(p.joueur)
    {
        case JOUEUR_1:
            if(RESERVE_JOUEUR_1 && CASE_VIDE)
                return TRUE;
            if(CONDITION_TOUR)
                return TRUE;
            if(CONDITION_TOUR_P)
                return TRUE;
        break;
        case JOUEUR_2:
            if(RESERVE_JOUEUR_2 && CASE_VIDE)
                return TRUE;
            if(CONDITION_TOUR)
                return TRUE;
            if(CONDITION_TOUR_P)
                return TRUE;
        break;
    }
    return FALSE;
}
/**
    Vérifie le déplacement de la lance.
    La lance peut seulement attaquer devant elle, mais sans limite de cases.
    Ne peut pas traverser les pièces.
    @param p une partie
    @param d coordonnées de départ
    @param a coordonnées d'arrivées
    @return TRUE si valide FALSE sinon
 */
int deplacement_valide_lance(partie_t p, coordonnees_t d, coordonnees_t a, int statut)
{
    switch(p.joueur)
    {
        case JOUEUR_1:
            if(RESERVE_JOUEUR_1 && CASE_VIDE && derniere_ligne(p, a) == FALSE)
                return TRUE;
            if(CONDITION_LANCE_1)
                return TRUE;
            if(CONDITION_GOLD_1_P)
                return TRUE;
		break;
        case JOUEUR_2:
            if(RESERVE_JOUEUR_2 && CASE_VIDE && derniere_ligne(p, a) == FALSE)
                return TRUE;
            if(CONDITION_LANCE_2)
                return TRUE;
            if(CONDITION_GOLD_2_P)
                return TRUE;
        break;
    }
    return FALSE;
}

/**
    Vérifie le déplacement du fou.
    Le fou peut seulement se déplacer en diagonale, mais sans limite.
    Une fois PROMU, il peut se déplacer comme le roi en plus d'avoir ces capacités d'attaques diagonales.
    Ne peut pas traverser les pièces.
    @param p une partie
    @param d les coordonnées de départ
    @param a les coordonnées d'arrivées
    @param statut un entier PROMU ou NON_PROMU
    @return TRUE si valide et FALSE sinon
 */
int deplacement_valide_fou(partie_t p, coordonnees_t d, coordonnees_t a, int statut)
{
    int difference_x = d.x - a.x;
    int difference_y = d.y - a.y;

    switch(p.joueur)
    {
        case JOUEUR_1:
            if(RESERVE_JOUEUR_1 && CASE_VIDE)
                return TRUE;
            if(CONDITION_FOU)
                return TRUE;
            if(CONDITION_FOU_P)
                return TRUE;
        break;

        case JOUEUR_2:
            if(RESERVE_JOUEUR_2 && CASE_VIDE)
                return TRUE;
            if(CONDITION_FOU)
                return TRUE;
            if(CONDITION_FOU_P)
                return TRUE;
        break;
    }
    return FALSE;
}

/**
    Vérifie si le déplacement de n'importe quel pièce est valide.
    Appelle la fonction adéquate selon la pièce qui veut être déplacé.
    Cette fonction est la base du jeu de Shogi.
    @param p une partie
    @param d les coordonnees de départ
    @param a les coordonnees d'arrivées
    @param type un entier qui désigne le type de pièce manipulé
    @param statut un entier PROMU ou NON_PROMU
    @return TRUE si le déplacement est valide et FALSE sinon
 */
int deplacement_valide(partie_t p, coordonnees_t d, coordonnees_t a, int type, int statut)
{
    if(arrive_valide(a) && !SURPLACE && !TEAMKILL)
    {
        switch(type)
        {
            case PAWN:
                return deplacement_valide_pion(p, d, a, statut);
            break;
            case LANCE:
                return deplacement_valide_lance(p, d, a, statut);
            break;
            case KNIGHT:
                return deplacement_valide_cavalier(p, d, a, statut);
            break;
            case BISHOP:
                return deplacement_valide_fou(p, d, a, statut);
            break;
            case ROOK:
                return deplacement_valide_tour(p, d, a, statut);
            break;
            case SILVER:
                return deplacement_valide_silver(p, d, a, statut);
            break;
            case GOLD:
                return deplacement_valide_gold(p, d, a, statut);
            break;
            case KING:
                return deplacement_valide_roi(d, a, statut);
            break;
        }
    }
    return FALSE;
}
/*
    -------------------------------------------------------------------
    -------------------------------------------------------------------
    -------------------------------------------------------------------
    -------------------------------------------------------------------
    -------------------------------------------------------------------
*/

/**
    @param arrive les coordonnées d'arrivées
    @return un booléen TRUE si l'arrivé est valide et FALSE sinon
 */
int arrive_valide(coordonnees_t arrive)
{
    if(arrive.x > 0 && arrive.x < 10 && arrive.y > 0 && arrive.x < 10)
        return TRUE;
    return FALSE;
}


/**
    @param p une partie
    @param arrive les coordonnées d'arrivées
    @return un booléen TRUE si il y a un pion du même joueur sur la colonne d'arrivée et FALSE sinon
 */
int pion_colonne_joueur(partie_t p, coordonnees_t arrive)
{
    int i;
    piece_t pion = piece_creer(p.joueur, PAWN, NON_PROMU);
    for(i = 1; i < NB_LIGNE - 1; i++)
    {
        if(cmp_piece(p.tablier[i][arrive.y], pion) == TRUE)
            return TRUE;
    }
    return FALSE;
}

/**
    Selon le joueur,
    Regarde si les coordonnées d'arrivées se situent sur la dernière ligne.
    @param p une partie
    @param arrive les coordonnées d'arrivées
    @return un booléen TRUE si la pièce se trouve sur la dernière ligne
 */
int derniere_ligne(partie_t p, coordonnees_t arrive)
{
    if(p.joueur == JOUEUR_1)
    {
        if(arrive.x == 1)
            return TRUE;
    }

    if(p.joueur == JOUEUR_2)
    {
        if(arrive.x == 9)
            return TRUE;
    }
    return FALSE;
}

/**
    Cette fonction sert seulement pour le cavalier.
    Il n'a pas le droit d'être parachuté sur l'une des 2 dernières lignes.

    @param p une partie
    @param a les coordonnées d'arrivées
 */
int deux_derniere_ligne(partie_t p, coordonnees_t a)
{
    if(p.joueur == JOUEUR_1)
    {
        if(a.x <= 2)
            return TRUE;
    }

    if(p.joueur == JOUEUR_2)
    {
        if(a.x >= 8)
            return TRUE;
    }
    return FALSE;
}
/**
    Vérifie si il y a une pièce qui bloque.

    @param p une partie
    @param d les coordonnées de départ
    @param a les coordonnées d'arrivées
    @return TRUE si il n'y a pas de bloquage et FALSE sinon
 */
int piece_sur_chemin_tour(partie_t p, coordonnees_t d, coordonnees_t a)
{
    int i;
    coordonnees_t c;
    /* si il se déplace en colonne */
    if(MEME_COLONNE)
    {
        /* si il va vers le haut */
        if(HAUT_D)
        {
            /* boucle qui regarde si il y a une pièce sur le chemin */
            for(i = d.x - 1; i > a.x; i--)
            {
                c = coordonnees_creer(i, a.y);
                if(CASE_NON_VIDE)
                    return TRUE;
            }
        }
        /* si il va vers le bas */
        if(BAS_D)
        {
            for(i = d.x + 1; i < a.x; i++)
            {
                c = coordonnees_creer(i, a.y);
                if(CASE_NON_VIDE)
                    return TRUE;
            }
        }
    }
    /* si il se déplace en ligne */
    if(MEME_LIGNE)
    {
        /* si il va vers la gauche */
        if(GAUCHE_D)
        {
            for(i = d.y - 1; i > a.y; i--)
            {
                c = coordonnees_creer(a.x, i);
                if(CASE_NON_VIDE)
                    return TRUE;
            }
        }

        /* si il va vers la droite */
        if(DROITE_D)
        {
            for(i = d.y + 1; i < a.y; i++)
            {
                c = coordonnees_creer(a.x, i);
                if(CASE_NON_VIDE)
                    return TRUE;
            }
        }
    }
    return FALSE;
}

/**
    Vérifie si il n'y a pas de pièces sur le chemin de la lance.
    La lance ne peut pas attaquer à travers d'autres pièces, comme la tour et le fou.

    @param p une partie
    @param d les coordonnées de départ
    @param a les coordonnées d'arrivées
    @return TRUE si sa bloque et FALSE sinon
 */
int piece_sur_chemin_lance(partie_t p, coordonnees_t d, coordonnees_t a)
{
    int i;
    coordonnees_t c;
    switch(p.joueur)
    {
        case JOUEUR_1:
            /* si il va vers le haut */
            if(HAUT_D)
            {
                for(i = d.x - 1; i > a.x; i--)
                {
                    c = coordonnees_creer(i, a.y);
                    if(CASE_NON_VIDE)
                        return TRUE;
                }
            }
        break;
        case JOUEUR_2:
            /* si il va vers le bas */
            if(BAS_D)
            {
                for(i = d.x + 1; i < a.x; i++)
                {
                    c = coordonnees_creer(i, a.y);
                    if(CASE_NON_VIDE)
                        return TRUE;
                }
            }
    }
    return FALSE;
}

int valeur_absolue(int a)
{
    if(a < 0)
        return -a;
    return a;
}

/**
    Vérifie si il n'y pas de pièces sur le déplacement du fou.
    On ne peut pas attaquer les pièces derrière d'autre pièces.
    Seul le cavalier peut sauter par dessus les pièces.

    @param p une partie
    @param d les coordonnées de départ
    @param a les coordonnées d'arrivées
    @return TRUE si il y a une pièce qui bloque et FALSE sinon
 */
int piece_sur_chemin_fou(partie_t p, coordonnees_t d, coordonnees_t a)
{
    int i;
    int j;
    coordonnees_t c;

    /* si il se déplace vers en haut à gauche */
    if(DIAGONALE_UP_LEFT_D)
    {
        /* on vérifie chaques cases entre le fou et les coordonnées de déplacement */
        for(i = d.x - 1, j = d.y - 1; i > a.x && j > a.y; i--, j--)
        {
            c = coordonnees_creer(i, j);
            if(CASE_NON_VIDE)
                return TRUE;
        }
    }
    /* direction en haut à droite */
    if(DIAGONALE_UP_RIGHT_D)
    {
        for(i = d.x - 1, j = d.y + 1; i > a.x && j < a.y; i--, j++)
        {
            c = coordonnees_creer(i, j);
            if(CASE_NON_VIDE)
                return TRUE;
        }
    }
    /* direction en bas à gauche */
    if(DIAGONALE_DOWN_LEFT_D)
    {
        for(i = d.x + 1, j = d.y - 1; i < a.x && j > a.y; i++, j--)
        {
            c = coordonnees_creer(i, j);
            if(CASE_NON_VIDE)
                return TRUE;
        }
    }
    /* direction en bas à droite */
    if(DIAGONALE_DOWN_RIGHT_D)
    {
        for(i = d.x + 1, j = d.y + 1; i < a.x && j < a.y; i++, j++)
        {
            c = coordonnees_creer(i, j);
            if(CASE_NON_VIDE)
                return TRUE;
        }
    }

    return FALSE;
}
