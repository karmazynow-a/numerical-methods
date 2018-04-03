#include </usr/include/gsl/gsl_eigen.h>
#include</usr/include/gsl/gsl_complex.h>
#include</usr/include/gsl/gsl_complex_math.h>
#include <stdio.h>
#include <math.h>

//#define delta(X,Y) ((X)==(Y)? (1.0):(0.0))

double delta (int x, int y){
	if (x==y) return 1.0;
	else return 0.0;
}

int main (void){
	int n=200, L=10, N=1, i, j;
	double dx = ((double)L)/(n+1), alfa = 0.0;
	gsl_matrix * A = gsl_matrix_calloc(n,n);
	double r, x_L;

	FILE *fp = fopen ("dane.dat", "w");
	FILE *fp1 = fopen ("wektor0.dat", "w");
	FILE *fp2 = fopen ("wektor100.dat", "w");


	for (alfa = 0.0; alfa <=100.0; alfa+=2.0){ 

		for (i=0; i<n; i++)
			for (j=0; j<n; j++){
				x_L = -L/2.0 + dx*(i+1);
				r = 1.0 + 4.0*alfa*x_L*x_L;
				gsl_matrix_set(A,i,j,(-delta(i,j+1) + 2*delta(i,j) - delta(i,j-1))*N/(r*dx*dx));
			}

		gsl_vector_complex *eval=gsl_vector_complex_calloc(n);
		gsl_matrix_complex *evec=gsl_matrix_complex_calloc(n,n);
		gsl_eigen_nonsymmv_workspace *w = gsl_eigen_nonsymmv_alloc(n);

		gsl_eigen_nonsymmv(A, eval, evec, w);

		gsl_eigen_nonsymmv_sort(eval, evec, GSL_EIGEN_SORT_ABS_ASC);

		fprintf (fp,"%4d ", (int)alfa);

		for (i=0; i<6; i++)
			fprintf (fp,"%10g ", sqrt(GSL_REAL(gsl_vector_complex_get(eval,i))));
 		fprintf (fp,"\n");

		if (alfa == 0){
			for (i=0; i<n; i++){
				fprintf (fp1,"%12g ",  -L/2.0 + dx*(i+1) );
				for (j=0; j<6; j++)
					fprintf (fp1,"%12g ", GSL_REAL(gsl_matrix_complex_get(evec,i,j)));
				fprintf (fp1,"\n");
				}	
			}

		if (alfa == 100){
			for (i=0; i<n; i++){
				fprintf (fp2,"%12g ",  -L/2.0 + dx*(i+1) );
				for (j=0; j<6; j++)
					fprintf (fp2,"%12g ", GSL_REAL(gsl_matrix_complex_get(evec,i,j)));
				fprintf (fp2,"\n");
				}	
			}

		}

	fclose (fp);
	fclose (fp1);
	fclose (fp2);

	return 0;
}


//ro(i) = 1 + 4*alfa*i*i;
//A[i][j] = (-delta(i,j+1) + 2*delta(i,j) - delta(i,j-1))*N/ro(i);
