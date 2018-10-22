#include <stdio.h>
#include <stdlib.h>

//Implémentation de la struct zMaillon et des piles
typedef struct zMaillon {
	int value;
	struct zMaillon *next;
} maillon, *pile;


//-------------------- Fonctions de contrôle de pile --------------------

//DESC : créer une pile vide (pointeur nul)
pile creer_pile_vide_gr_05 (void) {
	return NULL;
}

//DESC : détermine si la pile '_p' est la pile vide
unsigned int est_pile_vide_gr_05 (pile _p) {
	return (_p == NULL);
}


//DESC : retourne une nouvelle pile qui contient '_val' en tête et '_p' en queue
pile push_gr_05 (pile _p, int _val) {

	pile nouveau = malloc(sizeof(maillon)); //Réservation en mémoire d'un nouveau pointeur vers un maillon
	nouveau->value = _val;
	nouveau->next = _p;

	return nouveau;
}


//DESC : retourne la valeur de la tête de pile (mais ne la supprime pas)
int top_gr_05 (pile _p) {
	if(est_pile_vide_gr_05(_p))
		printf("Erreur : on prend le top d'une pile vide !\n");
	return _p->value;
}

//DESC : retourne la sous-pile en queue de '_p'
pile pop_gr_05 (pile _p) {
	if(est_pile_vide_gr_05(_p))
		return _p;
	return _p->next;
}

//DESC : libère la mémoire occupée par une pile
void cleanup_pile_gr_05 (pile _p) {

	if(!est_pile_vide_gr_05(_p))
		cleanup_pile_gr_05( pop_gr_05(_p) );
	free(_p);
}

//-------------------- Fonctions esthétiques --------------------

//DESC : affiche la pile
void afficher_pile_gr_05 (pile _p) {

	if(est_pile_vide_gr_05(_p)){
		//printf("PILE VIDE\n");
		return;
	}

	printf("%d ", top_gr_05(_p));
	afficher_pile_gr_05(pop_gr_05(_p));
}

//-------------------- Expressions arithmétiques --------------------

int calcul_expression_gr_05 (char *expr) {

	int i;
	pile p;

	int interruption = 0; //Si jamais on a interrompu le calcul, on arrête l'exécution de la fonction

	//On empile les opérandes de la chaîne dans un pile, et on les dépile dès qu'on croise un opérateur
	i  = 0;
	p = creer_pile_vide_gr_05();
	while (*(expr + i) != '\0' && interruption == 0) {

		int caractere = (int)*(expr + i);
		
		if(caractere >= 42 && caractere <= 47) { //S'il s'agit d'un opérateur

			int operation = 0;

			//Vérifie si on peut effectuer l'opération : si la pile n'a pas 2 éléments, l'expression n'est pas correcte, on arrête le calcul
			if(est_pile_vide_gr_05(pop_gr_05(p)))
				interruption = 1;
			else if(caractere == 42) //On calcule parmi les opérations *, +, - et / respectivement
				operation = top_gr_05(p) * top_gr_05(pop_gr_05(p));
			else if(caractere == 43)
				operation = top_gr_05(p) + top_gr_05(pop_gr_05(p));
			else if(caractere == 45)
				operation = top_gr_05(p) - top_gr_05(pop_gr_05(p));
			else if(caractere == 47)
				operation = top_gr_05(p) / top_gr_05(pop_gr_05(p));
			else //Le symbole saisi n'est pas un opérateur arithmétique : on abandonne le calcul
				interruption = 1;

			//printf("%d (op) %d = %d\n", top_gr_05(p), top_gr_05(pop_gr_05(p)), operation);

			p = pop_gr_05(pop_gr_05(p)); //On supprime de la pile les 2 éléments consommés dans l'opération
			p = push_gr_05(p, operation); //On ajoute à la pile le résultat trouvé
		}
		else if(caractere >= 48 && caractere <= 57) { //Sinon on empile le nombre dans 'p', il sera utilisé plus tard
			
			p = push_gr_05(p, caractere-48); //NOTE : l'entier 0 est codé 48, 1 codé 49, ...
		}
		else { //S'il s'agit d'un caractère qui n'est ni opérateur, ni un chiffre, il y a une erreur
			interruption = 1;
		}

		i++;
	}

	//Si on a rencontré une erreur ou si la pile contient 0 ou plusieurs nombres, c'est qu'il y a eu un problème
	if(interruption == 1 || est_pile_vide_gr_05(p) || !est_pile_vide_gr_05(pop_gr_05(p))){
		printf("[Erreur] Expression saisie invalide.\n");
		cleanup_pile_gr_05(p);
		return 0;
	}

	//Le résultat est correct
	int resultat = top_gr_05(p);
	cleanup_pile_gr_05(p);

	return resultat;
}

int main(void) {
	
	char chaine[] = "14+5*32*+"; //Correspond à l'expression ((1+4)*5)+(3*2)
	char chaine2[] = "145+*32*+"; //Correspond à l'expression ((1*(4+5))+(3*2)
	char chaine3[] = "145+$32*+"; //Mauvaise chaine (caractère non reconnu)
	char chaine4[] = "16+7*+";//Chaine avec une expression invalide (un opérateur en trop)
	char chaine5[] = "";//Chaine vide
	char chaine6[] = "16+7*8";//Chaine avec une expression invalide (un nombre en trop)

	printf("Le résultat de chaine : %d\n", calcul_expression_gr_05(chaine));
	printf("Le résultat de chaine2 : %d\n", calcul_expression_gr_05(chaine2));
	printf("Le résultat de chaine3 : %d\n", calcul_expression_gr_05(chaine3));
	printf("Le résultat de chaine4 : %d\n", calcul_expression_gr_05(chaine4));
	printf("Le résultat de chaine5 : %d\n", calcul_expression_gr_05(chaine5));
	printf("Le résultat de chaine6 : %d\n", calcul_expression_gr_05(chaine6));

    return 0;
}
