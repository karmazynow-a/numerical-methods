set term jpeg
set out "plot1.jpg"
set xlabel "x"
set ylabel "f(x)"
set yrange [*:*]

plot 'wektor0.dat' u 1:2 w l t '1',\
''u 1:3 w l t '2',\
''u 1:4 w l t '3',\
''u 1:5 w l t '4',\
''u 1:6 w l t '5',\
''u 1:7 w l t '6'
