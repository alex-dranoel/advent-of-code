from collections import Counter
from itertools import accumulate


def part_one(line):
    print(f"Part 1: {line.count('(') - line.count(')')}")


def part_one_counter(line):
    counter = Counter(line)
    print(f"Part 1: {counter['('] - counter[')']}")


def part_two(line):
    floor = 0
    counter = 0
    for ch in line:
        counter += 1
        floor += 1 if ch == '(' else -1
        if floor < 0:
            break

    print(f"Part 2: {counter}")


def part_two_accumulate(line):
    acc = accumulate([1 if c == '(' else -1 for c in line])
    # acc = accumulate(map(lambda c: 1 if c == '(' else -1, line))
    print(f"Part 2: {1 + next(i for i, x in enumerate(acc) if x == -1)}")


def combo_part_one_and_two(line):
    floor = 0
    index = None
    for i in range(0, len(line)):
        floor += 1 if line[i] == '(' else -1
        if floor < 0 and not index:
            index = i

    print(f"Part 1: {floor}")
    print(f"Part 2: {1+index}")


def combo_part_one_and_two_accumulate(line):
    acc = list(accumulate([1 if c == '(' else -1 for c in line]))

    print(f"Part 1: {acc[-1]}")
    print(f"Part 2: {1 + acc.index(-1)}")


def main():
    line = open("../../input.txt").readline()

    part_one(line)
    part_one_counter(line)

    part_two(line)
    part_two_accumulate(line)

    combo_part_one_and_two(line)
    combo_part_one_and_two_accumulate(line)


if __name__ == '__main__':
    main()
