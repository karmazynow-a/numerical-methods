set term png
set out 'wykres2b.png'

set xlabel 'n'
set ylabel 'f(n)'

plot 'dane2b.dat' u 1:2 w l t '|c2 - c2a|' , 
