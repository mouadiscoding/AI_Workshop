#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include "graphemat.h"
#include "liregraphe.h"

using namespace std;   

booleen  grapheDetruit = vrai;


static int nb_voisins = 0;


static int length = 0 ;
static booleen found = false ;


// remise � z�ro du tableau de marquage
static void initMarque (GrapheMat* graphe)
{

    for (int i=0; i<graphe->n; i++) graphe->marque [i] = faux;
}

GrapheMat* creerGrapheMat (int nMax, int value)
{
    // allocation de graphe
    GrapheMat* graphe  = (GrapheMat*) malloc (sizeof (GrapheMat));
    graphe->n       = 0;
    graphe->nMax    = nMax;
    graphe->value   = value; // value : vrai si le graphe est valu�
    graphe->nomS    = (NomSom*)  malloc (sizeof(NomSom)  *nMax);
    graphe->marque  = (booleen*) malloc (sizeof(booleen) *nMax);
    graphe->element = (int*)     malloc (sizeof(int)*nMax*nMax);
    graphe->valeur  = (int*)     malloc (sizeof(int)*nMax*nMax);
    // initialisation par d�faut
    for (int i=0; i<nMax; i++)
    {
        for (int j=0; j<nMax; j++)
        {
            graphe->element [i*nMax+j] = faux;
            graphe->valeur  [i*nMax+j] = INFINI;
        }
    }
    initMarque (graphe);
    grapheDetruit = faux;
    return graphe;
}


// d�sallocation d'un graphe
void detruireGraphe (GrapheMat* graphe)
{
    free (graphe->nomS);
    free (graphe->marque);
    free (graphe->element);
    free (graphe->valeur);
    free (graphe);
    grapheDetruit = vrai;
}

static int rang (GrapheMat* graphe, NomSom nom)
{
    int      i      = 0;
    booleen  trouve = faux;
    while ( (i<graphe->n) && !trouve)
    {
        trouve = strcmp (graphe->nomS [i], nom) == 0;
        if (!trouve) i++;
    }
    return trouve ? i : -1;
}

void ajouterUnSommet (GrapheMat* graphe, NomSom nom)
{
    if (rang (graphe, nom) == -1)
    {
        if (graphe->n < graphe->nMax)
        {
            strcpy (graphe->nomS [graphe->n++], nom);
        }
        else
        {
            printf ("\nNombre de sommets > %d\n", graphe->nMax);
        }
    }
    else
    {
        printf ("\n%s d�j� d�fini\n", nom);
    }
}

void ajouterUnArc (GrapheMat* graphe, NomSom somD, NomSom somA, int cout)
{
    int nMax = graphe->nMax;
    int rd = rang (graphe, somD);
    int rg = rang (graphe, somA);
    graphe->element [rd*nMax+rg] = vrai;
    graphe->valeur  [rd*nMax+rg] = cout;
}

void ecrireGraphe (GrapheMat* graphe)
{
    if (grapheDetruit == vrai)
    {
        printf ("Le graphe a ete detruit ou n'est pas encore cree\n");
    }
    else
    {
        int nMax = graphe->nMax;
        for (int i=0; i<graphe->n; i++) printf ("%s ", graphe->nomS[i]);
        printf (";\n");
        for (int i=0; i<graphe->n; i++)
        {
            printf ("\n%s : ", graphe->nomS[i]);
            for (int j=0; j<graphe->n; j++)
            {
                if (graphe->element [i*nMax+j] == vrai)
                {
                    printf ("%s ", graphe->nomS[j]) ;
                    if (graphe->value)
                    {
                        printf (" (%3d) ", graphe->valeur [i*nMax+j] );
                    }
                }
            }
            printf (";");
        }
    }
}


static void ecrireEtape (Matrice a, Matrice p, int k, int ns, int nMax)
{
    printf ("\n A implementer");
}

// initialiser les matrices a et p � partir de graphe
static void initFloyd (GrapheMat* graphe, Matrice* a, Matrice* p)
{
    printf ("\n A implementer");
}

void floyd (GrapheMat* graphe)
{
     printf ("\n A implementer");
}


static void profondeur (GrapheMat* graphe, int numSommet)
{
    int nMax = graphe->nMax;
    graphe->marque [numSommet] = vrai;
    printf ("%s\n", graphe->nomS [numSommet]);
    for (int i=0; i<graphe->n; i++)
    {
        if ( (graphe->element [numSommet*nMax+i] == vrai)
                && !graphe->marque [i] )
        {
            profondeur (graphe, i);
        }
    }
}


