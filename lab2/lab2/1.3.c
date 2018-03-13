#include <math.h>
#include <stdio.h>
#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>


int main (void){
	int n = 4, signum = 0, i, j, k;
	double det = 1.0, delta = 2.0, c=0.0;

	gsl_matrix * A = gsl_matrix_calloc(n,n);
	gsl_permutation * p = gsl_permutation_calloc(n);
	gsl_matrix * A1 = gsl_matrix_calloc(n,n);
	gsl_vector * x = gsl_vector_calloc(n);
	gsl_vector * b = gsl_vector_calloc(n);

	for(i=0; i<n; i++)
		for(j=0; j<n; j++){
			gsl_matrix_set(A,i,j, 1/(i+j+delta));
			gsl_matrix_set(A1,i,j, 1/(i+j+delta));
	}

	gsl_linalg_LU_decomp(A,p,&signum);

	//wyznacznik

	FILE *fp = fopen("dane.dat", "w");
	fprintf (fp, "Elementy diagonalne macierzy U:\n");

	for (i=0; i<n; i++){
		det = det * gsl_matrix_get (A, i, i);
		fprintf (fp, "%12f ", gsl_matrix_get (A, i, i));
	} 

	fprintf (fp, "\n\nWyznacznik macierzy: %g\n", det);

	//macierz odwrotna

	for (i=0; i<n; i++){
		for (j=0; j<n; j++) gsl_vector_set(b,j,0.0);
		gsl_vector_set(b,i,1.0);
		gsl_linalg_LU_solve(A,p,b,x);
		for (j=0; j<n; j++) gsl_matrix_set(A1,j,i,gsl_vector_get(x,j));
	}

	fprintf (fp, "\nMacierz odwrotna:\n");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++) fprintf (fp, "%14g ", gsl_matrix_get (A1, i, j));
		fprintf(fp, "\n");
	}

	//iloczyn A*A-1

	fprintf (fp, "\nMacierz A*A-1:\n");	
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			c=0.0;		
			for (k=0; k<n; k++){
				double w = 1/(i+k+delta);
				c+= w*gsl_matrix_get (A1, k, j);
				}
			fprintf(fp, "%14g ", c);
			}		
		fprintf(fp, "\n");
	}

	//wskaznik uwarunkowania		
	
	double wsk = 1/delta, wsk1 = fabs(gsl_matrix_get (A1, 0, 0));
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			if (wsk < fabs(1/(i+j+delta))) wsk = fabs(1/(i+j+delta));
			if (wsk1 < fabs(gsl_matrix_get (A1, i, j))) wsk1 = fabs(gsl_matrix_get (A1, i, j));
		}
	}

	fprintf (fp, "\nWskaznik uwarunkowania: %g\n", wsk*wsk1);


	fclose(fp);

	return 0;
}
