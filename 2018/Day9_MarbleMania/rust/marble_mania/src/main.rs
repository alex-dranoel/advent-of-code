use std::collections::*;

fn rotate<T>(deque: &mut VecDeque<T>, n: isize) {
    if n == 0 {
        return ();
    } else if n > 0 {
        for _ in 0..n {
            let front = deque.pop_front().unwrap();
            deque.push_back(front);
        }
    } else {
        for _ in 0..-n {
            let back = deque.pop_back().unwrap();
            deque.push_front(back);
        }
    }
}

fn play_game(n_player: usize, n_marble: usize) -> usize {
    let mut player_scores = vec![0; n_player];
    let mut board = VecDeque::with_capacity(n_marble);

    board.push_back(0);
    for marble in 1..=n_marble {
        if marble % 23 == 0 {
            rotate(&mut board, -7);
            player_scores[(marble - 1) % n_player] += marble + board.pop_back().unwrap();
            rotate(&mut board, 1);
        } else {
            rotate(&mut board, 1);
            board.push_back(marble);
        }
    }
    return player_scores.into_iter().max().unwrap();
}

fn main() {
    println!("Part 1: {}", play_game(441, 71032));
    println!("Part 2: {}", play_game(441, 7103200));
}