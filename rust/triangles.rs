//////////////////////////////////////////////////////////////////////////////////////////
// Similar to `../c/triangles.c` but much closer to the problem as originally described //
//////////////////////////////////////////////////////////////////////////////////////////

#![feature(map_into_keys_values)]

use std::collections::HashMap;

struct Triangle([usize; 3]);

impl Triangle {
    fn hash(&self) -> usize {
        self.0.iter().sum()
    }
}

impl PartialEq for Triangle {
    fn eq(&self, other: &Self) -> bool {
        let [a, b, c] = other.0;
        self.0 == [a, b, c]
            || self.0 == [a, c, b]
            || self.0 == [b, a, c]
            || self.0 == [b, c, a]
            || self.0 == [c, a, b]
            || self.0 == [c, b, a]
    }
}

fn main() {
    let triangles: Vec<Triangle> = [
        [1, 1, 5],
        [3, 3, 1],
        [5, 5, 5],
        [6, 6, 6],
        [2, 2, 3],
        [2, 3, 2],
        [5, 1, 1],
    ]
    .iter()
    .map(|a| Triangle(*a))
    .collect();

    let n = triangles.len();

    let mut result: HashMap<usize, Vec<Triangle>> = HashMap::new();

    for tri in triangles.into_iter() {
        let idx = tri.hash() % n;
        let vec = result.entry(idx).or_default();
        if !vec.contains(&tri) {
            vec.push(tri);
        }
    }

    let unique: usize = result.into_values().map(|vec| vec.len()).sum();

    println!("There are {} unique triangle kinds", unique);
}
