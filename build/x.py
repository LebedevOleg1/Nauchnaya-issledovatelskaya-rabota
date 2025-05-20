import matplotlib.pyplot as plt
import numpy as np

for i in range(10):
    data = np.loadtxt(f'/home/oleg/CLionProjects/НИР/build/output_{i}.csv', delimiter=',')
    plt.plot(data[:,0], data[:,1], label=f'Step {i*10}')
    
plt.xlabel('Position')
plt.ylabel('Temperature')
plt.legend()
plt.show()