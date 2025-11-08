/*
USACO "Diamond Collector" — Problem Summary
Link: https://usaco.org/index.php?page=viewproblem2&cpid=643

Problem:
You are given N diamond sizes (N <= 50,000) and a tolerance K.
You must place diamonds into two display cases. Inside each case,
the size difference between the smallest and largest diamond may not
exceed K (difference == K is allowed). Find the maximum total number
of diamonds that can be displayed across both cases.

Sample Input:
7 3
10
5
1
12
9
5
14

Sample Output:
5

Approach (O(N log N)):
1) Sort sizes in nondecreasing order.
2) For each starting index i, compute the length of the longest
   contiguous window [i..r-1] with a[r-1] - a[i] <= K using a single
   right pointer r that only moves forward (two pointers / sliding window).
   Store this in bestFrom[i].
3) Build a suffix maximum array sufMax[i] = max(bestFrom[i..N]) so that
   for any cut position j, sufMax[j] gives the best window starting at j or later.
4) For every i (first case = window starting at i with length bestFrom[i]),
   the second case must start strictly after this window ends, i.e. at index r,
   so we add sufMax[r]. Take the maximum over all i.

Note: Arrays are 1-indexed for clarity.
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50'000 + 5;

int a[MAXN];        // sorted diamond sizes, 1-indexed
int bestFrom[MAXN]; // bestFrom[i] = length of the longest valid window starting at i
int sufMax[MAXN];   // sufMax[i]   = max(bestFrom[i], bestFrom[i+1], ..., bestFrom[N])

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream in("diamond.in");
    ofstream out("diamond.out");

    int N, K;
    in >> N >> K;
    for (int i = 1; i <= N; ++i) in >> a[i];
    sort(a + 1, a + N + 1);

    // 1) Compute best window length starting at each index i via a single expanding pointer r
    int r = 1;
    for (int i = 1; i <= N; ++i) {
        while (r <= N && a[r] - a[i] <= K) ++r;
        // Window is [i .. r-1], so its length is (r - i)
        bestFrom[i] = r - i;
    }

    // 2) Build suffix maximums so we can query "best window starting at or after j" in O(1)
    sufMax[N + 1] = 0;
    for (int i = N; i >= 1; --i) {
        sufMax[i] = max(sufMax[i + 1], bestFrom[i]);
    }

    // 3) Combine two non-overlapping windows:
    //    First window starts at i and ends at r-1 (length bestFrom[i]).
    //    Second window must start at position r or later => sufMax[r].
    int answer = 0;
    r = 1;
    for (int i = 1; i <= N; ++i) {
        while (r <= N && a[r] - a[i] <= K) ++r;
        answer = max(answer, bestFrom[i] + sufMax[r]);
    }

    out << answer << '\n';
    return 0;
}
