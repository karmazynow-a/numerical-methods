set term png
set out 'wykresg.png'

set xlabel 'x'
set ylabel 'f(x)'

plot 'funkcjag.dat' u 1:2 w l t 'ln(x)*exp(-x*x)' , 
