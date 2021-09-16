use std::collections::HashSet;

#[derive(Clone, Copy, Debug)]
struct Edge {
    a: i8,
    b: i8,
    weight: i8,
}

/// Precondition: `graph` must be sorted by weight in ascending order
fn kruskal(graph: &[Edge]) -> Vec<Edge> {
    let mut tree: Vec<Edge> = Vec::new();
    let mut connected: HashSet<i8> = HashSet::new();

    for edge in graph {
        let is_connected = connected.contains(&edge.a) && connected.contains(&edge.b);

        if is_connected {
            continue;
        }

        connected.insert(edge.a);
        connected.insert(edge.b);

        tree.push(*edge);
    }

    tree
}

fn main() {
    let graph: Vec<Edge> = [(2, 3, 4), (0, 3, 5), (0, 2, 6), (0, 1, 10), (1, 3, 15)]
        .iter()
        .map(|&(a, b, weight)| Edge { a, b, weight })
        .collect();

    let tree = kruskal(&graph);

    println!("{:?}", &tree);
    println!("Cost: {}", tree.iter().map(|e| e.weight).sum::<i8>())
}
