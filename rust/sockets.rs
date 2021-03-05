//////////////////////////////////
// Demonstrates sockets in Rust //
//////////////////////////////////

use std::{
    io::{self, Read, Write},
    net::{TcpListener, TcpStream},
};

use io::Result;

const IP: &str = "127.0.0.1:4456";

fn send_id(socket: &mut TcpStream, id: u32) -> Result<()> {
    socket.write_all(&id.to_ne_bytes())
}

fn read_id(socket: &mut TcpStream) -> Result<u32> {
    let mut bytes = [0u8; 4];
    socket.read_exact(&mut bytes)?;
    Ok(u32::from_ne_bytes(bytes))
}

fn main() {
    match std::env::args().nth(1).as_deref() {
        Some("client") => {
            let id = std::process::id();
            println!("Running as a client with id: [{}]", id);

            let mut socket = TcpStream::connect(IP).expect("Couldn't connect to the server");
            println!("Connected to server id [{}]", read_id(&mut socket).unwrap());

            send_id(&mut socket, id).unwrap();

            let mut msg = String::new();
            socket.read_to_string(&mut msg).unwrap();
            println!("Message from server: {}", msg);
        }
        Some("server") => {
            let id = std::process::id();
            println!("Running as a server with id: [{}]", id);

            let listener = TcpListener::bind(IP).expect("Couldn't bind to addr/port");

            for connection in listener.incoming() {
                match connection {
                    Ok(mut socket) => {
                        send_id(&mut socket, id).unwrap();

                        println!(
                            "Connected to client id: [{}]",
                            read_id(&mut socket).unwrap()
                        );
                        socket.write_all("What's up, yo?".as_bytes()).unwrap();
                    }
                    Err(_) => {
                        println!("Couldn't accept connection from client");
                    }
                }
            }
        }
        _ => {
            panic!("Bad command line; usage: `sockets [client | server]`");
        }
    }
}
