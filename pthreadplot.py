# fit a second degree polynomial to the economic data
import numpy as np
import matplotlib.pyplot as plt
import matplotlib as mpl

X = []
Y = []
Z = []

X, Y, Z = np.loadtxt('thread.txt', delimiter=' ', unpack=True)

plt.grid(color = 'green', linestyle = '--', linewidth = 0.5)

cmap = plt.get_cmap('jet', 8)
norm = mpl.colors.Normalize(vmin=0, vmax=8)
sm = plt.cm.ScalarMappable(cmap=cmap, norm=norm)
sm.set_array([])
plt.colorbar(sm, ticks=np.linspace(0, 8, 9))

color = [cmap(0) if x==1 else cmap(1) if x==2 else cmap(2) if x==3 else cmap(3) if x==4 else cmap(4) if x==5 else cmap(5) if x==6 else cmap(6) if x==7 else cmap(7) for x in Z]

plt.scatter(Y, X, c=color)
plt.title('pthread implementation')
plt.xlabel('Time in seconds')
plt.ylabel('Size of matrix NxN')

plt.show()
