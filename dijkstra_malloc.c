#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


/*

  gcc -W -Wall dijkstra_malloc.c -lSDL -lSDL2 -lm -lSDL_ttf

*/


int nb_noeuds=0;
int nb_arcs= 0;


//la struct correspond a une sphere/ville
struct noeud{
  char nom_ville[30];
  int poids;
  bool parcouru;
};

typedef struct noeud noeud;

struct arc{
  char noeud1[30];
  char noeud2[30];
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




char chaine[30]="";
char ville_arriver[30]="";


void clean(char chaine[]){

  int i=0;
  for(i=0;i<30;i++)
    chaine[i]='\0';
}

void enleve_n(char chaine[]){
  int i=0;
  for(i=0;chaine[i]!=10||chaine[i]!='\n';i++);
  for(;i<30;i++)
    chaine[i]='\0';
}

void initialise(noeud *tab_noeuds,
		arc *tab_arcs){
  int i,j;
	
	
  printf("Quel est le nom du noeud de départ ?\n");
	
  fgets(chaine, sizeof(chaine), stdin);
  enleve_n(chaine);
  strcpy(tab_noeuds[0].nom_ville,chaine);
  clean(chaine);
  tab_noeuds[0].poids=0;
	
  printf("Quel est le nom du noeud d'arriver ?\n");
	
  fgets(chaine, sizeof(chaine), stdin);
  enleve_n(chaine);
  strcpy(ville_arriver,chaine);
  strcpy(tab_noeuds[nb_noeuds-1].nom_ville,chaine);
  clean(chaine);
	
  for(i=1;i<nb_noeuds-1;i++){
    printf("Quel est le nom du noeud suivant ?\n");
    fgets(chaine, sizeof(chaine), stdin);
    enleve_n(chaine);
    strcpy(tab_noeuds[i].nom_ville,chaine);
    clean(chaine);
  }
	
	
  for(i=0;i<nb_noeuds;i++){
    tab_noeuds[i].parcouru=false;
  }
  //je met tt les poids des noeuds a -1 car c'est le debut
  for(j=1;j<nb_noeuds;j++){
    tab_noeuds[j].poids=-1;
  }
	
  for(j=0;j<nb_arcs;j++){
    printf("Quels sont les arcs ?\n");
	
    printf("entrer le premier noeud\n");
    fgets(chaine, sizeof(chaine), stdin);
    enleve_n(chaine);
    strcpy(tab_arcs[j].noeud1,chaine);
    //printf("tab_arcs[j].noeud1 %s\n",tab_arcs[j].noeud1);
    clean(chaine);
	
    printf("entrer le deuxieme noeud\n");
    fgets(chaine, sizeof(chaine), stdin);
    enleve_n(chaine);
    strcpy(tab_arcs[j].noeud2,chaine);
    clean(chaine);
	
    printf("Quel est le poids de cette arc ?\n");
    fgets(chaine, sizeof(chaine), stdin);
    enleve_n(chaine);
    //printf("chaine issssssss : %s\n",chaine);
    tab_arcs[j].poids=atoi(chaine);
    //printf("laaaaaaaaa tab_arcs[j].poids %d\n",tab_arcs[j].poids);
    clean(chaine);
    
  }
  
  

}


//fonction qui va chercher le minimum des poids de chaque noeud pour que l'on part du noeud le plus petit, elle retourne l'undice du plus petit
int minimum(noeud *tab_noeuds){
	
  int i=0;
  int min_i=0;
  int compteur_de_moins_1=0;
  //je prend min_i a 0 car il va etre l'indice i a 0 et je vais le comparer avec les indices i+1,i+2...
  for(i=1;i<nb_noeuds;i++){
    //printf("tab_noeuds[i].nom_ville %s tab_noeuds[i].poids %d\n\n",tab_noeuds[i].nom_ville,tab_noeuds[i].poids);
    //if(tab_noeuds[i].parcouru==false)
    //	min_i;
    /*if(tab_noeuds[i].parcouru==true){
      continue;
      }*/

    if(tab_noeuds[i].poids==-1){
      compteur_de_moins_1++;
      //printf("compteur_de_moins_1: %d\n",compteur_de_moins_1);
      if(compteur_de_moins_1==(nb_noeuds-1))
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
      //printf("min_i issssssssssssss:%d\n",min_i);
    }
  }
  return min_i;
}


//pour une ville je vais trouver tous ses voisins
void trouve_voisin(char nom_ville[], voisin *tab_voisins,arc *tab_arcs){
  int i=0,j=0;
  //je parcours les arcs pour trouver le nom d'une ville dans le noeud1 ou noued2 et je rentre son voisin dans le tab_voisins
  for(i=0;i<nb_arcs;i++){
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


int trouve_poids_arc(char* voisin,char nom_ville[],arc *tab_arcs){//on va donner en parametre 2 noms de ville qui un arc en commun et ca va retouner le poids de l'arc

  int i=0;
  for(i=0;i<nb_arcs;i++){
    if(((strcmp(tab_arcs[i].noeud1,voisin)==0)&&(strcmp(tab_arcs[i].noeud2,nom_ville)==0))||((strcmp(tab_arcs[i].noeud1,nom_ville)==0)&&(strcmp(tab_arcs[i].noeud2,voisin)==0))){
      return tab_arcs[i].poids;
    }
  }
  printf("erreur dans la fonction trouve_poids_arc\n");
  return -2;
}


void parcours(noeud *tab_noeuds,
	      arc *tab_arcs,
	      antecedent *tab_antecedents,
	      voisin *tab_voisins){

  int min_i=0;
  int j=0,i=0,k=0;
  
  int val_arc=0;//valeur de l'arc entre le voisin et le noeud de depart

  
  while(strcmp(tab_noeuds[min_i].nom_ville,ville_arriver)!=0){//tant que on est pas a la ville d'arriver
    //while(x<4){
    min_i=minimum(tab_noeuds);
    printf("tab_noeuds[min_i].nom_ville iciiiiiiiiiiii %s\n",tab_noeuds[min_i].nom_ville);
    printf("min_i is:%d\n",min_i);
    printf("tab_noeuds[min_i].parcouru :%d\n",tab_noeuds[min_i].parcouru);
    trouve_voisin(tab_noeuds[min_i].nom_ville,tab_voisins,tab_arcs);

    for(j=0;strcmp(tab_voisins[j].nom_voisin,"0")!=0;j++){//le dernier tab_voisins[j].nom_voisin est égale a "0"
      for(i=0;i<nb_noeuds;i++){
	if(strcmp(tab_voisins[j].nom_voisin,tab_noeuds[i].nom_ville)==0){//voisin j est égale a noeuds i ici
	  if(tab_noeuds[i].parcouru==false){
	    val_arc=trouve_poids_arc(tab_noeuds[i].nom_ville,tab_noeuds[min_i].nom_ville,tab_arcs);//je recupere le poids de l'arc entre le voisin et la ville de où on part
						
	    printf("tab_noeuds[i].nom_ville is %s val_arc is:%d\n",tab_noeuds[i].nom_ville,val_arc);
	    printf("tab_noeuds[i].parcouru %d tab_noeuds[i].poids %d\n",tab_noeuds[i].parcouru,tab_noeuds[i].poids);
						
	    //return;
						
	    if( ((tab_noeuds[i].parcouru==false) && ((tab_noeuds[min_i].poids + val_arc) < tab_noeuds[i].poids))|| tab_noeuds[i].poids==-1) {
	      tab_noeuds[i].poids=tab_noeuds[min_i].poids + val_arc;  //j'affecte a la ville voisin le poids de l'arc qu'il a parcouru
	      printf("je fais rentrer %s et %s \n",tab_noeuds[i].nom_ville,tab_noeuds[min_i].nom_ville);
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



//PARTIE SDL



void pause();

void disque(int cx, int cy, int rayon, int coul,SDL_Surface *const ecran);


SDL_Surface *ecran;

enum {
  C_NOIR, C_BLEU_FONCE, C_VERT_FONCE, C_CYAN_FONCE, C_ROUGE_FONCE,
  C_MAGENTA_FONCE, C_OCRE, C_GRIS_CLAIR, C_GRIS, C_BLEU, C_VERT,
  C_CYAN, C_ROUGE, C_MAGENTA, C_JAUNE, C_BLANC,
 
  NB_COULEURS
};
 
Uint32 couleurs[NB_COULEURS];
 
void initCouleurs()
{
  couleurs[C_NOIR]          = SDL_MapRGB(ecran->format, 0x00, 0x00, 0x00);
  couleurs[C_BLEU_FONCE]    = SDL_MapRGB(ecran->format, 0x00, 0x00, 0x80);
  couleurs[C_VERT_FONCE]    = SDL_MapRGB(ecran->format, 0x00, 0x80, 0x00);
  couleurs[C_CYAN_FONCE]    = SDL_MapRGB(ecran->format, 0x00, 0x80, 0x80);
  couleurs[C_ROUGE_FONCE]   = SDL_MapRGB(ecran->format, 0x80, 0x00, 0x00);
  couleurs[C_MAGENTA_FONCE] = SDL_MapRGB(ecran->format, 0x80, 0x00, 0x80);
  couleurs[C_OCRE]          = SDL_MapRGB(ecran->format, 0x80, 0x80, 0x00);
  couleurs[C_GRIS_CLAIR]    = SDL_MapRGB(ecran->format, 0xC0, 0xC0, 0xC0);
  couleurs[C_GRIS]          = SDL_MapRGB(ecran->format, 0x80, 0x80, 0x80);
  couleurs[C_BLEU]          = SDL_MapRGB(ecran->format, 0x00, 0x00, 0xFF);
  couleurs[C_VERT]          = SDL_MapRGB(ecran->format, 0x00, 0xFF, 0x00);
  couleurs[C_CYAN]          = SDL_MapRGB(ecran->format, 0x00, 0xFF, 0xFF);
  couleurs[C_ROUGE]         = SDL_MapRGB(ecran->format, 0xFF, 0x00, 0x00);
  couleurs[C_MAGENTA]       = SDL_MapRGB(ecran->format, 0xFF, 0x00, 0xFF);
  couleurs[C_JAUNE]         = SDL_MapRGB(ecran->format, 0xFF, 0xFF, 0x00);
  couleurs[C_BLANC]         = SDL_MapRGB(ecran->format, 0xFF, 0xFF, 0xFF);
}




void ligneHorizontale(int x, int y, int w, Uint32 coul,SDL_Surface *const ecran)
{
  SDL_Rect r;
 
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = 1;
 
  SDL_FillRect(ecran, &r, coul);
}

void ligneVerticale(int x, int y, int h, Uint32 coul,SDL_Surface *const ecran)
{
  SDL_Rect r;
 
  r.x = x;
  r.y = y;
  r.w = 1;
  r.h = h;
 
  SDL_FillRect(ecran, &r, coul);
}


void pause()
{
  int continuer = 1;

  while (continuer)
    {
      SDL_Event event;
      SDL_WaitEvent(&event);
      switch (event.type)
	{
	case SDL_QUIT:
	  continuer = 0;
	case SDL_MOUSEBUTTONUP:
      	if (event.button.y > 0 && event.button.y <= 0+91   
      && event.button.x > 0 && event.button.x <= 0+91){
      
	  continuer = 0;
      }
     }
    }
}


void disque(int cx, int cy, int rayon, int coul,SDL_Surface *const ecran)
{
  int d, y, x;
 
  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;
 
  while (y >= x) {
    ligneHorizontale(cx - x, cy - y, 2 * x + 1, coul,ecran);
    ligneHorizontale(cx - x, cy + y, 2 * x + 1, coul,ecran);
    ligneHorizontale(cx - y, cy - x, 2 * y + 1, coul,ecran);
    ligneHorizontale(cx - y, cy + x, 2 * y + 1, coul,ecran);
 
    if (d < 0)
      d = d + (4 * x) + 6;
    else {
      d = d + 4 * (x - y) + 10;
      y--;
    }
 
    x++;
  }
}




void echangerEntiers(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}

void setPixel(int x, int y, Uint32 coul)
{
  *((Uint32*)(ecran->pixels) + x + y * ecran->w) = coul;
}

void setPixelVerif(int x, int y, Uint32 coul)
{
  if (x >= 0 && x < ecran->w &&
      y >= 0 && y < ecran->h)
    setPixel(x, y, coul);
}
 
void ligne(int x1, int y1, int x2, int y2, Uint32 coul)
{
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;
 
  if (abs(x2 - x1) < abs(y2 - y1)) {
    /* parcours par l'axe vertical */
 
    if (y1 > y2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }
 
    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;
 
    setPixelVerif(x, y, coul);
 
    for (y = y1+1; y <= y2; ++y) {
      if (d >= 0) {
	x += xincr;
	d += aincr;
      } else
	d += bincr;
 
      setPixelVerif(x, y, coul);
    }
 
  } else {
    /* parcours par l'axe horizontal */
     
    if (x1 > x2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }
 
    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;
 
    setPixelVerif(x, y, coul);
 
    for (x = x1+1; x <= x2; ++x) {
      if (d >= 0) {
	y += yincr;
	d += aincr;
      } else
	d += bincr;
 
      setPixelVerif(x, y, coul);
    }
  }   
}




void int_to_char(int nb){
  clean(chaine);
  sprintf(chaine, "%d", nb);
}




int main(){
  int i=0,j=0,k=0;
  clean(chaine);
  printf("Combien de noeuds ?\n");
  fgets(chaine, sizeof(chaine), stdin);
  nb_noeuds=atoi(chaine);
  clean(chaine);
    	
  printf("Combien d'arcs ?\n");
  fgets(chaine, sizeof(chaine), stdin);
  nb_arcs=atoi(chaine);
  clean(chaine);
	
	
  noeud *tab_noeuds = malloc (nb_noeuds * sizeof (noeud));
  arc *tab_arcs = malloc (nb_arcs * sizeof (arc));
  antecedent *tab_antecedents = malloc (nb_noeuds * sizeof (antecedent));
  voisin *tab_voisins = malloc (nb_noeuds * sizeof (voisin));
	
  initialise(tab_noeuds,tab_arcs);


	
	SDL_Rect positionBoutton;
  positionBoutton.x = 0;
  positionBoutton.y = 0;
  SDL_Surface *boutton = NULL;
  boutton = SDL_LoadBMP ("start.bmp");
	
	
  SDL_Rect position;
  TTF_Font *police = NULL;
  SDL_Color couleurNoire = {0, 0, 0,42};
  SDL_Color couleurBlanche = {255, 255, 255,42};
	
  SDL_Surface *tab_texte[nb_noeuds*nb_arcs];
  int indice_texte=0;

  int tab_position_noeuds[nb_noeuds][nb_noeuds];
	
  if (SDL_Init(SDL_INIT_VIDEO) >= 0){
    TTF_Init();
    police = TTF_OpenFont("po.TTF", 20);
    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    initCouleurs();
    if (ecran != NULL){
    
      SDL_WM_SetCaption("Ma super fenêtre SDL !", NULL);
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
      {
	int endroit_noeud=(640/nb_noeuds);//c'est l'endroit d'un seul noeud par rapport a la taille de l'ecran et du nb_noeuds
	int rayon=25;
         
         
	disque(25, 480/2-30, rayon,couleurs[C_JAUNE],ecran);//le premier cercle
	clean(chaine);
	position.x = 25 -12;
	position.y = (480/2-30) - 5;
	tab_position_noeuds[0][0]=position.x;
	tab_position_noeuds[0][1]=position.y;
	  
	strcpy(chaine,tab_noeuds[i].nom_ville);
	tab_texte[indice_texte] = TTF_RenderText_Blended(police, chaine,couleurNoire);
	clean(chaine);
	SDL_BlitSurface(tab_texte[indice_texte], NULL, ecran, &position);
	indice_texte=indice_texte+1;
	  
	  
	disque(640-25, 480/2-30, rayon,couleurs[C_JAUNE],ecran);//le dernier
	position.x = 640-25 -12;
	position.y = (480/2-30) - 5;
	  
	tab_position_noeuds[nb_noeuds-1][0]=position.x;
	tab_position_noeuds[nb_noeuds-1][1]=position.y;
	  
	strcpy(chaine,tab_noeuds[nb_noeuds-1].nom_ville);
	tab_texte[indice_texte] = TTF_RenderText_Blended(police, chaine,couleurNoire);
	clean(chaine);
	SDL_BlitSurface(tab_texte[indice_texte], NULL, ecran, &position);
	indice_texte=indice_texte+1;
         
	int x=0;
	int y=0;
         
	for(i=1;i<nb_noeuds-1;i++){
	  if(i%2==0){
	    y=25;
	    x=x+20;
	    position.x = x -12;
	    position.y = y - 5;
	    tab_position_noeuds[i][0]=x;
	    tab_position_noeuds[i][1]=y;
	      
	    disque(x, y, rayon,couleurs[C_JAUNE],ecran);
	    strcpy(chaine,tab_noeuds[i].nom_ville);
	    tab_texte[indice_texte] = TTF_RenderText_Blended(police, chaine,couleurNoire);
	    clean(chaine);
	    SDL_BlitSurface(tab_texte[indice_texte], NULL, ecran, &position);
	    indice_texte=indice_texte+1;
	  }else{
	    y=480-25;
	    x=endroit_noeud+x;
	    position.x = x -12;
	    position.y = y - 5;
	      
	    tab_position_noeuds[i][0]=x;
	    tab_position_noeuds[i][1]=y;
	      
	    disque(x, y, rayon,couleurs[C_JAUNE],ecran);
	    strcpy(chaine,tab_noeuds[i].nom_ville);
	    tab_texte[indice_texte] = TTF_RenderText_Blended(police, chaine,couleurNoire);
	    clean(chaine);
	    SDL_BlitSurface(tab_texte[indice_texte], NULL, ecran, &position);
	    indice_texte=indice_texte+1;
	      
	      
	  }
	    
	}
	
	//trace arcs
	for(i=0;i<nb_arcs;i++){
	  for(j=0;j<nb_noeuds;j++){
	    for(k=0;k<nb_noeuds;k++){
	      if(strcmp(tab_arcs[i].noeud1,tab_noeuds[j].nom_ville)==0){
		if(strcmp(tab_arcs[i].noeud2,tab_noeuds[k].nom_ville)==0){
		    
		  ligne(tab_position_noeuds[j][0], tab_position_noeuds[j][1],tab_position_noeuds[k][0],tab_position_noeuds[k][1],couleurs[C_JAUNE]);
		    
		  position.x=tab_position_noeuds[j][0]+((tab_position_noeuds[k][0]-tab_position_noeuds[j][0])/2);
		  position.y=tab_position_noeuds[j][1]+((tab_position_noeuds[k][1]-tab_position_noeuds[j][1])/2);
		
		  clean(chaine);
		  //printf("tab_arcs[i].poids: %d\n",tab_arcs[i].poids);
		  int_to_char(tab_arcs[i].poids);
		  //printf("chaine :%s",chaine);
		  tab_texte[indice_texte] = TTF_RenderText_Blended(police, chaine,couleurBlanche);
		  clean(chaine);
		  SDL_BlitSurface(tab_texte[indice_texte], NULL, ecran, &position);
		  indice_texte=indice_texte+1;
		}
	      }
	    }
	  }
	}
	SDL_BlitSurface (boutton,NULL,ecran, &positionBoutton);
      SDL_Flip(ecran);
	    
	//printf("ici\n");
      }
      pause();
    }
  }
	
	
  parcours(tab_noeuds,tab_arcs,tab_antecedents,tab_voisins);
  
  
    for(i=0;i<nb_noeuds;i++){
    printf("tab_noeuds[i].nom_ville: %s\n",tab_noeuds[i].nom_ville);
    printf("tab_noeuds[i].poids : %d\n", tab_noeuds[i].poids);
    printf("tab_noeuds[i].parcouru: %d\n\n",tab_noeuds[i].parcouru);
  }
  
  
  
  
  for(i=0;tab_antecedents[i].nom_noeud!=NULL;i++){
		printf("les antecedents sont:%s et nom:%s %d\n",tab_antecedents[i].nom_antecedent,tab_antecedents[i].nom_noeud,i);
	}
	printf("poids d'arriver au total en km quand on est passer par le chemin le plus court: %d\n",tab_noeuds[nb_noeuds-1].poids);
	
	char *recherche;
    recherche=tab_noeuds[nb_noeuds-1].nom_ville;
    
    printf("le chemin le plus court est donc : %s ",tab_noeuds[nb_noeuds-1].nom_ville);
  
  for(j=i-1;j>=0;j--){
    
    if(strcmp(recherche,tab_antecedents[j].nom_noeud)==0){
    	printf(", %s",tab_antecedents[j].nom_antecedent);
    	recherche=tab_antecedents[j].nom_antecedent;
    }
  }
  
    printf("\n");
    

    	
SDL_Surface *ecran2;	
police = TTF_OpenFont("po.TTF", 12);
ecran2 = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);

	
    if (ecran2 != NULL){
    
      SDL_WM_SetCaption("Ma super fenêtre SDL 222 !", NULL);
      SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran2->format, 0, 0, 0));
      {
	clean(chaine);
	strcpy(chaine,"Les antecedents de ");
	strcat(chaine,tab_noeuds[nb_noeuds-1].nom_ville);
	tab_texte[indice_texte] = TTF_RenderText_Blended(police, chaine,couleurBlanche);
	clean(chaine);
	
	
	position.x = 0;
	position.y = 3;
	SDL_BlitSurface(tab_texte[indice_texte], NULL, ecran2, &position);
	indice_texte=indice_texte+1;
	
	recherche=tab_noeuds[nb_noeuds-1].nom_ville;
	
	
	 for(j=i-1;j>=0;j--){
      
	  if(strcmp(recherche,tab_antecedents[j].nom_noeud)==0){
	    //printf(", %s",tab_antecedents[j].nom_antecedent);
	    
	    recherche=tab_antecedents[j].nom_antecedent;
	    strcpy(chaine,tab_antecedents[j].nom_antecedent);
	    tab_texte[indice_texte] = TTF_RenderText_Blended(police, chaine,couleurBlanche);
	clean(chaine);
	
	position.x = 0;
	position.y +=28;
	SDL_BlitSurface(tab_texte[indice_texte], NULL, ecran2, &position);
	indice_texte=indice_texte+1;
	
	  }
	 }
	 
	strcpy(chaine,"Poids en km du plus court chemin : ");
    	char num_to_string[10]="";
    	sprintf(num_to_string,"%d",tab_noeuds[nb_noeuds-1].poids);
    	
    	strcat(chaine,num_to_string);
	tab_texte[indice_texte] = TTF_RenderText_Blended(police, chaine,couleurBlanche);
	clean(chaine);
	
	position.x = 0;
	position.y += 50;
	SDL_BlitSurface(tab_texte[indice_texte], NULL, ecran, &position);
	indice_texte=indice_texte+1;
	
	
      }
    }
    
    
    SDL_Flip(ecran2);
pause();


  SDL_Quit();

  return EXIT_SUCCESS;
	
}

