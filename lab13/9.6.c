#include <stdio.h>
#include <math.h>
#include "nr.h"
#include "nrutil.h"


float f1 (float x){
	return 1./(x * sqrt(x*x - 1.));
}

float f2 (float x){
	return log(x);
}

float f2b (float x){
	return log(x)*exp(-x*x);
}

float f3 (float x){
	return sin(2*x)*exp(-2*x);
}

int main (void){

	float c1a = M_PI/3.;
	float c2a = -0.8700577;
	float c3a = 2./13.;

	FILE *fp1 = fopen("dane1.dat", "w");
	FILE *fp2a = fopen("dane2a.dat", "w");
	FILE *fp2b = fopen("dane2b.dat", "w");
	FILE *fp3 = fopen("dane3.dat", "w");

	int n, i;	

	//punkt 1 Gaussa-Legandre
	for (n=2; n<=100; ++n){
		float w[n+1], x[n+1];
		float c1 = 0;

		gauleg(1., 2., x, w, n);
		
		for (i=1; i<=n; ++i){
			c1 += w[i] * f1(x[i]);
		}

		fprintf (fp1, "%d %g\n", n, fabs(c1 - c1a));
	}

	//punkt 2a  Gaussa-Hermite
	for (n=2; n<=100; n+=2){
		float w[n+1], x[n+1];
		float c2 = 0;

		gauher(x, w, n);
		
		for (i=1; i<=n; ++i){
			c2 += w[i] * f2(fabs(x[i]));
		}
		c2 = c2/2.;

		fprintf (fp2a, "%d %g\n", n, fabs(c2 - c2a));
	}

	//punkt 2b Gaussa-Legendre
	for (n=2; n<=100; ++n){
		float w[n+1], x[n+1];
		float c2 = 0;

		gauleg(0., 5., x, w, n);
		
		for (i=1; i<=n; ++i){
			c2 += w[i] * f2b(x[i]);
		}

		fprintf (fp2b, "%d %g\n", n, fabs(c2 - c2a));
	}
	
	//punkt 3 Gaussa-Laguere'a
	for (n=2; n<=10; ++n){
		float w[n+1], x[n+1];
		float c3 = 0;

		gaulag(x, w, n, 0);
		
		for (i=1; i<=n; ++i){
			c3 += w[i] * f3(x[i]);
		}

		fprintf (fp3, "%d %g\n", n, fabs(c3 - c3a));
	}


	fclose (fp1);
	fclose (fp2a);
	fclose (fp2b);
	fclose (fp3);

	return 0;
}
