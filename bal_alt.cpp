#include "bits/stdc++.h"

using namespace std;

int main() {
  // Wczytujemy liczbę wiadarek śniegu.
  // Zwróc uwagę, że używamy typu `long long`, jako że liczba na wejściu
  // może być duża (większa niż typ `int` może przechować).
  long long N;
  cin >> N;

  // Użyjemy wyszukiwania binarnego, aby znaleźć promień najmniejszej kuli.
  // A będzie oznaczało tutaj najwiekszą wartość, dla której jesteśmy pewni,
  // że jesteśmy w stanie zbudować bałwana ze śniegu, jaki mamy.
  // B będzie oznaczało najmniejszą wartość, dla której jesteśmy pewni,
  // że nie jesteśmy w stanie zbudować bałwana.
  long long A = 1, B = 1'000'000'000;
  // Będziemy kontynuować nasz algorytm, dopóki A i B będą oddalone o dokładnie 
  // 1 -- oznacza to, że będziemy wiedzieli, że możemy ulepić bałwana dla 
  // promienia najmniejszej kuli A, ale już nie A+1.
  while (B - A  > 1) {
    // Sprawdzamy punkt pomiędzy A i B (dokładnie w środku),
    long long M = (A + B) / 2;
    // i liczymy ile wiaderek potrzebujemy dla tego punktu.
    long long potrzebne_wiaderka = M * M * 14;
    // Jeżeli liczba potrzebnych wiaderek jest mniejsza lub równa liczbie 
    // wiaderek jakie posiadamy, to aktualizujemy A (bo wiemy, że możemy
    // ulepić bałwana o promieniu najmniejszej kuli M.
    if (potrzebne_wiaderka <= N) {
      A = M; 
    // W przeciwnym wypadku aktualizujemy B.
    } else {
      B = M;
    }
  }

  // Największym promieniem najmniejszej kuli jest finalnie A.
  long long R = A;
  // Zatem wypisujemy wynik -- R * 12.
  cout << R * 12 << "\n";
}