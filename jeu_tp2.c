/* OUKACHE Ayas */
#include <stdio.h> 
#include <stdlib.h>

/* si le joueur gagne on renvoi +1 */
int joueur(int n){
	int C1, C2, C3;
	if((n+1 == 20)||((n+2)==20)||((n+3)==20)) return +1;
	else {
		C1 = adversaire(n+1);
		C2 = adversaire(n+2);
		C3 = adversaire(n+3);
	}
	if((C1 > C2)&&(C1>C3)) return C1;
	else if((C2>C1)&&(C2>C3)) return C2;
	else return C3;
}

/* si l'adversaire gagne on renvoi -1 */
int adversaire(int n){
	int C1, C2, C3;
	if(( (n+1)== 20 )||( (n+2)==20 )||( (n+3)==20 )) return -1;
	else {
		C1 = joueur(n+1);
		C2 = joueur(n+2);
		C3 = joueur(n+3);
	}
	if((C1<C2)&&(C1<C3)) return C1;
	else if((C2<C1)&&(C2<C3)) return C2;
	else return C3;
}

/* choix de l'ordinateur avec jeu optimal */
int choix_optimal(int n){
	int coup;
	/*pour tout les coups possible on renvoit le coup gagnant */
	if((n+1)==20) return 1;
	if((n+2)==20) return 2;
	if((n+3)==20) return 3;
	else {	
		/* sinon on renvoit le coup qui amene a le plus de possibilité de gagner */
		if(adversaire(n+1)==1) return 1;
		if(adversaire(n+2)==1) return 2;
		if(adversaire(n+3)==1) return 3;
		else{
			/* sinon on renvoit un coup au hasard */
			coup = rand()%4 ;
			if(coup == 0) coup =1;
			return coup;
		}
	}
}

/* choix aléatoire de l'ordinateur */
int choix_aleatoire(int total){
	int nbr_ord = rand()%4;
	if(nbr_ord == 0) nbr_ord = 1;
	if(total == 17) nbr_ord = 3;
	if(total == 18) nbr_ord = 2;
	if(total == 19) nbr_ord = 1;
	return nbr_ord;
}

