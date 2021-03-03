/////////////////////////////////////////////
// A clone of `../c/c11_threads.c` in Rust //
/////////////////////////////////////////////

fn main() {
    let mut threads = Vec::new();

    let thread = std::thread::spawn(|| println!("Hello Rust threads!"));
    threads.push(thread);

    for i in 0..10 {
        let thread = std::thread::spawn(move || println!("{}", i));
        threads.push(thread);
    }

    threads.into_iter().for_each(|t| {
        t.join().unwrap();
    });

}