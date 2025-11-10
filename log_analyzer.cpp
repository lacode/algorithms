/*
Log Analyzer — Problem Summary:
You process n commands over IPv4 addresses (four octets 0..255).
Commands:
  - k o0 o1 o2 o3 : record a connection to IP o0.o1.o2.o3
  - z o0 o1 o2 o3 : print the IP followed by how many times it appeared so far
                    (print 0 if it never appeared)
  - w             : print all seen IPs with their counts,
                    sorted by host octet (o3 ascending), then by o0, o1, o2. :contentReference[oaicite:0]{index=0}

Sample Input:
9
k 10 20 30 40
k 30 40 10 20
k 15 60 70 20
w
k 10 20 30 40
k 50 10 10 25
z 10 20 30 40
z 10 20 30 80
w 

Sample Output:
15 60 70 20 1
30 40 10 20 1
10 20 30 40 1

10 20 30 40 2
10 20 30 80 0
15 60 70 20 1
30 40 10 20 1
50 10 10 25 1
10 20 30 40 2 
*/

#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Comparator that defines the ordering of IP keys in the map.
// Sort by octet[3] (host) ascending, then octet[0], octet[1], octet[2].
struct CompareIPs {
  bool operator()(const vector<int>& left, const vector<int>& right) const {
    if (left[3] != right[3]) return left[3] < right[3];
    if (left[0] != right[0]) return left[0] < right[0];
    if (left[1] != right[1]) return left[1] < right[1];
    return left[2] < right[2];
  }
};

// Read an IPv4 address into `ip` (four integers).
void ReadIP(vector<int>& ip) {
  int octet;
  ip.clear();
  for (int i = 0; i <= 3; ++i) {
    cin >> octet;
    ip.push_back(octet);
  }
}

// Print an IPv4 address stored in `ip` (four integers separated by spaces).
void PrintIP(const vector<int>& ip) {
  for (int i = 0; i <= 3; ++i) {
    cout << ip[i] << ' ';
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  // Map: key = IP address (vector<int> of size 4), value = occurrence count.
  // Keys are ordered using CompareIPs as required by the problem.
  map<vector<int>, int, CompareIPs> ipCount;
  map<vector<int>, int, CompareIPs>::iterator it;

  vector<int> ip;           // holds a single IP during processing
  int commandCount;         // number of incoming commands
  char cmd;                 // command: 'k', 'z', or 'w'

  cin >> commandCount;

  for (int i = 1; i <= commandCount; ++i) {
    cin >> cmd;
    switch (cmd) {
      case 'k': { // record a connection to an IP
        ReadIP(ip);
        ++ipCount[ip];
        break;
      }
      case 'z': { // query count for an IP
        ReadIP(ip);
        PrintIP(ip);
        if (ipCount.count(ip) == 0)
          cout << 0 << "\n";
        else
          cout << ipCount[ip] << "\n";
        break;
      }
      case 'w': { // list all seen IPs with counts in the required order
        for (it = ipCount.begin(); it != ipCount.end(); ++it) {
          PrintIP(it->first);
          cout << it->second << "\n";
        }
        break;
      }
      default:
        break;
    }
  }

  return 0;
}
