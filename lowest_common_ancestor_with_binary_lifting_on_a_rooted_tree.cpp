/*
Lowest Common Ancestor (LCA) with Binary Lifting (Jump Pointers) on a rooted tree

https://cses.fi/problemset/result/15841073/

You are given a rooted tree with nodes 1..n, where node 1 is the root (the CEO).
For every node i = 2..n, you are given its direct parent p[i] (its immediate boss).

Then you must answer q queries. Each query gives two nodes a and b, and you must output
their LCA (Lowest Common Ancestor) in the rooted tree:
- The LCA of (a, b) is the deepest node that is an ancestor of both a and b.

Input
- First line: n q
- Second line: n-1 integers p[2], p[3], ..., p[n]  (parent of each node 2..n)
- Next q lines: a b

Output
- For each query, print one integer: LCA(a, b)

Constraints
- 1 <= n, q <= 2e5
So we need about O((n+q) log n).

Example
Input:
5 3
1 1 3 3
4 5
2 4
4 3

Tree:
1
├─2
└─3
  ├─4
  └─5

Output:
3
1
3
*/

#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 200000 + 5;
// 2^18 = 262144 > 200000, so 18 levels are enough (0..17).
static const int LOG = 18;

int n, q;

// up[v][k] = the 2^k-th ancestor of node v (binary lifting table).
int up[MAXN][LOG];

// children adjacency list (rooted tree: parent -> children)
vector<int> children[MAXN];

// depth[v] = depth of v from the root (root has depth 0)
int depthArr[MAXN];

void dfs_build(int node, int parent) {
    up[node][0] = parent;

    if (node == parent) depthArr[node] = 0;          // root case (1 -> 1)
    else depthArr[node] = depthArr[parent] + 1;

    for (int child : children[node]) {
        dfs_build(child, node);
    }
}

void build_binary_lifting() {
    // Fill up[v][k] using:
    // up[v][k] = up[ up[v][k-1] ][k-1]
    // meaning: jump 2^(k-1) twice to get 2^k.
    for (int k = 1; k < LOG; k++) {
        for (int v = 1; v <= n; v++) {
            up[v][k] = up[ up[v][k - 1] ][k - 1];
        }
    }
}

// Move node upward by exactly dist steps (dist can be any number, not necessarily power of two).
int lift(int node, int dist) {
    for (int k = 0; k < LOG; k++) {
        if (dist & (1 << k)) {
            node = up[node][k];
        }
    }
    return node;
}

int lca(int a, int b) {
    // Ensure a is the deeper node
    if (depthArr[a] < depthArr[b]) swap(a, b);

    // 1) Lift a up to the same depth as b
    a = lift(a, depthArr[a] - depthArr[b]);

    if (a == b) return a;

    // 2) Lift both up, from biggest jump to smallest, staying below the LCA
    for (int k = LOG - 1; k >= 0; k--) {
        if (up[a][k] != up[b][k]) {
            a = up[a][k];
            b = up[b][k];
        }
    }

    // Now a and b are children of the LCA
    return up[a][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    // Read parents for nodes 2..n and build rooted adjacency (parent -> child).
    // We also set root's parent to itself as a safe "sentinel":
    // - It prevents using 0 as "no ancestor"
    // - It prevents out-of-bounds when computing up[ up[v][k-1] ][k-1]
    up[1][0] = 1;

    for (int v = 2; v <= n; v++) {
        int parent;
        cin >> parent;
        children[parent].push_back(v);
    }

    // DFS to compute depth and immediate parent up[v][0]
    dfs_build(1, 1);

    // Precompute all 2^k ancestors
    build_binary_lifting();

    // Answer queries
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }

    return 0;
}
