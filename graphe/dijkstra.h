

#define NB_NOEUDS 10
#define NB_ARCS 17


/*

  gcc -W -Wall dijkstra.c -lSDL -lSDL2 -lm -lSDL_ttf

*/


/**la struct correspond a une sphere/ville*/
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


void initialise();
int minimum();
void trouve_voisin(char *nom_ville, voisin tab_voisins[]);
int trouve_poids_arc(char* voisin,char* nom_ville);
void parcours();
void pause();
void clean(char chaine[]);



