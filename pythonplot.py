import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import os

# Path to CSV files
folder = "build/data/output"

# Sort files numerically by frame number
files = sorted(
    [f for f in os.listdir(folder) if f.endswith(".csv")],
    key=lambda x: int(x.split("_")[1].split(".")[0])
)

# Load the first frame to initialize plot
data = np.loadtxt(os.path.join(folder, files[0]), delimiter=",")

# Fix the color scale across all frames (very important!)
vmin, vmax = 0, 100  # match your initial peak temperature
fig, ax = plt.subplots()
im = ax.imshow(data, cmap="hot", origin="lower", vmin=vmin, vmax=vmax)
cbar = plt.colorbar(im, ax=ax, label="Temperature")

# Animation update function
def update(frame):
    data = np.loadtxt(os.path.join(folder, files[frame]), delimiter=",")
    im.set_array(data)
    ax.set_title(f"Frame: {files[frame]}")
    return [im]

# Create animation with fixed timing
ani = animation.FuncAnimation(fig, update, frames=len(files), interval=1000, blit=True)

# Save as animated GIF
ani.save("heat_animation.gif", writer="pillow", fps=1)
print("✅ Saved: heat_animation.gif")
