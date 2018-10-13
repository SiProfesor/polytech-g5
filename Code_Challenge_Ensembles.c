// POLYTECH MARSEILLE - INFO3
// Algèbre
// Année 2018-2019
// Groupe 5 - Ex2 challenge

// ================

#include <stdio.h>
#include <stdlib.h>

#define VRAI (0 == 0)
#define FAUX (0 != 0)

typedef unsigned int bool;

//DESCRIPTION : Affiche un ensemble T donné (jusqu'à l'indice n - 1)
void afficher_ensemble_gr_05 (int *T, int n) {

  printf("{ ");
  for (int i = 0; i < n; i++) {
    printf("%d", *(T + i));

    if(i != n - 1) printf(" , ");
  }
  printf("}\n");
}

//DESCRIPTION : recherche si 'x' se trouve dans entre les bornes 'deb' et 'fin' (INCLUES) dans 'T' par dichotomie
bool recherche_dichotomique (int x, int *T, int deb, int fin) {

    int a, b, mid;
    a = deb; b = fin;
    while (b - a > 1) {

        mid = (b + a) / 2;
        
        if(*(T + mid) == x) { //Si on trouve l'élément, on sort de la boucle
            a = mid;
            b = mid;
        }
        else if(*(T + mid) > x) //Sinon, restriction des intervalles de recherche
            b = mid;
        else
            a = mid;
    }

    if(*(T + a) == x) //Si on a bien le bon résultat, on retourne l'index qui nous le donne
      return a;
    else //Sinon on retourne -1
      return -1;
}

//DESCRIPTION : affiche dans le terminal si l'élément 'x' appartient à l'ensemble 'T1' grâcé à une recherche par dichotomie
void appartient_gr_5(int x, int *T1, int s1, int n1) {

    //Vérification de la validité de la taille de T1
    if(n1 > s1) {
      printf("ALERTE : T1 possède un dépassement de capacité.\nLes éléments qui dépassent seront ignorés.\n");
      n1 = s1;
    }

    //Effectue une recherche dichotomique : on cherche si x est entre les bornes 'deb' et 'fin'
    int rech = recherche_dichotomique(x, T1, 0, n1 - 1);

    if(rech == -1) //Le résultat de 'recherche_dichotomique' retourne '-1' quand l'élément n'est pas dans le tableau
      printf("%d n'appartient pas à l'ensemble\n", x);
    else
      printf("%d appartient à l'ensemble (T[%d])\n", x, rech);
}

//DESCRIPTION : détermine si T1 est un ensemble INCLUS dans T2 (càd si tous les éléments de T1 appartiennent à T2)
void inclus_gr_05 (int *T1, int s1, int n1, int *T2, int s2, int n2) {

    //Vérification de la validité des tailles des ensembles (tableaux)
    if(n1 > s1) {
      printf("ALERTE : T1 possède un dépassement de capacité.\nLes éléments qui dépassent seront ignorés.\n");
      n1 = s1;
    }
    if(n2 > s2) {
      printf("ALERTE : T2 possède un dépassement de capacité.\nLes éléments qui dépassent seront ignorés.\n");
      n2 = s2;
    }

    //NOTE : on tient compte du fait qu'il n'y a aucun doublon et que les ensembles sont triés

    int i, minimum;
    bool res = VRAI; //Tant qu'on trouve les éléments de T1, alors l'inclusion est vérifiée

    i = 0;
    minimum = 0; //Le minimum sert à restreindre la recherche dichotomique car les tableaux sont triés
    while (i < n1 && res) {

        int rech = recherche_dichotomique(*(T1 + i), T2, minimum, n2 - 1);
        if(rech == -1) //Si la recherche dichotomique n'aboutit à rien, c'est que T1 c'est PAS inclus dans T2
          res = FAUX;
        else
          minimum = rech; //Accélère la recherche par dichotomie en augmentant la borne inférieure

        i++;
    }

    //Notifie du résultat
    if(res)
      printf("Inclus\n");
    else
      printf("Pas inclus\n");
}

