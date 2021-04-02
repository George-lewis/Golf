///////////////////////////////////////////////////////////////////////
// Finds fibonacci happy primes. First three: [1, 28657, 2971215073] //
// https://en.wikipedia.org/wiki/Fibonacci_number                    //
// https://en.wikipedia.org/wiki/Prime_number                        //
// https://en.wikipedia.org/wiki/Happy_number                        //
///////////////////////////////////////////////////////////////////////

use std::collections::HashMap;

struct Fib {
    mem: [u128; 2],
}

impl Fib {
    fn new() -> Self {
        Fib { mem: [0, 1] }
    }

    fn next(&mut self) -> u128 {
        let x = self.mem[0] + self.mem[1];
        self.mem = [self.mem[1], x];
        x
    }
}

struct Prime {
    mem: HashMap<u128, bool>,
}

impl Prime {
    fn new() -> Self {
        Self {
            mem: HashMap::new(),
        }
    }

    fn is_prime(&mut self, x: u128) -> bool {
        if let Some(&v) = self.mem.get(&x) {
            return v;
        }
        for i in 2..(x as f64).sqrt().ceil() as u128 {
            if x % i == 0 {
                self.mem.insert(x, false);
                return false;
            }
        }
        self.mem.insert(x, true);
        true
    }
}

struct Happy {
    mem: HashMap<u128, bool>,
}

impl Happy {
    fn new() -> Self {
        let mut hm = HashMap::new();
        hm.insert(1, true);
        Happy { mem: hm }
    }

    fn digits(mut x: u128) -> Vec<u128> {
        let mut vec = Vec::new();
        while x > 0 {
            vec.push(x % 10);
            x /= 10;
        }
        vec
    }

    fn _is_happy(&mut self, x: u128, mut mem: Vec<u128>) -> bool {
        if let Some(&v) = self.mem.get(&x) {
            return v;
        }
        if mem.contains(&x) {
            return false;
        }
        mem.push(x);
        let next = Self::digits(x).iter().sum();
        let result = self._is_happy(next, mem);
        self.mem.insert(next, result);
        result
    }

    fn is_happy(&mut self, x: u128) -> bool {
        self._is_happy(x, Vec::new())
    }
}

fn main() {
    let mut fib = Fib::new();
    let mut prime = Prime::new();
    let mut happy = Happy::new();
    let mut result = Vec::new();
    for _ in 0..200 {
        let n = fib.next();
        if !happy.is_happy(n) {
            continue;
        }
        if !prime.is_prime(n) {
            continue;
        }
        result.push(n);
    }
    println!("{:?}", result);
}
