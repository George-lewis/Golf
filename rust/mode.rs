////////////////////////////////////////////////////////////////////////
// Calculate the mode of a list of integers with increasing verbosity //
//         These implementations only calculate a single mode         //
////////////////////////////////////////////////////////////////////////

use std::{collections::HashMap, ops::AddAssign};

fn mode1(values: &[i32]) -> Option<i32> {
    values
        .iter()
        .cloned()
        .fold(HashMap::new(), |mut map, x| {
            map.entry(x).or_insert(0).add_assign(1);
            map
        })
        .into_iter()
        .max_by_key(|x| x.1)
        .map(|x| x.0)
}

fn mode2(values: &[i32])-> Option<i32> {
    let mut freqs: HashMap<i32, u32> = HashMap::new();

    for x in values {
        freqs.entry(*x).or_insert(0).add_assign(1);
    }

    freqs.into_iter().max_by_key(|x| x.1).map(|x| x.0)
}

fn mode3(values: &[i32])-> Option<i32> {

    if values.is_empty() {
        return Option::None;
    }

    let mut freqs: HashMap<i32, u32> = HashMap::new();

    for x in values {
        freqs.entry(*x).or_insert(0).add_assign(1);
    }

    let mut max_k = 0;
    let mut max_v = 0;

    for (k, v) in freqs {
        if v > max_v {
            max_k = k;
            max_v = v;
        }
    }

    Some(max_k)
}

fn mode4(values: &[i32])-> Option<i32> {

    if values.is_empty() {
        return Option::None;
    }

    let mut freqs: HashMap<i32, u32> = HashMap::new();

    for x in values {
        match freqs.get_mut(x) {
            Some(v) => *v += 1,
            None => {
                freqs.insert(*x, 1);
            }
        }
    }

    let mut max_k = 0;
    let mut max_v = 0;

    for (k, v) in freqs {
        if v > max_v {
            max_k = k;
            max_v = v;
        }
    }

    Some(max_k)
}

fn main() {
    let arr = &[1, 2, 3, 4, 5, 5, 5, 6];
    assert_eq!(5, mode1(arr).unwrap());
    assert_eq!(5, mode2(arr).unwrap());
    assert_eq!(5, mode3(arr).unwrap());
    assert_eq!(5, mode4(arr).unwrap());
}