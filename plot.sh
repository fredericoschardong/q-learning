#!/usr/bin/gnuplot
reset

# set the text color and font for the label
set label textcolor rgb "black" font "SVBasic Manual, 12"

set grid lc rgb "#d5e0c9"
 
set terminal png size 800,600; 

set output "q-learning-behavior.png"

set xrange[:150]
set ytics 5

set multiplot layout 5,1 rowsfirst

plot "<./main" u 1:2 w lines linecolor rgbcolor "blue" linewidth 2 notitle
plot "<./main" u 1:2 w lines linecolor rgbcolor "red" linewidth 2 notitle
plot "<./main" u 1:2 w lines linecolor rgbcolor "green" linewidth 2 notitle
plot "<./main" u 1:2 w lines linecolor rgbcolor "brown" linewidth 2 notitle
plot "<./main" u 1:2 w lines linecolor rgbcolor "black" linewidth 2 notitle

unset multiplot
