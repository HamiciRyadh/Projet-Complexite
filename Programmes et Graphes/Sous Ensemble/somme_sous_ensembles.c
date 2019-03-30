#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef struct Ensemble {
	int length;
	int somme;
	int *tab;
} Ensemble;

typedef struct List {
	Ensemble e;
	struct List *svt;
} List;


Ensemble sommeSousEnsembleIteratif(int tab[], int n, int value);
void afficherEnsemble(Ensemble e);
void freeList(List *tete);


int main(int argc, char *argv[]) {
	int i, j, k, value;
	double deb, fin, tempExec, somme;
	Ensemble result;

	int *ensemble = malloc(40*sizeof(int));
	for (i = 0; i < 10; i++) ensemble[i] = i;
	FILE *somme_sous_ensembles_iteratif = fopen("somme_sous_ensembles_iteratif.txt","w+");
	srand(time(NULL));
	
	for (i = 10; i < 40; i++) {
		printf("N = %d\n", i);
		ensemble[i] = i;

		value = rand()%(i*i);
		printf("Valeur a chercher : %d.\n", value);
		somme = 0;
		fprintf(somme_sous_ensembles_iteratif, "N = %d\n", i);
		for (j = 0; j < 10; j++) {
			deb = clock();
			result = sommeSousEnsembleIteratif(ensemble, i, value);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d terminee.\n", j+1);
			afficherEnsemble(result);
			fprintf(somme_sous_ensembles_iteratif, "%lf\n", tempExec);
			somme += tempExec;
			fflush(somme_sous_ensembles_iteratif);
		}
		fprintf(somme_sous_ensembles_iteratif, "\nAvg = %lf\n\n", somme/10);
		fflush(somme_sous_ensembles_iteratif);
	}

	fclose(somme_sous_ensembles_iteratif);

	return EXIT_SUCCESS;
}

Ensemble sommeSousEnsembleIteratif(int tab[], int n, int value) {
	List *tete = NULL, *tete2 = NULL, *fin = NULL, *fin2 = NULL, *curr = NULL;
	tete = malloc(sizeof(List));

	//Ensemble vide
	(tete->e).length = 0;
	(tete->e).somme = 0;
	(tete->e).tab = NULL;
	tete->svt = NULL;
	fin = tete;

	int i, j;
	for (i = 0; i < n; i++) {
		//On ne prend pas en considération cette valeur car elle est deja superieur a la valeur recherchee
		if (tab[i] > value) continue;

		tete2 = malloc(sizeof(List));

		//1er element = ensemble contenant le nombre seul
		(tete2->e).length = 1;
		(tete2->e).somme = tab[i];
		(tete2->e).tab = malloc(sizeof(int));
		(tete2->e).tab[0] = tab[i];
		tete2->svt = NULL;

		if (tab[i] == value) {
			freeList(tete);
			return tete2->e;
		}

		//Sauter le 1er element (ensemble vide)
		curr = tete;
		curr = (curr->svt);
		fin2 = tete2;
		while (curr != NULL) {
			if ((curr->e).somme + tab[i] > value) {
				curr = (curr->svt);
				continue;
			}

			fin2->svt = malloc(sizeof(List));
			fin2 = fin2->svt;

			(fin2->e).length = (curr->e).length + 1;
			(fin2->e).somme = (curr->e).somme + tab[i];
			(fin2->e).tab = malloc((fin2->e).length*sizeof(int));
			(fin2->e).tab[0] = tab[i];

			for (j = 1; j < (fin2->e).length; j++) {
				(fin2->e).tab[j] = (curr->e).tab[j-1];
			}

			if ((fin2->e).somme == value) {
				freeList(tete);
				return fin2->e;
			}

			curr = (curr->svt);
		}
		fin2->svt = NULL;

		fin->svt = tete2;
		fin = fin2;
	}

	freeList(tete);

	Ensemble result;
	result.somme = 0;
	result.length = 0;
	result.tab = NULL;
	return result;
}

void freeList(List *tete) {
	List *temps;

	while (tete != NULL) {
		temps = tete;
		tete = tete->svt;
		free((temps->e).tab);
		free(temps);
	}
}

void afficherEnsemble(Ensemble e) {
	printf("{");
	int i;
	for (i = 0; i < e.length; i++) {
		printf("%d,", e.tab[e.length-i-1]);
	}
	printf("}\n");
	printf("Somme : %d.\n", e.somme);
}