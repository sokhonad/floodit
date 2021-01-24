#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <math.h>

#include"tp_3.c"

#define TAILLE 12
#define NB_COULEUR 6
#define NB_COUPS 22

typedef enum 
{
    NOIR,ROUGE,VERT,JAUNE,
    BLEU,MAGENTA,CYAN,BLANC
} couleur_t;

couleur_t ** creeGrille(int t){
    int i;
    couleur_t **ptr;
    ptr=(couleur_t**)malloc(t*sizeof(couleur_t*));
    for (i = 0; i < t; ++i)
    {
        ptr[i]=(couleur_t*)malloc(t*sizeof(couleur_t));
    }
    return ptr;
}

void detritGrile(couleur_t ** G,int t){
    int i;
    for (i = 0; i < t; ++i)
    {
        free(G[i]);
    }
    free(G);
}

void randomGrile(couleur_t ** G,int t){
    int i,j;
    for (i = 0; i < t; ++i)
    {
        for (j = 0; j < t; ++j)
        {
            G[i][j]=rand()%NB_COULEUR;
        }
        
    }
}

void afficherGrile(couleur_t ** G,int t){
    int i,j;
    for (i = 0; i < t; ++i)
    {
        for (j = 0; j < t; ++j)
        {
            /*printf(" %d", G[i][j]);*/
            printf("\033[%dm %d", 40 + G[i][j], G[i][j] );
        }
        printf("\033[m\n");
       
    }
}

void propage_rec(couleur_t ** G,int t,couleur_t old,couleur_t c,int i,int j){
    /*update couleur*/
    G[i][j]=c;
    /*en haut*/
    if (i>0 && G[i][j]==old)
    {
       propage_rec(G,t,old,c,i-1,j);
    }
    /*a gauche*/
    if (j>0 && G[i][j-1]==old)
    {
        propage_rec(G,t,old,c,i,j-1);
    }
    /*en bas*/
    if (i<TAILLE-1 && G[i+1][j]==old)
    {
        propage_rec(G,t,old,c,i+1,j);
    }
    /*a droite*/
    if (j<TAILLE-1 && G[i][j+1]==old)
    {
        propage_rec(G,t,old,c,i,j+1);
    }

}
void propage(couleur_t ** G,int t,couleur_t c){
    if (G[0][0] != c)
    {
    propage_rec(G,t,G[0][0],c,0,0);
    }
}



void test(){
     printf("\033[41m%s\n","toto" );
    printf("\033[m\n");
}

int isFlooded(couleur_t ** G,int t){
    int i,j;
    for (i = 0; i < t; ++i)
    {
        for (j = 0; j < t; ++j)
        {
            if (G[i][j]!=G[0][0])
            {
                return 0;
            }
        }
    }
    return 1;
}

void creePile(int **p,int t){
	*p=(int*)malloc(t*sizeof(int));

}

void detruitPile (int ** p)
{
	free(*p);
	*p = NULL;
}

void propage_iter(couleur_t ** G,int t,couleur_t new_c){
	int *p;
	int pos,i,j;
	creePile(&p,t*t);
	viderPile(&top);
	int old_c = G[0][0];
    if (old_c != new_c)
    {
    empiler(p,&top,0);
    }
    while(est_vide(top)==0){
    	depiler(p,&top,&pos);
    	i=pos/t;
    	j=pos%t;
    	G[i][j]=new_c;
    	if (i>0 && G[i-1][j]==old_c)
    	{
    		empiler(p,&top,(i-1)*t+j);
    	}
    	if (i<TAILLE-1 && G[i+1][j]==old_c)
    	{
    		empiler(p,&top,(i+1)*t+j);
    	}
    	if (j>0 && G[i][j-1]==old_c)
    	{
    		empiler(p,&top,i*t+j-1);
    	}
    	if (i<TAILLE-1 && G[i][j+1]==old_c)
    	{
    		empiler(p,&top,i*t+j+1);
    	}
    }
    detruitPile(&p);
}


void play(int t){
    int c;
    couleur_t **G=creeGrille(t);
    int i;
    randomGrile(G,t);
    afficherGrile(G,t);
    i=0;
    while((i<NB_COULEUR) && !isFlooded(G,t)){
        printf("couleur?");
        scanf("%d",&c);
        /* propage(G,t,c); */
        propage_iter(G,t,c);
        afficherGrile(G,t);
    }
    if (isFlooded(G,t))
    {
        printf("gagne\n");
    }else{
        printf("perdu\n");
        detritGrile(G,t);
    }
    
}

couleur_t calculCouleur1(){
	return rand()%NB_COULEUR;
}

couleur_t calculCouleur2(couleur_t **G){
	couleur_t c=rand()%NB_COULEUR-1;
	if (c>=G[0][0])
	{
		c=c+1;
	}
	return c;
}


int main(){
    
    /*couleur_t **G;
    G=creeGrille(TAILLE);
    randomGrile(G,TAILLE);
    afficherGrile(G,TAILLE);
    propage(G,TAILLE,1);
    detritGrile(G,TAILLE);*/

    play(TAILLE);

   
  return 0;
}