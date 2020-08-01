import parse
from collections import defaultdict


def claim_from_str(line_format, line):
    return parse.parse(line_format, line.strip())


def make_claims_map(claims):
    claims_map = defaultdict(list)
    for c in claims:
        for y in range(c['h']):
            for x in range(c['w']):
                claims_map[(c['x'] + x, c['y'] + y)].append(c['id'])

    return claims_map


def part_one(claims_map):
    return sum([1 for ids in claims_map.values() if len(ids) > 1])


def part_two(claims_map, claims):
    for c in claims:
        if all([len(claims_map[(c['x'] + x, c['y'] + y)]) == 1 for y in range(c['h']) for x in range(c['w'])]):
            return c['id']


def main():
    line_format = "#{id:d} @ {x:d},{y:d}: {w:d}x{h:d}"
    claims = [claim_from_str(line_format, line) for line in open("../../input.txt")]
    claims_map = make_claims_map(claims)

    print("Part 1:", part_one(claims_map))
    print("Part 2:", part_two(claims_map, claims))


if __name__ == '__main__':
    main()
