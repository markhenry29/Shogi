/* main.c
------------
Projet Shogi

date de création: 21/03/2017.
*/
#include "piece.h"
#include "partie.h"

int main(int argc, char **argv)
{
	partie_t* jeu_shogi;
	char format_fichier[3]; /*Lecture du format des sauvegardes*/


	if(argc == 1)
	{
		printf("Lancement d'une nouvelle partie........\n");
		jeu_shogi= partie_nouvelle();
		partie_jouer(jeu_shogi);
	}
	else
	{
		FILE *fichier;
		if((fichier = fopen(argv[1], "r")) != NULL)
		{
			fread(&format_fichier, sizeof(char), 2, fichier); /*lit les 2 premieres lettre du fichier*/
			if(strncmp("PL", format_fichier, 2)==0)
			{
				printf("Partie Chargee!\n");
			    	jeu_shogi = partie_charger(argv[1]);
				partie_jouer(jeu_shogi);
			}
			else if(strncmp("PR", format_fichier, 2)==0)
			{
				jeu_shogi= partie_nouvelle();
				replay_jouer(jeu_shogi, argv[1]);
				
			}
		}
		else {
				printf("Sauvegarde non trouve! Au revoir!\n");
		     }
		fclose(fichier);
	}
	    partie_detruire(jeu_shogi);	
	return EXIT_SUCCESS;
}
