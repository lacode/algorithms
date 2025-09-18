/*
Input:
n days of stock prices.
fee = transaction fee (paid once per transaction, when buying).
price[i] = stock price on day i.

Goal: Maximize profit. 
We can:
Buy and sell any number of times (we can only hold one share at a time).
Each buy costs an additional fee.

Example:
7 2
1 2 5 3 4 2 6
Buy on day 1 (price 1 + fee 2 = 3), sell on day 3 (price 5). Profit = 2.
Buy on day 6 (price 2 + fee 2 = 4), sell on day 7 (price 6). Profit = 2.
Total = 4
*/


#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 7;

long long dp[MAXN];     // dp[i] = maximum profit achievable up to day i
int price[MAXN];        // stock price on each day

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, fee;          // n = number of days, fee = transaction fee (entry cost)
    cin >> n >> fee;

    for (int i = 1; i <= n; ++i)
        cin >> price[i];

    dp[0] = 0;           // no profit before trading starts
    long long bestBuy = -1e9;  
    // bestBuy = best possible value of (dp[j] - price[j+1]) so far
    // represents the maximum profit if we buy stock at some day before i

    for (int i = 1; i <= n; ++i) {
        // Two choices for day i:
        // 1. Do nothing today → profit stays dp[i-1]
        // 2. Sell today → profit = current price[i] - fee + bestBuy
        dp[i] = max(dp[i-1], price[i] - fee + bestBuy);

        // Update bestBuy: what if we decide to buy today?
        // dp[i-1] - price[i] means we pay today's price and keep earlier profit
        bestBuy = max(bestBuy, dp[i-1] - price[i]);
    }

    cout << dp[n] << '\n';   // maximum possible profit after n days
    return 0;
}
