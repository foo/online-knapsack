set terminal pdf
set output '03.pdf'

set xrange [0:1]
set yrange [0:1]
set size square

plot "data/03.dat" with lines title "xs(s)"