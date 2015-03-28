/* OUKACHE Ayas */
#ifndef __MEO_AB_H__
#define __MEO_AB_H__

/* Mise en oeuvre par pointeurs d'un arbre binaire */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct noeud {
	int id;
    char val[100];
	struct noeud *pere, *fg, *fd;
} t_noeud;


t_noeud* init_arbre(t_noeud* rac);
int arbre_vide(t_noeud* rac);
int filsg(t_noeud*);
int filsd(t_noeud*);

t_noeud* fg(t_noeud*);
t_noeud* fd(t_noeud*);
t_noeud* pere(t_noeud*);
t_noeud * racine(t_noeud * n); /* retourne le noeud de la racine */

int feuille(t_noeud*);

void supprime_noeud(t_noeud* n);
void modif_noeud(t_noeud*, char*);


char* val_noeud();
int get_id(t_noeud * r);
int get_lastid(t_noeud* r); /* retourne le dernier id de l'arbre */
void oter_feuille(t_noeud* n);
t_noeud* ajout_filsg(t_noeud* n, int id, char* mot);
t_noeud* ajout_filsd(t_noeud* n, int id, char* mot);

t_noeud* creer_noeud(int id, char* v);


#endif 

