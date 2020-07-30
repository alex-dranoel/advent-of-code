from itertools import accumulate, cycle
import numpy as np


def part_one(data):
    sum_data = np.sum(data)
    print("Part 1: %d" % sum_data)


def part_two(data):
    seen = {0}
    repeated_freq = next(freq for freq in accumulate(cycle(data)) if freq in seen or seen.add(freq))
    print("Part 2: %d" % repeated_freq)


if __name__ == '__main__':
    input_data = np.loadtxt("../../input.txt", dtype=np.int)
    part_one(input_data)
    part_two(input_data)

