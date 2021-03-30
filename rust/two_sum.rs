///////////////////////////////////////////
// some solutions to the two sum problem //
///////////////////////////////////////////

use std::collections::HashSet;

// O(n^2)
fn two_sum_1(target: i8, list: &[i8]) -> Option<(i8, i8)> {
    for i in 0..list.len() {
        for j in 0..list.len() {
            if list[i] + list[j] == target {
                return Some((list[i], list[j]))
            }
        }
    }
    None
}

// O(n log n)
fn two_sum_2(target: i8, list: &mut [i8]) -> Option<(i8, i8)> {
    let mut i: usize = 0;
    let mut j: usize = list.len() - 1;
    list.sort_unstable();
    loop {
        let a = list[i];
        let b = list[j];
        let x = a + b;
        if x < target {
            i += 1;
        } else if x > target {
            j -= 1;
        } else {
            return Some((a, b));
        }
        if i == j {
            return None;
        }
    }
}

// O(n)
fn two_sum_3(target: i8, list: &[i8]) -> Option<(i8, i8)> {
    let mut hs: HashSet<i8> = HashSet::new();
    for &x in list {
        if hs.contains(&(target - x)) {
            return Some((x, target - x))
        }
        hs.insert(x);
    }
    None
}

fn main() {
    dbg!(two_sum_1(5, &[7, 0, 1, 2, -7, 3, 4, 5, 1]));
    dbg!(two_sum_2(5, &mut [7, 0, 1, 2, -7, 3, 4, 5, 1]));
    dbg!(two_sum_3(5, &[7, 0, 1, 2, -7, 3, 4, 5, 1]));
}