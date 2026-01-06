#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
Greedy delivery on a cycle using inverse-permutation mapping and circular-distance (wrap-around) lap counting.

Algorithms:
- "Inverse permutation" / mapping reversal (cargo -> destination city)
- Greedy simulation on a cycle (always detach as soon as you reach the destination of the current last wagon)
- Counting laps via total forward distance on a circular array (compute ceil(total_steps / n))
Time: O(n), Memory: O(maxCargoValue) (here cargo values <= 1e6 per statement).

There are n cities on a cycle: 1 -> 2 -> ... -> n -> 1 -> ...
A train starts in city 1 and moves along this cycle forever.

The train has exactly n wagons in a fixed order behind the locomotive:
w[1], w[2], ..., w[n]  (wagon n is the last one).

Each wagon carries one "cargo type" (an integer). Each city i wants exactly one cargo type m[i].
The multiset of wagon cargo types equals the multiset of demanded cargo types (in fact: a permutation).

In each city the driver may detach (leave) ONLY the last wagon of the train.
Detached wagons are gone forever (cannot be reattached).
Goal: deliver every cargo to the correct city (detach that wagon in the city that wants its cargo).

We want the minimal number of full laps around the island.
A new lap is counted when the train leaves city 1 and goes to city 2.

Input:
n
w1 w2 ... wn
m1 m2 ... mn

Output:
minimal number of laps.

Example:
Input:
5
1 2 3 4 5
1 3 4 2 5
Output:
3

Explanation (intuitive):
Detach cargo 5 in lap 1, cargo 4 in lap 2, and cargos 3,2,1 in lap 3.

BEFORE inversion (given by input):
---------------------------------
We have the "city -> cargo" table, i.e. what each city wants:

index = city number (1..n)
value = cargo type demanded by that city

Example (n = 5):
city:        1  2  3  4  5
m[city]:     1  3  4  2  5

Meaning:
- city 1 wants cargo 1
- city 2 wants cargo 3
- city 3 wants cargo 4
- city 4 wants cargo 2
- city 5 wants cargo 5


AFTER inversion (built in code):
--------------------------------
We build the inverse mapping "cargo -> city", i.e. where each cargo must be delivered:

index = cargo type
value = destination city for that cargo

destinationOfCargo[cargo] = city such that m[city] == cargo

From the same example:
cargo:                     1  2  3  4  5
destinationOfCargo[cargo]: 1  4  2  3  5

Meaning:
- cargo 1 must be delivered to city 1
- cargo 2 must be delivered to city 4
- cargo 3 must be delivered to city 2
- cargo 4 must be delivered to city 3
- cargo 5 must be delivered to city 5

We "inverted the permutation": instead of asking
  "what cargo does this city want?" (city -> cargo)
we can now ask (in O(1)):
  "to which city should this cargo go?" (cargo -> city)

This is exactly what we need, because the train always sees the LAST wagon's cargo first.
*/


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    // wagons[1..n] = cargo type carried by the i-th wagon (1-indexed).
    vector<ll> wagons(n + 1);
    for (ll i = 1; i <= n; i++) cin >> wagons[i];

    // demands[1..n] = cargo type demanded by city i (not strictly needed later, but shown for clarity)
    vector<ll> demands(n + 1);

    // destinationOfCargo[x] = city index that demands cargo type x
    // In the original solution they allocate size ~1e6 because cargo values are bounded.
    // We size this array up to ~1e6 because cargo types are numbered from 1 to 1,000,000,
    // not from 1 to the number of cities.
    vector<ll> destinationOfCargo(1'000'000 + 10, 0);

    // Build the "inverse mapping": city -> cargo  becomes  cargo -> city
    for (ll city = 1; city <= n; city++) {
        cin >> demands[city];
        destinationOfCargo[demands[city]] = city;
    }

    // currentCity = where the train currently is (we start at city 1)
    ll currentCity = 1;

    // totalSteps = total number of edges travelled along the cycle (each move to next city = +1 step)
    ll totalSteps = 0;

    // Process wagons from the last one to the first one,
    // because we can detach only the last wagon.
    for (ll i = n; i >= 1; i--) {
        ll cargo = wagons[i];
        ll targetCity = destinationOfCargo[cargo]; // where this cargo must be delivered

        if (targetCity == currentCity) {
            // We are already at the destination -> detach immediately, no travel needed.
            continue;
        }

        // We always travel forward along the cycle.
        // Distance on a cycle from currentCity to targetCity (forward only):
        // - if targetCity > currentCity: targetCity - currentCity
        // - else: wrap around: (n - currentCity) + targetCity
        if (targetCity < currentCity) {
            totalSteps += (n - currentCity) + targetCity;
            currentCity = targetCity;
        } else if (targetCity > currentCity) {
            totalSteps += (targetCity - currentCity);
            currentCity = targetCity;
        }
    }

    // Each full lap corresponds to exactly n forward steps (edges).
    // We need the minimal number of laps that covers totalSteps, i.e. ceil(totalSteps / n).
    ll laps = (totalSteps + n - 1) / n;

    cout << laps << "\n";
    return 0;
}
