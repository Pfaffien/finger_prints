#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
from math import *

"""
C++ project
"""


def main(x, f):
    """
    Plot of some useful functions
    """
    plt.figure()
    plt.plot(x, f(x), color = "black")
    plt.title("Selected function")
    plt.savefig("img/saved/graph_selected_function.png")
    plt.show()


if __name__ == "__main__":
    N = 10000
    x = np.linspace(0, 5, N)
    f = lambda x: 1 - np.exp(- 1 / x**16)
    selected = f(x)
    main(x, f)
