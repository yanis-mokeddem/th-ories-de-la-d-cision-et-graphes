#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


#define NB_NOEUDS 10
#define NB_ARCS 17

/*

  gcc -W -Wall dijkstra.c -lSDL -lSDL2 -lm -lSDL_ttf

*/


//la struct correspond a une sphere/ville
struct noeud{
  char *nom_ville;
  int poids;
  bool parcouru;
};

typedef struct noeud noeud;

struct arc{
  char *noeud1;
  char *noeud2;
  int poids;
};

typedef struct arc arc;

struct antecedent{
  char *nom_noeud;//c'est le nom d'une ville
  char *nom_antecedent;//c'est le noeud par lequelle je suis passé avant d'arriver au noeud actuel

};

typedef struct antecedent antecedent;

struct voisin{
  char *nom_voisin;
};

typedef struct voisin voisin;


noeud tab_noeuds[NB_NOEUDS];
arc tab_arcs[NB_ARCS];
antecedent tab_antecedents[20];
voisin tab_voisins[NB_NOEUDS];

void initialise(){
  int i,j;

  tab_noeuds[0].nom_ville="bordeaux";
  tab_noeuds[0].poids=0;

  tab_noeuds[1].nom_ville="poitiers";
  tab_noeuds[2].nom_ville="montpellier";
  tab_noeuds[3].nom_ville="marseille";
  tab_noeuds[4].nom_ville="lyon";
  tab_noeuds[5].nom_ville="paris";
  tab_noeuds[6].nom_ville="brest";
  tab_noeuds[7].nom_ville="nantes";
  tab_noeuds[8].nom_ville="arras";
  tab_noeuds[9].nom_ville="strasbourg";

  for(i=0;i<NB_NOEUDS;i++){
    tab_noeuds[i].parcouru=false;
  }
  //je met tt les poids des noeuds a -1 car c'est le debut
  for(j=1;j<NB_NOEUDS;j++){
    tab_noeuds[j].poids=-1;
  }
  //j'affecte la valeur de l'arc entre de noeuds
  tab_arcs[0].noeud1="bordeaux";
  tab_arcs[0].noeud2="poitiers";
  tab_arcs[0].poids=237;
	
  tab_arcs[1].noeud1="bordeaux";
  tab_arcs[1].noeud2="nantes";
  tab_arcs[1].poids=334;

  tab_arcs[2].noeud1="poitiers";
  tab_arcs[2].noeud2="montpellier";
  tab_arcs[2].poids=557;


  tab_arcs[3].noeud1="poitiers";
  tab_arcs[3].noeud2="paris";
  tab_arcs[3].poids=338;


  tab_arcs[4].noeud1="montpellier";
  tab_arcs[4].noeud2="lyon";
  tab_arcs[4].poids=303;


  tab_arcs[5].noeud1="montpellier";
  tab_arcs[5].noeud2="strasbourg";
  tab_arcs[5].poids=797;


  tab_arcs[6].noeud1="montpellier";
  tab_arcs[6].noeud2="marseille";
  tab_arcs[6].poids=171;


  tab_arcs[7].noeud1="marseille";
  tab_arcs[7].noeud2="strasbourg";
  tab_arcs[7].poids=809;


  tab_arcs[8].noeud1="marseille";
  tab_arcs[8].noeud2="lyon";
  tab_arcs[8].poids=315;


  tab_arcs[9].noeud1="lyon";
  tab_arcs[9].noeud2="strasbourg";
  tab_arcs[9].poids=494;


  tab_arcs[10].noeud1="lyon";
  tab_arcs[10].noeud2="paris";
  tab_arcs[10].poids=465;


  tab_arcs[11].noeud1="strasbourg";
  tab_arcs[11].noeud2="arras";
  tab_arcs[11].poids=522;


  tab_arcs[12].noeud1="paris";
  tab_arcs[12].noeud2="brest";
  tab_arcs[12].poids=593;


  tab_arcs[13].noeud1="paris";
  tab_arcs[13].noeud2="nantes";
  tab_arcs[13].poids=386;

  tab_arcs[14].noeud1="paris";
  tab_arcs[14].noeud2="arras";
  tab_arcs[14].poids=185;


  tab_arcs[15].noeud1="brest";
  tab_arcs[15].noeud2="nantes";
  tab_arcs[15].poids=298;


  tab_arcs[16].noeud1="nantes";
  tab_arcs[16].noeud2="arras";
  tab_arcs[16].poids=561;


}


