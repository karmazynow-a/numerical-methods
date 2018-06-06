set term png
set out 'wykres.png'

set xlabel 'x'
set ylabel 'f(x)'

plot 'dane.dat' u 1:2 w l t 'funkcja' , \
	 '' u 1:3 w l t 'aproksymacja' , 

