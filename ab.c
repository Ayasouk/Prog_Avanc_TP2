/* Mise en oeuvre par pointeurs d'un arbre binaire */
/* OUKACHE Ayas */
#include "ab.h"



t_noeud* init_arbre(t_noeud *r)
{	
    if(NULL != r)
        supprime_noeud(r);
    return NULL;
}

int arbre_vide(t_noeud *r){
	return (r==NULL);
}

int filsg(t_noeud *r){
    if(r != NULL)
		return(r->fg!=NULL);
	return 0;
}

int filsd(t_noeud *r){
	if(r != NULL)
		return(r->fd!=NULL);
	return 0;
}

/* renvoi le noeud du fils gauche si existant */
t_noeud * fg(t_noeud * n){
	if(!arbre_vide(n)){
		if(filsg(n)){
			return n->fg;
		}
	}
	return NULL;
}

/* renvoi le noeud du fils droit si existant */
t_noeud * fd(t_noeud * n){
	if(!arbre_vide(n)){
		if(filsd(n)){
			return n->fd;
		}
	}
	return NULL;
}

/* renvoi le noeud du pere si existant */
t_noeud * pere(t_noeud * n){
	if(!arbre_vide(n)){
		if(n->pere != NULL){
			return n->pere;
		}
	}
	return NULL;
}

/* renvoi le noeud de la racine */
t_noeud * racine(t_noeud * n){
	if(arbre_vide(pere(n))) return n;
	return racine(pere(n));
}

/* renvoi le dernier id de l'arbre */
int get_lastid(t_noeud* r){ 
	if(feuille(r)) return get_id(r);
	return get_lastid(fd(r));
}

int get_id(t_noeud * r){
	if(!arbre_vide(r)){
		return r->id;
	}
	return -1;
}

int feuille(t_noeud *r){
    return(!filsd(r)&&!filsg(r));
}

char* val_noeud(t_noeud* n){
	if(NULL != n)
        return n->val;
    return NULL;
}

void modif_noeud(t_noeud* n, char* mot){
	if(NULL != n)
		strcpy(n->val,mot);
}

void oter_feuille(t_noeud *n)
{
    t_noeud * ancien;
	if(NULL != n && feuille(n)){
        if(NULL == n->pere){
                free(n);
		} else {
            ancien=n;
			n=n->pere;
			if(n->fg==ancien)
                n->fg=NULL;
            else
				n->fd=NULL;
            free(ancien);
		}
    }
}



t_noeud* ajout_filsg(t_noeud* n, int id, char* mot){
	
    //fprintf(stderr, "ajout_filsg\n");
	t_noeud * nouveau;
	if(NULL != n && filsg(n)){
		nouveau = NULL ;
	}
    else {
        nouveau=(t_noeud *)malloc(sizeof(t_noeud));
        nouveau->id = id;
        strcpy(nouveau->val,mot);
        nouveau->fg=NULL;
        nouveau->fd=NULL;
        if( NULL == n){
            nouveau->pere = NULL;
        }
        else { // if( !filsg(n)) {
            nouveau->pere=n;
            n->fg = nouveau;
        }
    }
    return nouveau;
}

t_noeud* ajout_filsd(t_noeud* n, int id, char* mot){
	//fprintf(stderr, "ajout_filsd\n");
	t_noeud * nouveau;
	if(NULL != n && filsd(n)){
		nouveau = NULL ;
	}
    else {
        nouveau=(t_noeud *)malloc(sizeof(t_noeud));
        nouveau->id = id;
        strcpy(nouveau->val,mot);
        nouveau->fg=NULL;
        nouveau->fd=NULL;
        if( NULL == n){
            nouveau->pere = NULL;
        }
        else { // if( !filsd(n)) {
            nouveau->pere=n;
            n->fd = nouveau;
        }
    }
    return nouveau;
}

void supprime_noeud(t_noeud* n){
	if(n != NULL){
		//suppression sous-arbre gauche
		if(n->fg) { supprime_noeud(n->fg); n->fg = NULL;}
		//suppression sous-arbre droit
		if(n->fd) { supprime_noeud(n->fd); n->fd = NULL;}
		
		if(n->pere != NULL){
			if(n->pere->fg==n)
				n->pere->fg=NULL;
			else
				n->pere->fd=NULL;
		}
		
		free(n);
	}
}

t_noeud* creer_noeud(int id, char* v){
    
    t_noeud * nouveau;
    nouveau=(t_noeud *)malloc(sizeof(t_noeud));
    nouveau->id = id;
    strcpy(nouveau->val,v);
    nouveau->fg=NULL;
    nouveau->fd=NULL;

    return nouveau;
}



