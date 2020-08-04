from collections import deque


def play_game(n_player, last_marble):
    player_scores = [0] * n_player
    board = deque([0])

    for marble in range(1, last_marble + 1):
        if marble % 23 == 0:
            board.rotate(7)
            player_scores[(marble - 1) % n_player] += marble + board.pop()
            board.rotate(-1)
        else:
            board.rotate(-1)
            board.append(marble)

    return max(player_scores)


def part_one():
    return play_game(441, 71032)


def part_two():
    return play_game(441, 7103200)


if __name__ == '__main__':
    print("Part 1:", part_one())
    print("Part 2:", part_two)
