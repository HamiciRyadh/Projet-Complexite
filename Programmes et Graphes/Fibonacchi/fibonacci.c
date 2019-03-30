#include<stdio.h>
#include<stdlib.h>
#include<time.h>


int fibonacci_iteratif(const int n);
int fibonacci_recurcif(const int n);

int main(int argc, char *argv[]) {
	double deb, fin, tempExec, somme;
	int i, j;

	FILE *simple = fopen("simple.txt","w");
	FILE *complexe = fopen("complexe.txt","w");

	for (j = 30; j <= 44; j++) {
		somme = 0;
		printf("Simple\n");
		fprintf(simple, "N = %d\n", j);
		for (i = 0; i < 10; i++) {
			deb = clock();
			fibonacci_iteratif(j);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d Simple terminee.\n", i+1);
			fprintf(simple, "%lf\n", tempExec);
			somme += tempExec;
		}
		fprintf(simple, "\nAvg = %lf\n\n", somme/10);
		fflush(simple);

		somme = 0;
		fprintf(complexe, "N = %d\n", j);
		for (i = 0; i < 10; i++) {
			deb = clock();
			fibonacci_recurcif(j);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d Complexe terminee.\n", i+1);
			fprintf(complexe, "%lf\n", tempExec);
			somme += tempExec;
		}
		fprintf(complexe, "\nAvg = %lf\n\n", somme/10);
		fflush(complexe);
	}

	fclose(simple);
	fclose(complexe);
}

int fibonacci_iteratif(const int n) {
	int f0 = 0, f1 = 1, i, somme;
	if (n == 0) return 0;
	if (n == 1) return 1;

	for (i = 2; i <= n; i++) {
		somme = f0 + f1;
		f0 = f1;
		f1 = somme;
	}

	return somme;
}

int fibonacci_recurcif(const int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;

	return fibonacci_recurcif(n-1)+fibonacci_recurcif(n-2);
}