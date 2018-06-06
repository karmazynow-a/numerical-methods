set term png
set out 'wykres.png'

set xlabel "x"
set ylabel "y"
plot  "eps2.dat" u 1:2 w lp lt 3,\
	"kontur.dat" u 1:2 w l lt 1,\
	"minimum.dat" u 1:2 w p pt 1 ps 3 lt -1
