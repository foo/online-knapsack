set terminal pdf
set output '05.pdf'

set xrange [0:1]
set yrange [0:1]
set size square

set style data lines
set style fill   pattern 4 border
plot "data/05.dat" with filledcurves x1 linestyle 1 title "f_without_if(x)"