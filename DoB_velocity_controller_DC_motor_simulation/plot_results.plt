
set timestamp
set terminal pdf
set output "DC_motor_simulation_results.pdf"
set title "Motor Internal Data"
set xlabel "Time (s)"
set ylabel "Motor Anguler Velocity (rad.s^{-1})"
#set xrange [0:10]
#set yrange [-1:20]
#set xtic 0,0.5,20
#plot "simulation_results.txt" using 1:4 with line title "Wres", "simulation_results.txt" using 1:3 with line title "Jdw",
plot "simulation_results.txt" using 1:2 with line title "Ia*Kt" , "simulation_results.txt" using 1:4 with line title "Anguler Velocity (d0)" 

