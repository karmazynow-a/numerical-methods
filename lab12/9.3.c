#include <stdio.h>
#include <math.h>

double fun (double x){
	return log(x*x*x + 3*x*x + x + 0.1)*sin(18*x);
}

void clear(double (*A)[9], int n){
	int i, j;
	for (i=0; i<n; ++i)
		for (j=0; j<n; ++j)
			A[i][j] = 0.;
}

void trapez(double (*D)[9]);
void trzy_osiem(double (*D)[9]);

int main(void){
	int n, i, j, k;

	FILE *fp = fopen ("dane.dat", "w");

	double D[9][9];


	fprintf (fp, "metoda trapezów\n");
	
	trapez(D);

	//zapis
	for (i=0; i<9; ++i){
		for (j=0; j<=i; ++j)
			fprintf(fp , "%10g ", D[i][j]);
		fprintf(fp , "\n");
	}

	fprintf (fp, "\nmetoda 3/8\n");
	
	trzy_osiem(D);

	//zapis
	for (i=0; i<9; ++i){
		for (j=0; j<=i; ++j)
			fprintf(fp , "%10g ", D[i][j]);
		fprintf(fp , "\n");
	}

	fclose (fp);

	return 0;
}

void trapez(double (*D)[9]){
	double h;
	int n, i, j, k, N;

	clear (D, 9);

	//pierwsza kolumna
	for (n=0; n<9; ++n){
		h = 1./pow(2, n);
		N = pow (2, n);

		for (i=0; i<=N-1; ++i){
			D[n][0] += h/2 * (fun(i*h) + fun( (i+1)*h ));
		}
	}

	//wzór ekstrapolacyjny
	for (n=1; n<9; ++n)
		for (k=1; k<9; ++k)
			D[n][k] = (pow(4, k)*D[n][k-1] - D[n-1][k-1]) / (pow(4, k) - 1);
}

void trzy_osiem(double (*D)[9]){
	double h;
	int n, i, j, k, N;

	clear (D, 9);

	//pierwsza kolumna
	for (n=0; n<9; ++n){
		h = 1./(3*pow(2, n));
		N = 3*pow (2, n);

		for (i=0; i<=(N/3)-1; ++i){
			D[n][0] += (3*h/8) * (fun(3*i * h) + 3*fun((3*i+1) * h) + 3*fun((3*i+2) * h) + fun((3*i+3) * h) );
		}
	}	

	//wzór ekstrapolacyjny
	for (n=1; n<9; ++n)
		for (k=1; k<9; ++k)
			D[n][k] = (pow(4, k)*D[n][k-1] - D[n-1][k-1]) / (pow(4, k) - 1);

}
