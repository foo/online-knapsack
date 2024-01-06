set terminal pdf
set output '02.pdf'

set xrange [0:1]
set yrange [0:1]

set size square
plot "data/02.dat" with lines title "F(x)" 