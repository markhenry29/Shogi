/* piece.c
----------------


date de création: 22/03/2107.
*/
#include "partie.h"


/**
    @param p une partie
    @param x un entier
    @param y un entier
    @return TRUE si la case du tablier est vide et FALSE sinon
 */
int case_vide(partie_t p, coordonnees_t c)
{
    if(p.tablier[c.x][c.y].type == VIDE)
        return TRUE;
    return FALSE;
}


/**
    Affecte la pièce à l'une des case du tablier.
 */
void modifier_case(partie_t *p, piece_t piece, coordonnees_t c)
{
    p->tablier[c.x][c.y] = piece;
}

/**
    Change de joueur.
    Si c'est le joueur 1 qui joue, ce sera maintenant le joueur 2 et vice versa.
    @param *p un pointeur sur une partie
 */
void changer_joueur(partie_t *p)
{
    if(p->joueur == JOUEUR_1)
        p->joueur = JOUEUR_2;

    else if(p->joueur == JOUEUR_2)
        p->joueur = JOUEUR_1;
}
/**
    Affiche le plateau du jeu à la console.
    @param *p un pointeur sur une partie
 */
void afficher_plateau(partie_t *p)
{
    int i, j;
    afficher_reserve(p);
    printf(" \t");
  /* Coordonnées horizontales */
    for(i = 0; i <NB_COLONNE; i++)

    {
        printf("%d  ",i);
    }
    printf("\n\n"); /* Pour la premiere coordonee verticale */

  /* On affiche maintenant les pièces */
    for(i = 0;i< NB_LIGNE;i++)
    {
        printf("%d  ",i);/* Coordonnées verticales */
        printf("\t");
        for(j = 0; j < NB_COLONNE; j++)
        {
            piece_afficher(p->tablier[i][j]);
            printf("  ");
        }
        printf("\n");
    }
}




coordonnees_t saisie_case()
{
    coordonnees_t res;
    printf("Saisir une case : Abscisse x, Ordonnee y compris entre 0 et 10\n");
    do
    {
        printf("Abscisse x: ");
        scanf("%d", &res.x);
        printf("Ordonnee y: ");
        scanf("%d", &res.y);
    }
    while((res.x > NB_LIGNE-1 || res.y > NB_COLONNE-1 || res.x < 0 || res.y < 0));

    return res;
}


partie_t * partie_creer()
{
    int i;
    partie_t *res = (partie_t*)malloc(sizeof(partie_t));
    res->tablier = (piece_t**)malloc(NB_LIGNE*sizeof(piece_t*));
    for(i=0;i<NB_LIGNE;i++)
    {
        res->tablier[i] = malloc(NB_COLONNE*sizeof(piece_t));
    }
    res->CoupsJoues = liste_initialiser();
    res->reserve_joueur_1 = creer_tab_reserve();
    res->reserve_joueur_2 = creer_tab_reserve();

    return res;
}

void init_tablier(partie_t * partie)
{
    int i,j;
	    /*INIT PIECES*/
    for(i=0;i<NB_LIGNE;i++)
    {
        for(j=0;j<NB_COLONNE;j++)
        {
            partie->tablier[i][j].type = VIDE;
            partie->tablier[i][j].joueur = JOUEUR_VIDE;
            partie->tablier[i][j].statut = NON_PROMU;
        }
    }

    for(j=1;j<=9;j++)
    {
        partie->tablier[3][j].type = PAWN;
        partie->tablier[3][j].joueur = JOUEUR_2;
        partie->tablier[7][j].type = PAWN;
        partie->tablier[7][j].joueur = JOUEUR_1;
    }

    /*JOUEUR 2*/
    partie->tablier[1][1].type= LANCE;
    partie->tablier[1][2].type= KNIGHT;
    partie->tablier[1][3].type= SILVER;
    partie->tablier[1][4].type= GOLD;
    partie->tablier[1][5].type= KING;
    partie->tablier[1][6].type= GOLD;
    partie->tablier[1][7].type= SILVER;
    partie->tablier[1][8].type= KNIGHT;
    partie->tablier[1][9].type= LANCE;

    partie->tablier[2][2].type= ROOK;
    partie->tablier[2][2].joueur= JOUEUR_2;
    partie->tablier[2][8].type= BISHOP;
    partie->tablier[2][8].joueur= JOUEUR_2;

     for(j=1;j<=9;j++)
    {
        partie->tablier[1][j].joueur= JOUEUR_2;
    }


    /*JOUEUR 1*/
    partie->tablier[9][1].type= LANCE;
    partie->tablier[9][2].type= KNIGHT;
    partie->tablier[9][3].type= SILVER;
    partie->tablier[9][4].type= GOLD;
    partie->tablier[9][5].type= KING;
    partie->tablier[9][6].type= GOLD;
    partie->tablier[9][7].type= SILVER;
    partie->tablier[9][8].type= KNIGHT;
    partie->tablier[9][9].type= LANCE;

    partie->tablier[8][8].type= ROOK;
    partie->tablier[8][8].joueur= JOUEUR_1;
    partie->tablier[8][2].type= BISHOP;
    partie->tablier[8][2].joueur= JOUEUR_1;

    for(j=1;j<=9;j++)
    {
        partie->tablier[9][j].joueur= JOUEUR_1;
    }
}

