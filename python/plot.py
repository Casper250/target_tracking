import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("../data/results.csv")

plt.plot(data["x"], data["y"])

plt.xlabel("x")
plt.ylabel("sin(x)")
plt.title("Result from C++ calculation")

plt.grid()
plt.savefig("../data/results.png", dpi=300, bbox_inches="tight")
print("Plot saved to data/results.png")