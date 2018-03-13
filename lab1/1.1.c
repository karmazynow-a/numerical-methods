#include <math.h>
#include <stdio.h>
#include </usr/include/gsl/gsl_math.h>		//biblioteka matematyczna - operuje na double
#include </usr/include/gsl/gsl_linalg.h>	//biblioteka z algebrą liniową


int main (void){
	double h=0.1, pi=M_PI, omega=1.0, okres=2*pi, tmax=3*okres,  v0=0.0, A=1.0;
	int n=tmax/h, i, j, signum=0; //sigmun do gsl
	
	//tworzenie macierzy
	gsl_matrix * B = gsl_matrix_calloc(n,n); //lepiej wyzerowowac - zerowe elementy macirzy
	gsl_vector * x = gsl_vector_calloc(n);
	gsl_vector * b = gsl_vector_calloc(n);
	gsl_permutation * p = gsl_permutation_calloc(n);	//wymagany przez procedure

	//wypełnianie macierzy i wektorów
	for(i=0; i<n; i++){
		for(j=0; j<n; j++){
			gsl_matrix_set(B,i,j,0.0);
			if (i==j) gsl_matrix_set(B,i,j,1.0);
			if (i==j+1) gsl_matrix_set(B,i,j,omega*omega*h*h - 2.0);
			if (i==j+2) gsl_matrix_set(B,i,j,1.0);
		}
	}
	gsl_matrix_set(B,1,0,-1.0);

	gsl_vector_set(b,0,A);
	gsl_vector_set(b,1,v0*h);

	//rozwiazywanie
	gsl_linalg_LU_decomp(B,p,&signum);	//zamiana na macierze LU
	gsl_linalg_LU_solve(B,p,b,x);


	FILE *fp = fopen("dane.dat", "w");

	for (i=0; i<n; i++) fprintf (fp, "%f %f %f\n", h*i, gsl_vector_get(x,i),A*cos(omega*h*i));

	fclose(fp);


	return 0;
}
