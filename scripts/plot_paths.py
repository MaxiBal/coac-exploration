import numpy as np
import matplotlib.pyplot as plt


from matplotlib.animation import FuncAnimation

fig, ax = plt.subplots()

paths = []

ant_plots = [ax.plot(path[0], path[1], label=f"Ant {i}")[0] for i, path in enumerate(paths)]

ax.plot(100, 100, 'x')

ax.axis([-500, 500, -500, 500])

def update(t):
    for i, plot in enumerate(ant_plots):
        path_data = np.array(paths[i])
        plot.set_data(path_data[:t, 0], path_data[:t, 1])


ani = FuncAnimation(fig, update, frames=len(paths[0]), interval=350, repeat=False)

fig.legend()
plt.show()


