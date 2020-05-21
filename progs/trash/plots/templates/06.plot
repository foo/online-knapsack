set terminal pdf
set output '06.pdf'

set xrange [0.0:0.72]
set yrange [0:0.9]
set size square

plot "data/06.dat" using 1:2 with lines title "lower (G1)" , \
     "data/06.dat" using 1:3 with lines title "upper (G2)" , \
     "data/06.dat" using 1:4 with lines title "upper (G3)" , \
     "data/06.dat" using 1:5 with lines title "diff"