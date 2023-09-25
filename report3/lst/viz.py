import pandas as pd
import matplotlib.pyplot as plt


df = pd.read_csv("rez.txt")

def func(n):
    x = df[df["no"] == n]
    x = x.values[[0, 3, 6, 9, 12]]

    # print(x[:, 2])
    # print(x[:, 4])

    n = x[:, 2]

    delta = x[:, 4]
    print(delta[0] / delta[1], delta[1] / delta[2], delta[2] / delta[3], delta[3] / delta[4])

    delta = x[:, 5]
    print(delta[0] / delta[1], delta[1] / delta[2], delta[2] / delta[3], delta[3] / delta[4])

    delta = x[:, 6]
    print(delta[0] / delta[1], delta[1] / delta[2], delta[2] / delta[3], delta[3] / delta[4])

    print()

    plt.plot(n, delta)

for n in range(4):
    func(n)

plt.legend([n for n in range(4)])

plt.xscale("log")
plt.yscale("log")
plt.savefig("fig.pdf")