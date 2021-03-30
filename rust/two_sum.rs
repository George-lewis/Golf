////////////////////////////////////////////////
// an n_log_n solution to the two sum problem //
////////////////////////////////////////////////

fn two_sum(target: i8, list: &mut [i8]) -> Option<(i8, i8)> {
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

fn main() {
    dbg!(two_sum(5, &mut [7, 0, 1, 2, -7, 3, 4, 5, 1]));
}