#ifndef GRAPHEMAT_H
#define GRAPHEMAT_H
#include <limits.h>
#include "liste.h"

typedef int  booleen;
#define faux 0
#define vrai 1
typedef char NomSom[20];  // nom d'un sommet
#define INFINI INT_MAX

typedef int* Matrice;

typedef struct Path {
    int* ipath ;
    char** spath;
    int cost ;
} Path;

typedef struct Noeud{
  Noeud* parent;
  char* nom;     
  int cout;
  int heuristique;
} Noeud;

typedef struct {
  int      n;       // nombre de sommets
  int      nMax;    // nombre max de sommets
  booleen  value;   // graphe valu� ou non
  NomSom*  nomS;    // noms des sommets
  Matrice  element; // existence d'un arc (i, j)
  Matrice  valeur;  // cout de l'arc (i, j)
  booleen* marque;  // sommet marqu� (visit�) ou non
} GrapheMat;

static void initMarque(GrapheMat* graphe);
GrapheMat* creerGrapheMat     (int nMax, int value);
void       detruireGraphe     (GrapheMat* graphe);
static int rang (GrapheMat* graphe, NomSom nom);
void       ajouterUnSommet    (GrapheMat* graphe, NomSom nom);
void       ajouterUnArc       (GrapheMat* graphe, NomSom somD, NomSom somA, int cout);
void       ecrireGraphe       (GrapheMat* graphe);
void       parcoursProfond    (GrapheMat* graphe);
void       floyd              (GrapheMat* graphe);
void enLargeur(GrapheMat* graphe, int numSommet, char* but);
void enProfondeur(GrapheMat* graphe, const char* but);
NomSom* explorationEnProfondeurDabord (GrapheMat* graphe, const char* but);
void explorationEnProfondeurDabord (GrapheMat* graphe);
NomSom* EPL_Recursive(GrapheMat* graphe, int numSommet, char* but, int limite);
NomSom* explorationEnProfondeurLimitee (GrapheMat* graphe, int numSommet, char* but, int limite);
void explorationEnProfondeurIterative(GrapheMat* graphe, int numSommet, char* but, int limite);
void explorationCoutUniforme(GrapheMat* graphe, int numSommet, char* but);
void explorationGloutonne(GrapheMat* graphe, int numSommet, char* but);
void explorationAetoile(GrapheMat* graphe, int numSommet, char* but);
char** plusProcheVoisin(GrapheMat* graphe, int numSommet);
int** two_opt(GrapheMat* graphe, char** chemin);
void escalade(GrapheMat* graphe, int numSommet);
#endif