void partie_detruire(partie_t *p)
{
    int i;
    detruire_tab_reserve(p->reserve_joueur_1);
    detruire_tab_reserve(p->reserve_joueur_2);
	liste_detruire(p->CoupsJoues);
    for(i=0;i<NB_LIGNE; i++)
    {
        free(p->tablier[i]);
    }
    free(p->tablier);
    free(p);
}

void partie_jouer(partie_t *p)
{
  int n;
  int game = TRUE;
  coordonnees_t a;
  coordonnees_t d;
  afficher_plateau(p);



  while (game)
    {
		n=0;
        printf("\nTour: Joueur %d\n", p->joueur);
		do
    	{
    		printf("Pour Jouer: Entrez 1\nPour Annuler le coup precedent: Entrez 2 \nPour Quitter : Entrez 3\n ");
    		scanf("%d",&n);
    	}
    	while(n==0);
        if (n==1)
	{
        	printf("Choisissez une piece pour jouer!\n");
        	d = saisie_case();
       		printf("Choisissez la case d'arrivee!\n");
        	a = saisie_case();
		if(deplacement_valide(*p, d, a, p->tablier[d.x][d.y].type, p->tablier[d.x][d.y].statut) && !MIND_CONTROL)
            	{
			printf("\n");
                	deplacement(p, d, a);

                	if(partie_echec(*p) == INVALIDE)
                    {
                        printf("DEPLACEMENT INVALIDE !\n");
                        changer_joueur(p);
                        annuler_deplacement(p);
                        changer_joueur(p);
                    }
                    afficher_plateau(p);

                    if(partie_echec(*p) == ECHEC)
                    {
                        printf("ECHEC AU ROI !\n");

                        /*if(partie_mat(*p) == MAT)
                            printf("MAT !");*/
                    }

                	changer_joueur(p);
            	}
	 	else
     		{	printf("\n");
           		afficher_plateau(p);
	       		printf("Deplacement non valide. Reessayez.\n");
     		}
	}
	else if (n==2)
	     {
	 		annuler_deplacement(p);
			afficher_plateau(p);
         }
    else if (n==3)
		{
			int save,save_type;
			int save_boucle = TRUE;
			printf("Partie Quittee!\n");
			printf("Voulez vous sauvegarder? Si Oui :Entrez 1\n");
			scanf("%d",&save);
			if(save==1)
			{

				while(save_boucle)
				{
					printf("Voulez vous sauvegarder le plateau seulement ou la partie en cours?\n");
					printf("Pour le plateau : Entrez 1\n");
					printf("Pour la partie : Entrez 2\n");
					scanf("%d",&save_type);
					if(save_type== 1)
						{
							char nom_du_fichier[30];
							printf("Entrez le nom du sauvegarde: ");
							scanf("%s",nom_du_fichier);
							partie_sauvegarder(p,nom_du_fichier);
							printf("\nPlateau sauvegarde!\n");
							save_boucle = FALSE;
							game = FALSE;
						}
					else if (save_type== 2)
						{
							char nom_du_fichier[30];
							printf("Entrez le nom du sauvegarde: ");
							scanf("%s",nom_du_fichier);
							replay_sauvegarder(p,nom_du_fichier);
							printf("\nPartie sauvegardee!\n");
							save_boucle = FALSE;
							game = FALSE;
						}
				}

			}
			else
				{
					game = FALSE;
				}
		}
    }
    printf("Au revoir!\n");


}



/**
    Affiche la réserve de chaque joueur.
    met à jour la réserve à chaque fois qu'on appelle cette fonction

    @param *p un pointeur sur une partie
 */
