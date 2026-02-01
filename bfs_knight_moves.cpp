/*
  Problem:
  We have a grid with:
    - 's' : start 
    - 't' : target 
    - 'x' : blocked cell 
    - other chars : free cells

  Allowed moves are exactly like a chess knight:
    (±1, ±2) and (±2, ±1)  -> 8 possibilities total.

  Goal:
    Find the minimum number of knight moves from 's' to 't',
    or print "NO" if it is impossible.

  Using Breadth-First Search (BFS) algorithm:
    Each move has the same cost (1 move). The grid can be seen as an unweighted graph:
    - each free cell is a node
    - edges connect nodes that a knight can jump between
    BFS on an unweighted graph computes the shortest path length in O(V + E),
    which here is O(rows*cols), because each cell is processed at most once,
    and from each cell we try 8 moves.
*/
#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;

const int MAXN = 1000 + 7;
char grid[MAXN][MAXN];
int dist[MAXN][MAXN];
int rows, cols;

// 8 knight moves (like a chess knight)
pair<int,int> moves[8] {
    { 1,-2},
    { 1, 2},
    { 2, 1},
    { 2,-1},
    {-1, 2},
    {-1,-2},
    {-2, 1},
    {-2,-1},
};

void BFS(pair<int,int> start) {
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            dist[i][j] = -1; // -1 means "unvisited / unreachable"
        }
    }

    queue<pair<int,int>> Q;
    Q.push(start);
    dist[start.fi][start.se] = 0; // start distance = 0 moves

    while (!Q.empty()) {
        pair<int,int> v = Q.front();
        Q.pop();

        // try all 8 knight moves
        for (int k = 0; k < 8; k++) {
            pair<int,int> u;
            u.fi = v.fi + moves[k].fi;
            u.se = v.se + moves[k].se;

            // out of bounds -> skip
            if (((u.fi < 1) || (u.fi > rows)) || ((u.se < 1) || (u.se > cols)))
                continue;

            // blocked cell -> skip
            if (grid[u.fi][u.se] == 'x')
                continue;

            // first time visiting u -> set distance and push
            if (dist[u.fi][u.se] == -1) {
                dist[u.fi][u.se] = dist[v.fi][v.se] + 1;
                Q.push(u);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    cin >> rows >> cols;

    pair<int,int> knightStart, target;

    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            cin >> grid[i][j];

            // 's' marks the knight start position
            if (grid[i][j] == 's') {
                knightStart = {i, j};
            }

            // 't' marks the target position
            if (grid[i][j] == 't') {
                target = {i, j};
            }
        }
    }

    BFS(knightStart);

    int d = dist[target.fi][target.se];
    if (d == -1)
        cout << "NO\n";
    else
        cout << d << "\n";

    return 0;
}


