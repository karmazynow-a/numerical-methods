#include <stdio.h>
#include <math.h>

#define IT_MAX 1000

double fun (double x, double y);

int main (void){
	double x = -0.75, y = 1.75, h = 0.1, df_x, df_y, delta = pow(10, -4);
	double x_prev, y_prev, epsilon = pow(10, -2);
	int i;

	FILE *fp1 = fopen("eps1.dat", "w");
	FILE *fp2 = fopen("fxy.dat", "w");

	fprintf (fp1, "%10g %10g\n", x, y);

	for (i=1; i<IT_MAX; ++i){
		x_prev = x;
		y_prev = y;
		
		df_x = ( fun(x+delta, y) - fun(x-delta, y) )/(2*delta);
		df_y = ( fun(x, y+delta) - fun(x, y-delta) )/(2*delta);

		x = x - h*df_x;
		y = y - h*df_y;

		fprintf (fp1, "%10g %10g\n", x, y);

		double norma = sqrt( pow(x_prev - x, 2) + pow(y_prev - y, 2)  );

		if (norma < epsilon){
			break;
		}
	}
	
	for (x=-2.; x<=2; x+= 0.02){
		for (y=-2.; y<=2.; y+=0.02){
			fprintf(fp2, "%5g %5g %5g\n", x, y, fun(x,y));
		}
		fprintf(fp2, "\n");
	}

	fclose(fp1);
	return 0;
}

double fun (double x, double y){
	return (2.5 * pow(x*x - y, 2)) + pow(1.- x, 2);
}




