/*
Problem summary (Heads & Tails):
We are given a sequence of n coin flips (characters) and an integer k.

Interpretation:
- 'O' means HEAD and contributes +1.
- 'R' means TAIL and contributes -k.

Your program should output one integer — the length of the longest contiguous sequence in which there are exactly k times as many heads as tails.
We must find the maximum length of a contiguous segment (subarray) whose total sum is exactly 0.

  - Let prefix[i] = sum(arr[1..i]).
    A subarray (l..r) has sum 0 if:
      prefix[r] == prefix[l-1]
  - So for each prefix sum value, we only need to remember the FIRST index
    where it appeared. When we see the same sum again at i, the subarray
    from (first_index + 1) to i sums to 0, and its length is i - first_index.

  Complexity:
  - O(n log n) with std::map (stores key-value pairs in a balanced binary search tree).
    (O(n) if we used unordered_map)
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 7;

int arr[MAXN];                 // arr[i] = +1 for 'O', otherwise -k
map<long long, int> prev_sums; // prefix_sum -> earliest index where it occurred

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // 1-based indexing for convenience.
    for (int i = 1; i <= n; ++i) {
        char c;
        cin >> c;
        if (c == 'O') arr[i] = 1;
        else          arr[i] = -k;
    }

    // Prefix sum 0 is considered to occur at index 0 (before any elements).
    // This allows subarrays starting at 1 to be counted correctly.
    prev_sums[0] = 0;

    int ans = 0;
    long long curr_sum = 0; // current prefix sum up to position i

    for (int i = 1; i <= n; ++i) {
        curr_sum += arr[i]; // prefix[i]

        // If we have seen this prefix sum before at index prev_ind,
        // then the subarray (prev_ind+1 .. i) has sum 0.
        auto it = prev_sums.find(curr_sum);
        if (it != prev_sums.end()) {
            int prev_ind = it->second;
            ans = max(ans, i - prev_ind);
        } else {
            // Store only the earliest occurrence to maximize possible length.
            prev_sums[curr_sum] = i;
        }
    }

    cout << ans << "\n";
    return 0;
}
