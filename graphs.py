#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
from math import *

"""
C++ project
"""


def main(x, f, name):
    """
    Plot of some useful functions
    """
    plt.figure()
    plt.plot(x, f(x), color = "black")
    plt.title("alpha = 1")
    plt.savefig("img/saved/graph_function_{}.png".format(name))
    plt.show()


if __name__ == "__main__":
    N = 10000
    x = np.linspace(0, 5, N)
    f = lambda x: 1 - np.exp(- 1 / x**2)
    g = lambda x: np.exp(-x)
    h = lambda x: 1 / (1 + x)
    main(x, f, "selected")
    main(x, g, "exp")
    main(x, h, "inv")
