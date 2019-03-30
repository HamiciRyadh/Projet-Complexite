#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void genererTableau(const int size);
int *lireTableau(char *name, const int length);
void trisMinimumSuccessif(int tab[], int n);
void trisBulle(int *tab, int n);
int posMin(int tab[], int n, int startPos);
void permuter(int tab[], int pos1, int pos2);
int partition(int tableau[], int deb, int fin);
void tri_rapide(int tableau[],int debut,int fin);
int *tri_denombrement(int tab[], int n, int k);
void tri_fusion(int tab[], int deb, int fin);
void tri_fusion_fusionner(int tab[], int deb, int m, int fin);
void afficher(int tab[], int length);


int main(int argc, char *argv[]) {
	char *tab_files[] = {"10000.txt","20000.txt","30000.txt","40000.txt","50000.txt","60000.txt","70000.txt","80000.txt","90000.txt","100000.txt",
		"110000.txt","120000.txt","130000.txt","140000.txt","150000.txt","160000.txt","170000.txt","180000.txt","190000.txt","200000.txt",
		"210000.txt","220000.txt","230000.txt","240000.txt","250000.txt","260000.txt","270000.txt","280000.txt","290000.txt","300000.txt"};
	int tab_lengths[] = {10000, 20000,30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000,
		110000, 120000, 130000, 140000, 150000, 160000, 170000, 180000, 190000, 200000,
		210000, 220000, 230000, 240000, 250000, 260000, 270000, 280000, 290000, 300000};

	double deb, fin, tempExec, somme;
	int i, j;

	int *tab;

	FILE *rapide = fopen("rapide.txt","w+");
	FILE *bulle = fopen("bulle.txt","w+");
	FILE *min_suc = fopen("min_suc.txt","w+");
	FILE *fusion = fopen("fusion.txt","w+");
	FILE *denombrement = fopen("denombrement.txt","w+");

	for (j = 0; j < 30; j++) {
		genererTableau(tab_lengths[j]);

		somme = 0;
		printf("Tris Rapide\n");
		printf("N = %d\n", tab_lengths[j]);
		fprintf(rapide, "N = %d\n", tab_lengths[j]);
		for (i = 0; i < 10; i++) {
			tab = lireTableau(tab_files[j], tab_lengths[j]);
			deb = clock();
			tri_rapide(tab, 0, tab_lengths[j]-1);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d du tri rapide terminee.\n", i+1);
			fprintf(rapide, "%lf\n", tempExec);
			somme += tempExec;
		}
		fprintf(rapide, "\nAvg = %lf\n\n", somme/10);

		somme = 0;
		printf("Tris a Bulle\n");
		printf("N = %d\n", tab_lengths[j]);
		fprintf(bulle, "N = %d\n", tab_lengths[j]);
		for (i = 0; i < 10; i++) {
			tab = lireTableau(tab_files[j], tab_lengths[j]);
			deb = clock();
			trisBulle(tab, tab_lengths[j]);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d du tri a Bulle terminee.\n", i+1);
			fprintf(bulle, "%lf\n", tempExec);
			somme += tempExec;
		}
		fprintf(bulle, "\nAvg = %lf\n\n", somme/10);

		somme = 0;
		printf("Tris Minimum Successif\n");
		printf("N = %d\n", tab_lengths[j]);
		fprintf(min_suc, "N = %d\n", tab_lengths[j]);
		for (i = 0; i < 10; i++) {
			tab = lireTableau(tab_files[j], tab_lengths[j]);
			deb = clock();
			trisMinimumSuccessif(tab, tab_lengths[j]);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d du tri a minimum successif terminee.\n", i+1);
			fprintf(min_suc, "%lf\n", tempExec);
			somme += tempExec;
		}
		fprintf(min_suc, "\nAvg = %lf\n\n", somme/10);

		somme = 0;
		printf("Tri Fusion\n");
		printf("N = %d\n", tab_lengths[j]);
		fprintf(fusion, "N = %d\n", tab_lengths[j]);
		for (i = 0; i < 10; i++) {
			tab = lireTableau(tab_files[j], tab_lengths[j]);
			deb = clock();
			tri_fusion(tab, 0, tab_lengths[j] - 1);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d du tri fusion terminee.\n", i+1);
			fprintf(fusion, "%lf\n", tempExec);
			somme += tempExec;
			free(tab);
		}
		fprintf(fusion, "\nAvg = %lf\n\n", somme/10);

		somme = 0;
		printf("Tris Denombrmeent\n");
		printf("N = %d\n", tab_lengths[j]);
		fprintf(denombrement, "N = %d\n", tab_lengths[j]);
		for (i = 0; i < 10; i++) {
			tab = lireTableau(tab_files[j], tab_lengths[j]);
			deb = clock();
			tab = tri_denombrement(tab, tab_lengths[j], 32768);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d du tri denombrmeent terminee.\n", i+1);
			fprintf(denombrement, "%lf\n", tempExec);
			somme += tempExec;
			free(tab);
		}
		fprintf(denombrement, "\nAvg = %lf\n\n", somme/10);
	}

	fclose(rapide);
	fclose(bulle);
	fclose(min_suc);
	fclose(fusion);
	fclose(denombrement);

	system("shutdown -s");

	return 0;
}