void parcoursProfond (GrapheMat* graphe)
{
    initMarque (graphe);
    for (int i=0; i<graphe->n; i++)
    {
        if (!graphe->marque [i]) profondeur (graphe, i);
    }
}


// ---------------------------------------------------------------------
void enLargeur(GrapheMat* graphe, int numSommet, char* but) {

    if (numSommet < 0 || numSommet >= graphe->n) {
        cout << "Numéro de sommet invalide\n";
        return;
    }
    initMarque(graphe);
    Liste* li = creerListe(0, NULL, NULL); 

    insererEnFinDeListe(li, graphe->nomS[numSommet]);
    graphe->marque[numSommet] = vrai;

    while (!listeVide(li)) {
        char* sommetCourant = (char*) extraireEnTeteDeListe(li);
        cout << sommetCourant << " ";
        if(strcmp(sommetCourant, but) == 0){
            cout << "but trouvé!";
            return;
        }
        int indiceSommetCourant = rang(graphe, sommetCourant);
        for (int i = 0; i < graphe->n; i++) {
            if (graphe->element[indiceSommetCourant * graphe->nMax + i] == vrai &&
                graphe->marque[i] == faux) {
                graphe->marque[i] = vrai;
                insererEnFinDeListe(li, graphe->nomS[i]);
            }
        }
    }
    detruireListe(li);
    }

// Exploration en profondeur d'un graphe.
/*
void enProfondeur(GrapheMat* graphe, int numSommet, char* but){
    bool trouve = false;
    int nMax = graphe->nMax;
    Liste* li = creerListe(0, NULL, NULL);
    insererEnFinDeListe(li, graphe->nomS[numSommet]);
    graphe->marque [numSommet] = vrai;
    while (!listeVide(li)) {
        char* sommetCourant = (char*) extraireEnFinDeListe(li);
        int numSommet = rang(graphe, sommetCourant);
        cout << sommetCourant << " ";
        if(strcmp(sommetCourant, but) == 0){
            trouve = true;
            cout << "but trouvé!";
            return;
        }
        for (int i = graphe->n; i > 0; i--) {
            if ((graphe->element[numSommet*nMax+i] == vrai) && (graphe->marque[i] == faux)) {
                //cout << " insertion " << i << " ";
                insererEnFinDeListe(li, graphe->nomS[i]);
                graphe->marque[i] = vrai;
            }
        }
        // si il y a des noeuds isolés
        for (int i=0; i < graphe->n; i++) {
            if (listeVide(li) && !graphe->marque[i]){
                insererEnFinDeListe (li, graphe->nomS [i]);
                graphe->marque[i] = vrai;
                break;
            }
        }
    }
    if(!trouve) cout << "\nle but " << but << " n'existe pas dans le graphe.";
    detruireListe(li);
}
*/
void enProfondeur (GrapheMat* graphe, const char* but) {
    bool trouve = faux;
    int nMax = graphe->nMax;
    int numSommet = 0;
    Liste* li = creerListe(0, NULL, NULL);
    insererEnFinDeListe (li, graphe->nomS[numSommet]);
    graphe->marque[numSommet] = vrai;

    while(!listeVide (li)){
        // extraire l'element a partir de la liste
        Objet* extrait =  extraireEnFinDeListe(li);
        char* valeurExtraite = (char*)extrait;
        numSommet = rang(graphe, valeurExtraite);
        cout << graphe->nomS [numSommet] << " ";
        // vérification de l'état but
        if (strcmp(graphe->nomS [numSommet], but) == 0){
            cout << "but trouvé!";
            return;
        } 

        // ajout des fils dans la frontiere 
        for (int i=graphe->n; i > 0; i--) {
            if ( (graphe->element [numSommet*nMax+i] == vrai) && !graphe->marque [i] ) {
                insererEnFinDeListe (li, graphe->nomS [i]);
                graphe->marque[i] = vrai;
            }
        }
        // si il y a des noeuds isolés
        for (int i=0; i < graphe->n; i++) {
            if (listeVide(li) && !graphe->marque[i]){
                insererEnFinDeListe (li, graphe->nomS [i]);
                graphe->marque[i] = vrai;
                break;
            }
        }
    }
    if(!trouve) cout << "\nle but " << but << " n'existe pas dans le graphe.";
    detruireListe(li);
}
NomSom* explorationEnProfondeurDabord (GrapheMat* graphe, const char* but) {
    int numSommet = 0;
    int nMax = graphe->nMax;
    Liste* frontiere = creerListe(0, NULL, NULL); // initialisation de la frontiere
    insererEnFinDeListe (frontiere, graphe->nomS[0]); // 0 est l'indice du premiet sommet
    graphe->marque[0] = vrai;

    while(!listeVide (frontiere)){
        // extraire l'element a partir de la liste
        Objet* extrait =  extraireEnFinDeListe(frontiere);
        char* valeurExtraite = (char*)extrait;
        numSommet = rang(graphe, valeurExtraite);
        printf ("%s\n", graphe->nomS [numSommet]);

        // vérification de l'état but
        if (strcmp(graphe->nomS [numSommet], but) == 0) return (NomSom*)graphe->nomS [numSommet];

        // ajout des fils dans la frontiere 
        for (int i=graphe->n; i > 0; i--) {
            if ( (graphe->element [numSommet*nMax+i] == vrai) && !graphe->marque [i] ) {
                insererEnFinDeListe (frontiere, graphe->nomS [i]);
                graphe->marque[i] = vrai;
            }
        }
        // si il y a des noeuds isolés
        for (int i=0; i < graphe->n; i++) {
            if (listeVide(frontiere) && !graphe->marque[i]){
                insererEnFinDeListe (frontiere, graphe->nomS [i]);
                graphe->marque[i] = vrai;
                break;
            }
        }
    }
    return NULL;
}

