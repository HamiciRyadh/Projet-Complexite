#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 14

typedef struct Ensemble {
	int length;
	int *tab;
} Ensemble;

typedef struct List {
	Ensemble e;
	struct List *svt;
} List;

List *sousEnsembles(int tab[], int deb, int fin);
List *sousEnsembles_fusionner(List *liste1, List* liste2, int tab[], int m);
Ensemble sommeSousEnsemble(List *liste, int value);
List *sousEnsemblesIteratif(int tab[], int n);
List *sousEnsembleRecurcif(int tab[], int n);
void afficher(List *liste);
void afficherEnsemble(Ensemble e);
void freeList(List *tete);


int main(int argc, char *argv[]) {
	int i, j, k;
	double deb, fin, tempExec, somme;
	List *liste;

	int *ensemble = malloc(40*sizeof(int));
	for (i = 0; i < 10; i++) ensemble[i] = i;
	FILE *sous_ensembles_iteratif = fopen("sous_ensembles_iteratif.txt","w+");
	FILE *sous_ensembles_recurcif = fopen("sous_ensembles_recurcif.txt","w+");

	for (i = 10; i < 40; i++) {
		printf("N = %d\n", i);
		ensemble[i] = i;

		somme = 0;
		fprintf(sous_ensembles_iteratif, "N = %d\n", i);
		for (j = 0; j < 10; j++) {
			deb = clock();
			liste = sousEnsemblesIteratif(ensemble, i);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d iterative terminee.\n", j+1);
			fprintf(sous_ensembles_iteratif, "%lf\n", tempExec);
			somme += tempExec;
			freeList(liste);
			fflush(sous_ensembles_iteratif);
		}
		fprintf(sous_ensembles_iteratif, "\nAvg = %lf\n\n", somme/10);

		somme = 0;
		fprintf(sous_ensembles_recurcif, "N = %d\n", i);
		for (j = 0; j < 10; j++) {
			deb = clock();
			liste = sousEnsemblesIteratif(ensemble, i);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d iterative terminee.\n", j+1);
			fprintf(sous_ensembles_recurcif, "%lf\n", tempExec);
			somme += tempExec;
			freeList(liste);
			fflush(sous_ensembles_recurcif);
		}
		fprintf(sous_ensembles_recurcif, "\nAvg = %lf\n\n", somme/10);
	}

	fclose(sous_ensembles_iteratif);
	fclose(sous_ensembles_recurcif);
	/*
	int i, j, value = 138457;

	int ensemble[N] = {1,2,7,14,49,98,343,686,2409,2793,16808,17206,111705,117993};
	List *liste = sousEnsemblesIteratif(ensemble, N);
	List *liste2 = sousEnsembleRecurcif(ensemble, N);
	//afficher(liste);

	//Iterative
	Ensemble res = sommeSousEnsemble(liste, value);
	if (res.length == -1) printf("Aucune solution.\n");
	else afficherEnsemble(res);

	//Recurcive
	res = sommeSousEnsemble(liste2, value);
	if (res.length == -1) printf("Aucune solution.\n");
	else afficherEnsemble(res);
	*/
	return 0;
}

List *sousEnsemblesIteratif(int tab[], int n) {
	List *tete = NULL, *tete2 = NULL, *fin = NULL, *fin2 = NULL, *curr = NULL;
	tete = malloc(sizeof(List));

	//Ensemble vide
	(tete->e).length = 0;
	(tete->e).tab = NULL;
	tete->svt = NULL;
	fin = tete;

	int i, j;
	for (i = 0; i < n; i++) {
		tete2 = malloc(sizeof(List));

		//1er element = ensemble contenant le nombre seul
		(tete2->e).length = 1;
		(tete2->e).tab = malloc(sizeof(int));
		(tete2->e).tab[0] = tab[i];
		tete2->svt = NULL;

		//Eviter de faire un test sur la tete a chaque iteration
		curr = tete;
		curr = (curr->svt);
		fin2 = tete2;
		while (curr != NULL) {
			fin2->svt = malloc(sizeof(List));
			fin2 = fin2->svt;

			(fin2->e).length = (curr->e).length + 1;
			(fin2->e).tab = malloc((fin2->e).length*sizeof(int));
			(fin2->e).tab[0] = tab[i];

			for (j = 1; j < (fin2->e).length; j++) {
				(fin2->e).tab[j] = (curr->e).tab[j-1];
			}

			curr = (curr->svt);
		}
		fin2->svt = NULL;

		fin->svt = tete2;
		fin = fin2;
	}

	return tete;
}

Ensemble sommeSousEnsemble(List *liste, int value) {
	List *curr = liste;
	Ensemble e;
	int i, somme;
	while (curr != NULL) {
		somme = 0;
		e = curr->e;
		for (i = 0; i < e.length; i++) {
			somme += e.tab[i];
		}
		if (somme == value) return e;
		curr = curr->svt;
	}

	e.length = -1;
	return e;
}