//DESCRIPTION : crée un ensemble 'T3' de taille 'n3' qui représente l'union de 'T1' et 'T2'
void union_gr_05 (int *T1, int s1, int n1, int *T2, int s2, int n2, int *T3, int s3, int *n3) {
    
    //Si jamais l'ensemble de sortie n'a pas été initialisé, on réserve de la place en mémoire
    if(T3 == NULL) {
      printf("Ensemble de sortie indéfini.\n");
      T3 = malloc(s3 * sizeof(int));
    }

    int i, j, k; //Itérateurs qui désignent à quel case on se trouve pour T1, T2 et T3 respectivement
    i=0; j=0; k=0;
    while (i < n1 || j < n2) { //Tant que T1 et T2 n'ont pas été tous remplis...

        if(i >= n1 || (j < n2 && *(T1+i) > *(T2+j)) ) {

            //Quand T1 est complètement inséré, on passe à T2
            //    OU
            //s'il reste des éléments dans T1 ET T2, si jamais T1[i] > T2[j], c'est au tour de T2
            *(T3+k) = *(T2+j);
            j++;
        }
        else if(j >= n2 || (i < n1 && *(T1+i) < *(T2+j)) ) {
            //Réciproquement pour T2 cette fois
            *(T3+k) = *(T1+i);
            i++;
        }
        else {
            //Doublon : on place l'élément de T1 et on incrémente i et j
            *(T3+k) = *(T1+i);
            i++;
            j++;
        }

        k++; //Quand on a ajouté qqch dans T3, on passe à l'index suivant
    }

    *n3 = k; //La taille de T3 (donc n3) vaut le nombre d'insertions qu'on a fait (k)
}

void inter_gr_05 (int *T1, int s1, int n1, int *T2, int s2, int n2, int *T3, int s3, int *n3) {

    //Si jamais l'ensemble de sortie n'a pas été initialisé, on réserve de la place en mémoire
    if(T3 == NULL) {
      printf("Ensemble de sortie indéfini.\n");
      T3 = malloc(s3 * sizeof(int));
    }

    int i, k; //Itérateurs qui désignent à quel case on se trouve pour T1 et T3 respectivement
    int minimum; //Comme les ensembles sont ordonnés, quand on trouve un élément de T1 en j, on commencera la prochaine recherche à j + 1
   
    k=0;
    minimum = 0;
    for(i = 0; i < n1; i++) { //Pour chaque élément de T1, s'il se trouve dans T2, on l'ajoute à T3

        int rech = recherche_dichotomique(*(T1 + i), T2, minimum, n2 - 1);
        if(rech != -1) {
            *(T3+k) = *(T1+i);
            k++;
            minimum = rech;
        }
    }

    *n3 = k; //La taille de T3 (donc n3) vaut le nombre d'insertions qu'on a fait (k)
}

int main (void)
{

  //Création de 2 ensembles T1 et T2

  const int s1 = 10; //Capacités maximales respectives de T1 et T2
  const int s2 = 15;

  int n1 = 3; //Nombre actuel d'éléments dans T1 et T2
  int n2 = 7;

  int T1[s1]; //Les tableaux qui représentent T1 et T2
  int T2[s2];

  for(int i=0;i<n1;i++) T1[i]=i+2; //Initialisation
  for(int j=0;j<n2;j++) T2[j]=j;

  printf("T1 = "); afficher_ensemble_gr_05(T1, n1);
  printf("T2 = "); afficher_ensemble_gr_05(T2, n2);

  //Appartenance
  printf("\nAppartenance de 5 à T1 : "); appartient_gr_5(5, T1, s1, n1);
  printf("Appartenance de 5 à T2 : "); appartient_gr_5(5, T2, s2, n2);

  //Inclusion
  printf("\nInclusion de T1 dans T2 : "); inclus_gr_05(T1, s1, n1, T2, s2, n2);
  printf("Inclusion de T2 dans T1 : "); inclus_gr_05(T2, s2, n2, T1, s1, n1);

  //Création d'un ensemble T3
  const int s3 = 25;
  int n3 = 0;
  int T3[s3];

  //Union de T1 et T2
  union_gr_05(T1, s1, n1, T2, s2, n2, T3, s3, &n3);
  printf("\nT1 union T2 = "); afficher_ensemble_gr_05(T3, n3);

  //Intersection de T1 et T2
  inter_gr_05(T1, s1, n1, T2, s2, n2, T3, s3, &n3);
  printf("\nT1 inter T2 = "); afficher_ensemble_gr_05(T3, n3);

  return 0;

}