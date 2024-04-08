#include "../Code_Arbre/arbre.h"
#include "../Code_Liste/liste.h"
#include <iostream>
#include <cstring>

using namespace std;

namespace explorationArbre {

    // Exploration en largeur d'un arbre binaire.
    void enLargeur(Noeud* racine, char* (*afficher) (Objet*),int (*comparer) (Objet*, Objet*), Objet* but){
        Liste* li = creerListe(0, afficher, NULL);
        insererEnFinDeListe(li, racine);
        while(true){
            if(listeVide(li)){
                cout << " echec...";
                return;
            }
            
            Noeud* extrait = (Noeud*) extraireEnTeteDeListe(li);
            cout << afficher(extrait->reference) << " ";
            if(comparer(extrait->reference, but) == 0){
                    return;
            }
            if (extrait->gauche != NULL) insererEnFinDeListe (li,
                    extrait->gauche);
            if (extrait->droite != NULL) insererEnFinDeListe (li,
                    extrait->droite);
        }
    }

    // Exploration en profondeur préfixé d'un arbre binaire.
    /*void prefixe(Noeud* racine, char* (*afficher), int (*comparer) (Objet*, Objet*), Objet* but){
        if(racine == NULL){
            cout << "echec";
            return;
        }
        Liste* li = creerListe(0, afficher, NULL);
        insererEnFinDeListe(li, racine);
        while(true){
            if(listeVide(li)){
                cout << "echec";
                return;
            }else {
                Noeud* extrait = extraireEnFinDeListe(li);
                cout << afficher(extrait->reference) " ";
                if(comparer(extrait->reference, but)){
                    return;
                }
                if(extrait->droite){
                    insererEnFinDeListe(li, racine->droite);
                }
                if(extrait->gauche){
                    insererEnFinDeListe(li, racine->gauche);
                }
            }
        }
    }*/

    // Exploration en profondeur préfixé d'un arbre binaire.
    void prefixe(Noeud* racine, char* (*afficher) (Objet*), int (*comparer) (Objet*, Objet*), Objet* but){

        if(racine != NULL){
            cout << afficher(racine->reference);
            if(comparer(racine->reference, but) == 0){
                return;
            }
            prefixe(racine->gauche, afficher, comparer, but);
            prefixe(racine->droite, afficher, comparer, but);
        }
        cout << "echec";
        return;
    }

    // Exploration en profondeur infixé d'un arbre binaire
    void infixe(Noeud* racine, char* (*afficher) (Objet*), int (*comparer) (Objet*, Objet*), Objet* but){
        if(racine != NULL){
            infixe(racine->gauche, afficher, comparer, but);
            cout << afficher(racine->reference) << " ";
            if(comparer(racine->reference, but) == 0){
                return;
            }
            infixe(racine->droite, afficher, comparer, but);
        }
        cout << "echec";
        return;
        
    }

    // Exploration en profondeur postfixé d'un arbre binaire
    void postfixe(Noeud* racine, char* (*afficher) (Objet*), int (*comparer) (Objet*, Objet*), Objet* but){
        if(racine != NULL){
            postfixe(racine->gauche, afficher, comparer, but);
            postfixe(racine->droite, afficher, comparer, but);
            cout << afficher(racine->reference) << " ";
            if(comparer(racine->reference, but) == 0){
                return;
            }
        }
        cout << "echec";
        return;
        
    }

    // Exploration en profondeur limité d'un arbre binaire (prefixé)
    bool EPL_prefixe(Noeud* racine, char* (*afficher) (Objet*), int (*comparer) (Objet*, Objet*), Objet* but, int limite){
        if(racine != NULL && limite >= 0){
            cout << afficher(racine->reference) << " ";
            if(comparer(racine->reference, but) == 0){
                return true;
            }
            EPL_prefixe(racine->gauche, afficher, comparer, but, limite-1);
            EPL_prefixe(racine->droite, afficher, comparer, but, limite-1);
        }
        cout << "echec";
        return false;
    }

    // Exploration en profondeur limité d'un arbre binaire (infixé)
    bool EPL_infixe(Noeud* racine, char* (*afficher) (Objet*), int (*comparer) (Objet*, Objet*), Objet* but, int limite){
        if(racine != NULL && limite >= 0){
            EPL_infixe(racine->gauche, afficher, comparer, but, limite-1);
            cout << afficher(racine->reference) << " ";
            if(comparer(racine->reference, but) == 0){
                return true;
            }
            EPL_infixe(racine->droite, afficher, comparer, but, limite-1);
        }
        cout << "echec";
        return false;
    }

    // Exploration en profondeur limité d'un arbre binaire (postfixé)
    bool EPL_postfixe(Noeud* racine, char* (*afficher) (Objet*), int (*comparer) (Objet*, Objet*), Objet* but, int limite){
        if(racine != NULL && limite >= 0){
            EPL_postfixe(racine->gauche, afficher, comparer, but, limite-1);
            EPL_postfixe(racine->droite, afficher, comparer, but, limite-1);
            cout << afficher(racine->reference) << " ";
            if(comparer(racine->reference, but) == 0){
                return true;
            }
        }
        cout << "echec";
        return false;  
    }

    // Exploration iterative en profendeur d'un arbre binaire (prefixé)
    void explorationIterativeEnProfondeurPrefixe(Noeud* racine, char* (*afficher) (Objet*), int (*comparer) (Objet*, Objet*), Objet* but){
        int limite = 0;
        bool trouve = false;
        while(!trouve){
            trouve = EPL_prefixe(racine, afficher, comparer, but, limite);
            limite++;
        }
    }

    // Exploration iterative en profendeur d'un arbre binaire (infixé)
    void explorationIterativeEnProfondeurInfixe(Noeud* racine, char* (*afficher) (Objet*), int (*comparer) (Objet*, Objet*), Objet* but){
        int limite = 0;
        bool trouve = false;
        while(!trouve){
            trouve = EPL_infixe(racine, afficher, comparer, but, limite);
            limite++;
        }
    }

    // Exploration iterative en profendeur d'un arbre binaire (postfixé)
    void explorationIterativeEnProfondeurPostfixe(Noeud* racine, char* (*afficher) (Objet*), int (*comparer) (Objet*, Objet*), Objet* but){
        int limite = 0;
        bool trouve = false;
        while(!trouve){
            trouve = EPL_postfixe(racine, afficher, comparer, but, limite);
            limite++;
        }
    }
    
}