void explorationEnProfondeurDabord (GrapheMat* graphe){
    // on initialise tout les noeuds comme non explore
    initMarque (graphe);
    char but[10]; NomSom* solution = NULL;
    printf("Veuillez saisire le but: ");
    scanf("%s", &but);
    printf("\n");
    solution = explorationEnProfondeurDabord (graphe, but);
    if (solution != NULL) printf("\nLe but %s existe dans l'arbre.", solution);
    else printf("\nLe but %s n'existe pas dans l'arbre.", but);
}
    // Exploration en prondeur limitée d'un graphe.
NomSom* EPL_Recursive(GrapheMat* graphe, int numSommet, char* but, int limite){
    if (numSommet < 0 || numSommet >= graphe->n) {
    cout << "Sommet de départ invalide\n";
    return NULL;
    }
    if (limite < 0) return NULL;
    graphe->marque[numSommet] = vrai;
    cout << graphe->nomS[numSommet] << " ";
    if(strcmp(graphe->nomS[numSommet], but) == 0){
        return (NomSom*)graphe->nomS [numSommet];
    }else if (limite == 0) {
        return NULL;
    }else{
        for (int i = 0; i < graphe->n; i++) {
            if (graphe->element[numSommet * graphe->nMax + i] == vrai && graphe->marque[i] == faux) {
                NomSom* resultat = EPL_Recursive(graphe, i, but, limite-1);
                if(resultat != NULL) return resultat;
            }
        }
        return NULL;
    }
}

NomSom* explorationEnProfondeurLimitee (GrapheMat* graphe, int numSommet, char* but, int limite) {
    return EPL_Recursive (graphe, numSommet, but, limite);
}

// Exploration en profondeur itérative d'un graphe.
void explorationEnProfondeurIterative(GrapheMat* graphe, int numSommet, char* but, int limite){
    NomSom* resultat;
    for(int i = 0; i<limite; i++){
        initMarque (graphe);
        cout << "Iteration " << i << ": \n";
        resultat = explorationEnProfondeurLimitee(graphe, 0, but, i);
        if (resultat != NULL) {
            cout << " Solution trouv" << char(130) << "e!";
            return;
        }
        cout << "\n";
    }
    if (resultat == NULL) {
        cout << "le but " << but << " n'existe pas dans le graphe.";
    }
}

Noeud* creerNoeud(Noeud* parent, char* nom, int cout){
    Noeud* noeud = (Noeud*)malloc(sizeof(Noeud));
    noeud->parent = parent;
    noeud->nom = nom;
    noeud->cout = cout;
    return noeud;
}

static int comparerNoeud(Objet* a, Objet* b){
    Noeud* noeudA = (Noeud*)a;
    Noeud* noeudB = (Noeud*)b;
    return noeudA->cout > noeudB->cout ? 1 : -1;
}

