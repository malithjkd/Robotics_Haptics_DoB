import random
import math
import matplotlib.pyplot as plt
import numpy as np

random.seed(10)

omega = 2 * math.pi * 50

out_data_with_noize = np.zeros((1050, 3))

for x in range(0,1000):
	t = x*0.003	# in seconds
	out_data_with_noize[x,0] = t
	if(x<333):
		out_data_with_noize[x,2]  = random.uniform(-0.5,0.5)
	elif(x<666):
		out_data_with_noize[x,2]  = random.uniform(-0.5,0.7)
	else:
		out_data_with_noize[x,2]  = random.uniform(-0.7,0.5)
	y = 5*math.sin(omega*t) + out_data_with_noize[x,2]
	out_data_with_noize[x,1] = y



plt.plot(out_data_with_noize[:,0],out_data_with_noize[:,1],label="Noizy data")
plt.plot(out_data_with_noize[:,0],out_data_with_noize[:,2],label="Noizye")
plt.title('Output data - with noize')
plt.xlabel('Time[s]')
plt.ylabel('Encoder position[rad]')
plt.legend(loc="upper right")
plt.grid
plt.show()


