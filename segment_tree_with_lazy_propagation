/*
Segment tree with lazy propagation supporting range assignment and range maximum queries.
Problem summary – “Tetris 2D”

We have a board of width W, represented as a 1D array of column heights 
(the resulting shape is 2D, but we only track heights per column).
K blocks will fall onto it, one after another, in a fixed order.

Each block:
- has height 1 and some integer width L,
- is described in the input by (L, X),
  where X is the column of the left edge (0-based).
- when it lands, it occupies columns [X, X + L - 1].

All blocks fall straight down (no rotation).  
A block keeps falling until any part of it would:
- go below height 0, or
- intersect a previously placed block.
Then it stops just above the first obstacle it meets.

After all blocks have fallen, we must output
the height of the highest occupied cell over the whole board.

Input format:
- First line: W K
  W – board width, K – number of blocks.
- Next K lines: L X
  L – block width, X – starting column of the block (left edge).

Output:
- One integer: the maximum height after all K blocks have landed.

Sample
Input:
8 5
3 1
2 6
1 4
4 3
5 0

Output:
3
*/

#include <bits/stdc++.h>
using namespace std;

const int MAX_TREE_SIZE = 1 << 21;   // maximum size of the segment tree array
int treeMax[MAX_TREE_SIZE];         // treeMax[v] = current max height on the segment of node v
int lazyValue[MAX_TREE_SIZE];       // lazyValue[v] = pending assignment for the whole segment of node v (0 = no pending update)

// Find the smallest power of two that is >= x
int findNextPowerOfTwo(int x) {
    int nextPower = 1;
    while (nextPower < x)
        nextPower <<= 1;            // multiply by 2
    return nextPower;
}

// Push a pending lazy assignment from node 'node' down to its children
void pushDown(int node) {
    if (lazyValue[node] == 0)
        return;                     // nothing to propagate

    // Both children take the same assigned value
    treeMax[2 * node]     = lazyValue[node];
    treeMax[2 * node + 1] = lazyValue[node];
    lazyValue[2 * node]   = lazyValue[node];
    lazyValue[2 * node + 1] = lazyValue[node];

    lazyValue[node] = 0;            // clear lazy value on the parent
}

// Query the maximum height on interval [queryL, queryR]
// node      - current node index in the tree
// nodeL, nodeR - segment [nodeL, nodeR] represented by this node
int queryMax(int queryL, int queryR, int node, int nodeL, int nodeR) {
    // Query range is completely outside the node segment
    if (nodeR < queryL || nodeL > queryR)
        return 0;                   // neutral value for max (heights are non-negative)

    // Node segment is completely inside the query range
    if (queryL <= nodeL && nodeR <= queryR)
        return treeMax[node];

    // Node segment is partially inside the query range
    pushDown(node);                 // ensure children have correct values

    int mid = (nodeL + nodeR) / 2;
    int leftMax  = queryMax(queryL, queryR, 2 * node,     nodeL,     mid);
    int rightMax = queryMax(queryL, queryR, 2 * node + 1, mid + 1,   nodeR);
    return max(leftMax, rightMax);
}

// Set all positions in [queryL, queryR] to 'value'
// node, nodeL, nodeR – same meaning as in queryMax
void updateRangeSetMax(int queryL, int queryR, int node, int nodeL, int nodeR, int value) {
    // Query range is completely outside the node segment
    if (nodeR < queryL || nodeL > queryR)
        return;

    // Node segment is completely inside the update range
    if (queryL <= nodeL && nodeR <= queryR) {
        treeMax[node]   = value;
        lazyValue[node] = value;    // remember that the whole segment is now 'value'
        return;
    }

    // Node segment is partially inside the update range
    pushDown(node);                 // propagate any pending update before going down

    int mid = (nodeL + nodeR) / 2;
    updateRangeSetMax(queryL, queryR, 2 * node,     nodeL,     mid, value);
    updateRangeSetMax(queryL, queryR, 2 * node + 1, mid + 1,   nodeR, value);

    // Recompute this node's max from its children
    treeMax[node] = max(treeMax[2 * node], treeMax[2 * node + 1]);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int boardWidth, numBlocks;
    cin >> boardWidth >> numBlocks;

    // We build a segment tree over [0, baseSize - 1],
    // where baseSize is the smallest power of two >= boardWidth.
    int baseSize = findNextPowerOfTwo(boardWidth);

    for (int i = 0; i < numBlocks; i++) {
        int blockWidth, startColumn;
        cin >> blockWidth >> startColumn;

        // Block of width 'blockWidth' occupies [startColumn, endColumn]
        blockWidth--;                          // to compute inclusive end
        int endColumn = startColumn + blockWidth;

        // 1) Find the current maximum height on that interval.
        int currentMaxHeight = queryMax(startColumn, endColumn,
                                        1, 0, baseSize - 1);

        // 2) Place the new block: height on that interval becomes currentMaxHeight + 1.
        updateRangeSetMax(startColumn, endColumn,
                          1, 0, baseSize - 1, currentMaxHeight + 1);
    }

    // Finally, query the maximum height over the whole board.
    int finalHeight = queryMax(0, baseSize - 1, 1, 0, baseSize - 1);
    cout << finalHeight << "\n";

    return 0;
}
