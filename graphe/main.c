#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include"dijkstra.h"



int main(){
  int i=0,j=0;

  initialise();
  for(i=0;i<NB_NOEUDS;i++){
    printf("tab_noeuds[i].nom_ville: %s\n",tab_noeuds[i].nom_ville);
    printf("tab_noeuds[i].poids : %d\n", tab_noeuds[i].poids);
    printf("tab_noeuds[i].parcouru: %d\n\n",tab_noeuds[i].parcouru);
  }
  parcours();

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
    
    
    
  char chaine[50]="";
    
  SDL_Rect position;
  TTF_Font *police = NULL;
  //SDL_Color couleurNoire = {0, 0, 0,42};
  SDL_Color couleurBlanche = {255, 255, 255,42};
  
  SDL_Surface *ecran;
	
  SDL_Surface *tab_texte[NB_NOEUDS];
  int indice_texte=0;
    
    
  if (SDL_Init(SDL_INIT_VIDEO) >= 0){
    TTF_Init();
    police = TTF_OpenFont("po.TTF", 12);
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    
    //initCouleurs();
    
    if (ecran != NULL){
    
      SDL_WM_SetCaption("Ma super fenêtre SDL 222 !", NULL);
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
      {
      
	char *recherche;
	recherche=tab_noeuds[9].nom_ville;
	
	
	strcpy(chaine,"Les antecedents de ");
	strcat(chaine,tab_noeuds[9].nom_ville);
	tab_texte[indice_texte] = TTF_RenderText_Blended(police, chaine,couleurBlanche);
	clean(chaine);
	
	position.x = 0;
	position.y = 3;
	SDL_BlitSurface(tab_texte[indice_texte], NULL, ecran, &position);
	indice_texte=indice_texte+1;
	
	for(j=i-1;j>=0;j--){
      
	  if(strcmp(recherche,tab_antecedents[j].nom_noeud)==0){
	    //printf(", %s",tab_antecedents[j].nom_antecedent);
	    
	    recherche=tab_antecedents[j].nom_antecedent;
	    strcpy(chaine,tab_antecedents[j].nom_antecedent);
	    tab_texte[indice_texte] = TTF_RenderText_Blended(police, chaine,couleurBlanche);
	clean(chaine);
	
	position.x = 0;
	position.y +=28;
	SDL_BlitSurface(tab_texte[indice_texte], NULL, ecran, &position);
	indice_texte=indice_texte+1;
	
	  }
	}
    	
    	strcpy(chaine,"Poids en km du plus court chemin : ");
    	char num_to_string[10]="";
    	sprintf(num_to_string,"%d",tab_noeuds[9].poids);
    	
    	strcat(chaine,num_to_string);
	tab_texte[indice_texte] = TTF_RenderText_Blended(police, chaine,couleurBlanche);
	clean(chaine);
	
	position.x = 0;
	position.y += 50;
	SDL_BlitSurface(tab_texte[indice_texte], NULL, ecran, &position);
	indice_texte=indice_texte+1;
    	
	
      }
    
    
    }
    SDL_Flip(ecran);
      pause();
    
   } 
	

    return 0;
  }
