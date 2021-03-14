////////////////////////////////////
// Reads random data from urandom //
////////////////////////////////////

use core::slice;
use std::{fs::File, io::Read, mem::{MaybeUninit, size_of}};

use num_traits::Unsigned;

fn rand_bytes(buf: &mut [u8]) {
    let mut urandom = File::open("/dev/urandom").unwrap();
    urandom.read_exact(buf).unwrap();
}

unsafe fn rand<T>() -> T {
    let mut t = MaybeUninit::<T>::uninit();
    let slice = slice::from_raw_parts_mut(t.as_mut_ptr() as *mut u8, size_of::<T>());
    rand_bytes(slice);
    t.assume_init()
}

fn urand<T: Unsigned>() -> T {
    unsafe { rand() }
}

fn main() {
    let random: u32 = urand();
    println!("{}", random);
}
