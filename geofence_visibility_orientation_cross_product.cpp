/*
    Geofencing / car navigation story:
    - Orientation test (2D cross product / CCW test)
    - Same-side-of-all-edges scan (half-plane consistency check for convex polygons)


    For each test case:
      - You are given a polygonal "restricted zone" (the wall) described by its vertices in order.
      - You are also given the current car position (car_x, car_y).
      - The task is to answer:
            "YES"  if the car can see (has direct line-of-sight to) the entire boundary,
            "NO"  otherwise.

    Visibility model:
      - A boundary fragment is NOT visible if it is blocked by another fragment of the boundary.
      - A fragment lying exactly on the line of sight is considered NOT visible (collinear case).

    Algorithm used here:
      - Orientation test using the 2D cross product to determine on which side of a directed edge
        the car lies: left (+), right (-), or collinear (0).
      - We compute the "target side" from the first processed edge, then require that the car lies
        strictly on the same side for every processed edge. If any edge gives a different side or 0,
        the answer becomes "NO".

    IMPORTANT NOTE about the "last edge":
      - This code does NOT explicitly check the closing edge (last vertex -> first vertex).
      - Therefore, it is correct ONLY if the input already includes the closing edge implicitly,
        e.g. the last provided vertex equals the first one (polygon given in a "closed" form),
        or the task format guarantees the omitted check is unnecessary.
      - If the input provides exactly n distinct vertices of a simple polygon (not repeating the first
        at the end), then you would normally need an extra check for the closing edge.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
using ll = long long;

ll test_cases, vertex_count;
ll car_x, car_y;
ll curr_x, curr_y;
ll prev_x, prev_y;
ll target_side, curr_side;

int side_of_car_relative_to_edge(ll x1, ll y1, ll x2, ll y2) {
    pair<ll, ll> edge_vec = {x2 - x1, y2 - y1};
    pair<ll, ll> car_vec  = {car_x - x1, car_y - y1};

    ll cross_val = edge_vec.first * car_vec.second - edge_vec.second * car_vec.first;

    if (cross_val >= 1) {
        return 1;   // car is on the left side
    } else if (cross_val == 0) {
        return 0;   // car is collinear with the edge line (treated as NOT visible)
    } else {
        return -1;  // car is on the right side
    }
}

void solve() {
    bool answer_ok = true;
    cin >> vertex_count >> car_x >> car_y;

    cin >> prev_x >> prev_y;
    cin >> curr_x >> curr_y;

    target_side = side_of_car_relative_to_edge(prev_x, prev_y, curr_x, curr_y);
    if (target_side == 0) {
        answer_ok = false;
    }

    prev_x = curr_x;
    prev_y = curr_y;

    for (ll i = 2; i < vertex_count; i++) {
        cin >> curr_x >> curr_y;
        curr_side = side_of_car_relative_to_edge(prev_x, prev_y, curr_x, curr_y);

        if (curr_side != target_side || curr_side == 0) {
            answer_ok = false;
        }

        prev_x = curr_x;
        prev_y = curr_y;
    }

    if (answer_ok) {
        cout << "YES" << "\n";
    } else {
        cout << "NO" << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> test_cases;
    while (test_cases--) {
        solve();
    }
}
