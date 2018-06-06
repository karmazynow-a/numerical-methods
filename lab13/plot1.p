set term png
set out 'wykres1.png'

set xlabel 'n'
set ylabel 'f(n)'

plot 'dane1.dat' u 1:2 w l t '|c1 - c1a|' , 
