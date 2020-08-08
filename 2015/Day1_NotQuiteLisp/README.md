# An easy start

## Part one
For this first puzzle, the solution is almost instant for the first part. In **C++** and **Rust**, a simple range-based for loop do the job easily and quickly. The amount of code to be written is very small: a `floor` variable will be increment for each `(`encountered, and decremented for each `)`. 

#### Rust part one:
```Rust    
fn part_one(line: &str) {  
    let mut floor = 0;  
    for c in line.chars() {  
        floor += if c == '(' {1} else {-1};  
    }  
    println!("Part 1: {}", floor);  
}
```

#### C++ part one:
```c++
void part_one(string_view instructions) {  
    int floor {0};  
    for (auto ch: instructions) {  
        floor += ch == '(' ? 1 : -1;  
    }  
    cout << "Part 1: " << floor << endl;  
}
```

In **Python**, writing such loop is of course possible but is probably not the pythonic way of getting the solution. The string class in python provides some more higher level methods that can be used to get the solution in a one-liner. Python strings provide have a`count(item)` method, that can be used to count how many `(`or `)` are part of it. The solution for part one is therefore trivially obtained.

#### Python part one:
	
```python
def part_one(line):  
    print(f"Part 1: {line.count('(') - line.count(')')}")
```
  
*Note*: the `collections` module in Python provides a class named `Counter` which can be used to extract character frequencies of a string. For our simple case that does not really bring an added value, but if we were to search more than two characters, the `Counter` class would be the way to go. Here is the solution using this class:
	
```python
def part_one_counter(line):  
    counter = Counter(line)  
    print(f"Part 1: {counter['('] - counter[')']}")
```
    
For part one, **Python** is clearly a winner already. There might exist some library that provide the same counting feature in C++ and Rust, but Python provides it in its standard. 
   
### Conclusion
Python higher level feature leads to a one-liner solution and is probably the fastest way to get the answer. Someone could also just copy paste the string into an online character frequency counter. No code to write.
Without knowing the second part of the puzzle, those solutions are probably the best approach. However, someone lucky might have gone another road, and compute partial sums. For example, for an input such as `(()))()` transformed into integers lead to `1,1,-1,-1,-1,1,-1`. One can compute the partial sums of this array: `1,2,1,0,-1,0,-1`. The last element leads to the answer for part one too. There is indeed some extra work, but part two is directly solved now already as you'll see below.

 ## Part two
The second part of the puzzle will probably make C++ and Rust developers quite happy for the simple reason that the ranged-base for loop solution of part one can easily be extended to get the answer to part two. By just adding a `counter` to keep track of the index, and a `break` statement as soon as the `floor` variable is `-1` will provide the right answer. 

#### Rust part two from one:
```Rust    
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
```

#### C++ part two from one:

```c++
void part_two_from_one(string_view instructions) {  
    int floor {0};  
    int counter {0};  
    for (auto ch: instructions) {  
        counter++;  
        floor += ch == '(' ? 1 : -1;  
        if (floor < 0) break;  
    }  
    cout << "Part 2: " << counter << endl;  
}  
```

Python developers cannot just start from the pythonic solution to part one (that's not a big problem given that it was a one-liner). The same approach as in C++ and Rust can be used in Python:

#### Python part two from one:
	
```python
def part_two(line):  
    floor = 0  
    counter = 0  
    for ch in line:  
        counter += 1  
        floor += 1 if ch == '(' else -1  
        if floor < 0:  
            break  
  
    print(f"Part 2: {counter}")
```
  
But again, that's probably not the pythonic way. A more idiomatic solution can be obtained by the partial sum idea mentioned above.

## Using partial sum
This approach did not directly come to my mind just from part one problem. But with the second part of the puzzle, this became much more evident. Still, writing the solutions presented above is likely to be the quickest way to the answer. Nevertheless, exploring the partial sum idea leads to better code according to me (nice code is not the goal of Advent of Code, but for past challenge, I like to search for good-looking code).

In C++, the STL provides all the necessary tools to implement this approach: `vector`, `transform`, `partial_sum`, `distance`, `find` are to be used. The idea is to `transform` the input string into a `vector` of `1` and `-1`, on which we can apply the `partial_sum` algorithm. The last element is the answer to part one. Using `find` with value `-1` gives us a pointer to the first element of the vector, which combined with the `distance` function gives the answer to part two of the puzzle.

#### C++ partial sum:
```c++
void combo_part_one_and_two_stl(string_view instructions) {  
    vector<int> partial_sum;  
    partial_sum.reserve(instructions.size());  
    transform(all(instructions), back_inserter(partial_sum), [](char ch) {return ch=='('?1:-1;});  
    partial_sum(all(partial_sum), begin(partial_sum));  
    cout << "Part 1: " << partial_sum.back() << endl;  
    cout << "Part 2: " << 1 + distance(begin(partial_sum), find(all(partial_sum), -1)) << endl;  
} 
```

*Note*: `all(v)` is a macro defined as `#define all(v) std::begin(v), std::end(v)`

Rust implementation of this approach is very similar except that iterator operations can be chained. There is also a little more work for the partial_sum as such a specific algorithm is not part of rust std, and must be implemented by mean of `scan`. The Rust code is using `map` to transform the string characters `(` and `)` into `1` and `-1`, next applying `scan` to get the partial sums. The output is `collect`-ed as a `Vec'`-tor whose last element is the answer to part one. Iterating further into this vector with the use of `enumerate` to get both the index and the value of each element, the `find` function gets us the first element with value `-1` from which we retrieve the index by `map`-ping it (shifted by one). This gives us the answer to part two.

#### Rust partial sum:
```Rust    
fn accumulate<T: Copy + AddAssign>(acc: &mut T, next: T) -> Option<T> {  
    *acc += next;  
    Some(*acc)  
}
fn combo_part_one_and_two_accumulate(line: &str) {  
    let partial_sum: Vec<i32> = line.chars()  
        .map(|c| {if c == '(' {1} else {-1}})  
        .scan(0, accumulate)  
        .collect();  
  
    let floor = partial_sum.last().unwrap();  
    let index = partial_sum.iter().enumerate()  
        .find(|(_index, &x)| x == -1)  
        .map(|(index, _x)| 1+index).unwrap();  
  
    println!("Part 1: {}", floor);  
    println!("Part 2: {}", index);  
}
```

Python's way of doing the partial sum solution presented in this section is ... easier for the least. Much easier actually. List comprehension is used to perform the transform step, the result of which is fed to the `accumulate` function of the `itertools` module. A `list` is finally build out of the `accumulate` output. Again, the last element is the answer to part one. Getting the answer to part two is as easy as calling the method `index(value)` of list to find the first element matching the value. Including the printing, this is a nice three pythonic lines of codes.

#### Python partial sum:
```python
def combo_part_one_and_two_accumulate(line):  
    acc = list(accumulate([1 if c == '(' else -1 for c in line]))  
  
    print(f"Part 1: {acc[-1]}")  
    print(f"Part 2: {1 + acc.index(-1)}")
```

According to me, it's hard to get something shorter than this, to be compared with the verbosity of C++ and Rust for that example.
