/////////////////////////////////////////////
// An example 3D array abstraction in Rust //
/////////////////////////////////////////////

#![feature(const_fn)]
#![feature(const_generics)]
#![feature(const_evaluatable_checked)]

use std::{
    fmt::{Debug, Display},
    ops::{Index, IndexMut},
};

#[derive(Debug)]
struct Array3D<
    T: Sized + Copy + Debug + Default + PartialEq,
    const W: usize,
    const H: usize,
    const D: usize,
> where
    [T; W * H * D]: Sized,
{
    internal: [T; W * H * D],
}

impl<
        T: Sized + Copy + Debug + Default + PartialEq,
        const W: usize,
        const H: usize,
        const D: usize,
    > Array3D<T, W, H, D>
where
    [T; W * H * D]: Sized,
{
    fn new_init(init: T) -> Self {
        Array3D {
            internal: [init; W * H * D],
        }
    }
    fn new() -> Self {
        Array3D {
            internal: [T::default(); W * H * D],
        }
    }
    const fn idx(index: (usize, usize, usize)) -> usize {
        index.0 + index.1 * W + index.2 * W * D
    }
}

impl<
        T: Sized + Copy + Debug + Default + PartialEq,
        const W: usize,
        const H: usize,
        const D: usize,
    > Index<(usize, usize, usize)> for Array3D<T, W, H, D>
where
    [T; W * H * D]: Sized,
{
    type Output = T;

    fn index(&self, index: (usize, usize, usize)) -> &Self::Output {
        &self.internal[Self::idx(index)]
    }
}

impl<
        T: Sized + Copy + Debug + Default + PartialEq,
        const W: usize,
        const H: usize,
        const D: usize,
    > IndexMut<(usize, usize, usize)> for Array3D<T, W, H, D>
where
    [T; W * H * D]: Sized,
{
    fn index_mut(&mut self, index: (usize, usize, usize)) -> &mut Self::Output {
        &mut self.internal[Self::idx(index)]
    }
}

impl<
        T: Sized + Copy + Debug + Default + PartialEq,
        const W: usize,
        const H: usize,
        const D: usize,
    > Display for Array3D<T, W, H, D>
where
    [T; W * H * D]: Sized,
{
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{:?}", self.internal)
    }
}

impl<
        T: Sized + Copy + Debug + Default + PartialEq,
        const W: usize,
        const H: usize,
        const D: usize,
    > PartialEq for Array3D<T, W, H, D>
where
    [T; W * H * D]: Sized,
{
    fn eq(&self, other: &Self) -> bool {
        self.internal == other.internal
    }
}

fn main() {
    let mut arr = Array3D::<u8, 10, 10, 10>::new();

    arr[(5, 5, 5)] = 9;

    println!("{}", arr);
}

#[cfg(test)]
mod tests {

    use super::Array3D;

    #[derive(Debug, Clone, Copy, Default)]
    struct A {
        x: u8,
        y: u8,
    }

    impl PartialEq for A {
        fn eq(&self, other: &Self) -> bool {
            self.x == other.x && self.y == other.y
        }
    }

    #[test]
    fn test_new() {
        assert_eq!(Array3D::<u8, 0, 0, 0>::new().internal, [0; 0]);
        assert_eq!(Array3D::<u16, 1, 1, 0>::new().internal, [0; 0]);
        assert_eq!(Array3D::<i32, 0, 1, 1>::new().internal, [0; 0]);
        assert_eq!(Array3D::<u8, 1, 1, 1>::new().internal, [0; 1]);
        assert_eq!(Array3D::<u8, 2, 3, 4>::new().internal, [0; 24]);
        assert_eq!(Array3D::<u8, 3, 3, 3>::new().internal, [0; 27]);

        assert_eq!(
            Array3D::<A, 1, 1, 2>::new().internal,
            [A { x: 0, y: 0 }, A { x: 0, y: 0 }]
        );
    }

    #[test]
    fn test_new_init() {
        assert_eq!(Array3D::<u8, 0, 0, 0>::new_init(1).internal, [1; 0]);
        assert_eq!(Array3D::<u16, 1, 1, 0>::new_init(2).internal, [2; 0]);
        assert_eq!(Array3D::<i32, 4, 5, 1>::new_init(-77).internal, [-77; 20]);
        assert_eq!(
            Array3D::<A, 1, 1, 2>::new_init(A { x: 1, y: 1 }).internal,
            [A { x: 1, y: 1 }, A { x: 1, y: 1 }]
        );
    }

    #[test]
    fn test() {
        let mut array = Array3D::<u8, 2, 2, 2>::new();
        assert_eq!(array.internal, [0; 2 * 2 * 2]);
        array[(0, 0, 0)] = 1;
        array[(0, 1, 0)] = 3;
        array[(1, 1, 1)] = 9;
        assert_eq!(array.internal, [1, 0, 3, 0, 0, 0, 0, 9])
    }
}
