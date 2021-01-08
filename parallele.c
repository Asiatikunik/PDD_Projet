#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

/*
   Nous utilisons des define sur les paramètres qui peut être changer.
   Dans le but que cela soit plus rapide pour les tests.
 */
#define TAILLE_TAB 20 
#define NB_TAB 100 // Doit être plus petit que TAILLE_TAB
#define MIN_ALEA 1
#define MAX_ALEA 100

void afficher_tab(int** tab);
int nb_aleatoire(int min, int max);
void init_tab_alea(int** tab);
void fusion(int* tab, int debut, int milieu, int fin);
void triFusion(int* tab, int debut, int fin) ;
void tri_merge(int* tab1, int* tab2);
void tri_parallele(int** tab);


// Cette fonction permet d'afficher le tableau 
void afficher_tab(int** tab){
	printf("Affichage du tableau: \n");
	for(int s=0; s<NB_TAB; s++){
		for(int k=0; k<TAILLE_TAB; k++)
			printf("%3d ", tab[s][k]);
		printf("\n");
	}

	printf("\n\n");
}

/*	
	Sous fonction de initiation du tableau 
	Cette fonction permet de retournée un notre aléatoire
 */
int nb_aleatoire(int min, int max) {
	return rand()%(max-min+1) + min;
}

// Cette fonction permet d'initialisé le tableau avec des valeurs aléatoire
void init_tab_alea(int** tab){
	for(int s=0; s<NB_TAB; s++)
		for(int k=0; k<TAILLE_TAB; k++)
			tab[s][k] = nb_aleatoire(MIN_ALEA, MAX_ALEA);

}

/*
   Cette fonction est lié au triFusion.
   Elle prend un tableau en paramètre. Elle possède en réalité deux parties.
   debut -> milieu
   milieu+1 -> fin
   Qui sont deux sous tableaux trié
   Elle "retourne" le grand tableau trié
 */
void fusion(int* tab, int debut, int milieu, int fin) {
	int *tmp;
	int count1 = debut;
	int count2 = milieu+1;
	int i;

	tmp = malloc( (milieu - debut + 1) * sizeof(int));

	//on recopie les éléments du début du tab
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

// La fonction récursive pour l'application du tri fusion.
// C'est ici, que le divisé pour régné s'applique
void triFusion(int* tab, int debut, int fin) {
	if (debut < fin){

		// Trouvez le point milieu pour diviser le tableau en deux moitiés
		int milieu = (debut + fin) / 2;

		triFusion(tab, debut, milieu);
		triFusion(tab, milieu+1, fin);

		fusion(tab, debut, milieu, fin); // Fusionnez les deux moitiés triées
	}
}


/*
   Sous fonction de tri_parallele
   Cette fonction déplace les valeurs des tableaux,
   En paramètre, ce sont deux tableaux trié.
   les plus petit dans le tab1 et les plus grand dans tab2
   en les gardants trié.
 */
void tri_merge(int* tab1, int* tab2){

	int tmp[TAILLE_TAB*2];
	int count=TAILLE_TAB;
	int a=0, b=0;

	for(int i=0; i<TAILLE_TAB*2; i++){
		if (a == TAILLE_TAB){
			tmp[i] = tab2[b]; 
			b++;
		}else if (b == TAILLE_TAB){ 
			tmp[i] = tab1[a]; 
			a++;
		}else if(tab1[a] <= tab2[b]){
			tmp[i] = tab1[a];
			a++;
		}else{
			tmp[i] = tab2[b];
			b++;
		}
	}

	for(int i=0; i<TAILLE_TAB; i++)
		tab1[i] = tmp[i];

	for(int i=0; i<TAILLE_TAB; i++){
		tab2[i] = tmp[count];
		count++;
	}
}

/*
   Cette fonction permet trié un tableau deux dimensions.
   Elle utilise le tri fusion.
   Et tri merge.
 */
void tri_parallele(int** tab){
	int b1, b2;
	int max, min;
	int k;
	#pragma omp parallel for
	for(int i=0; i<NB_TAB; i++)
		triFusion(tab[i], 0, TAILLE_TAB);

	for (int j = 0; j < NB_TAB; j++) {
		k = 1+(j%2);
		#pragma omp parallel for
		for (int i = 0; i < NB_TAB/2; i++) {
			b1 = (k+2*i)%NB_TAB;
			b2 = (k+2*i+1)%NB_TAB;
			if(b1 < b2){
				min = b1;
				max = b2;
			}else{
				min = b2;
				max = b1;
			}
			tri_merge(tab[min], tab[max]);
		}
	}
}




int main(void) {

	double start = omp_get_wtime(); // Pour le tmp d'exec
	srand((unsigned)time(NULL)); // A faire 1 fois, pour les fonctions aléatoire

	// Allocation mémoire pour le tableau deux dimensions
	int **p_tab ;
	p_tab = malloc(sizeof(p_tab) * NB_TAB ) ;

	for(int i=0; i<NB_TAB; i++)
		p_tab[i] = malloc(TAILLE_TAB * sizeof(int));
	init_tab_alea(p_tab);
	//		afficher_tab(p_tab);

	tri_parallele(p_tab);
	//		afficher_tab(p_tab);

	// Le free du tableau alloué
	for(int i=0; i<NB_TAB; i++)
		free(p_tab[i]);
	free(p_tab);

	// Pour le tmp d'exec
	double stop = omp_get_wtime();
	double time = stop - start;
	printf("temps exec = %f\n",time);


	return EXIT_SUCCESS;
}


