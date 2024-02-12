#include "bits/stdc++.h"

using namespace std;

// Tablica wystąpienia będzie zawierała dla każdego indeksu x
// jak dużo wartości x mamy w ciągu.
int wystapienia[1'000'007];

int main() {
  int N;
  cin >> N;
  for (int i=0; i<N; i++) {
    int x;
    // Wczytujemy ciąg...
    cin >> x;
    // i zliczamy wystąpienia elementów tego ciągu.
    wystapienia[x]++;
  }

  // Zmienna na liczbę operacji.
  // Zwróć uwagę, że musimy użyć typu `long long`.
  long long operacje = 0;

  // Iterujemy się po wszystkich wartościach od największej do najmniejszej.
  for (int i=1'000'000; i>=1; i--) {
    // Jeżeli mamy za dużo elementów,
    if (wystapienia[i] > 1) {
      // zliczamy o ile mamy ich za dużo,
      int za_duzo = wystapienia[i] - 1;
      // wszystkie zmniejszamy o 1,
      wystapienia[i-1] += za_duzo;
      // i dodajemy je do liczby operacji.
      operacje += za_duzo;
    }
  }

  cout << operacje << "\n";
}