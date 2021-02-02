////////////////////////////////////
//   A CLI calculator in Rust    //
///////////////////////////////////

use std::io::Write;

fn main() {
    loop {

        print!("Please input a simple expression: ");
        std::io::stdout().flush().ok().unwrap();

        let mut input = String::new();
        std::io::stdin().read_line(&mut input).unwrap();
        input.pop();

        if input.eq_ignore_ascii_case("quit") {
            println!("Bye!");
            return;
        }

        // A crazy amount of effort to avoid 3 `match` blocks
        fn parse_input<'a>(s: &'a String) -> Result<(f64, &'a str, f64), ()> {
            let mut iter = s.split_ascii_whitespace();
            let a = iter.next().ok_or(())?.parse::<f64>().map_err(|_| ())?;
            let op = iter.next().ok_or(())?;
            let b = iter.next().ok_or(())?.parse::<f64>().map_err(|_| ())?;
            Ok((a, op, b))
        }

        let (a, op, b) = match parse_input(&input) {
            Ok((x, y, z)) => (x, y, z),
            _ => {
                println!("Couldn't parse input!");
                continue;
            }
        };

        let result = match op {
            "+" => a + b,
            "-" => a - b,
            "*" => a * b,
            "/" => a / b,
            "^" => a.powf(b),
            _ => {
                println!("[{}] isn't a supported operator!", op);
                continue;
            }
        };

        println!("---");

        println!("{} {} {} = {}", a, op, b, result);

        println!("---");

    }
}