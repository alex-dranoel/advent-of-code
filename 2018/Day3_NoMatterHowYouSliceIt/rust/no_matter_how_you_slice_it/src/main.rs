use std::str::FromStr;
use std::fmt::Debug;
use std::path::Path;
use std::fs::File;
use std::io::{BufReader, BufRead};

use lazy_static::lazy_static;
use regex::Regex;
use std::collections::HashMap;

type ClaimsMap = HashMap<(i32, i32), Vec<i32>>;

lazy_static! {
    static ref RE: Regex = Regex::new(r"(?P<id>\d+) @ (?P<x>-?\d+),(?P<y>-?\d+): (?P<w>\d+)x(?P<h>\d+)").unwrap();
}

fn vec_from_file<T: FromStr>(filename: impl AsRef<Path>) -> Vec<T>
    where T::Err: Debug
{
    BufReader::new(File::open(filename).expect("Could not open file"))
        .lines()
        .map(|l| l.expect("Could not read line"))
        .map(|l| l.parse().expect(&format!("Could not parse line '{}'", l)))
        .collect()
}

#[derive(Debug)]
struct Claim {
    id: i32,
    x: i32,
    y: i32,
    h: i32,
    w: i32,
}

impl Claim {
    fn squares(&self) -> Vec<(i32, i32)> {
        let mut squares: Vec<(i32, i32)> = Vec::with_capacity((self.h * self.w) as usize);
        for i in self.y..self.y+self.h {
            for j in self.x..self.x+self.w {
                squares.push((j, i));
            }
        }
        squares
    }
}
impl FromStr for Claim {
    type Err = ();

    fn from_str(s: &str) -> Result<Self, Self::Err> {

        let caps = RE.captures(s).unwrap();
        let id: i32 = caps["id"].parse().unwrap();
        let x: i32 = caps["x"].parse().unwrap();
        let y: i32 = caps["y"].parse().unwrap();
        let h: i32 = caps["h"].parse().unwrap();
        let w: i32 = caps["w"].parse().unwrap();

        Ok(Claim {id, x, y, h, w})
    }
}

fn make_claims_map(claims: &[Claim]) -> ClaimsMap {
    let mut claims_map: ClaimsMap = HashMap::new();

    claims.iter().for_each(|claim| {
        claim.squares().iter().for_each(|square| {
            claims_map
                .entry(*square)
                .and_modify(|ids|ids.push(claim.id))
                .or_insert(vec!(claim.id));
        });
    });
    claims_map
}

fn part_one(claims_map: &ClaimsMap) -> usize {
    claims_map.iter()
        .filter(|(_, ids)| ids.len() > 1)
        .count()
}

fn part_two(claims_map: &ClaimsMap, claims: &[Claim]) -> Option<i32> {
    let candidates: Vec<&Claim> = claims.iter()
        .filter(|claim| {
            claim.squares().iter().all(|square| claims_map.get(square).unwrap().len() == 1)
        })
        .collect();

    if candidates.len() > 0 {
        Some(candidates[0].id)
    } else {
        None
    }
}
fn main() {
    let claims: Vec<Claim> = vec_from_file("../../input.txt");
    let claims_map = make_claims_map(&claims);

    println!("Part 1: {}", part_one(&claims_map));
    println!("Part 2: {}", part_two(&claims_map, &claims).unwrap_or(-1));
}
