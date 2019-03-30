#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int tres_simple(int n);
int Simple(int n);
int Complexe(int n);

int main(void) {
	double deb, fin, tempExec, somme;
	int i, j;

	FILE *simple = fopen("simple.txt","w");
	FILE *tresSimple = fopen("tresSimple.txt","w");
	FILE *complexe = fopen("complexe.txt","w");

	for (j = 28; j <= 38; j++) {
		somme = 0;
		printf("Tres Simple\n");
		fprintf(tresSimple, "N = %d\n", j);
		for (i = 0; i < 10; i++) {
			deb = clock();
			tres_simple(j);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d Tres simple terminee.\n", i+1);
			fprintf(tresSimple, "%lf\n", tempExec);
			somme += tempExec;
		}
		fprintf(tresSimple, "\nAvg = %lf\n\n", somme/10);
		fflush(tresSimple);

		somme = 0;
		printf("Simple\n");
		fprintf(simple, "N = %d\n", j);
		for (i = 0; i < 10; i++) {
			deb = clock();
			Simple(j);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d Simple terminee.\n", i+1);
			fprintf(simple, "%lf\n", tempExec);
			somme += tempExec;
		}
		fprintf(simple, "\nAvg = %lf\n\n", somme/10);
		fflush(simple);

		somme = 0;
		printf("Complexe");
		fprintf(complexe, "N = %d\n", j);
		for (i = 0; i < 10; i++) {
			deb = clock();
			Complexe(j);
			fin = clock();
			tempExec = ((double) (fin - deb))/CLOCKS_PER_SEC;
			printf("Iteration %d Complexe terminee.\n", i+1);
			fprintf(complexe, "%lf\n", tempExec);
			somme += tempExec;
		}
		fprintf(complexe, "\nAvg = %lf\n\n", somme/10);
		fflush(complexe);
	}

	fclose(tresSimple);
	fclose(simple);
	fclose(complexe);

	system("shutdown -s");

	return 0;
}

int Simple(int n) {
	if (n == 0) return 2;
	else {
		int val = Simple(n-1);
		return val*val;
	}
}

int Complexe(int n) {
	if (n == 0) return 2;
	else return Complexe(n-1)*Complexe(n-1);
}

int tres_simple(int n) {
	int val = 2, i;
	for (i = 0; i < n; i++) {
		val = val*val;
	}
	return val;
}