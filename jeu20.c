/* OUKACHE Ayas */
#include <stdio.h> 
#include <stdlib.h>
#include "jeu_tp2.h"
#include <getopt.h>

void usage(char * program){
	printf("%s [-Oo] \n -O ou -o est l'option pour optimiser les coups de l'ordinateur \n", program);
}

int main(int argc, char * argv[]){
	int opt_flag = 0;
	char opt;
	if(argc > 2){
		usage(argv[0]);	
		return 0;
	}	

	while((opt=getopt(argc, argv, "oO")) != -1){
		switch(opt){
			case 'o' : opt_flag = 1;
				   break;
			case 'O' : opt_flag = 1;
				   break;		
		}	
	}

	int nbr_ord=0;
	int nbr_jou=0;
	int total=0;
	
	while(total != 20){
		if(opt_flag) nbr_ord = choix_optimal(total);
		else nbr_ord = choix_aleatoire(total); 
		total += nbr_ord;
		printf("ordi joue : %d total : %d\n", nbr_ord, total);
		if(total == 20){
			printf("Vous avez perdu ! \n");
			return 0;		
		}

		printf("entrez votre choix de 1 a 3\n");
		scanf("%d", &nbr_jou);
		total += nbr_jou;
		printf("joueur joue : %d total : %d\n", nbr_jou, total);
		if(total == 20){
			printf("Felicitation vous avez gagné !\n");
		}
	}
	printf("FIN DE LA PARTI\n");
	return 0;
}


