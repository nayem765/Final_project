import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import glob
import os

# Folder containing all output CSVs
output_dir = "build/data/output"
csv_files = sorted(glob.glob(os.path.join(output_dir, "heat_*.csv")))

if not csv_files:
    print("No CSV files found in:", output_dir)
    exit()

# Load first frame to initialize plot
first_frame = np.loadtxt(csv_files[0], delimiter=",")

fig, ax = plt.subplots()
im = ax.imshow(first_frame, cmap="hot", origin="lower")
cbar = plt.colorbar(im, ax=ax)
cbar.set_label("Temperature")

# Title updates as frame evolves
# Update function
def update(frame_num):
    data = np.loadtxt(os.path.join(output_dir, csv_files[frame_num]), delimiter=",")
    im.set_array(data)
    ax.set_title(f"Heat Equation Animation - {csv_files[frame_num]}")

ani = animation.FuncAnimation(
    fig, update, frames=len(csv_files), interval=100, repeat=False
)

plt.show()

