#include <math.h>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <iostream>

#define max(X,Y) ((X)>(Y)? (X):(Y))
#define min(X,Y) ((X)<(Y)? (X):(Y))
#define abs(X) ((X)>0? (X):-(X))

void multiMatrixVec (int n, double (*A)[1000], double *x, double *y, int m);
double gradient (double *r, int n);
double scalar (double *a, double *b, int n);

int main (void){

	int n = 1000, i, j, m=5;
	double A[n][n], b[n], x[n], y[n];

	time_t t1,t2;
	double t21;
	time(&t1);
//start

auto execTimeStart = std::chrono::steady_clock::now();

	FILE * fp = fopen ("dane.dat", "w");

	for (i=0; i<n; i++){
		b[i] = i+1;
		x[i] = 0;
		for (j=0; j<n; j++){
			if (abs(i-j) <= m) A[i][j] = 1./(1 + abs(i-j));
			else A[i][j] = 0.;
		}
	}


	int k=0;
	double v[n], r[n], alfa = 0.0, beta = 0.0, licznik = 100000, mianownik =0.0, tmpVec[n];

	multiMatrixVec (n, A, x, y, m);
	
	for (i=0; i<n; i++){
		v[i] = r[i] = b[i] - y[i];
	}
	
	
	while (gradient (r, n) > pow (10, -6)){

		licznik = scalar (r, r, n);
		multiMatrixVec (n, A, v, tmpVec, m);
		mianownik = scalar(v, tmpVec, n);

		alfa = licznik/mianownik;

		for(i=0; i<n; i++){
			x[i] = x[i] + alfa*v[i];
		}

		for(i=0; i<n; i++){
			r[i] = r[i] - alfa*tmpVec[i];
		}

		beta = scalar(r,r,n)/licznik;

		for(i=0; i<n; i++){
			v[i] = r[i] + beta*v[i];
		}

		fprintf(fp, "%d %g %g %g %g\n", k, gradient (r, n), alfa, beta, gradient (x, n));
		k++;
	}
	//gaussj(a,n,x,1);
	time(&t2);
auto execTimeStop = std::chrono::steady_clock::now();
//koniec


	t21=difftime(t2,t1);   //roznica daje czas wykonania
	//printf ("czas: %g", t21);
	std::cout<< std::chrono::duration<double, std::milli>(execTimeStop - execTimeStart).count();

	fclose(fp);

	return 0;
}

double gradient (double *r, int n){
	return sqrt(scalar(r, r, n));
}

double scalar (double *a, double *b, int n){
	int i;
	double sum = 0.0;
	
	for(i=0; i<n; i++)
		sum += a[i] * b[i];

	return sum;
}	

void multiMatrixVec (int n, double (*A)[1000], double *x, double *y, int m){
	int i, j;

	for (i=0; i<n; i++){
		y[i] = 0.0;
		for (j=max(0, i-m); j<= min(n-1, i+m); j++)
			y[i]+=A[i][j]*x[j];
	}
}
