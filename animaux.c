/* OUKACHE Ayas */

#include "ab.h"

#define TAILLE 500


/* permet d'afficher l'arbre en entier récursivement */
void affiche_aux(t_noeud* r, int prof, char* choix){
	int i;
	if(arbre_vide(r)){
		printf("arbre vide\n");
	}
	for(i=0; i<prof; i++){ /*on affiche les "branches" en fonction de la profondeur */
		printf("|___");
	}
	printf("[%s] %s\n", choix, val_noeud(r));
	
	if(filsg(r)){ 
		affiche_aux(fg(r), prof+1, "oui");
	}
	
	if(filsd(r)){
		affiche_aux(fd(r), prof+1, "non");
	}
}

void affiche(t_noeud* r){
	affiche_aux(r, 0, " ");
}

/*
 Fonction qui cherche et renvoie le noeud d'id id à partir de la racine r
 Renvoie NULL si non trouve
 */
t_noeud* cherche(t_noeud* r, int id)
{
	t_noeud* res = NULL;
    if(r != NULL) {
        if(r->id == id) {
            res = r;
        }
        else if(feuille(r)) {
            res = NULL;
        }
        else {
            if(filsg(r)){
                res = cherche(r->fg, id);
            }
            if(!res && filsd(r)){ // si on n'a pas trouvé, on cherche à droite
                res = cherche(r->fd, id);
            }
        }
    }
	return res;
}


/*
Fonction qui se positionne sur le noeud d'id = pere et ajoute le fils gauche d'id id et de valeur q
*/
t_noeud* ajout(t_noeud* r, int pere, int id, char* q)
{
	t_noeud* res = cherche(r, pere);
	if(res){
		if(!filsg(res))
			ajout_filsg(res, id, q);
		else if(!filsd(res))
			ajout_filsd(res, id, q);
		else {
			fprintf(stderr, "Le noeud %d a déjà un fg et un fd, problème dans le fichier !!\n", pere);
			res=0;
		}
	}
	else {
		fprintf(stderr, "Impossible d'ajouter %d, %s car le noeud d'id %d est introuvable !\n",id, q, pere);
	}
	return res;
}

/*
 Fonction qui charge le fichier contenant l'arborescence de la classification
 */
t_noeud* loadClassification(char *fn)
{
    t_noeud* r = NULL;
	char line[TAILLE], q[TAILLE];
	int id, pere;
	FILE* fd = fopen(fn, "r");
	if (fd==NULL){ 
		perror ("Error opening file");
		return 0;
	}
	
	r = init_arbre(NULL); // création de l'arbre vide

	while(!feof(fd)){
		fgets(line, TAILLE, fd);
		sscanf(line, "%d %d %[^\n]", &id, &pere, q);
		if( NULL == r ){
            r = creer_noeud(id, q);
        } else if(!ajout(r, pere, id, q)) {
			exit(0);
		}
	}
	fclose(fd);
	return r;
}

void purge(){ /* permet d'absorber tout les caractéres inutiles avant saisi de texte*/
	char c;
	do{
		c = getchar();
	}while(c!='\n');
}

/*
 Fonction principale
 */
int main(int argc, char **argv)
{
	char c; /* choix de l'utilisateur O(ui) ou N(on) */
	char f;
	
	/* données relatif à l'entrer d'un nouvel animal dans l'arbre */
	char newAnimal[64];
	char oldAnimal[64];
	char newQuestion[128];
	if(argc < 2)
	{
		printf("Usage : %s <fic>\n", argv[0]);
		printf("<fic> doit contenir la classification sous forme d'arbre\n");
		exit(EXIT_SUCCESS);
	}
	char *fn = argv[1];

	t_noeud* classif = loadClassification(fn);
	fprintf(stderr, "Classification chargée ...\n");
	
	
	affiche(classif); //affichage de la classification

	printf("\n\n");
	t_noeud * r = classif ;
	printf("Repondez par O(ui) ou par N(on)\n");
	printf("%s\n", val_noeud(r));
	
	while(!arbre_vide(r)){ 
	
		if(feuille(r)){ /* si on a trouvé l'animal alors on verifi si cest le bon animal */
			purge();
			f = getchar();
			switch(f){
				case 'O' : printf("OUI cool\n");
							break;
				case 'N' : printf("Quelle est la reponse ?\n"); /* si c'est pas le bon animal ajout du nouveau animal */
							purge();
							fscanf(stdin, "%[^\n]s", newAnimal);
							printf("%s", newAnimal); 
							printf("\nDonnez une question pour lequel on repond Oui pour \"%s\" et non pour \"%s\" \n", newAnimal, val_noeud(r));
							purge();
							fscanf(stdin, "%[^\n]s", newQuestion);
							strcpy(oldAnimal, val_noeud(r)); /* on recupere l'animal deja present dans l'arbre */
							modif_noeud(r, newQuestion); /* on modifi le noeud de l'animal pour inserer la question */
							r = ajout_filsd(r, get_lastid(classif)+1, oldAnimal); /* reimplementation de l'animal à droite */
							r = pere(r);
							r = ajout_filsg(r, get_lastid(classif)+2, newAnimal); /* implementation du nouvel animal à gauche */
							r = pere(r);
							break;
				default : perror("erreur");
			}
			break; 
		}
		
		c = getchar(); /* celon la question demandé on repon O pour oui ou N pour non */
		switch(c){
			case 'O' : if(filsg(r)){  /* on continu l'affichage avec le sous-arbre correspondant a un oui ou non */ 
							r = fg(r);
							printf("%s\n", val_noeud(r));
						}	
						break;
					
			case 'N' : if(filsd(r)){
							r = fd(r);
							printf("%s\n", val_noeud(r));
						}
						break;
		}
	}
	r= racine(r);
	printf("retourne a la racine\n");
	affiche(r);
	return 0;
}

