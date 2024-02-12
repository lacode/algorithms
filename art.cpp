#include "bits/stdc++.h"

using namespace std;

int main() {
  // Wczytujemy numer punktu artykułu.
  int N;
  cin >> N;
  
  // Dopóki N jest większe niż 26, ...
  while (N > 26) {
    // wypisujemy z
    cout << "z";
    // i zmniejszamy N o 26.
    N -= 26;
  }

  // Następnie obliczamy jaka powinna być ostatnia litera dopisku.
  // Wiemy, że musi to być N-ta kolejna litera alfabetu, zatem 
  // dodajemy N-1 do pierwszej litery - 'a'.
  char ostatnia_litera =  'a' + (N - 1);

  // I wypisujemy go razem ze znakiem końca linii.
  cout << ostatnia_litera << "\n";
}