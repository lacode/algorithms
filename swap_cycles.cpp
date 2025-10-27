// swap_cycles.cpp
/*
PROBLEM (summary)
-----------------
From the USA Computing Olympiad (USACO): https://usaco.org/index.php?page=viewproblem2&cpid=1014

N cows labeled 1..N stand in a line. You are given M intervals [L_i, R_i].
One "round" consists of applying all M reversals in order. Repeat the same
M-step round exactly K times. Output the final order from left to right.

Key constraints 
---------------
N up to 10^5, M up to 10^2, K up to 10^9

Sample Input
------------
7 2 2
2 5
3 7

Sample Output
-------------
1
2
4
3
5
7
6

Permutation (top index -> bottom index after one full round):
  1 -> 1
  2 -> 5
  3 -> 7
  4 -> 6
  5 -> 2
  6 -> 3
  7 -> 4

Cycle decomposition:
  (1) (2 5) (3 7 4 6)

Highlighted 4-cycle block (in order as visited):
  [3, 7, 4, 6]

Successive rotations of that 4-cycle (each row is one step):
  row 0: 3 7 4 6
  row 1: 7 4 6 3
  row 2: 4 6 3 7
  row 3: 6 3 7 4

Example with K = 10:
  10 = 4 * 2 + 2  -> shift = 10 mod 4 = 2
  So after K rounds the 4-cycle appears as row 2: 4 6 3 7.

Why cycles solve it
-------------------
Applying all reversals once maps each position i -> P[i].
This permutation P breaks into disjoint cycles. Repeating the same round
K times just rotates each cycle by (K mod cycle_length).

Takeaways for implementation
----------------------------
- Build P by starting from identity [1..N] and applying the M reversals once.
- For each unvisited position, walk its cycle and write answers shifted by (K % cycle_len).
- Time: O(M * N + N)  (often written O(M * N)), Memory: O(N).

Complexity notes
----------------
- Building the permutation by applying the M reversals once costs
  O( sum_i (r_i - l_i + 1) ), which in the worst case is O(M * N)
  (e.g., every interval spans the whole array).

- Cycle decomposition and writing the answer costs O(N).

=> Total time: O(M * N + N)  (often written simply as O(M * N))
   Memory:     O(N).

With N ≤ 1e5 and M ≤ 100, that’s at most ~1e7 operations, which is fine.

K can be as large as 1e9; it doesn’t change the runtime thanks to
using K % cycle_length when rotating each cycle.
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100 * 1000 + 10;

int cows[MAXN];
bool visited[MAXN];
int resultPos[MAXN];
int n, m;
long long k;

void reverseRange(int leftIdx, int rightIdx) {
    int len = (rightIdx - leftIdx + 1);
    for (int i = 0; i < len / 2; ++i) {
        swap(cows[leftIdx + i], cows[rightIdx - i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    // Start from identity permutation.
    for (int i = 1; i <= n; ++i) cows[i] = i;

    // Apply the M reversals once to build the permutation P.
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        reverseRange(l, r);
    }

    // Decompose P into cycles and rotate each by k % cycle_len.
    vector<int> cycle;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            int cur = i;
            while (!visited[cur]) {
                cycle.push_back(cur);
                visited[cur] = true;
                cur = cows[cur];
            }
            int L = (int)cycle.size();
            int shift = (int)(k % L);
            for (int j = 0; j < L; ++j) {
                int pos = cycle[j];
                int afterK = cycle[(j + shift) % L];
                resultPos[pos] = afterK;
            }
            cycle.clear();
        }
    }

    for (int i = 1; i <= n; ++i) {
        cout << resultPos[i] << '\n';
    }
    return 0;
}
