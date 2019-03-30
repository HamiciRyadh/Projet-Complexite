#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void produitMatriciel(int max, int N);
int **creerMatriceCarreeVide(int n) {
	int **mat = calloc(n, sizeof(int));
	int i;
	for (i = 0; i < n; i++) {
		mat[i] = calloc(n, sizeof(int));
	}

	return mat;
}

void remplireMatriceCarree(int **mat, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			mat[i][j] = i+j;
		}
	}
}


int main(void) {
	int i, j;
	for (i = 1; i <= 20; i++) {
		for (j = 8; j <= 256; j*=2) {
			produitMatriciel(1000*5*i, j);
		}
	}

	system("shutdown -s");

	return EXIT_SUCCESS;
}

void produitMatriciel(int max, int N) {
	int i, j, k, p, l;
	double deb, fin, tempExec, somme;

	int **mat = creerMatriceCarreeVide(N);
	int **mat1 = creerMatriceCarreeVide(N);
	remplireMatriceCarree(mat1, N);
	int **mat2 = creerMatriceCarreeVide(N);
	remplireMatriceCarree(mat2, N);

	FILE *file = fopen("MxN.txt","a+");
	if (file == NULL) {
		fprintf(stderr, "%s\n", "Une erreur est survenue.");
		exit(EXIT_FAILURE);
	}
	FILE *file2 = fopen("AvgMxN.txt","a+");
	if (file == NULL) {
		fprintf(stderr, "%s\n", "Une erreur est survenue.");
		exit(EXIT_FAILURE);
	}
	fprintf(file, "N = %d, M = %d\n", N, max);
	fprintf(file2, "N = %d, M = %d\n", N, max);

	somme = 0;
	for (l = 0; l < 10; l++) {
		printf("Iteration %d, N = %d, M = %d.\n", l+1, N, max);
		deb = clock();
		for (p = 0; p < max; p++) {
			for (i = 0; i < N; i++) {
				for (j = 0; j < N; j++) {
					for (k = 0; k < N; k++) {
						mat[i][j]=mat1[i][k]*mat2[k][i]+mat[i][j];
					}
				}
			}

			for (i = 0; i < N; i++) {
				for (j = 0; j < N; j++) {
					mat1[i][j]=mat[i][j];
				}
			}
		}
		fin = clock();
		tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
		somme += tempExec;
		fprintf(file, "%lf\n", tempExec);
	}
	fprintf(file, "\nAvg = %lf\n\n", somme/10);
	fprintf(file2, "Avg = %lf\n\n", somme/10);
	fclose(file);
	fclose(file2);
}
