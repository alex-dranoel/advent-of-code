use std::{
    fs::File,
    io::{BufRead, BufReader},
    path::Path,
    str::FromStr,
    fmt::Debug,
    collections::HashMap,
};

use itertools::Itertools;

fn vec_from_file<T: FromStr>(filename: impl AsRef<Path>) -> Vec<T>
    where T::Err: Debug
{
    BufReader::new(File::open(filename).expect("Could not open file"))
        .lines()
        .map(|l| l.expect("Could not read line"))
        .map(|l| l.parse().expect(&format!("Could not parse line '{}'", l)))
        .collect()
}

struct WordType {
    two: bool,
    three: bool,
}

impl std::str::FromStr for WordType {
    type Err = ();

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let mut char_counts: HashMap<char, u32> = HashMap::new();
        s.chars().for_each(|c| {
            char_counts
                .entry(c)
                .and_modify(|n| *n += 1)
                .or_insert(1);
        });
        let two = char_counts.values().any(|v| *v == 2);
        let three = char_counts.values().any(|v| *v == 3);
        Ok(WordType{ two, three })
    }
}

fn part_one(data: &Vec<String>) -> usize {
    let word_types: Vec<WordType> = data.iter()
        .map(|word| word.parse::<WordType>().unwrap())
        .filter(|w_t| w_t.two || w_t.three)
        .collect();

    let n_two = word_types.iter().filter(|w_t| w_t.two).count();
    let n_three = word_types.iter().filter(|w_t| w_t.three).count();
    n_two * n_three
}

fn part_two(data: &Vec<String>) -> String {
    let mut answer = "".to_string();
    for combo in data.iter().combinations(2) {
        let mut n_diff = 0;
        answer = "".to_string();
        for (ch1, ch2) in combo[0].chars().zip(combo[1].chars()) {
            if ch1 == ch2 {
                answer.push(ch1)
            } else {
                n_diff += 1;
            }
            if n_diff > 1 {
                break;
            }
        }
        if n_diff == 1 {
           break;
        }
    }
    answer
}

fn main() {
    let data: Vec<String> = vec_from_file("../../input.txt");

    println!("Part 1: {}", part_one(&data));
    println!("Part 2: {}", part_two(&data));
}