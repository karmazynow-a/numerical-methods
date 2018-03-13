set term jpeg
set out 'wynik.jpg'
set xlabel 't'
set ylabel 'x(t)'

plot 'dane.dat' u 1:2 w l t 'xn',\
'' u 1:3 w p t 'xdok'
