use std::{
    fs::File,
    io::{BufRead, BufReader},
    path::Path,
    str::FromStr,
    fmt::Debug,
    collections::HashSet,
};

fn vec_from_file<T: FromStr>(filename: impl AsRef<Path>) -> Vec<T>
    where T::Err: Debug
{
    BufReader::new(File::open(filename).expect("Could not open file"))
        .lines()
        .map(|l| l.expect("Could not read line"))
        .map(|l| l.parse().expect(&format!("Could not parse line '{}'", l)))
        .collect()
}

fn part_one(data: &[i32]) {
    let sum = data.iter().sum::<i32>();
    println!("Part 1: {}", sum);
}

fn part_two(data: &[i32]) {
    let mut frequency = 0;
    let mut set = HashSet::new();
    for change in data.iter().cycle() {
        frequency += change;
        if !set.insert(frequency) {
            break;
        }
    }
    println!("Part 2: {}", frequency);
}

fn main() {
    let data: Vec<i32> = vec_from_file("../../input.txt");
    part_one(&data);
    part_two(&data);
}