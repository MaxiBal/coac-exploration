import matplotlib.pyplot as plt
import numpy as np

from matplotlib.animation import FuncAnimation

def objective_function(x, y):
    return 100.0*(y - x ** 2) ** 2 + (1-x) ** 2

x = np.arange(-20.0,20.0,0.1)
y = np.arange(-20.0,20.0,0.1)

X, Y = np.meshgrid(x, y)

Z = objective_function(X, Y)

moving_data = [
    [(-4.25411, -7.09048), (-3.07603, -3.05544), (6.26462, 8.55683), (-9.28317, 1.37116), ],
    [(-3.74749, 0.795185), (2.27276, 10), (-1.5004, -0.0504713), (-0.633662, -10), ],
    [(-1.12454, -4.85123), (-1.12454, -4.85123), (2.62942, 1.13353), (-1.12454, -4.85123), ],
    [(2.27276, 10), (-1.12454, -4.85123), (1.28918, 6.99316), (-1.12454, -4.85123), ],
    [(-1.5004, -0.0504713), (1.28918, 6.99316), (0.581543, 0.429243), (0.581543, 0.429243), ],
    [(-1.5004, -0.0504713), (1.28918, 6.99316), (-1.5004, -0.0504713), (1.28918, 6.99316), ],
    [(0.196615, 0.491598), (-3.90637, 10), (0.581543, 0.429243), (0.581543, 0.429243), ],
    [(0.904253, 4.40277), (0.581543, 0.429243), (0.904253, 4.40277), (0.196615, 0.491598), ],
    [(0.581543, 0.429243), (0.581543, 0.429243), (0.825594, 0.815858), (0.581543, 0.429243), ],
    [(0.581543, 0.429243), (0.581543, 0.429243), (0.581543, 0.429243), (0.581543, 0.429243), ],
    [(0.581543, 0.429243), (0.49746, 0.222754), (0.49746, 0.222754), (0.825594, 0.815858), ],
]

# create a figure with an axes
fig, ax = plt.subplots()
# set the axes limits
# set equal aspect such that the circle is not shown as ellipse
ax.set_aspect("equal")
# create a point in the axes

ax.plot(1, 1, marker='x')

points = [ax.plot(0, 0, marker='o')[0] for _ in range(len(moving_data[0]))]

im = ax.pcolormesh(X, Y, Z,cmap=plt.cm.RdBu)

def update(t):
    for ant in range(len(moving_data[0])):
        x, y = moving_data[t][ant]
        points[ant].set_data(x, y)
        

        
ani = FuncAnimation(fig, update, frames=len(moving_data), interval=350, repeat=False)
fig.colorbar(im) # adding the colobar on the right

plt.show()