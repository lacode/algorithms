/*
Problem description:

In a small city there are `num_intersections` intersections, numbered from 1 to `num_intersections`.
Between some pairs of intersections there are two-way roads, and all roads together form a tree
(there is exactly one simple path between any two intersections). Intersection 1 is the main
dispatch center.

Each taxi company chooses one intersection as its "base". A taxi company based at intersection X
is allowed to serve passengers only inside its own "district" – that is, at intersection X and at
all intersections located in X's subtree when the road network is viewed as a tree rooted in 1.

We receive `num_queries` queries. Each query gives:
  - `taxi_vertex` – the base intersection of a taxi company,
  - `vertex_a` and `vertex_b` – locations of two passengers.

For each query we must answer:
  - "YES" if *both* passengers A and B lie inside the district of `taxi_vertex`
    (i.e., if `taxi_vertex` is an ancestor of both A and B in the rooted tree),
  - "NO" otherwise.

Algorithm:

1. Read the tree (the road network) as an undirected graph.
2. Root the tree at intersection 1.
3. Run a DFS starting from 1 and assign each vertex:
     - `preorder[v]`  – the time when we first enter vertex v,
     - `postorder[v]` – the time when we leave vertex v.
4. In a rooted tree, vertex x is an ancestor of vertex y if and only if:
       preorder[x] <= preorder[y]  AND  postorder[x] >= postorder[y]
5. For each query (taxi_vertex, vertex_a, vertex_b), we check if taxi_vertex is an ancestor
   of both vertex_a and vertex_b using the condition above. If yes, print "YES", otherwise "NO".

This gives O(num_intersections) preprocessing with DFS and O(1) time per query.

Example:

Input:
5
1 2
1 3
2 4
2 5
4
2 4 5
1 3 4
3 2 3
2 3 4

Output:
YES
YES
NO
NO

Explanation:
- Query 1: taxi at 2, passengers at 4 and 5 – both are in the subtree of 2 -> YES.
- Query 2: taxi at 1, passengers at 3 and 4 – all intersections are in the subtree of 1 -> YES.
- Query 3: taxi at 3, passengers at 2 and 3 – 2 is not in the subtree of 3 -> NO.
- Query 4: taxi at 2, passengers at 3 and 4 – 3 is not in the subtree of 2 -> NO.
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX_VERTICES = 5e5 + 7;
vector<int> edges[MAX_VERTICES];
bool is_visited[MAX_VERTICES];
int preorder [MAX_VERTICES];
int postorder [MAX_VERTICES];

int act_preorder_postorder;

void DFS (int v) {
    int i;
    is_visited[v] = true;
    preorder[v] = act_preorder_postorder;
    ++act_preorder_postorder;
    for (i = 0; i < (int)edges[v].size(); i++) {
        if (is_visited[edges[v][i]] == false) {
            DFS(edges[v][i]);
        }
    }
    postorder[v] = act_preorder_postorder;
    ++act_preorder_postorder;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int num_intersections, num_queries;
    int vertex_a, vertex_b, taxi_vertex;
    int i;

    cin >> num_intersections;
    for (i = 1; i < num_intersections; ++i) {
        cin >> vertex_a >> vertex_b;
        edges[vertex_a].push_back(vertex_b);
        edges[vertex_b].push_back(vertex_a);
    }

    act_preorder_postorder = 1;
    DFS(1);

    cin >> num_queries;
    for (i = 1; i <= num_queries; ++i) {
        cin >> taxi_vertex >> vertex_a >> vertex_b;
        if ((preorder[taxi_vertex] <= preorder[vertex_a]) && (postorder[taxi_vertex] >= postorder[vertex_a]) &&
            (preorder[taxi_vertex] <= preorder[vertex_b]) && (postorder[taxi_vertex] >= postorder[vertex_b]))
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}
