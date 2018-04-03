set term jpeg
set out 'X.jpg'
set xlabel 'k'
set ylabel '|x|=f(k)'

plot 'dane.dat' u 1:5 w l t 'xk'