Noeud* chercherUnNoeud(Liste* li, Noeud* noeud){
    bool trouve = faux;
    Noeud* noeudCourant;
    while (!listeVide(li) && !trouve){
        noeudCourant = (Noeud*)extraireEnTeteDeListe(li);
        if (strcmp(noeudCourant->nom, noeud->nom) == 0) trouve = vrai;
    }
    return trouve ? noeudCourant : NULL;
}

char*  afficherChemin(Noeud* noeud, char* chemin )
{
    if (noeud != NULL)
    {
        afficherChemin(noeud->parent, chemin);
        strcat(chemin, noeud->nom);
        strcat(chemin, " ");
    }
    return chemin ;
}



// Exploraiton  à coût uniforme d'un graphe.
void explorationCoutUniforme(GrapheMat* graphe, int numSommet, char* but){
    initMarque(graphe);
    int* couts = (int*)malloc(graphe->n * sizeof(int));
    for(int i = 0; i < graphe->n; i++){
        couts[i] = 0;
    }
    booleen trouve = faux;
    Noeud* noeudBut = (Noeud*)malloc(sizeof(Noeud));
    Liste* li = creerListe(1, NULL, comparerNoeud);
    Noeud* racine = creerNoeud(NULL, graphe->nomS[numSommet], 0);
    insererEnOrdre(li, racine);
    graphe->marque[numSommet] = vrai;
    while(!listeVide(li)){
        Noeud* noeudParent = (Noeud*)extraireEnTeteDeListe(li);
        char* nomParent = noeudParent->nom;
        int numParent = rang(graphe, nomParent);
        graphe->marque[numParent] = vrai;
        cout << nomParent << " ";
        if(strcmp(nomParent, but) == 0){
            noeudBut = noeudParent;
            cout << "But trouv" << char(130) << "! ";
            trouve = vrai;
            break;
        }
        for(int i = 0; i < graphe->n; i++){
            if(graphe->element[numParent*graphe->nMax+i] == vrai){
                if(!graphe->marque[i]){
                    int coutCourant = graphe->valeur[numParent*graphe->nMax+i];
                    char* nomFils = graphe->nomS[i];
                    couts[i] = coutCourant + couts[numParent];
                    Noeud* noeudFils = creerNoeud(noeudParent, nomFils, couts[i]);
                    insererEnOrdre(li, noeudFils);
                }else if( ( couts[numParent] + graphe->valeur[numParent*graphe->nMax+i] ) < couts[i] ){
                    int coutCourant = graphe->valeur[numParent*graphe->nMax+i];
                    char* nomFils = graphe->nomS[i];
                    couts[i] = coutCourant + couts[numParent];
                    Noeud* noeudFils = creerNoeud(noeudParent, nomFils, couts[i]);
                    insererEnOrdre(li, noeudFils);
                }
            }
        }
    }

    if (trouve) {
        char* chemin = (char*)malloc(sizeof(100));
        afficherChemin(noeudBut, chemin);
        cout << "\nLe plus court Chemin: " << chemin << endl;
        cout << "Cout Total: " << noeudBut->cout << endl;
        free(chemin);
    }else{
        cout << "Le but " << but << " n'existe pas dans le graphe.";
    }
    free(noeudBut);
    free(couts);
    detruireListe(li);

}

