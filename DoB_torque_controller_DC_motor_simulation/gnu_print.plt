set timestamp
set terminal pdf
set output "motor_simulator_result.pdf"
set title "Torqur controller"
set xlabel "Time (s)"
set ylabel "Theta dot"
plot "motor_simulate_data.txt" using 1:2 with line title "Theta dot", "motor_simulate_data.txt" using 1:3 with line title "Torque cmd", "motor_simulate_data.txt" using 1:4 with line title "Torque load", "motor_simulate_data.txt" using 1:5 with line title "Torque external-estimate" 
