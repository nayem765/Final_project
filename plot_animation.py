import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import os

# Directory containing CSV files
output_dir = "build/data/output"

# Find and sort the CSV files
csv_files = sorted([
    f for f in os.listdir(output_dir)
    if f.startswith("heat_") and f.endswith(".csv")
])

if not csv_files:
    print(f"No output CSV files found in: {output_dir}")
    exit()

# Load the first frame
first_frame = np.loadtxt(os.path.join(output_dir, csv_files[0]), delimiter=",")

fig, ax = plt.subplots()
im = ax.imshow(first_frame, cmap="hot", origin="lower")
cbar = plt.colorbar(im, ax=ax)
cbar.set_label("Temperature")
ax.set_title("Heat Equation Animation")

# Update function
def update(frame_num):
    data = np.loadtxt(os.path.join(output_dir, csv_files[frame_num]), delimiter=",")
    im.set_array(data)
    ax.set_title(f"Heat Equation Animation - {csv_files[frame_num]}")

ani = animation.FuncAnimation(
    fig, update, frames=len(csv_files), interval=100, repeat=False
)

# Save animation
ani.save("heat_animation.gif", writer="imagemagick", dpi=150)


print("Animation saved as heat_animation.mp4")

# Optional: plt.show() to preview
# plt.show()
