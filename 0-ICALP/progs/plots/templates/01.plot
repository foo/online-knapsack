set terminal pdf
set output '01.pdf'

set xrange [0:1]
set yrange [0:1]
set size square

set style data lines
set style fill   pattern 4 border
plot "data/01.dat" with lines  title "f(x)"