//fonction qui va chercher le minimum des poids de chaque noeud pour que l'on part du noeud le plus petit, elle retourne l'undice du plus petit
int minimum(){
  int i=0;
  int min_i=0;
  int compteur_de_moins_1=0;
  //je prend min_i a 0 car il va etre l'indice i a 0 et je vais le comparer avec les indices i+1,i+2...
  for(i=1;i<NB_NOEUDS;i++){
    //printf("tab_noeuds[i].nom_ville %s tab_noeuds[i].poids %d\n\n",tab_noeuds[i].nom_ville,tab_noeuds[i].poids);
    //if(tab_noeuds[i].parcouru==false)
    //	min_i;
    /*if(tab_noeuds[i].parcouru==true){
      continue;
      }*/

    if(tab_noeuds[i].poids==-1){
      compteur_de_moins_1++;
      //printf("compteur_de_moins_1: %d\n",compteur_de_moins_1);
      if(compteur_de_moins_1==(NB_NOEUDS-1))
	return 0;
      continue;
    }
    if(tab_noeuds[min_i].parcouru==true){
      min_i=min_i+1;
      continue;
    }
    //printf("tab_noeuds[min_i].poids %d tab_noeuds[i].poids %d\n",tab_noeuds[min_i].poids,tab_noeuds[i].poids);
    if((tab_noeuds[min_i].poids>tab_noeuds[i].poids) && tab_noeuds[i].parcouru==false){	
      min_i=i;
      printf("min_i issssssssssssss:%d\n",min_i);
    }
  }
  return min_i;
}


//pour une ville je vais trouver tous ses voisins
void trouve_voisin(char *nom_ville, voisin tab_voisins[]){
  int i=0,j=0;
  //je parcours les arcs pour trouver le nom d'une ville dans le noeud1 ou noued2 et je rentre son voisin dans le tab_voisins
  for(i=0;i<NB_ARCS;i++){
    if(strcmp(nom_ville,tab_arcs[i].noeud1)==0){
      tab_voisins[j].nom_voisin=tab_arcs[i].noeud2;
      j++;
    }
    if(strcmp(nom_ville,tab_arcs[i].noeud2)==0){
      tab_voisins[j].nom_voisin=tab_arcs[i].noeud1;
      j++;
    }
  }
  tab_voisins[j].nom_voisin="0";//"0" signifie que c'est la fin du tab_voisins
}


int trouve_poids_arc(char* voisin,char* nom_ville){//on va donner en parametre 2 noms de ville qui un arc en commun et ca va retouner le poids de l'arc

  int i=0;
  for(i=0;i<NB_ARCS;i++){
    if(((strcmp(tab_arcs[i].noeud1,voisin)==0)&&(strcmp(tab_arcs[i].noeud2,nom_ville)==0))||((strcmp(tab_arcs[i].noeud1,nom_ville)==0)&&(strcmp(tab_arcs[i].noeud2,voisin)==0))){
      return tab_arcs[i].poids;
    }
  }
  printf("erreur dans la fonction trouve_poids_arc\n");
  return -2;
}


