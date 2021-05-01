set dgrid3d
set auto
set surface
unset key
set samples 5
set isosamples 50
set terminal pdf
set output 'plot.pdf'
set cntrparam levels 100
set cntrparam cubic
set contour surface
set dgrid3d 100,100
set ytics 0.1
set xtics 0.1
set zrange [0.56:0.7]
set view 140,30
set xlabel "a"
set ylabel "b"
splot "data.dat" using 1:2:3 with pm3d