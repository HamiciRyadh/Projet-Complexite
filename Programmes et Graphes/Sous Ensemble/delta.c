#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void genererTableau(const int size);
int *lireTableau(char *name, int length);
void tri_fusion(int tab[], int deb, int fin);
void tri_fusion_fusionner(int tab[], int deb, int m, int fin);
int *calculer_delta_iteratif(int tab1[], int size1, int tab2[], int size2);
int *calculer_delta_recurcif(int tab1[], int size1, int tab2[], int size2);
int *calculer_delta(int tab1[], int size1, int idx1, int tab2[], int size2, int idx2, int *result, int idx);


int main(int argc, char *argv[]) {
	char *tab_files[] = {"10000.txt","20000.txt","30000.txt","40000.txt","50000.txt","60000.txt","70000.txt","80000.txt","90000.txt","100000.txt",
		"110000.txt","120000.txt","130000.txt","140000.txt","150000.txt","160000.txt"};
	int tab_lengths[] = {10000, 20000,30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000,
		110000, 120000, 130000, 140000, 150000, 160000};

	double deb, fin, tempExec, somme;
	int i, j;

	int *tab1, *tab2, *result;

	//for (j = 0; j < 16; j++) genererTableau(tab_lengths[j]);

	FILE *delta_iteratif = fopen("delta_iteratif.txt","w+");
	FILE *delta_recurcif = fopen("delta_recurcif.txt","w+");

	for (j = 0; j < 15; j++) {
		
		somme = 0;
		printf("N = %d\n", tab_lengths[j]);
		fprintf(delta_iteratif, "N = %d\n", tab_lengths[j]);
		for (i = 0; i < 10; i++) {
			tab1 = lireTableau(tab_files[j], tab_lengths[j]);
			tab2 = lireTableau(tab_files[j+1], tab_lengths[j+1]);
			deb = clock();
			tri_fusion(tab1, 0, tab_lengths[j] - 1);
			tri_fusion(tab2, 0, tab_lengths[j+1] - 1);
			result = calculer_delta_iteratif(tab1, tab_lengths[j], tab2, tab_lengths[j+1]);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d du delta iteratif terminee.\n", i+1);
			fprintf(delta_iteratif, "%lf\n", tempExec);
			somme += tempExec;
			free(result);
		}
		fprintf(delta_iteratif, "\nAvg = %lf\n\n", somme/10);
		
		somme = 0;
		printf("N = %d\n", tab_lengths[j]);
		fprintf(delta_recurcif, "N = %d\n", tab_lengths[j]);
		for (i = 0; i < 10; i++) {
			tab1 = lireTableau(tab_files[j], tab_lengths[j]);
			tab2 = lireTableau(tab_files[j+1], tab_lengths[j+1]);
			deb = clock();
			tri_fusion(tab1, 0, tab_lengths[j] - 1);
			tri_fusion(tab2, 0, tab_lengths[j+1] - 1);
			result = calculer_delta_recurcif(tab1, tab_lengths[j], tab2, tab_lengths[j+1]);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d du delta recurcif terminee.\n", i+1);
			fprintf(delta_recurcif, "%lf\n", tempExec);
			somme += tempExec;
			free(result);
		}
		fprintf(delta_recurcif, "\nAvg = %lf\n\n", somme/10);
	}

	fclose(delta_iteratif);
	fclose(delta_recurcif);
	return EXIT_SUCCESS;
}

int *calculer_delta_iteratif(int tab1[], int size1, int tab2[], int size2) {
	int idx1, idx2, cpt, i;
	int *tab, *result;

	tab = malloc((size1+size2)*sizeof(int));
	cpt = 0;
	idx1 = 0;
	idx2 = 0;

	while (idx1 < size1 && idx2 < size2) {
		if (tab1[idx1] == tab2[idx2]) {
			idx1++;
			idx2++;
		} else if (tab1[idx1] < tab2[idx2]) {
			tab[cpt] = tab1[idx1];
			idx1++;
			cpt++;
		} else {
			tab[cpt] = tab2[idx2];
			idx2++;
			cpt++;
		}
	}
	result = malloc((cpt + size1-idx1 + size2-idx2)*sizeof(int));

	for (i = 0; i < cpt; i++) {
		result[i] = tab[i];
	}

	free(tab);

	while (idx1 < size1) {
		result[cpt] = tab1[idx1];
		cpt++;
		idx1++;
	}

	while (idx2 < size2) {
		result[cpt] = tab2[idx2];
		cpt++;
		idx2++;
	}

	return result;
}

