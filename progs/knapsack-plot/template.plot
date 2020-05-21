set dgrid3d
#set auto
set surface
unset key
set samples 5
set isosamples 50
set terminal eps size 5, 5
set size 1,1
set output 'plot.eps'
set cntrparam levels 100
set cntrparam cubic
set contour surface
set dgrid3d 100,100
set ytics 0.1
set xtics 0.1
set zrange [0.58:0.7]
#set view 10,30
set view map
set xlabel "x"
set ylabel "b"
splot "data.dat" using 1:2:3 with pm3d