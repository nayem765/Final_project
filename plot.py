import numpy as np
import matplotlib.pyplot as plt
import os

# Path to folder containing your output CSVs
folder = "build/data/output"

# 🔧 Choose the frame number you want to plot (e.g., 0, 1000, 2000, ..., 10000)
frame_number = 0000  # change this to 1000, 2000, etc.

# Format the filename
filename = f"heat_{frame_number:04d}.csv"
filepath = os.path.join(folder, filename)

# Check if file exists
if not os.path.exists(filepath):
    print(f"❌ File not found: {filepath}")
    exit()

# Load and plot
data = np.loadtxt(filepath, delimiter=",")
plt.imshow(data, cmap="hot", origin="lower")
plt.colorbar(label="Temperature")
plt.title(f"Frame: {filename}")
plt.tight_layout()
plt.show()
