set term png
set out "wykres.png"

set xlabel 'Re(z)'
set ylabel 'Im(z)'

plot 'p1.dat' u 3:4 w l t 'z1' , \
'p2.dat' u 3:4 w l t 'z2' , \
'p3.dat' u 3:4 w l t 'z3' , \
'p4.dat' u 3:4 w l t 'z4' , \
