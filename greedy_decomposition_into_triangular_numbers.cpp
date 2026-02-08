// Construct a parentheses string whose number of non-empty contiguous substrings
// that are correct bracket sequences equals exactly N.
//
// Strategy:
// - A block B(k) = ")" + "()" repeated k times contributes exactly T_k = k*(k+1)/2
//   correct contiguous substrings (all lie fully inside the tail "()"..."()").
// - Between blocks we get ")", which prevents any correct substring from crossing
//   block boundaries. Therefore totals add up.
// - Greedily represent N as a sum of triangular numbers.

#include <bits/stdc++.h>
using namespace std;

static inline long long tri(long long k) {
    return k * (k + 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    cin >> n;

    // Start k near sqrt(2n), with a small safety buffer (+3),
    // then we will decrease it until tri(k) <= current n.
    long long k = (long long) sqrtl(2.0L * (long double)n) + 3;

    string ans;
    ans.reserve(100000);

    while (n > 0) {
        while (k > 0 && tri(k) > n) --k;

        // Use the largest triangular number <= n
        n -= tri(k);

        // Append block: ")" + k times "()"
        ans.push_back(')');
        for (long long i = 0; i < k; i++) {
            ans.push_back('(');
            ans.push_back(')');
        }
    }

    cout << ans << "\n";
    return 0;
}