void afficher_reserve(partie_t *p)
{
	int i;
	int index_reserve_1 = 0;
	int index_reserve_2 = 0;
	/* Joueur1 */
	for(i=1;i<NB_LIGNE;i++)
	{
			p->tablier[10][i] = p->reserve_joueur_1->tab_reserve[index_reserve_1];
			index_reserve_1++;
	}
	for(i=1;i<NB_COLONNE-1;i++)
	{
			p->tablier[i][10] = p->reserve_joueur_1->tab_reserve[index_reserve_1];
			index_reserve_1++;
	}

	/* Joueur2 */
	for(i=0;i<NB_COLONNE-1;i++)
	{
			p->tablier[0][i] = p->reserve_joueur_2->tab_reserve[index_reserve_2];
			index_reserve_2++;
	}
	for(i=1;i<NB_LIGNE-1;i++)
	{
			p->tablier[i][0] = p->reserve_joueur_2->tab_reserve[index_reserve_2];
			index_reserve_2++;
	}
}


void partie_sauvegarder(partie_t *p, char* s)
{
	FILE* fichier = NULL;
	int i,j;
	char dossier[100] = "Plateaux/";
	char *concat1= strcat(dossier,s);
	char * nom_du_fichier = strcat(concat1,".plt"); /*Concat "Plateaux + nom + .plt"*/
	fichier = fopen(nom_du_fichier, "w");
	if(fichier != NULL)
	{
		fprintf(fichier, "PL\n");
		for(i=0; i<NB_LIGNE; i++)
		{
			for(j = 0; j < NB_COLONNE; j++)
			{
				fputc(piece_caractere(p->tablier[i][j]), fichier);
			}
			fprintf(fichier, "\n");
		}
		fclose(fichier);
	}
	else
		printf("ERREUR: Impossible d'ouvrir le fichier ou fichier introuvable");
}

void ajouter_reserve_chargement(partie_t* res)
{
	int i;
	for(i=1;i<NB_LIGNE;i++)
   	{
		if(res->tablier[10][i].type != VIDE)
			tab_reserve_ajouter(res->reserve_joueur_1,res->tablier[10][i]);
    }
	for(i=1;i<NB_COLONNE-1;i++)
    {
		if(res->tablier[i][10].type != VIDE)
			tab_reserve_ajouter(res->reserve_joueur_1,res->tablier[i][10]);
   	}
	for(i=0;i<NB_COLONNE-1;i++)
    {
		if(res->tablier[0][i].type != VIDE)
			tab_reserve_ajouter(res->reserve_joueur_2,res->tablier[0][i]);
   	}
	for(i=1;i<NB_LIGNE-1;i++)
   	{
		if(res->tablier[i][0].type != VIDE)
			tab_reserve_ajouter(res->reserve_joueur_2,res->tablier[i][0]);
    }
}

partie_t* partie_charger(char* s)
{
    FILE * fichier = NULL;
	char format_fichier[3];
    int i, j;
    partie_t *res = partie_nouvelle();
    fichier = fopen(s,"r+");
    if(fichier != NULL)
    {
		char c;
		fread(&format_fichier, sizeof(char), 2, fichier);
		fgetc(fichier);/*saut de ligne*/
		for(i=0;i<NB_LIGNE;i++)
    	{
        	for(j=0; j<NB_COLONNE; j++)
        	{
         		 c = fgetc(fichier);
         		 res->tablier[i][j] = piece_identifier(c);
       		 }
        	fgetc(fichier);
    	}

				/*ajout des pieces reserves*/
   		ajouter_reserve_chargement(res);
	}
	else
		printf("ERREUR: Impossible d'ouvrir le fichier ou fichier introuvable\n");

	fclose(fichier);
    return res;
}

partie_t* partie_nouvelle()
{
   partie_t *partie = partie_creer();
   init_tablier(partie);
   partie->joueur = JOUEUR_1;
   return partie;
}

void replay_sauvegarder(partie_t *p, char *s)
{

  maillon_t *m;
  FILE *f;
  char dossier[100] = "Parties/";
  char *concat1= strcat(dossier,s);
  char * nom_du_fichier = strcat(concat1,".part");/*Concat "Plateaux + nom + .part"*/
  if((f=fopen(nom_du_fichier, "w")) != NULL)
    {
        fprintf(f, "PR\n");
        for(m = p->CoupsJoues->fin; m != NULL; m = m->precedent)
        {
            fprintf(f, "%d %d %d %d %d %d", m->coup->depart.x, m->coup->depart.y, m->coup->arrive.x, m->coup->arrive.y,
m->coup->capture, m->coup->promo);
			if(m != p->CoupsJoues->debut)
				fprintf(f,"\n");
        }

    printf("Sauvegarde reussie\n");
    }
   else
    printf("Echec de la sauvegarde\n");
   fclose(f);

}

