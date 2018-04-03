set term jpeg
set out "r.jpg"
set xlabel "k"
set ylabel "|r|=f(k)"
set logscale y

plot 'dane.dat' u 1:2 w l t 'rk'