void genererTableau(const int size) {
	char name[20];
	int i;
	sprintf(name, "%d.txt", size);
	FILE *file = fopen(name, "w+");

	srand(time(NULL));

	fprintf(file, "%s", "{");
	for (i = 0; i < size; i++) {
		fprintf(file, "%d,", rand()%32768);
	}

	fclose(file);
}

int *lireTableau(char *name, int length) {
	int i = 0, val = 0;
	int *t = malloc(length*sizeof(int));

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

void trisMinimumSuccessif(int *tab, int n) {
    int i = 0, pos = 0;

    while (i < n) {
        pos = posMin(tab, n, i);
        permuter(tab, pos, i);
        i++;
    }
}

void trisBulle(int *tab, int n) {
    int i,k;
    int permute = 1;

    for (i = 0; i < n && permute == 1; i++) {
        permute = 0;
        for (k = n-1; k > i+1; k--) {
            if (tab[k] < tab[k-1]) {
                permuter(tab, k, k-1);
                permute = 1;
            }
        }
    }
}

int posMin(int *tab, int n, int startPos) {
    int position = startPos, i;

    for (i = startPos+1; i < n; i++) {
        if (tab[position] > tab[i]) position = i;
    }

    return position;
}

void permuter(int *tab, int pos1, int pos2) {
    int temps = tab[pos1];
    tab[pos1] = tab[pos2];
    tab[pos2] = temps;
}


int partition(int tab[], int deb, int fin) {
    int cpt = deb;
    int pivot = tab[deb];
    int i;

    for(i = deb+1; i <= fin; i++) {
        if(tab[i] < pivot) {
            cpt++;
            permuter(tab, cpt, i);
        }
    }
    
    permuter(tab, cpt, deb);
    return(cpt);
}

void tri_rapide(int tab[], int deb, int fin) {
    if(deb < fin) {
        int pivot = partition(tab, deb, fin);
        tri_rapide(tab, deb, pivot-1);
        tri_rapide(tab, pivot+1, fin);
    }
}

int *tri_denombrement(int tab[], int n, int k) {
	int i;
	int *c = calloc(k,sizeof(int));
	int *b = calloc(n,sizeof(int));

	for (i = 0; i < n; i++) {
		c[tab[i]] += 1;
	}

	for (i = 1; i < k; i++) {
		c[i] = c[i] + c[i-1];
	}
	for (i = n-1; i >= 0; i--) {
		b[c[tab[i]]-1] = tab[i];
		c[tab[i]] -= 1;
	}
	free(c);
	for (i = 0 ; i < n; i++) {
		tab[i] = b[i];
	}
	return b;
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

void afficher(int tab[], int length) {
	int i = 0;
	printf("Affichage\n");
	for (i = 0; i < length; i++) printf("%d,", tab[i]);
		printf("\n");
}