// Exploration gloutonne par le meilleur d'abord d'un graphe.
void explorationGloutonne(GrapheMat* graphe, int numSommet, char* but){
    bool trouve = faux;
    int heuristique[] = {366, 374, 329, 244, 253, 178, 193, 98, 0};
    initMarque(graphe);
    int* couts = (int*)malloc(graphe->n * sizeof(int));
    for(int i = 0; i < graphe->n; i++){
        couts[i] = 0;
    }
    Noeud* noeudBut = (Noeud*)malloc(sizeof(Noeud));
    Liste* li = creerListe(1, NULL, comparerNoeud);
    Noeud* racine = creerNoeud(NULL, graphe->nomS[numSommet], 0);
    racine->heuristique = heuristique[numSommet];
    insererEnOrdre(li, racine);
    graphe->marque[numSommet] = vrai;
    while(!listeVide(li) && !trouve){
        Noeud* noeudParent = (Noeud*)extraireEnTeteDeListe(li);
        char* nomParent = noeudParent->nom;
        int numParent = rang(graphe, nomParent);
        graphe->marque[numParent] = vrai;
        cout << nomParent << " ";
        if(strcmp(nomParent, but) == 0){
            noeudBut = noeudParent;
            cout << "But trouv" << char(130) << "! ";
            trouve = vrai;
            break;
        }
        for(int i = 0; i < graphe->n; i++){
            if(graphe->element[numParent*graphe->nMax+i] == vrai){
                if(!graphe->marque[i]){
                    char* nomFils = graphe->nomS[i];
                    int coutCourant = heuristique[i];                    
                    couts[i] = coutCourant + couts[numParent];
                    Noeud* noeudFils = creerNoeud(noeudParent, nomFils, couts[i]);
                    noeudFils->heuristique = heuristique[i];
                    insererEnOrdre(li, noeudFils);
                }else if( ( couts[numParent] + graphe->valeur[numParent*graphe->nMax+i] ) < couts[i] ){
                    char* nomFils = graphe->nomS[i];
                    int coutCourrant = heuristique[i];
                    couts[i] = coutCourrant + couts[numParent];
                    Noeud* noeudFils = creerNoeud(noeudParent, nomFils, couts[i]);
                    noeudFils->heuristique = heuristique[i];
                    insererEnOrdre(li, noeudFils);
                }
            }
        }
    }
    
    if (trouve) {
        char* chemin = (char*)malloc(sizeof(100));
        afficherChemin(noeudBut, chemin);
        cout << "\nLe plus court Chemin: " << chemin << endl;
        cout << "Cout Total: " << noeudBut->cout << endl;
        free(chemin);
    }else{
        cout << "Le but " << but << " n'existe pas dans le graphe.";
    }
    free(noeudBut);
    free(couts);
    detruireListe(li);
}

// Exploration A* d'un graphe.
void explorationAetoile(GrapheMat* graphe, int numSommet, char* but){
    bool trouve = faux;
    int heuristique[] = {366, 253, 329, 374, 176, 380, 193, 0, 160, 100};
    initMarque(graphe);
    int* couts = (int*)malloc(graphe->n * sizeof(int));
    for(int i = 0; i < graphe->n; i++){
        couts[i] = 0;
    }
    Noeud* noeudBut = (Noeud*)malloc(sizeof(Noeud));
    Liste* li = creerListe(1, NULL, comparerNoeud);
    Noeud* racine = creerNoeud(NULL, graphe->nomS[numSommet], 0);
    racine->heuristique = heuristique[numSommet];
    insererEnOrdre(li, racine);
    graphe->marque[numSommet] = vrai;
    while(!listeVide(li) && !trouve){
        Noeud* noeudParent = (Noeud*)extraireEnTeteDeListe(li);
        char* nomParent = noeudParent->nom;
        int numParent = rang(graphe, nomParent);
        graphe->marque[numParent] = vrai;
        cout << nomParent << " ";
        cout << noeudParent->cout << "\n ";
        if(strcmp(nomParent, but) == 0){
            noeudBut = noeudParent;
            cout << "But trouv" << char(130) << "! ";
            trouve = vrai;
        }
        for(int i = 0; i < graphe->n; i++){
            if(graphe->element[numParent*graphe->nMax+i] == vrai){
                if(!graphe->marque[i]){
                    char* nomFils = graphe->nomS[i];
                    int coutCourant = heuristique[i] + graphe->valeur[numParent*graphe->nMax+i];                    
                    couts[i] = coutCourant;
                    Noeud* noeudFils = creerNoeud(noeudParent, nomFils, couts[i]);
                    noeudFils->heuristique = heuristique[i];
                    insererEnOrdre(li, noeudFils);
                }else if( ( couts[numParent] + graphe->valeur[numParent*graphe->nMax+i] + heuristique[i] ) < couts[i] ){
                    char* nomFils = graphe->nomS[i];
                    int coutCourrant = heuristique[i] + graphe->valeur[numParent*graphe->nMax+i];
                    couts[i] = coutCourrant;
                    Noeud* noeudFils = creerNoeud(noeudParent, nomFils, couts[i]);
                    noeudFils->heuristique = heuristique[i];
                    insererEnOrdre(li, noeudFils);
                }
            }
        }
    }
    if (trouve) {
        char* chemin = (char*)malloc(sizeof(100));
        afficherChemin(noeudBut, chemin);
        cout << "\nLe plus court Chemin: " << chemin << endl;
        cout << "Cout Total: " << noeudBut->cout << endl;
        free(chemin);
    }else{
        cout << "Le but " << but << " n'existe pas dans le graphe.";
    }
    free(noeudBut);
    free(couts);
    detruireListe(li);
    
}


