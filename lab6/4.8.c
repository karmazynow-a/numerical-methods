#include <stdio.h>
#include <complex.h>
#include <math.h>

#define IT_MAX 20

double complex get_r(double complex a[5], double complex b[5], double complex z, int l);

int main (void){

	double complex a[5];	
	double complex b[5];
	double complex z[IT_MAX + 1];
	double complex R[IT_MAX + 1];
	double complex r1,r2,r3;
	double complex z1,z2,z3;
	int l, j, k, n=4;
	double a_min = pow(10,-10);


	a[0] = 16. + 8.I;
	a[1] = -20. + 14I;
	a[2] = 4. - 8I;
	a[3] = -4. + I;
	a[4] = 1 + 0I;

	double complex z_a = 0 + 0I;
	double complex z_b = 0.1 + 0.1I;

	FILE * fp1 = fopen ("data1.dat", "w");


	for (l = n; l>=1; l--){
		for (j=1; j<= IT_MAX; j++){
			if(j==1){
				z1 = z_a;
				z2 = z_b;
				fprintf (fp1, "%10d %10d %10g %10g\n",l,j, creal(z2), cimag(z2));
				r1 = get_r(a, b, z1, l);
				r2 = get_r(a, b, z2, l);
			}

			z3 = z2 - r2*(z2 - z1)/(r2 - r1);
			r3 = get_r (a, b, z3, l);

			if(cabs(z3 - z2) < a_min) break;

			z1 = z2;
			z2 = z3;
			r1 = r2;
			r2 = r3;

			fprintf (fp1, "%10d %10d %10g %10g\n",l,j, creal(z2), cimag(z2));
 
		}

		fprintf(fp1, "\n");
		for (j=0; j<n; j++) a[j] = b[j];
	}



	return 0;
}

double complex get_r(double complex a[5], double complex b[5], double complex z, int l){
	b[l] = 0;
	int k;
	for (k = l-1; k>=0; k--)
		b[k] = a[k+1] + z*b[k+1];

	return a[0] + z*b[0];
}
