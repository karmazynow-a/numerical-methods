#include "stdio.h"
#include "math.h"
#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>

#define N 2
#define M 2

double fun (double x){
	return exp(-x*x);
}

double silnia (int x){
	if (x==0 || x==1) return 1.;
	double s = 1.; 
	int i;
	for (i=2; i<=x; i++)
		s*=i;
	return s;
}

int main(void){
	int n = N + M;
	double c[n+1];
	int i,j;

	//szukamy c, wzór8
	int k, pot;
	for (k=0; k<=n; k++){
		c[k] = 0.;
		if (k%2==0){
			pot=k/2;
			c[k] = pow(-1, pot)/silnia(pot);
		}
	}

	//tworzymy macierz a MxM i wektor y - wynik x ze wspołczynnikami b
	gsl_matrix * A = gsl_matrix_calloc(M,M);
	gsl_vector * y = gsl_vector_calloc(M);
	gsl_vector * x = gsl_vector_calloc(M);
	gsl_permutation * p = gsl_permutation_calloc(M);
	int signum = 0;

	for (i=0; i<M; ++i)
		for (j=0; j<M; ++j)
			gsl_matrix_set(A, i, j, c[N-M+i+j+1] );

	for (i=0; i<M; ++i)
		gsl_vector_set(y, i, -c[N+1+i] );

	gsl_linalg_LU_decomp(A, p, &signum);
	gsl_linalg_LU_solve(A, p, y, x);

	//tworzymy wektor b, b[0] reszte przepisujemy
	double b[M+1];
	b[0] = 1;
	for (i=0; i<M; ++i)
		b[M-i] = gsl_vector_get(x, i);

	//wektor a, wzór 6 w dwóch pętlach od 0 do n sumy iloczynu
	double a[N+1];	
	for (i=0; i<=N; ++i){
		a[i] = 0.;
		for (j=0; j<=i; ++j){
			a[i] += c[i-j] * b[j];
		}
	}

	FILE *fp = fopen("dane.dat", "w");
	double xmin = -5., xmax = 5.;
	double skok = (xmax - xmin)/100;
	
	for (i=0; i<100; ++i){
		double ap_l = 0., ap_m = 0.;
		for (j=0; j<=N; ++j)
			ap_l += a[j] * pow(xmin + i*skok, j); 

		for (j=0; j<=M; ++j)
			ap_m += b[j] * pow(xmin + i*skok, j); 

		fprintf(fp, "%10g %10g %10g\n", xmin + i*skok, fun(xmin + i*skok), ap_l/ap_m);
	}

	fclose (fp);

	return 0;
}
