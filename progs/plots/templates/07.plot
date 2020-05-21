set terminal pdf
set output '07.pdf'

set xrange [0.0:0.72]
set yrange [0:0.9]
set size square

plot "data/07.dat" using 1:2 with lines title "G1(x)" , \
     "data/07.dat" using 1:3 with lines title "G2(x)" , \
     "data/07.dat" using 1:5 with lines title "inv_g_new(x)"