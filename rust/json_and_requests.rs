/////////////////////////////////////////////////////////////////////////////////
// Demonstrates http requests and json serialization / deserialization in Rust //
/////////////////////////////////////////////////////////////////////////////////

#![allow(non_snake_case)]

use std::io::Read;

use serde::{Deserialize, Serialize};

fn main() {
    request("https://jsonplaceholder.typicode.com/todos/1");
}
#[derive(Deserialize, Serialize)]
struct Todo {
    userId: u8,
    id: u8,
    title: String,
    completed: bool,
}

fn request(url: &str) {
    let result = match reqwest::blocking::get(url) {
        Ok(mut response) => {
            if response.error_for_status_ref().is_err() {
                Err(())
            } else {
                let mut string = String::new();
                match response.read_to_string(&mut string) {
                    Ok(_) => Ok(string),
                    Err(_) => Err(()),
                }
            }
        }
        Err(_) => Err(()),
    };
    match result {
        Ok(string) => {
            let todo: Todo = serde_json::from_str(&string).expect("couldn't deserialize!");
            let pretty = serde_json::to_string_pretty(&todo).expect("couldn't serialize!");
            println!("{}", pretty);
        }
        Err(_) => {
            panic!("oh no!");
        }
    }
}
