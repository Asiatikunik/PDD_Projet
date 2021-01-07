#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define TAILLE_TAB 21474836
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

void fusion(int* tab, int debut, int milieu, int fin) {
	int *tmp;
	int count1 = debut;
	int count2 = milieu+1;
	int i;

	tmp = malloc( (milieu - debut + 1) * sizeof(int));

	for(i=debut; i<=milieu; i++) 
		tmp[i-debut] = tab[i];
	

	for(i=debut; i<=fin; i++) {        
		if (count1 == milieu+1) 
			break; 
		else if (count2 == (fin+1)){ 
			tab[i] = tmp[count1-debut];
			count1++;
		} else if ( tmp[count1-debut] < tab[count2]){
			tab[i] = tmp[count1-debut];
			count1++;
		} else {
			tab[i] = tab[count2];
			count2++;
		}
	}
	free(tmp);
}

// Tri par fusion
void triFusion(int* tab, int debut, int fin) {
	if (debut < fin){

		// Trouvez le point milieu pour diviser le tableau en deux moitiés
		int milieu = (debut + fin) / 2;
		omp_set_num_threads(4); 
		#pragma omp task 
		
		triFusion(tab, debut, milieu);
		triFusion(tab, milieu+1, fin);
		
		#pragma omp taskwait
		// Fusionnez les deux moitiés triées
		fusion(tab, debut, milieu, fin);
		
	}
}

int main(void) {
	//On prend le tmps début du prog
	double start = omp_get_wtime();
	int* p_tab = NULL;
	p_tab = malloc(TAILLE_TAB * sizeof(int));
	srand((unsigned)time(NULL)); // A faire 1 fois, pour les fonctions aléatoire

	init_tab_alea(p_tab);
	//	afficher_tab(p_tab);

	triFusion(p_tab, 0, TAILLE_TAB);
	//	afficher_tab(p_tab);

	free(p_tab);
	//On affiche le temps de fin du prog
	double stop = omp_get_wtime();
	double time = stop - start;
	printf("temps exec = %f\n",time);
	return EXIT_SUCCESS;
}
