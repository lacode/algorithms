#include "bits/stdc++.h"

using namespace std;

int main() {
  // Wczytujemy liczbę wiadarek śniegu.
  // Zwróc uwagę, że używamy typu `long long`, jako że liczba na wejściu
  // może być duża (większa niż typ `int` może przechować).
  long long N;
  cin >> N;

  // Obliczamy promień najmniejszej kuli.
  long long R = floor(sqrt(N / 14));

  // Wypisujemy wynik.
  cout << R * 12 << "\n";
}