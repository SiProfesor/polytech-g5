#include <stdio.h>
#include <stdlib.h>

//Implémentation de la struct zMaillon et des listes
typedef struct zMaillon {
	int value;
	struct zMaillon *next;
} maillon, *liste;

//-------------------- Fonctions de contrôle de liste --------------------

//DESC : créer une liste vide (pointeur nul)
liste creer_liste_vide_gr_05 (void) {
	return NULL;
}

//DESC : détermine si la liste '_l' est la liste vide
unsigned int est_liste_vide_gr_05 (liste _l) {
	return (_l == NULL);
}

//DESC : retourne une nouvelle liste qui contient '_val' en tête et '_l' en queue
liste inserer_gr_05 (liste _l, int _val) {

	liste nouveau = malloc(sizeof(maillon)); //Réservation en mémoire d'un nouveau pointeur vers un maillon
	nouveau->value = _val;
	nouveau->next = _l;

	return nouveau;
}

//DESC : retourne la valeur de la tête de liste (mais ne la supprime pas)
int tete_liste_gr_05 (liste _l) {
	return _l->value;
}

//DESC : retourne la sous-liste en queue de '_l'
liste queue_liste_gr_05 (liste _l) {
	return _l->next;
}

//DESC : libère la mémoire occupée par une liste
void cleanup_liste_gr_05 (liste _l) {

	if(!est_liste_vide_gr_05(_l))
		cleanup_liste_gr_05( _l->next );
	free(_l);
}



//-------------------- Fonctions esthétiques --------------------

//DESC : affiche la liste
void afficher_liste_gr_05 (liste _l) {

	if(est_liste_vide_gr_05(_l)){
		printf("\n");
		return;
	}

	printf("%d ", _l->value);
	afficher_liste_gr_05(_l->next);
}

//-------------------- Fonctions de tri de liste --------------------

//DESC : trie la liste '_l' selon la méthode du tri bulle
void trier_liste_gr_05 (liste _l) {

	unsigned int permutation = 0;

	liste debutTri = _l; //La première bulle à trier
	liste finTri = NULL; //La dernière bulle à trier (exclue) : sera définie lors de la première itération

	do {

		permutation = 0;
		liste p = debutTri; //On démarre le tri à ce maillon
		liste fin = finTri; //Variable temporaire qui contient la dernière bulle à trier

		while (!est_liste_vide_gr_05(p->next) && (fin == NULL || (p->value) != (fin->value) )) { //On trie chaque bulle (donc chaque maillon) jusqu'à l'avant dernier

			if( (p->value) > (p->next->value) ){ //Si la bulle est désordonnée, on la permutte

				int tmp = (p->value);
				(p->value) = (p->next->value);
				(p->next->value) = tmp;

				if(!permutation) {
					permutation = 1; //On a bien fait une permutation
					debutTri = p; //Il s'agit de la première bulle triée lors de cette itération
				}

				finTri = p; //Il s'agit de la dernière bulle triée lors de cette itération
				//Il sera donc inutile de retrier les prochains maillons si la valeur de 'finTri' n'est pas remodifiée
			}

			p = (p->next); //Passe au maillon suivant
		}
	} while (permutation);
}

//-------------------- Fonctions de vérification de palindrome --------------------

//DESC : inverse la liste 'l' - fonction auxilliaire
liste inverse_liste_rec_gr_05 (liste l, liste copie)
{
		if ( est_liste_vide_gr_05(l) ) return copie ;
		return inverse_liste_rec_gr_05 ( queue_liste_gr_05(l), inserer_gr_05 (copie, tete_liste_gr_05(l)) ) ;
}

//DESC : inverse la liste 'l'
liste inverse_liste_gr_05 (liste l)
{
		return inverse_liste_rec_gr_05 ( l, creer_liste_vide_gr_05() ) ;
}

