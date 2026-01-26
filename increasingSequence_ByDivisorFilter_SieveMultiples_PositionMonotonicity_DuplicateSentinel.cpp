/*
  Increasing-by-Divisor Filter (choose K)

  We are given an array A[1..N]. For a chosen integer K (1 <= K <= 1e6),
  we keep only elements that are divisible by K (preserving their original order).
  The remaining sequence must be STRICTLY increasing.

  Task: find any K that maximizes the number of kept elements.

  Core idea
  ---------
  - For each value v (1..1e6) we store:
      pos[v] = 0   -> v does not appear in the input
      pos[v] = i   -> v appears exactly once at position i (1-based)
      pos[v] = -1  -> v appears at least twice (duplicate marker / sentinel)
  - If a value v is duplicated, then any K dividing v would keep v at least twice,
    making strict increase impossible. We mark such v as -1.
  - For a fixed K, only multiples of K can remain: K, 2K, 3K, ...
    If we scan these values in increasing order, then the filtered sequence is
    strictly increasing iff the ORIGINAL positions of these values are strictly
    increasing (monotonic).

  Algorithms / techniques used
  ----------------------------
  - Value-to-position indexing (array pos[])
  - Duplicate detection via sentinel (-1)
  - Sieve-like iteration over multiples for each K
  - Monotonicity check on positions
  - Overall complexity ~ sum_{K=1..M} M/K = O(M log M), with M = 1e6

  Checks candidate K:
  - Iterates over all multiples v = K, 2K, 3K, ...
  - If v is present (pos[v] != 0), it would be kept by this K.
  - We verify that the original positions are strictly increasing.
    If any pos[v] is a duplicate marker (-1) OR breaks monotonicity,
    then K is invalid.
  Returns:
    -1 if invalid
     count of kept elements otherwise
*/

#include <bits/stdc++.h>
using namespace std;

static const int MAXV = 1'000'000;
static const int DUPLICATE = -1;

// pos[v]:
//  0         -> value v does not appear
//  >0        -> v appears exactly once at this 1-based position
//  DUPLICATE -> v appears at least twice
int pos[MAXV + 10];

int checkK(int K) {
    int keptCount = 0;
    int lastPos = 0;

    for (int v = K; v <= MAXV; v += K) {
        if (pos[v] == 0) continue;

        // If pos[v] == -1 (duplicate) then -1 < lastPos (lastPos starts at 0) => invalid K.
        // Also catches non-increasing order of positions.
        if (pos[v] < lastPos) return DUPLICATE;

        lastPos = pos[v];
        keptCount++;
    }
    return keptCount;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // Build pos[] with duplicate marker
    for (int i = 1; i <= N; ++i) {
        int x;
        cin >> x;
        if (pos[x] != 0) pos[x] = DUPLICATE;
        else pos[x] = i;
    }

    int bestK = 1;
    int bestKept = -1;

    for (int K = 1; K <= MAXV; ++K) {
        int res = checkK(K);
        if (res > bestKept) {
            bestKept = res;
            bestK = K;
        }
    }

    cout << bestK << "\n";
    return 0;
}
