#include <stdio.h>
#include <math.h>

#define K 200

double wielomian(double *X, double *Y, int n, double x);

int main(void){
	int n;
	int i=0, j, k;
	double x_min = -5, x_max = 5;
	double x;
	double delta = (x_max - x_min)/K;

	FILE *fp1 = fopen("dane1.dat", "w");
	FILE *fp2 = fopen("dane2.dat", "w");
	
	for (n=5; n<=20; n+=5){
		fprintf(fp1, "%d\n", n);

		double X[n+1], f[n+1][n+1], f_tmp[n+1];
	
		for (i=0; i<=n; i++){
			X[i] = x_min + i*(x_max - x_min)/n;
			f[i][0]=1./(1+X[i]*X[i]);
		}

		for (j=1; j<=n; j++){
			for (i=j; i<=n; i++){
				f[i][j] = (f[i][j-1] - f[i-1][j-1])/(X[i] - X[i-j]);
			}
		}
	
		for (i=0; i<=K; i++){
			x = x_min + delta*i;

			for (j=0; j<=n; j++)
				f_tmp [j] = f[j][j];
				//printf ("%10g\n", f[j]); 

			fprintf(fp1, "%5g %10g %10g\n", x, 1/(1 + x*x), wielomian(X, f_tmp, n, x));
		}

		fprintf(fp1, "\n\n");
	}


	for (n=5; n<=20; n+=5){
		fprintf(fp2, "%d\n", n);

		double X[n+1], f[n+1][n+1], f_tmp[n+1];
	
		for (i=0; i<=n; i++){
			X[i] = 0.5*((x_min - x_max)*cos(3.1415* ( (2.*i+1.) /( 2.*n + 2.) ) ) + (x_min + x_max));
			f[i][0]=1./(1+X[i]*X[i]);
		}

		for (j=1; j<=n; j++){
			for (i=j; i<=n; i++){
				f[i][j] = (f[i][j-1] - f[i-1][j-1])/(X[i] - X[i-j]);
			}
		}
	
		for (i=0; i<=K; i++){
			x = x_min + delta*i;

			for (j=0; j<=n; j++)
				f_tmp [j] = f[j][j];
				//printf ("%10g\n", f[j]); 

			fprintf(fp2, "%5g %10g %10g\n", x, 1/(1 + x*x), wielomian(X, f_tmp, n, x));
		}

		fprintf(fp2, "\n\n");
	}

	return 0;
}

double wielomian(double *X, double *Y, int n, double x){
	double w = 0., il = 1;
	int i, j;

	for (j=0; j<=n; j++) {		
		il = 1.;

		for (i=0; i<j; i++)
			il = il * (x - X[i]);
		//printf ("%10g %10g\n", w, il);

		w += Y[j] * il;
	}

	return w;
}
