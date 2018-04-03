set term jpeg
set out "przyblizenia.jpg"

set xlabel 'iteracje'
set ylabel 'przyblizenia watosci wlasnych'

plot 'dane3.dat' u 1:2 w l t 'lambda1',\
'' u 1:3 w l t 'lambda2',\
'' u 1:4 w l t 'lambda3',\
'' u 1:5 w l t 'lambda4',\
'' u 1:6 w l t 'lambda5',\
'' u 1:7 w l t 'lambda6',\
'' u 1:8 w l t 'lambda7'
