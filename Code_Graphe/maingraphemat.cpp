#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphemat.h"
#include "liregraphe.h"

typedef GrapheMat Graphe;

int menu () {

  printf ("\n\nGRAPHES avec matrices\n\n");

  printf ("0 - Fin du programme\n");
  printf ("1 - Creation a partir d'un fichier\n");
  printf ("2 - Initialisation d'un graphe vide\n");
  printf ("3 - Ajout d'un sommet\n");
  printf ("4 - Ajout d'un arc\n");
  printf ("5 - Liste des sommets et des arcs\n");
  printf ("6 - Destruction du graphe\n");
  printf ("7 - Parcours en profondeur d'un graphe\n");
  printf ("8 - Floyd \n");
  printf ("------------------------------------------------\n");
  printf ("9 - Exploration en Profondeur d'un graphe\n");
  printf ("10 - Exploration en largeur d'un graphe\n");
  printf ("11 - Exploration En Profondeur Limit%ce \n", char(130));
  printf ("12 - Exploration en profondeur it%crative\n", char(130));
  printf ("13 - Exploration par cout uniforme\n");
  printf ("14 - Exploration gloutonne\n");
  printf("15- Exploration A*\n");
  printf ("------------------------------------------------\n");
  printf("16- Exploration par le plus proche voisin\n");
  printf("17- Exploration par Escalade 2-OPT\n");
  printf ("Votre choix ? ");
  int cod; scanf ("%d", &cod); getchar();
  printf ("\n");
  return cod;
}
int main () {
  Graphe* graphe;
  booleen fini = faux;
  while (!fini) {
    switch ( menu() ) {
    case 0:
      fini = vrai;
      break;
    case 1: {  // cr�ation � partir d'un fichier
      printf ("Nom du fichier contenant le graphe ? ");
      char nomFe [50];
      scanf  ("%s", nomFe);
      //strcpy (nomFe, "graphe.txt");
      FILE* fe = fopen (nomFe, "r");
      if (fe == NULL) {
        perror (nomFe);
      } else {
        graphe = lireGraphe (fe, 20); // 20 sommets maximum
        fclose (fe);
      }
      } break;
   case 2: {  // cr�ation d�un graphe vide
      printf ("Nombre maximum de sommets ? ");
      int nMaxSom; scanf  ("%d", &nMaxSom);
      printf ("0) non valu%c; 1) graphe valu%c ? ", char(130), char(130));
      int value; scanf ("%d", &value);

      graphe = creerGrapheMat (nMaxSom, value);

    } break;
    case 3: {  // ajouter un sommet
      printf ("Nom du sommet a ins%crer ? ", char(130));
      NomSom somD; scanf  ("%s", somD);
      ajouterUnSommet (graphe, somD);
    } break;
    case 4: {  // ajouter un arc
      printf ("Nom du sommet de d%cpart ? ", char(130));
      NomSom somD; scanf  ("%s", somD);
      printf ("Nom du sommet d'arriv%ce ? ", char(130));
      NomSom somA; scanf  ("%s", somA);
      int cout;
      if (graphe->value) {
        printf ("Cout de la relation ? ");
        scanf ("%d", &cout);
      } else {
        cout = 0;
      }
      ajouterUnArc (graphe, somD, somA, cout);
    } break;
    case 5:
      ecrireGraphe (graphe);
      break;
    case 6:
      detruireGraphe (graphe);
      break;
    case 7:
      parcoursProfond (graphe);
      break;
    case 8: {
     if (graphe->value) {
        printf ("\nLes plus courts chemins\n\n");
          floyd (graphe);
      } else {
        printf ("Graphe non valu%c\n", char(130));
      }
    } break;
    case 9:{
      // printf ("Nom du sommet but?");
      // char somD[10]; scanf  ("%s", &somD);
      // enProfondeur(graphe, somD);
      explorationEnProfondeurDabord(graphe);
    } break;
    case 10:{
      printf ("Nom du sommet but?");
      NomSom somD; scanf  ("%s", somD);
      enLargeur(graphe, 0, somD);
    } break;
    case 11:{
      printf ("Nom du sommet but?");
      NomSom somD; scanf  ("%s", somD);
      printf ("Limite de profondeur?");
      int limite; scanf  ("%d", &limite);
      explorationEnProfondeurLimitee(graphe, 0, somD, limite);
    } break;
    case 12:{
      printf ("Nom du sommet but?");
      NomSom somD; scanf  ("%s", somD);
      printf ("Limite de profondeur?");
      int limite; scanf  ("%d", &limite);
      explorationEnProfondeurIterative(graphe, 0, somD, limite);
    } break;
    case 13:{
      printf ("Nom du sommet but?");
      NomSom somD; scanf  ("%s", somD);
      explorationCoutUniforme(graphe, 0, somD);
    } break;
    case 14:{
      printf ("Nom du sommet but?");
      NomSom somD; scanf  ("%s", somD);
      explorationGloutonne(graphe, 0, somD);
    } break;
    case 15:{
      printf ("Nom du sommet but?");
      NomSom somD; scanf  ("%s", somD);
      explorationAetoile(graphe, 0, somD);
    } break;
    case 16:{
      printf ("Numero du Sommet de depart?");
      int somD; scanf  ("%i", &somD);
      plusProcheVoisin(graphe, somD);
    } break;
    case 17:{
      printf ("Numero du Sommet de depart?");
      int somD; scanf  ("%i", &somD);
      escalade(graphe, somD);
    } break;
    }   // switch
    if (!fini) {
      printf ("\n\nTaper Return pour continuer\n");
      getchar();
    }
  }

return 0;
}
