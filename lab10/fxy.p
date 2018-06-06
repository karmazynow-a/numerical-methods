set xrange [-2:2]
set yrange [-2:2]
set table "kontur.dat"
unset key
set contour
unset surface

set view map
set cntrparam levels 50
splot "fxy.dat" u 1:2:3 w l lt -1
unset table