// Algorithme du plus proche voisin
char** plusProcheVoisin(GrapheMat* graphe, int numSommet){
    initMarque(graphe);
    char* nom;
    int indice = 0;
    int nMax = graphe->nMax;
    int cout_plus_proche = 0;
    char* depart = graphe->nomS[numSommet] ;
    char ** chemin = (char **) malloc((graphe->n + 1) * sizeof(char*));
    chemin[indice++] = depart;
    Liste* li = creerListe(0, NULL, comparerNoeud);
    Noeud* racine = creerNoeud(NULL, depart, 0);
    Noeud* PlusProcheVoisin;
    insererEnFinDeListe(li, racine);
    Liste* li_temporaire;
    while(!listeVide(li)) {
        printf("%d\n", indice);
        li_temporaire = creerListe(1, NULL, comparerNoeud);
        Noeud* extrait = (Noeud*) extraireEnTeteDeListe(li);
        int indice_extrait = rang(graphe, extrait->nom);
        graphe->marque[indice_extrait] = vrai;
        for(int i = 0; i < graphe->n; i++) {
            if(graphe->element[indice_extrait*nMax+i] && !graphe->marque[i] && i != indice_extrait ) {
                int cout = graphe->valeur[indice_extrait*nMax+i];
                char* nomFils = (char *) graphe->nomS[i];
                Noeud* noeudFils = (Noeud *) creerNoeud(extrait, nomFils, cout);
                insererEnOrdre(li_temporaire, noeudFils);
            }
        }
        PlusProcheVoisin = (Noeud*)extraireEnTeteDeListe(li_temporaire);
        if (PlusProcheVoisin != NULL) {
            insererEnFinDeListe(li, PlusProcheVoisin);
            nom = PlusProcheVoisin->nom;
            chemin[indice++] = PlusProcheVoisin->nom;
            cout_plus_proche += PlusProcheVoisin->cout;
        }
        free(li_temporaire);
    }
    cout_plus_proche += graphe->valeur[numSommet * nMax + rang(graphe, nom)];
    chemin[indice++] = depart;
    length = indice;
    printf("Le plus proche voisin: ");
    for (int i = 0; i < indice; i++) {
        printf("%s ", chemin[i]);
    }
    printf("\n");
    printf("Cout total: %d\n", cout_plus_proche);
    return chemin;
}

static void show_indices(GrapheMat* graphe, char** path )
{
    for (int i = 0 ; i < length ; i++)
    {
        if(i !=  length  - 1 )
            printf("%d - ", rang(graphe, path[i]));
        else
            printf("%d", rang(graphe, path[i]));
    }
}
static void show_indices(GrapheMat* graphe, int* path )
{
    for (int i = 0 ; i < length ; i++)
    {
        if(i != length - 1 )
            printf("%d - ", path[i]);
        else
            printf("%d", path[i]);
    }
}

static void show_path(GrapheMat* graphe, int* path)
{
     for (int i = 0 ; i < length ; i++)
    {
        if(i != length - 1 )
            printf("%s - ", graphe->nomS[path[i]]);
        else
            printf("%s", graphe->nomS[path[i]]);
    }
}

int* get_indices(GrapheMat* graphe, char** path)
{
    int* indices = (int *)malloc(length * sizeof(int));
    for (int j = 0 ; j < length; j++)
    {
        indices[j] = rang(graphe, path[j]);
    }
    return indices;
}

static char** get_path(GrapheMat* graphe, int* path)
{
    char ** spath = (char**)malloc(sizeof(char*) * length) ;
    for (int i= 0; i< length; i++)
    {
        spath[i] = graphe->nomS[path[i]];
    }
    return spath;
}
static int path_cost(GrapheMat* graphe ,int* path)
{
    int nMax = graphe->nMax;
    int path_cost = 0 ;
    for (int i = 1; i< length ; i++)
    {
        path_cost += graphe->valeur[path[i-1]*nMax + path[i]];
    }
    return path_cost;
}

static void copy_to(int* from, int* to, int start = 0, int limit = length)
{
    for(int i= start; i< limit; i++)
    {
        to[i] = from[i];
    }
}
static int* swap(int* tab, int i, int j)
{
    int* new_tab = (int *)malloc(length * sizeof(int));
    copy_to(tab, new_tab,0, length);
    new_tab[i] = tab[j];
    new_tab[j] = tab[i];
    return new_tab;

}