liste_t* replay_charger(char * s)
{
  int tab[6];
  char format_fichier[3];
  FILE *f;
  maillon_t *m;
  coordonnees_t d, a;
  liste_t *l;
  l = liste_initialiser();
  f = fopen(s,"r+");
  if(f !=NULL)
  {
    fread(&format_fichier, sizeof(char), 2, f);
	fgetc(f);/*saut de ligne*/
  	while(!feof(f))
  	{
   	 	fscanf(f, "%d %d %d %d %d %d", &tab[0], &tab[1], &tab[2], &tab[3], &tab[4], &tab[5]);
    	d = coordonnees_creer(tab[0], tab[1]);
   	 	a = coordonnees_creer(tab[2], tab[3]);
		m = maillon_creer(coup_creer(d, a, tab[4], tab[5]));
    	liste_ajouter_debut(l,m);
  	}
	fclose(f);
  }
  return l;
}

void replay_jouer(partie_t *p,char *s)
{
	int i,taille;
	liste_t* l;
	l =replay_charger(s);
	taille = l->taille;
 	for(i=0;i<taille;i++)
	{
		maillon_t *m;
    	m = liste_extraire_fin(l);
    	deplacement(p, m->coup->depart, m->coup->arrive);
		changer_joueur(p);
		maillon_detruire(m);
 	}
	liste_detruire(l);
	partie_jouer(p);

}

/**
    Vérifie si le roi ennemi est en echec, et aussi son propre roi.
    Le joueur ne peut pas se mettre en echec par lui même, le coup est invalide.(INVALIDE)

    @param p une partie
    @return ECHEC si il y a echec, INVALIDE si le joueur tente de se suicider, et FALSE sinon.
*/
int partie_echec(partie_t p)
{
    int i;
    int j;
    coordonnees_t r1 = coordonnees_roi(p, JOUEUR_1);
    coordonnees_t r2 = coordonnees_roi(p, JOUEUR_2);
    coordonnees_t c;

    /* on parcourt le tablier. */
    for(i = 1; i < NB_LIGNE - 1; i++)
    {
        for(j = 1; j < NB_COLONNE - 1; j++)
        {
            c = coordonnees_creer(i, j);
            /* Si le roi du joueur 2 est en echec, alors... */
            if(CONDITION_ECHEC_ROI_2)
                {
                    if(p.joueur == JOUEUR_1)
                        return ECHEC;
                    if (p.joueur == JOUEUR_2)
                        return INVALIDE;
                }
            /* Si le roi du joueur 1 est en echec... */
            else if(CONDITION_ECHEC_ROI_1)
                {
                    if(p.joueur == JOUEUR_2)
                        return ECHEC;
                        /* si c'est le joueur 1 qui joue alors le coup sera interdit. */
                    if (p.joueur == JOUEUR_1)
                        return INVALIDE;
                }
        }
    }

    return FALSE;
}


/*
int partie_mat(partie_t p)
{
	int i;
	int compteur = 0;
	coordonnees_t r;
	coordonnees_t d;
	coordonnees_t a;
	if(p.joueur == JOUEUR_1)
        r = coordonnees_roi(p, JOUEUR_2);
    else
        r = coordonnees_roi(p, JOUEUR_1);
*/
	/* RIGHT UPRIGHT UP UPLEFT... (cercle trigo)  */
 /*   int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
	int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

	printf("blabla\n");
	for(i = 0; i < 8; i++)
    {
        d = coordonnees_creer(r.x, r.y);
        a = coordonnees_creer(r.x + dx[i], r.y + dy[i]);

        if(deplacement_valide(p, d, a, KING, NON_PROMU) == FALSE)
        {
            compteur++;
            continue;
        }
        deplacement(&p, d, a);
        changer_joueur(&p);
        if(partie_echec(p) == ECHEC)
        {
            compteur++;
        }
        changer_joueur(&p);
        annuler_deplacement(&p);
        printf("%d\n", partie_echec(p));
    }


    if(compteur == 8)
        return MAT;

    return FALSE;
}*/

coordonnees_t coordonnees_roi(partie_t p, int joueur)
{
    int i;
    int j;
    piece_t roi1 = piece_creer(JOUEUR_1, KING, NON_PROMU);
    piece_t roi2 = piece_creer(JOUEUR_2, KING, NON_PROMU);
    /* r1 -> coordoonnees du roi du joueur1
       r2 -> coordoonnees du roi du joueur2 */
    coordonnees_t r1;
    coordonnees_t r2;

    /* on cherche les deux rois sur le plateaux. */
    for(i = 1; i < NB_LIGNE - 1; i++)
    {
        for(j = 1; j < NB_COLONNE - 1; j++)
        {
            if(cmp_piece(roi1, p.tablier[i][j]))
                r1 = coordonnees_creer(i, j);
            if(cmp_piece(roi2, p.tablier[i][j]))
                r2 = coordonnees_creer(i, j);
        }
    }
    if(joueur == JOUEUR_1)
        return r1;
    else
        return r2;
}
