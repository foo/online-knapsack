set terminal pdf color
set output '04.pdf'

set xrange [0.1:0.52]
set yrange [0:0.5]
set size square
set style line 5 lt rgb "cyan" lw 3 pt 6
set arrow from 0.219, graph 0 to 0.219, graph 1 nohead
#set arrow from 0.22222, graph 0 to 0.22222, graph 1 nohead
set arrow from 0.438, graph 0 to 0.438, graph 1 nohead
#set arrow from 0.44444, graph 0 to 0.44444, graph 1 nohead

plot "data/04.dat" using 1:2 with lines lc rgb 'red' title "some M (Lower)" , \
     "data/04.dat" using 1:3 with lines lc rgb 'red' title "no M (Upper)", \
     "data/04.dat" using 1:5 with lines lc rgb 'green' title "g(s)", \
     "data/04.dat" using 1:6 with lines lc rgb 'blue' title "no M some A+ (Lower)", \
     "data/04.dat" using 1:7 with lines lc rgb 'brown' title "some M, some A+ (Upper)", \
     "data/04.dat" using 1:8 with lines lc rgb 'purple' title "2arg killer for t*<1/3"