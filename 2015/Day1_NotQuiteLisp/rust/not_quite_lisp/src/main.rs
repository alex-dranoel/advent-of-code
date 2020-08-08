use std::str::FromStr;
use std::fmt::Debug;
use std::path::Path;
use std::io::{BufReader, BufRead};
use std::fs::File;
use std::ops::AddAssign;

fn vec_from_file<T: FromStr>(filename: impl AsRef<Path>) -> Vec<T>
    where T::Err: Debug
{
    BufReader::new(File::open(filename).expect("Could not open file"))
        .lines()
        .map(|l| l.expect("Could not read line"))
        .map(|l| l.parse().expect(&format!("Could not parse line '{}'", l)))
        .collect()
}

fn accumulate<T: Copy + AddAssign>(acc: &mut T, next: T) -> Option<T> {
    *acc += next;
    Some(*acc)
}

fn part_one(line: &str) {
    let mut floor = 0;
    for c in line.chars() {
        floor += if c == '(' {1} else {-1};
    }
    println!("Part 1: {}", floor);
}

fn part_two_from_one(line: &str) {
    let mut floor = 0;
    let mut counter = 0;
    for c in line.chars() {
        counter += 1;
        floor += if c == '(' {1} else {-1};
        if floor < 0 {
            break;
        }
    }
    println!("Part 2: {}", counter);
}

fn part_two(line: &str) {
    let mut floor = 0;
    let mut counter: usize = 0;
    while floor >= 0 {
        floor += if &line[counter..counter+1] == "(" {1} else {-1};
        counter += 1;
    }
    println!("Part 2: {}", counter);
}

fn part_two_accumulate(line: &str) {
    let index: usize = line.chars()
        .map(|c| {if c == '(' {1} else {-1}})
        .scan(0, accumulate).enumerate()
        .find(|(_, floor)| *floor == -1)
        .map(|(index, _)| 1+index).unwrap();

    println!("Part 2: {}", index);
}

fn combo_part_one_and_part_two(line: &str) {
    let mut floor = 0;
    let mut counter: usize = 0;
    let mut index: Option<usize> = None;
    for c in line.chars() {
        floor += if c == '(' {1} else {-1};
        counter += 1;
        if floor < 0 && index.is_none() {
            index = Some(counter);
        }
    }
    println!("Part 1: {}", floor);
    println!("Part 2: {}", index.unwrap());
}

fn combo_part_one_and_two_accumulate(line: &str) {
    let partial_sum: Vec<i32> = line.chars()
        .map(|c| {if c == '(' {1} else {-1}})
        .scan(0, accumulate)
        .collect();

    let floor = partial_sum.last().unwrap();
    let index = partial_sum.iter()
        .enumerate()
        .find(|(_index, &x)| x == -1)
        .map(|(index, _x)| 1+index)
        .unwrap();

    println!("Part 1: {}", floor);
    println!("Part 2: {}", index);
}

fn main() {
    let data: Vec<String> = vec_from_file("../../input.txt");
    let line = data[0].clone();

    part_one(&line);
    part_two_from_one(&line);
    part_two(&line);
    part_two_accumulate(&line);
    combo_part_one_and_part_two(&line);
    combo_part_one_and_two_accumulate(&line);
}
