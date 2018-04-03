#include <stdio.h>
#include <math.h>

#define IT_MAX 12
#define abs(X) ((X)>0? (X):-(X))

void mat_vec (double *wynik, double *wektor, double (*macierz)[7], int n);
void orto (double * wekt1, double *wekt2, int n);
double vec_vec (double * wekt1, double *wekt2, int n);
void mat_mat (double (*wynik)[7], double (*mat1)[7], double (*mat2)[7], int n);

int main (void){
	int k, i, n=7, j;
	double A[n][n], lambda[IT_MAX], X[n][n], tmpA[n][n], D[n][n];
	double x1[n], x2[n];
         double przyblizenia[IT_MAX][n];

	FILE *fp1 = fopen ("dane1.dat", "w");
	FILE *fp2 = fopen ("dane2.dat", "w");
         FILE *fp3 = fopen ("dane3.dat", "w");

	for (i=0; i<n; i++)
		for (j=0; j<n; j++)
			A[i][j] = 1./sqrt(2+abs(i-j));
			//X[i][j] = 1.;

	for (k=0; k<n; k++){

		for (j=0; j<n; j++) x1[j] = 1.0;

		for (i=0; i<IT_MAX; i++){	

			mat_vec(x2, x1, A, n);

			for (j=0; j<k; j++)
				orto (x2, X[j], n);
			

			lambda[k] = vec_vec(x2, x1, n)/vec_vec(x1, x1, n);
                        przyblizenia[i][k] = lambda[k];

			for (j=0; j<n; j++)
				x1[j] = x2[j]/sqrt(vec_vec(x2, x2, n));
		}

		for (j=0; j<n;j++)
			X[k][j] = x1[j];
	}

	for (j=0; j<n; j++)
		fprintf (fp1, "%g\n", lambda[j]);


	mat_mat(tmpA, X, A, n);

	double tmp;
	for (i=0; i<n; i++)
		for (j=i+1; j<n; j++){
			tmp = X[i][j];
			X[i][j] = X[j][i];
			X[j][i] = tmp;
		}

	mat_mat(D, tmpA, X, n);

	for (i=0; i<n; i++){
		for (j=0; j<n; j++)
			fprintf(fp2, "%12g ", D[i][j]);
		fprintf(fp2, "\n");
	}

        for (i=0; i<IT_MAX; i++){
            fprintf(fp3, "%3d", i+1);
            for (j=0; j<n; j++)
               fprintf (fp3, "%12g", przyblizenia[i][j]);
            fprintf(fp3, "\n");
         }



	fclose (fp1);
	fclose (fp2);
         fclose (fp3);

	return 0;
}

void mat_vec (double *wynik, double *wektor, double (*macierz)[7], int n){
	int i, j;
	for (i=0; i<n; i++){
		wynik[i] = 0.0;
		for (j=0; j<n; j++)
			wynik[i] += macierz[i][j] * wektor[j];
	}
}

//zmieniamy ten i+1, czyli wekt1
void orto (double * wekt1, double *wekt2, int n){
	double scal = vec_vec(wekt1, wekt2, n);
	int i=0;
	for (i=0; i<n; i++)
		wekt1[i] = wekt1[i] - scal*wekt2[i];

}
double vec_vec (double * wekt1, double *wekt2, int n){
	int i;
	double sum = 0.0;
	for (i=0; i<n; i++)
		sum += wekt1[i] * wekt2[i];
	return sum;
}

void mat_mat (double (*wynik)[7], double (*mat1)[7], double (*mat2)[7], int n){
	int i,j,k;
	for (i=0; i<n; i++)
		for (j=0; j<n; j++){
			wynik[i][j] = 0.;
			for (k=0; k<n; k++)
				wynik[i][j] += mat1[i][k]*mat2[k][j];
	}

}