void afficher(List *liste) {
	List *curr = liste;
	while (curr != NULL) {
		afficherEnsemble(curr->e);
		curr = (curr->svt);
	}
}

void afficherEnsemble(Ensemble e) {
	printf("{");
	int i;
	for (i = 0; i < e.length; i++) {
		printf("%d,", e.tab[e.length-i-1]);
	}
	printf("}\n");
}

List *sousEnsembleRecurcif(int tab[], int n) {
	List *liste = NULL, *temps = NULL;
	liste = sousEnsembles(tab, 0, n-1);

	temps = malloc(sizeof(List));
	(temps->e).length = 0;
	temps->svt = liste;

	return temps;
}

List *sousEnsembles(int tab[], int deb, int fin) {
	if (deb < fin) {
		int m = (deb+fin)/2;
		List *liste1 = sousEnsembles(tab, deb, m);
		List *liste2 = sousEnsembles(tab, m+1, fin);
		return sousEnsembles_fusionner(liste1, liste2, tab, m);
	}
	return NULL;
}

List *sousEnsembles_fusionner(List *liste1, List* liste2, int tab[], int m) {
	List *liste = NULL, *fin = NULL, *curr1 = NULL, *curr2 = NULL, *prec = NULL;
	int i;

	if (liste1 == NULL) {
		fin = malloc(sizeof(List));
		(fin->e).length = 1;
		(fin->e).tab = malloc(sizeof(int));
		(fin->e).tab[0] = tab[m];

		liste = fin;
	}
	if (liste2 == NULL) {
		fin = malloc(sizeof(List));
		(fin->e).length = 1;
		(fin->e).tab = malloc(sizeof(int));
		(fin->e).tab[0] = tab[m+1];

		if (liste == NULL) liste = fin;
		else liste->svt = fin;
	}

	if (liste1 != NULL && liste2 != NULL) {
		List *prec2 = NULL;
		curr1 = liste1;
		while (curr1 != NULL) {
			curr2 = liste2;
			while (curr2 != NULL) {
				if (liste == NULL) {
					liste = malloc(sizeof(List));
					fin = liste;
				} else {
					fin->svt = malloc(sizeof(List));
					fin = fin->svt;
				}
				
				(fin->e).length = (curr1->e).length + (curr2->e).length;
				(fin->e).tab = malloc((fin->e).length*sizeof(int));

				for (i = 0; i < (curr1->e).length; i++) {
					(fin->e).tab[i] = (curr1->e).tab[i];
				}

				for (i = 0; i < (curr2->e).length; i++) {
					(fin->e).tab[i+(curr1->e).length] = (curr2->e).tab[i];
				}

				prec2 = curr2;
				curr2 = curr2->svt;
			}
			prec = curr1;
			curr1 = curr1->svt;
		}
		prec->svt = liste2;
		prec2->svt = liste;
		fin = NULL;
		return liste1;
	} else if (liste1 != NULL && liste2 == NULL) {
		curr1 = liste1;
		while (curr1 != NULL) {
			fin->svt = malloc(sizeof(List));
			fin = fin->svt;

			(fin->e).length = (curr1->e).length + 1;
			(fin->e).tab = malloc((fin->e).length*sizeof(int));

			for (i = 0; i < (curr1->e).length; i++) {
				(fin->e).tab[i] = (curr1->e).tab[i];
			}

			(fin->e).tab[(fin->e).length-1] = tab[m+1];

			prec = curr1;
			curr1 = curr1->svt;
		}
		prec->svt = liste;
		fin->svt = NULL;
		return liste1;
	} else if (liste1 == NULL && liste2 != NULL) {
		curr2 = liste2;
		while (curr2 != NULL) {
			fin->svt = malloc(sizeof(List));
			fin = fin->svt;

			(fin->e).length = (curr2->e).length + 1;
			(fin->e).tab = malloc((fin->e).length*sizeof(int));

			for (i = 0; i < (curr2->e).length; i++) {
				(fin->e).tab[i] = (curr2->e).tab[i];
			}

			(fin->e).tab[(fin->e).length-1] = tab[m];

			prec = curr2;
			curr2 = curr2->svt;
		}
		prec->svt = liste;
		fin->svt = NULL;
		return liste2;
	} else if (liste1 == NULL && liste2 == NULL) {
		fin->svt = malloc(sizeof(List));
		fin = fin->svt;

		(fin->e).length = 2;
		(fin->e).tab = malloc(2*sizeof(int));
		(fin->e).tab[1] = tab[m];
		(fin->e).tab[0] = tab[m+1];
		
		fin->svt = NULL;
		return liste;
	}
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