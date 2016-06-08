#!/usr/bin/gnuplot
reset

# this is to use the user-defined styles we just defined.
set style increment user

# set the text color and font for the label
set label textcolor rgb "black" font "SVBasic Manual, 12"

set grid lc rgb "#d5e0c9"
 
set terminal png size 800,600; 

set output "q-learning-frequency.png"

set boxwidth 0.05 absolute
plot "<./main | cut -f 2 -d ' ' | sort | uniq -c" using ($2-0.2):1 smooth frequency with boxes linecolor rgbcolor "blue" fill solid 1.0 noborder notitle,\
     "<./main | cut -f 2 -d ' ' | sort | uniq -c" using ($2-0.1):1 smooth frequency with boxes linecolor rgbcolor "red" fill solid 1.0 noborder notitle,\
     "<./main | cut -f 2 -d ' ' | sort | uniq -c" using 2:1 smooth frequency with boxes linecolor rgbcolor "green" fill solid 1.0 noborder notitle,\
     "<./main | cut -f 2 -d ' ' | sort | uniq -c" using ($2+0.1):1 smooth frequency with boxes linecolor rgbcolor "brown" fill solid 1.0 noborder notitle,\
     "<./main | cut -f 2 -d ' ' | sort | uniq -c" using ($2+0.2):1 smooth frequency with boxes linecolor rgbcolor "black" fill solid 1.0 noborder notitle
