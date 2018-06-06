#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include </usr/include/gsl/gsl_errno.h>
#include </usr/include/gsl/gsl_fft_complex.h>

#define PI 3.1415

int main(void){

int k;
FILE *fp1 = fopen ("dane1.dat", "w");

for (k=8; k<=12; k+=2){

	int N = pow(2,k);
	double dane[2*N], T = 0.1, tmax = 3*T, dt = tmax/N, sigma = T/20; 
	double f0[2*N], f_z[2*N], f[2*N], g1[2*N], g2[2*N];

	

	srand(time(0));

	int i;
	//wypelnienie f0 i f
	double omega = 2 * PI / T;
	for (i=0; i<N; ++i){
		double t = dt * i;
		f0[2*i] = sin(t*omega) + sin(2*t*omega) + sin(3*t*omega);
		f0[2*i+1] = 0.;

		f[2*i] = f0[2*i] + ( (rand()/(RAND_MAX + 1.)) - 0.5 );
		f[2*i+1] = 0.;

		f_z[2*i] = f[2*i];
		f_z[2*i+1] = f[2*i+1];

		g1[2*i] = exp(-t*t/(2*sigma*sigma))/(sigma*sqrt(2*PI));
		g1[2*i+1] = 0.;

		g2[2*i] = g1[2*i];
		g2[2*i+1] = 0.;
	}

	//transformaty
	gsl_fft_complex_radix2_forward(f, 1, N);
	gsl_fft_complex_radix2_forward(g1, 1, N);
	gsl_fft_complex_radix2_backward(g2, 1, N);

	//splot
	double a1, b1, a2, b2;
	for (i=0; i<N; ++i){

		a1 = f[2*i];
		b1 = f[2*i + 1];
		a2 = g1[2*i] + g2[2*i];
		b2 = g1[2*i + 1] + g2[2*i + 1];
	 	f[2*i] = (a1*a2) - (b1*b2);
	 	f[2*i+1] = (a1*b2) + (b1*a2);
	}

	gsl_fft_complex_radix2_backward(f, 1, N);

	//szukanie elementu fmax
	double fmax = fabs(f[0]);
	for (i = 1; i<N; ++i)
		if (fabs (f[2*i]) > fmax)	
			fmax = fabs (f[2*i]);
	
	fprintf (fp1, "\n%d\n", k);
	for (i=0; i<N; ++i)
		fprintf(fp1, "%g %g %g %g\n", 2*i*dt, f0[2*i], f_z[2*i], f[2*i]*2.5/fmax);

}
	fclose (fp1);	

	return 0;
}
