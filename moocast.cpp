/*
USACO "Moocast" — Problem Summary (concise)
https://usaco.org/index.php?page=viewproblem2&cpid=668

We have N cows (1 ≤ N ≤ 200). Each cow i has coordinates (x_i, y_i) and a walkie-talkie
with power p_i. A cow i can directly transmit to cow j if the Euclidean distance between
them is ≤ p_i. Note this relation is directional: i→j may exist even if j→i does not.

Cows can relay messages through multiple hops. For each possible starting cow, consider
all cows reachable via directed transmissions (including the starter). Among all starters,
output the maximum reachable count.

Example
Input:
4
1 3 5
5 4 3
7 2 1
6 1 1

Output:
3
(From cow 1, three cows total are reachable including itself.)
One integer: the largest number of cows that can be reached from a single starting cow
  using zero or more directed hops (count the origin).

Typical solution outline
1) Build a directed graph: add edge i→j if (x_i−x_j)^2 + (y_i−y_j)^2 ≤ p_i^2.
2) For each node, run DFS/BFS to count how many nodes are reachable.
3) Answer is the maximum count over all starts.

Complexity
- Graph construction: O(N^2)
- Reachability (run N searches): O(N * (N + M)) ≤ ~O(N^2) with N ≤ 200

*/


#include <bits/stdc++.h>
using namespace std;

const int MAX_COWS = 210;

int cows_x[MAX_COWS];
int cows_y[MAX_COWS];
int cows_power[MAX_COWS];
vector <int> graph[MAX_COWS];
bool visited[MAX_COWS];
int act_range;

void DFS_alg (int v) {
 int i;
 visited[v] = true;
 ++act_range;
 for(i=0; i<graph[v].size(); i++){
    if( visited[ graph[v][i] ] == false ){
       DFS_alg( graph[v][i] );
    }
 }
}


int main() {
 ios_base::sync_with_stdio(0);
 cin.tie(0);
 cout.tie(0);

 freopen("moocast.in", "r", stdin);
 freopen("moocast.out", "w", stdout);


 int number_of_cows;
 int cows_dist, cows_dist_x, cows_dist_y;
 int max_range;
 int i, j;

 cin >> number_of_cows;
 for (i=0; i<number_of_cows; ++i) {
    cin >> cows_x[i];
    cin >> cows_y[i];
    cin >> cows_power[i];
    cows_power[i] = cows_power[i]*cows_power[i];
 }

 for (i=0; i<number_of_cows; ++i) {
    for (j=i; j<number_of_cows; ++j) {
       cows_dist_x = (cows_x[i]-cows_x[j]);
       cows_dist_y = (cows_y[i]-cows_y[j]);
       cows_dist = cows_dist_x*cows_dist_x + cows_dist_y*cows_dist_y;
	   if ( cows_dist <= cows_power[i] )
          graph[i].push_back(j);
	   if ( cows_dist <= cows_power[j] )
          graph[j].push_back(i);
    }
 }

 max_range = 0;
 for (i=0; i<number_of_cows; ++i) {
     for (j=0; j<number_of_cows; ++j) {
        visited[j] = 0;
	 }
	 act_range = 0;
	 DFS_alg(i);
	 max_range = max(act_range,max_range);
 }
 
 cout << max_range << "\n";
 return 0;
}
