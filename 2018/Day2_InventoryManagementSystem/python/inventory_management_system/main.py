import numpy as np
from collections import Counter
from itertools import combinations, compress


def part_one(data, allow_counts=(2, 3), use_counter=False):
    def counts(x):
        if use_counter:
            return sum(x in Counter(word).values() for word in data)
        else:
            return sum(any(word.count(c) == x for c in word) for word in data)

    return np.prod([counts(x) for x in allow_counts])


def part_two_with_enumerate(data, n_diff=1):
    for one, two in combinations(data, 2):
        diff_index = [i for i, (e1, e2) in enumerate(zip(one, two)) if e1 != e2]
        if len(diff_index) == n_diff:
            return ''.join([c for i, c in enumerate(one) if i not in diff_index])


def part_two_with_compress(data, n_diff=1):
    for one, two in combinations(data, 2):
        is_char_diff = [e1 == e2 for e1, e2 in zip(one, two)]
        if sum(is_char_diff) == (len(one) - n_diff):
            return ''.join(list(compress(one, is_char_diff)))


if __name__ == '__main__':
    input_data = np.loadtxt("../../input.txt", dtype=object)
    # Part1
    print("Part 1:", part_one(input_data))

    # Part2
    print("Part 2:", part_two_with_enumerate(input_data))
    print("Part 2:", part_two_with_compress(input_data))
