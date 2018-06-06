set term png
set out 'wykres2a.png'

set xlabel 'n'
set ylabel 'f(n)'

plot 'dane2a.dat' u 1:2 w l t '|c2 - c2a|' , 