Path* creerPath (int* ipath, char** spath, int cost)
{
    Path * path = (Path *) malloc(sizeof(Path));
    path->cost = cost;
    path->ipath = ipath;
    path->spath = spath;

    return path ;
}

char *  afficher_path(Noeud* node, char * all )
{
    if (node != NULL)
    {
        afficher_path(node->parent, all);
        strcat(all, node->nom);
        strcat(all, " -> ");
    }
    return all ;
}
static char* show_path(Objet* o)
{
    Path * p = (Path*)o ;
    char * spath = (char*)malloc(sizeof(char*) * length) ;
    for (int i= 0; i< length; i++)
    {
        strcat(spath, p->spath[i]);
    }
    return spath;

}

static int compare_path(Objet* n1, Objet* m1)
{
    Path * n = (Path *)n1 ;
    Path * m = (Path*)m1 ;
    if (n->cost > m->cost ) return 1;
    else if (n->cost == m->cost ) return 0;
    else return -1 ;
}

int** two_opt(GrapheMat* graphe, char** chemin){
    int k = 0;
    int** list_indices = (int**) malloc(length * sizeof(int*));
    int* indices_initials = get_indices(graphe, chemin);
    int* temp = (int*)malloc(length * sizeof(int));
    copy_to(indices_initials, temp, 0, length);
    printf("----------------------\n");
    show_indices(graphe, indices_initials); printf("\t");
    show_path(graphe, indices_initials); printf("\n");
    int cout = path_cost(graphe, indices_initials);
    printf("Cout initial: %d\n", cout);
    printf("Tours voisins \n");
    for(int i = 0; i < length - 2; i++)
    {
        int* nouveau_temp = get_indices(graphe, chemin);
        for(int j = i + 2; j < length - 1; j++)
        {
            if (i == 0 && j == length - 2) continue;
            int* nouveau_indices = swap(nouveau_temp, i + 1, j);
            list_indices[k] = nouveau_indices;
            k++;
            printf("(%d,%d) , (%d,%d)    --> \t",nouveau_temp[i], nouveau_temp[i+1], nouveau_temp[j], nouveau_temp[j+1]);
            show_indices(graphe, nouveau_temp);
            printf("\n");
        }
        free(nouveau_temp);
    }
    nb_voisins = k;
    printf("Liste des indices: \n");
    for(int i = 0; i < nb_voisins; i++)
    {
        show_indices(graphe, list_indices[i]);
        printf("\t"); show_path(graphe, list_indices[i]);
        printf("\t"); printf("Cout: %d\n", path_cost(graphe, list_indices[i]));
    }
    return list_indices;
}


void escalade(GrapheMat* graphe, int numSommet) {
    Liste* li = creerListe(1, NULL, comparerNoeud);
    int* meilleur_chemin = (int*)malloc((graphe->n + 1) * sizeof(int));
    char** pvc = plusProcheVoisin(graphe, numSommet);
    int* indice_pvc = get_indices(graphe, pvc);
    int cout = path_cost(graphe, indice_pvc);
    Path* chemin = creerPath(indice_pvc, pvc, cout);
    insererEnFinDeListe(li, chemin);
    while(!listeVide(li)){
        Liste* temp_li = creerListe(1, (char *(*)(Objet *))show_path, compare_path);
        Path * extrait = (Path *)extraireEnTeteDeListe(li);
        int** voisins = two_opt(graphe, extrait->spath);
        for(int i = 0; i < nb_voisins; i++){
            Path* voisin = creerPath(voisins[i], get_path(graphe, voisins[i]), path_cost(graphe, voisins[i]));
            insererEnOrdre(temp_li, voisin);
            show_path(voisin);
        }
        Path* meilleur_voisin = (Path*)extraireEnTeteDeListe(temp_li);
        if(path_cost(graphe, meilleur_voisin->ipath) < cout ){
            insererEnFinDeListe(li, meilleur_voisin);
            cout = path_cost(graphe, meilleur_voisin->ipath);
            copy_to(meilleur_voisin->ipath, meilleur_chemin, 0);
            free(meilleur_voisin);
        }
        else break;

    }
    printf("\nEscalade 2-OPT: \n");
    show_path(graphe, meilleur_chemin);
    printf("\n");
    printf("Cout: %d\n", path_cost(graphe, meilleur_chemin));
}

