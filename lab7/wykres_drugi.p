set term png
set out 'czeb.png'

set xlabel 'x'
set ylabel 'f(x)'

plot 'dane2.dat' u 1:2 w l t 'funkcja' , \
	 '' u 1:3 w l t 'wielomian'

