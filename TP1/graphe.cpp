#include "../Code_Graphe/graphemat.h"
#include "../Code_Liste/liste.h"
#include <iostream>
#include <cstring>

using namespace std;

namespace explorationGraphe {

    // Exploration eu largeur d'un graphe.
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
    void enProfondeur(GrapheMat* graphe, int numSommet, char* but){
        int nMax = graphe->nMax;
        graphe->marque [numSommet] = vrai;
        cout << graphe->nomS[numSommet];
        if(strcmp(graphe->nomS[numSommet], but) == 0){
            return;
        }
        for (int i=0; i<graphe->n; i++)
        {
            if ( (graphe->element [numSommet*nMax+i] == vrai)
                    && !graphe->marque [i] )
            {
                enProfondeur (graphe, i, but);
            }
        }
    }


    // Exploration en prondeur limitée d'un graphe.
    bool EPL(GrapheMat* graphe, int numSommet, char* but, int limite){
        if (numSommet < 0 || numSommet >= graphe->n) {
        cout << "Sommet de départ invalide\n";
        return false;
        }
        graphe->marque[numSommet] = vrai;
        cout << graphe->nomS[numSommet] << " ";
        if(strcmp(graphe->nomS[numSommet], but) == 0){
            return true;
        }else if (limite == 0){
            cout << "coupure";
            return false;
        }else{
            for (int i = 0; i < graphe->n; i++) {
            if (graphe->element[numSommet * graphe->nMax + i] == vrai && graphe->marque[i] == faux) {
                limite = limite - 1;
                EPL(graphe, i, but, limite);
            }
            }
            return false;
        }

    }

    // Exploration en profondeur itérative d'un graphe.
    void explorationEnProfondeurIterative(GrapheMat* graphe, int numSommet, char* but){
        int limite = 0;
        bool trouve = false;
        while(!trouve){
            trouve = EPL(graphe, numSommet, but, limite);
            limite++;
        }
    }

    // Exploration à coût uniforme d'un graphe.
    void explorationCoutUniforme(GrapheMat* graphe, int numSommet, char* but){

    initMarque(graphe);
    int* coutAcces = (int*)malloc(graphe->n * sizeof(int));
    for (int i = 0; i < graphe->n; i++) {
        coutAcces[i] = INFINI;
    }
    Liste* li = creerListe(1, NULL, NULL); 
    insererEnTeteDeListe(li, graphe->nomS[numSommet]);
    coutAcces[numSommet] = 0;

    while (!listeVide(li)) {

        char* sommetCourant = (char*) extraireEnTeteDeListe(li);

        cout << sommetCourant << " coût : " << coutAcces[rang(graphe, sommetCourant)];

        if(strcmp(sommetCourant, but) == 0){
            cout << "(but trouvée)";
            return;
        }

        int indiceSommetCourant = rang(graphe, sommetCourant);
                graphe->marque[indiceSommetCourant] = vrai;

        for (int i = 0; i < graphe->n; i++) {
            if (graphe->element[indiceSommetCourant * graphe->nMax + i] == vrai) {
                int nouveauCout = coutAcces[indiceSommetCourant] + graphe->valeur[indiceSommetCourant * graphe->nMax + i];
                if (nouveauCout < coutAcces[i]) {
                    coutAcces[i] = nouveauCout;
                    insererEnOrdre(li, graphe->nomS[i]);
                }
            }
        }
    }

    detruireListe(li);
    free(coutAcces);
    }
}