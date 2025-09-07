/* Computing the diameter of a tree:

1. Choose any vertex and perform a DFS/BFS to find the vertex u that is the farthest from the starting point.
2. Perform another DFS/BFS starting from u to find the vertex v that is the farthest from u.
3. The diameter of the tree is the distance between u and v.

Time complexity: O(n)

           1
         / | \
        2  3  4
       /      \
      5        6
     / \      / \
    7   8    9  10

The longest path is:
7 → 5 → 2 → 1 → 4 → 6 → 10

It passes through 6 edges.

Diameter = 6

You could also go from 8 to 9, and the path would be the same length:
8 → 5 → 2 → 1 → 4 → 6 → 9 — also 6 edges.*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

constexpr int MAX_N = 1e5 + 1;

vector<int> graph[MAX_N];
bool visited[MAX_N];
int farthest_node, max_depth;

void dfs(int v, int depth = 0) {
    visited[v] = true;

    if (depth > max_depth) {
        farthest_node = v;
        max_depth = depth;
    }

    for (int s : graph[v]) {
        if (!visited[s]) {
            dfs(s, depth + 1);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // First DFS to find the farthest node from node 1
    max_depth = 0;
    dfs(1);

    // Reset visited array
    fill(visited + 1, visited + n + 1, false);

    // Second DFS from the farthest node to get the diameter
    max_depth = 0;
    dfs(farthest_node);

    cout << max_depth + 1 << "\n"; // +1 to count the number of nodes in the longest path

    return 0;
}
