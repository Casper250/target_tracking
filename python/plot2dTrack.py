import pandas as pd
import matplotlib.pyplot as plt

# Load CSV
df = pd.read_csv("data/CVresults.csv")

# Positions
plt.figure()

plt.plot(df["x_1"], df["x_2"], label="True",marker="o")

plt.plot(df["x_hat_1"], df["x_hat_2"], label="Estimated", marker="x")

plt.xlabel("x")
plt.ylabel("y")
plt.title("Position")
plt.legend()
plt.grid(True)
plt.axis("equal")

plt.savefig("data/position.png")

# Velocity
plt.figure()

plt.plot(df["x_3"], df["x_4"], label="True", marker="o")

plt.plot(df["x_hat_3"], df["x_hat_4"], label="Estimated", marker="x")

plt.xlabel("vx")
plt.ylabel("vy")
plt.title("Velocity")
plt.legend()
plt.grid(True)
plt.axis("equal")

plt.savefig("data/velocity.png")
plt.close()