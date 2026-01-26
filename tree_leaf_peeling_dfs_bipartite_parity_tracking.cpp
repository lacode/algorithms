/*
  Scenario: Network routing with unreliable next-hop choice (tree network)

  Algorithms used:

  - DFS Bipartite Coloring (tree parity)
  - Leaf Peeling / Pruning via Degrees (stack/queue of leaves)
  - Constructive sequence with parity tracking


  We have a network shaped like a tree with routers 1..n.
  A packet starts at router 1, and we want to guarantee it reaches router n.

  We can issue control-plane "instructions" to the network:
    1        : forward the packet by exactly one hop along any active link.
               If multiple next-hops exist, the network may choose any of them (unreliable tie-breaking).
               If the current router has no active links, the packet stays.
    2 u      : disable router u (and all incident links).
               If the packet is currently at u, it is dropped (must never happen).
               If u is already disabled, nothing happens.
  Constraint: we cannot disable two routers consecutively (change-control / stabilization rule).

  Task: output a sequence of at most 3n instructions that guarantees the packet ends at router n,
        regardless of which neighbor is chosen on each forwarding step.

  --------------------------------------------------------------------

  1) DFS Bipartite Coloring (tree parity)
     - Root the tree at router 1 and color each router by depth parity (0/1).
     - On a tree, every edge connects opposite colors.
     - Therefore, every forwarding instruction "1" flips the packet's color class.

  2) Leaf Peeling / Pruning via Degrees (stack/queue of leaves)
     - Maintain current degrees of routers in the *remaining* network.
     - Repeatedly select a leaf router (degree 1) that is NOT the destination router n,
       and disable it.
     - After disabling a leaf, its neighbor's degree decreases; if that neighbor becomes a leaf
       (and is not router n), it becomes eligible next.
     - This is the classic "peel leaves" process used in tree pruning.

  3) Constructive sequence with parity tracking
     - We track the packet's current color class (parity) as `packetParity`.
     - Before disabling a leaf router x, we ensure the packet cannot be on x:
         * If x has the same parity as the packet, issue one forward (instruction "1")
           so the packet parity flips, making it impossible for the packet to be at x
           when we disable x.
     - We also respect the rule "no two consecutive disables":
         * If the last instruction was a disable, we insert two forwards "1, 1"
           between disables. Two forwards preserve packetParity (flip twice),
           so our parity reasoning remains consistent.

  Operation encoding in code:
    - store -1   => instruction "1"
    - store r>=0 => instruction "2 (r+1)" (disable router r, 0-based internally)
*/

#include <bits/stdc++.h>
using namespace std;

/* DFS to assign bipartite parity (depth parity) in the tree.
   parity[v] = 0/1, and every edge connects opposite parities. */
static void assignParityDFS(int v, int parent,
                            const vector<vector<int>>& links,
                            vector<int>& parity) {
    for (int to : links[v]) {
        if (to == parent) continue;
        parity[to] = 1 - parity[v];
        assignParityDFS(to, v, links, parity);
    }
}

static void solveTestcase() {
    int routerCount;
    cin >> routerCount;

    vector<vector<int>> links(routerCount);
    for (int i = 0; i < routerCount - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        links[a].push_back(b);
        links[b].push_back(a);
    }

    const int sourceRouter = 0;                 // router 1
    const int destinationRouter = routerCount - 1; // router n

    // 1) Bipartite parity via DFS from the source.
    vector<int> parity(routerCount, 0);
    assignParityDFS(sourceRouter, -1, links, parity);

    // 2) Degree array for leaf-peeling (pruning) process.
    vector<int> activeDegree(routerCount);
    for (int i = 0; i < routerCount; ++i) {
        activeDegree[i] = (int)links[i].size();
    }

    // Stack of currently prunable leaves (degree==1) excluding destination.
    vector<int> prunableLeaves;
    prunableLeaves.reserve(routerCount);
    for (int i = 0; i < routerCount; ++i) {
        if (activeDegree[i] == 1 && i != destinationRouter) {
            prunableLeaves.push_back(i);
        }
    }

    // Constructed instruction sequence:
    //  -1 means "forward"
    //  >=0 means "disable that router"
    vector<int> instructionPlan;
    instructionPlan.reserve(3 * routerCount);

    // Packet parity: starts at sourceRouter which we colored as 0.
    int packetParity = 0;

    while (!prunableLeaves.empty()) {
        int leafRouter = prunableLeaves.back();
        prunableLeaves.pop_back();

        // If leafRouter parity equals packetParity, one forward flips parity,
        // ensuring the packet cannot be on leafRouter when we disable it.
        if (parity[leafRouter] == packetParity) {
            packetParity ^= 1;
            instructionPlan.push_back(-1); // instruction "1"
        }

        // Rule: cannot disable twice in a row.
        // Insert two forwards between disables; parity returns to same value.
        if (!instructionPlan.empty() && instructionPlan.back() != -1) {
            instructionPlan.push_back(-1);
            instructionPlan.push_back(-1);
        }

        // Disable the chosen leaf router.
        instructionPlan.push_back(leafRouter);

        // Update degrees; newly formed leaves become prunable (except destination).
        for (int neighbor : links[leafRouter]) {
            if (--activeDegree[neighbor] == 1 && neighbor != destinationRouter) {
                prunableLeaves.push_back(neighbor);
            }
        }
    }

    // Output plan in required format.
    cout << instructionPlan.size() << '\n';
    for (int op : instructionPlan) {
        if (op == -1) {
            cout << 1 << '\n';
        } else {
            cout << 2 << ' ' << (op + 1) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;
    while (tests--) solveTestcase();
    return 0;
}
