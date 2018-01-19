
#ifndef dijkstra_malloc_h

enum {
  C_NOIR, C_BLEU_FONCE, C_VERT_FONCE, C_CYAN_FONCE, C_ROUGE_FONCE,
  C_MAGENTA_FONCE, C_OCRE, C_GRIS_CLAIR, C_GRIS, C_BLEU, C_VERT,
  C_CYAN, C_ROUGE, C_MAGENTA, C_JAUNE, C_BLANC,
 
  NB_COULEURS
};


SDL_Surface *ecran;
Uint32 couleurs[NB_COULEURS];

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




void clean(char chaine[]);
void enleve_n(char chaine[]);
void initialise(noeud *tab_noeuds,arc *tab_arcs);
int minimum(noeud *tab_noeuds);
void trouve_voisin(char nom_ville[], voisin *tab_voisins,arc *tab_arcs);
int trouve_poids_arc(char* voisin,char nom_ville[],arc *tab_arcs);
void parcours(noeud *tab_noeuds,arc *tab_arcs,antecedent *tab_antecedents,voisin *tab_voisins);

void pause();

void disque(int cx, int cy, int rayon, int coul,SDL_Surface *const ecran);
void ligneHorizontale(int x, int y, int w, Uint32 coul,SDL_Surface *const ecran);
void ligneVerticale(int x, int y, int h, Uint32 coul,SDL_Surface *const ecran);
void echangerEntiers(int* x, int* y);
void setPixel(int x, int y, Uint32 coul);
void setPixelVerif(int x, int y, Uint32 coul);
void ligne(int x1, int y1, int x2, int y2, Uint32 coul);
void int_to_char(int nb);

void initCouleurs();

char chaine[30]="";
char ville_arriver[30]="";



#endif