//DESC : renvoie si la liste 'l' est un palindrome - fonction auxilliaire (compare avec la liste inverse 'l2')
int palindrome_aux_gr_05(liste l, liste l2)
{

	//On veut faire les tests sur la moitié de la liste (car l'autre moitié est représentée par l2)

	//Si pas fait, calcule la taille de la liste 'l' puis on fera la comparaison sur la moitié de 'l'
	static int remain = -1;
	//NOTE : NE PAS OUBLIER de reset la valeur 'remain' quand on a fini d'utiliser la fonction

	if(remain == -1) { //Si on a pas encore calculé le nbr d'étapes restantes (=> premier appel), on le fait maintenant

		remain = 1; //On commence à 1 test par défaut
		liste queue = l;
		while(!est_liste_vide_gr_05(queue_liste_gr_05(queue))){
			queue = queue_liste_gr_05(queue);
			remain++;
		}
		remain /= 2; //On ne fait les tests que sur la moitié
		//printf("Tests sur %d maillons\n", remain);
	}
	
	//La liste vide OU arrivé à la moitié de la liste => considéré comme un palindrome
	if(remain == 0 || (est_liste_vide_gr_05(l) && est_liste_vide_gr_05(l2)) ){
		remain = -1;
		return 1;
	}

	//Si les deux listes sont de tailles différentes --> pas palindrome
	if ( est_liste_vide_gr_05(queue_liste_gr_05(l)) != est_liste_vide_gr_05(queue_liste_gr_05(l2)) ){
		remain = -1;
		return 0;
	}
	
	//Si jamais le premier et dernier élément de l sont différents, ce n'est pas un palindrome
	if(tete_liste_gr_05(l) != tete_liste_gr_05(l2)){
		remain = -1;
		return 0;
	}

	//S'ils sont égaux, alors on regarde aux maillons suivants (donc le 2e et l'avant-dernier, etc...)
	remain--;
	return palindrome_aux_gr_05(queue_liste_gr_05(l), queue_liste_gr_05(l2));
}

//DESC : indique si la liste liste 'l' est un palindrome
int palindrome_gr_05(liste l)
{

	liste l2 = inverse_liste_gr_05(l);
	int result = palindrome_aux_gr_05(l,l2);

	cleanup_liste_gr_05(l2);

	return result;
}


int main (void) {

	//------ QUESTION 1 : tri de listes ------

	liste l = creer_liste_vide_gr_05();

	l = inserer_gr_05(l, 6);
	l = inserer_gr_05(l, 5);
	l = inserer_gr_05(l, 3);
	l = inserer_gr_05(l, 3);
	l = inserer_gr_05(l, 9);
	l = inserer_gr_05(l, 1);
	printf("Liste : "); afficher_liste_gr_05(l);

		//printf("Tete : %d\n", tete_liste_gr_05(l));
		//printf("Queue : "); afficher_liste_gr_05(queue_liste_gr_05(l));

	trier_liste_gr_05(l);
	printf("Trié : "); afficher_liste_gr_05(l);

	//------ QUESTION 2 : palindromes ------

	liste l2 = creer_liste_vide_gr_05(); //Test sur la fonction 'inverse_liste_gr_05'
	l2 = inverse_liste_gr_05(l);
	printf("Liste inverse de l: "); afficher_liste_gr_05(l2);
	cleanup_liste_gr_05(l2);

	printf("La liste l est-elle un palindrome : %d\n\n", palindrome_gr_05(l));
	cleanup_liste_gr_05(l);

	liste l_palin = creer_liste_vide_gr_05();
	l_palin = inserer_gr_05(l_palin, 1);
	l_palin = inserer_gr_05(l_palin, 2);
	l_palin = inserer_gr_05(l_palin, 3);
	l_palin = inserer_gr_05(l_palin, 3);
	l_palin = inserer_gr_05(l_palin, 2);
	l_palin = inserer_gr_05(l_palin, 1);

	printf("Liste l_palin: "); afficher_liste_gr_05(l_palin);
	printf("La liste l_palin est-elle un palindrome : %d\n", palindrome_gr_05(l_palin));

	cleanup_liste_gr_05(l_palin);

	return 0;
}
