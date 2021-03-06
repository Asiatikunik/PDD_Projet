#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE_TAB 10000
#define MIN_ALEA 1
#define MAX_ALEA 10000


int nb_aleatoire(int min, int max); 
void init_tab_alea(int* tab);
void afficher_tab(int* tab);
void fusion(int* tab, int debut, int milieu, int fin);
void triFusion(int* tab, int debut, int fin);


int nb_aleatoire(int min, int max) {
    return rand()%(max-min+1) + min;
}

void init_tab_alea(int* tab){
	for(int s=0; s<TAILLE_TAB; s++){
		tab[s] = nb_aleatoire(MIN_ALEA, MAX_ALEA);
	}
}

void afficher_tab(int* tab){
	printf("Affichage du tableau: \n");
	for(int s=0; s<TAILLE_TAB; s++){
		printf("%d ", tab[s]);
	}
	printf("\n");
}

void fusion(int* tab, int debut, int milieu, int fin){
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;
 
    int G[n1], D[n2];
 
    for (int i = 0; i < n1; i++)
        G[i] = tab[debut + i];
    for (int j = 0; j < n2; j++)
        D[j] = tab[milieu + 1 + j];
 
    // maintient trois pointeurs, un pour chacun des deux tableaux et un pour
    // maintenir l'index actuel du tableau trié final
    int i, j, k;
    i = 0;
    j = 0;
    k = debut;
 
    while (i < n1 && j < n2){
        if (G[i] <= D[j]){
            tab[k] = G[i];
            i++;
        }else{
            tab[k] = D[j];
            j++;
        }
        k++;
    }
 
    // Copiez tous les éléments restants du tableau non vide
    while (i < n1) {
        tab[k] = G[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        tab[k] = D[j];
        j++;
        k++;
    }
}
     
// Tri par fusion
void triFusion(int* tab, int debut, int fin) {
    if (debut < fin){
 
        // Trouvez le point milieu pour diviser le tableau en deux moitiés
        int milieu = (debut + fin) / 2;
 
        triFusion(tab, debut, milieu);
        triFusion(tab, milieu+1, fin);
 
        // Fusionnez les deux moitiés triées
        fusion(tab, debut, milieu, fin);
    }
}

int main(void) {

	int* p_tab = NULL;
	p_tab = malloc(TAILLE_TAB * sizeof(int));
	srand((unsigned)time(NULL)); // A faire 1 fois, pour les fonctions aléatoire

	init_tab_alea(p_tab);
	afficher_tab(p_tab);

	triFusion(p_tab, 0, TAILLE_TAB);
	afficher_tab(p_tab);

	free(p_tab);


	return EXIT_SUCCESS;
}