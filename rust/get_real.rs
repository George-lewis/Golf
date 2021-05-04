///////////////////////////////////////////////////////////////////////////
//           An implementation of some algorithms found in               //
// "Accurate Floating Point Product and Exponentiation" by Stef Graillat //
//            https://hal.archives-ouvertes.fr/hal-00164607              //
///////////////////////////////////////////////////////////////////////////

macro_rules! last {
    ($e:expr) => {
        *$e.last().unwrap()
    };
}

fn split(a: f64) -> (f64, f64) {
    const FACTOR: u32 = 2_u32.pow(std::f64::MANTISSA_DIGITS / 2) + 1;
    let c = a * FACTOR as f64;
    let x = c - (c - a);
    let y = a - x;
    (x, y)
}

fn two_product(a: f64, b: f64) -> (f64, f64) {
    let x = a * b;
    let (a1, a2) = split(a);
    let (b1, b2) = split(b);
    let y = a2 * b2 - (((x - a1*b1) - a2*b1) - a1*b2);
    (x, y)
}

fn comp_lin_power(x: f64, n: u8) -> f64 {
    let mut p = vec![x];
    let mut e = vec![0_f64];
    for _ in 2..=n {
        let (p_i, pi) = two_product(last!(p), x);
        e.push(last!(e) + pi);
        p.push(p_i);
    }
    last!(p) + last!(e)
}

fn main() {
    let result = comp_lin_power(5.5, 3);
    println!("5.5^3 = {}", result);
}