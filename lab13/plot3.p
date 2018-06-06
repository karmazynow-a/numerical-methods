set term png
set out 'wykres3.png'

set xlabel 'n'
set ylabel 'f(n)'

plot 'dane3.dat' u 1:2 w l t '|c3 - c3a|' , 