void parcours(){

  int min_i=0;
  int j=0,i=0;
  int k=0;
  int val_arc=0;//valeur de l'arc entre le voisin et le noeud de depart
  char *ville_arriver="strasbourg";

  //int x=0;
  
  while(strcmp(tab_noeuds[min_i].nom_ville,ville_arriver)!=0){//tant que on est pas a la ville d'arriver
    //while(x<4){
    min_i=minimum();
    printf("tab_noeuds[min_i].nom_ville iciiiiiiiiiiii %s\n",tab_noeuds[min_i].nom_ville);
    printf("min_i is:%d\n",min_i);
    //printf("tab_noeuds[min_i].parcouru :%d\n",tab_noeuds[min_i].parcouru);
    trouve_voisin(tab_noeuds[min_i].nom_ville,tab_voisins);

    for(j=0;strcmp(tab_voisins[j].nom_voisin,"0")!=0;j++){//le dernier tab_voisins[j].nom_voisin est égale a "0"
      for(i=0;i<NB_NOEUDS;i++){
	if(strcmp(tab_voisins[j].nom_voisin,tab_noeuds[i].nom_ville)==0){//voisin j est égale a noeuds i ici
	  if(tab_noeuds[i].parcouru==false){
	    val_arc=trouve_poids_arc(tab_noeuds[i].nom_ville,tab_noeuds[min_i].nom_ville);//je recupere le poids de l'arc entre le voisin et la ville de où on part
						
	    printf("tab_noeuds[i].nom_ville is %s val_arc is:%d\n",tab_noeuds[i].nom_ville,val_arc);
	    printf("tab_noeuds[i].parcouru %d tab_noeuds[i].poids %d\n",tab_noeuds[i].parcouru,tab_noeuds[i].poids);
						
	    //return;
						
	    if(((tab_noeuds[i].parcouru==false) && ((tab_noeuds[min_i].poids + val_arc) < tab_noeuds[i].poids))|| tab_noeuds[i].poids==-1) {
	      tab_noeuds[i].poids=tab_noeuds[min_i].poids + val_arc;  //j'affecte a la ville voisin le poids de l'arc qu'il a parcouru
	      tab_antecedents[k].nom_noeud=tab_noeuds[i].nom_ville;
	      tab_antecedents[k].nom_antecedent=tab_noeuds[min_i].nom_ville;
	      k++;

	      printf("tab_noeuds[i].poids %d\n\n",tab_noeuds[i].poids);
	    }
	  }
	}
      }
    }
    tab_noeuds[min_i].parcouru=true;//on le passe a true que lorsqu'il a fait les operations sur ses voisins
    //x++;
  }
}


void clean(char chaine[]){

  int i=0;
  for(i=0;i<30;i++)
    chaine[i]='\0';
}



int main(){
  int i=0,j=0;

  initialise();
  for(i=0;i<NB_NOEUDS;i++){
    printf("tab_noeuds[i].nom_ville: %s\n",tab_noeuds[i].nom_ville);
    printf("tab_noeuds[i].poids : %d\n", tab_noeuds[i].poids);
    printf("tab_noeuds[i].parcouru: %d\n\n",tab_noeuds[i].parcouru);
  }
  parcours();
  /*for(i=0;tab_voisins[i].nom_voisin!=NULL;i++){
    printf("tab_voisins[i].nom_voisin: %s\n",tab_voisins[i].nom_voisin);
    }*/

  for(i=0;tab_antecedents[i].nom_noeud!=NULL;i++){
    printf("les antecedents sont:%s et nom:%s %d\n",tab_antecedents[i].nom_antecedent,tab_antecedents[i].nom_noeud,i);
  }
  printf("poids d'arriver au total en km quand on est passer par le chemin le plus court: %d\n",tab_noeuds[9].poids);
	
  char *recherche;
  recherche=tab_noeuds[9].nom_ville;
  printf("le chemin le plus court est donc : %s  ",tab_noeuds[9].nom_ville);
  
  
  for(j=i-1;j>=0;j--){
    //printf("les antecedents sont:%s et nom:%s %d\n",tab_antecedents[i].nom_antecedent,tab_antecedents[i].nom_noeud,i);
    
    if(strcmp(recherche,tab_antecedents[j].nom_noeud)==0){
      printf(", %s",tab_antecedents[j].nom_antecedent);
      recherche=tab_antecedents[j].nom_antecedent;
    }
  }
  printf("\n");
    
	

    return 0;
  }
