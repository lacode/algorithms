/*
Problem summary (Heads & Tails):
We are given a sequence of n coin flips (characters) and an integer k.

Interpretation:
- 'O' means HEAD and contributes +1.
- 'R' means TAIL and contributes -k.

Your program should output one integer — the length of the longest contiguous sequence in which there are exactly k times as many heads as tails.
We must find the maximum length of a contiguous segment (subarray) whose total sum is exactly 0.

Brute force algorithm (O(n^2)):
1) Read input and build array a[1..n] using the mapping above.
2) For every possible left endpoint l (1..n):
     - set running_sum = 0
     - extend the right endpoint r from l..n:
         running_sum += a[r] 
         if running_sum == 0:
             update answer = max(answer, r - l + 1)
This checks all O(n^2) subarrays, but uses a running sum so each subarray sum is updated in O(1),
avoiding an even slower O(n^3) “sum from scratch” approach.

Complexity:
- Time:  O(n^2)  (all pairs (l, r))
- Memory: O(n)   (the converted array)
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        char c;
        cin >> c;
        a[i] = (c == 'O') ? 1 : -k;
    }

    int ans = 0;

    // Brute force O(n^2): choose left endpoint l, extend right endpoint r, keep a running sum.
    for (int l = 1; l <= n; l++) {
        long long running_sum = 0;
        for (int r = l; r <= n; r++) {
            running_sum += a[r];
            if (running_sum == 0) {
                ans = max(ans, r - l + 1);
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
