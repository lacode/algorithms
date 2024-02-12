#include <iostream>

using namespace std;

const int MAXN = 100 * 1000 + 7;

int books[MAXN];

int main() {
  int N;
  cin >> N;
  int maxtime;
  cin >> maxtime;

  for (int i = 0; i < N; i++)
    cin >> books[i];

  int left = 0;
  int right = 0;

  int current_time = 0;
  int result = 0;

  while (left < N) {
    while (right < N && current_time <= maxtime) {
      ++right;
      current_time += books[right];

      if (current_time <= maxtime)
        result = max(right - left, result);
    }
    ++left;
    current_time -= books[left];
  }

  cout << result;

  return 0;
}