int *calculer_delta_recurcif(int tab1[], int size1, int tab2[], int size2) {
	int idx1, idx2, idx;
	int *result;

	result = malloc((size1+size2)*sizeof(int));
	idx = 0;
	idx1 = 0;
	idx2 = 0;

	return calculer_delta(tab1, size1, idx1, tab2, size2, idx2, result, idx);
}

int *calculer_delta(int tab1[], int size1, int idx1, int tab2[], int size2, int idx2, int *result, int idx) {
	if (idx1 == size1 && idx2 == size2) {
		int *deltaTab1Tab2, i;
		deltaTab1Tab2 = malloc(idx*sizeof(int));

		for (i = 0; i < idx; i++) {
			deltaTab1Tab2[i] = result[i];
		}
		free(result);

		return deltaTab1Tab2;
	}

	if (idx1 != size1 && idx2 == size2) {
		result[idx] = tab1[idx1];
		return calculer_delta(tab1, size1, idx1+1, tab2, size2, idx2, result, idx+1);
	}

	if (idx1 == size1 && idx2 != size2) {
		result[idx] = tab2[idx2];
		return calculer_delta(tab1, size1, idx1, tab2, size2, idx2+1, result, idx+1);
	}

	if (tab1[idx1] == tab2[idx2]) {
		idx1++;
		idx2++;
	} else if (tab1[idx1] < tab2[idx2]) {
		result[idx] = tab1[idx1];
		idx1++;
		idx++;
	} else {
		result[idx] = tab2[idx2];
		idx2++;
		idx++;
	}
	return calculer_delta(tab1, size1, idx1, tab2, size2, idx2, result, idx);
}

void genererTableau(const int size) {
	char name[20];
	int i, j, r, auth, *tab;
	sprintf(name, "%d.txt", size);
	FILE *file = fopen(name, "w+");

	srand(time(NULL));
	tab = malloc(size*sizeof(long));

	i = 0;
	while (i < size) {
		r =  rand()%32768;
		r = r<<16;
		r += rand()%32768;

		auth = 0;
		for (j = 0; j < i; j++) {
			if (tab[j] == r) {
				auth = 1;
				break;
			}
		}
		if (auth == 1) continue;
		tab[i] = r;
		i++;
	}

	fprintf(file, "%s", "{");
	for (i = 0; i < size; i++) {
		fprintf(file, "%d,", tab[i]);
	}

	fclose(file);
}

int *lireTableau(char *name, int length) {
	int i = 0, val = 0;
	int *t = calloc(length, sizeof(int));

	FILE *file = fopen(name,"r");
	if (fscanf(file, "{%d,", &val) != EOF) {
		t[i] = val;
		i++;
		while (fscanf(file, "%d,", &val) != EOF) {
			t[i] = val;
			i++;
		}
	}
	fclose(file);

	return t;
}

void tri_fusion(int tab[], int deb, int fin) {
	if (deb < fin) {
		int m = (deb+fin)/2;
		tri_fusion(tab, deb, m);
		tri_fusion(tab, m+1, fin);
		tri_fusion_fusionner(tab, deb, m, fin);
	}
}

void tri_fusion_fusionner(int tab[], int deb, int m, int fin) {
	int i, j, k, *t;
	t = calloc((fin-deb+1), sizeof(int));

	i = deb;
	j = m+1;
	k = 0;

	while (i <= m && j <= fin) {
		if (tab[i] < tab[j]) {
			t[k] = tab[i];
			i++;
		} else {
			t[k] = tab[j];
			j++;
		}
		k++;
	}

	if (i <= m) {
		for (j = i; j <= m; j++) {
			t[k] = tab[j];
			k++;
		}
	} else {
		for (i = j; i <= fin; i++) {
			t[k] = tab[i];
			k++;
		}
	}

	for (i = deb; i <= fin; i++) {
		tab[i] = t[i-deb];
	}

	free(t);
}
