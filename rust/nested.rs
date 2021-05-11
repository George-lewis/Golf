
///! A proc macro that allows for easily writing statements of the form:
///!
///! ```
///! if A {
///!     w();
///!     if B {
///!         e();
///!         true
///!     } else {
///!         f();
///!         false
///!     }
///! } else {
///!     q();
///!     false
///! }
///!
///! This can be written like:
///! nested! {
///!     A => w; q
///!     B => e; f
///! }

use std::ops::Deref;

use proc_macro::TokenStream;
use quote::ToTokens;
use syn::{Expr, Token, parse::{Parse, ParseStream}};
use quote::quote;

#[derive(Clone)]
struct MyExpr {
    cond: Expr,
    one: Expr,
    two: Expr
}

impl Parse for MyExpr {
    fn parse(input: ParseStream) -> syn::Result<Self> {
        let cond = input.parse().expect("cond?");
        input.parse::<Token![=>]>().expect("=>?");
        let one = input.parse().expect("one?");
        input.parse::<Token![;]>()?;
        let two = input.parse().expect("two?");
        let self_ = MyExpr {
            cond,
            one,
            two,
        };
        Ok(self_)
    }
}

struct MyExprs(Vec<MyExpr>);

impl Deref for MyExprs {
    type Target = [MyExpr];

    fn deref(&self) -> &Self::Target {
        self.0.deref()
    }
}

impl Parse for MyExprs {
    fn parse(input: ParseStream) -> syn::Result<Self> {
        let mut v = vec![];
        while !input.is_empty() {
            let new = MyExpr::parse(input)?;
            v.push(new);
        }
        Ok(MyExprs(v))
    }
}

fn _jiggle(exprs: &[MyExpr], idx: usize) -> impl ToTokens + Into<TokenStream> {
    let cur = exprs[idx].clone();
    let cond = cur.cond;
    let one = cur.one;
    let two = cur.two;

    if idx != exprs.len() - 1 {
        let nest = _jiggle(exprs, idx + 1);
        quote! {
            if #cond {
                #one();
                #nest
            } else {
                #two();
                false
            }
        }
    } else {
        quote! {
            if #cond {
                #one();
                true
            } else {
                #two();
                false
            }
        }
    }
}

fn jiggle(exprs: &MyExprs) -> TokenStream {
    _jiggle(exprs, 0).into()
}

#[proc_macro]
pub fn nested(ts: TokenStream) -> TokenStream {
    let exprs: MyExprs = syn::parse(ts).unwrap();
    jiggle(&exprs)
}