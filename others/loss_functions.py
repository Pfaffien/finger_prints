#!/usr/bin/env python3

import matplotlib.pyplot as plt

"""
C++ project: graphs of loss functions
"""


def main():
    data = open("data_transx.txt", "r")
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
    plt.show()


if __name__ == "__main__":
    main()