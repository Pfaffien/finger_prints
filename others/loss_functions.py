#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

"""
C++ project: graphs of loss functions
"""


def loss_tx():
    """
    Plot the loss function for tx_finger.png
    """
    data = open("data_tx.txt", "r")
    lines = data.readlines()
    values = []

    for line in lines:
        values.append(line)
        
    size, values = values[0], values[1:]
    new_values = []

    for elt in values:
        new_values.append(float(elt[:-1]))

    p = [i for i in range(-int(size)//2+1, int(size)//2+1)]

    data.close()

    plt.figure()
    plt.plot(p, new_values)
    plt.xlabel("p")
    plt.ylabel("l(p)")
    plt.title("Loss function for a translation along x")
    plt.savefig("../img/saved/loss_function_tx.png")
    plt.show()


def loss_txy():
    """
    Plot the loss function for txy_finger.png
    """
    data = open("data_txy.txt", "r")
    lines = data.readlines()
    values = []

    for line in lines:
        values.append(line)

    size_x, size_y = int(values[0]), int(values[1])
    values = values[2:]
    new_values = []

    for elt in values:
        new_values.append(float(elt[:-1]))

    new_values = np.array(new_values)
    l = new_values.reshape(size_x, size_y).transpose()
    p_x = [i for i in range(-int(size_x)//2+1, int(size_x)//2+1)]
    p_y = [i for i in range(-int(size_y)//2+1, int(size_y)//2+1)]
    px, py = np.meshgrid(p_x, p_y)

    fig = plt.figure()
    ax = fig.gca(projection = "3d")
    ax.plot_surface(px, py, l, rstride = 3, cstride = 3, cmap = "viridis", edgecolor = "none")
    plt.plot(size_y * [-10], p_y, color = "red", label = "p_x = -10")
    plt.plot(p_x, size_x * [30], color = "orange", label = "p_y = 30")
    ax.set_xlabel("p_x")
    ax.set_ylabel("p_y")
    ax.set_zlabel("l(p_x, p_y)")
    ax.set_title("Loss function of a translation along x and y")
    ax.legend()
    plt.savefig("../img/saved/loss_function_txy.png")
    plt.show()


def main():
    loss_tx()
    loss_txy()


if __name__ == "__main__":
    main()