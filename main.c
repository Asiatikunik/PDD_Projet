#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE_TAB 10
#define MIN_ALEA 1
#define MAX_ALEA 100

typedef struct TABLEAU TABLEAU;
struct TABLEAU {
    int array[TAILLE_TAB];
};

TABLEAU init_tab(TABLEAU tab);
void afficher_tab(TABLEAU tab);
int nb_aleatoire(int, int);
TABLEAU tableau_aleatoire(TABLEAU tab);


TABLEAU init_tab(TABLEAU tab){

	for(int i = 0; i < TAILLE_TAB; i++) 
		tab.array[i] = 0;

	return tab;
}

void afficher_tab(TABLEAU tab){
	for(int i = 0; i < TAILLE_TAB; i++) 
		printf("%d ", tab.array[i]);
	printf("\n");
}
 
int nb_aleatoire(int min, int max) {
    return rand()%(max-min+1) + min;
}

TABLEAU tableau_aleatoire(TABLEAU tab){

	for(int i= 0; i < TAILLE_TAB; i++)
		tab.array[i] = nb_aleatoire(MIN_ALEA, MAX_ALEA);

	return tab;
}

int main(void) {

	TABLEAU tab;

	srand((unsigned)time(NULL)); // A faire 1 fois, pour les fonctions aléatoire
	tab = init_tab(tab);
	afficher_tab(tab);

	tab = tableau_aleatoire(tab);
	afficher_tab(tab);


	// for(int i = 0; i < 10; ++i)
	// 	printf("%d\n", nb_aleatoire(1, 100));


	return EXIT_SUCCESS;
}