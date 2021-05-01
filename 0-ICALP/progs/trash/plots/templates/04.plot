set terminal pdf color
set output '04.pdf'

set xrange [0.1:0.52]
set yrange [0:0.5]
set size square
set style line 5 lt rgb "cyan" lw 3 pt 6

plot "data/04.dat" using 1:2 with lines lc rgb 'blue' title "upper(s)" , \
     "data/04.dat" using 1:3 with lines lc rgb 'brown' title "lower(s)", \
     "data/04.dat" using 1:5 with lines lc rgb 'red' title "g(s)"