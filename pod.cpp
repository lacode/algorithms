#include "bits/stdc++.h"

using namespace std;

int main() {
  string n_str;
  int k;

  cin >> n_str >> k;

  array<int, 10> counts {0};
  for (auto c: n_str) counts[c - '0'] ++;
  array<int, 11> pr;
  pr[0] = 1;
  for (int i = 0; i < 10; i++) {
    pr[i + 1] = pr[i] * (1 + counts[i]);
  }
  
  vector<vector<long long>> DP(pr[10], vector<long long>(k));

  DP[pr[10] - 1][0] = 1;

  for (int i = pr[10] - 1; i > 0; i --) {
    for (int d = 0; d <= 9; d++) {
      if (i % pr[d + 1] >= pr[d]) {
        for (int mod = 0; mod < k; mod++) {
          int new_mod = (10 * mod + d) % k;
          DP[i - pr[d]][new_mod] += DP[i][mod];
        }
      }
    }
  }

  cout << DP[0][0] << "\n";
}