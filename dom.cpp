#include "bits/stdc++.h"

using namespace std; 

char obrazek[1007][1007];

string symuluj(string kolumna) {
  int sniezynki = 0, puste = 0;
  int poczatek_segmentu = 0;
  for (int i=0; i<kolumna.size(); i++) {
    // Zliczamy śnieżynki i puste pola w danym segmencie.
    if (kolumna[i] == '*') sniezynki++;
    if (kolumna[i] == '.') puste++;
    if (kolumna[i] == '#') {
      // Kiedy segment się kończy
      // najwyższe pola będą puste,
      for (int j=0; j<puste; j++) {
        kolumna[poczatek_segmentu+j] = '.';
      }
      // a pola poniżej będą śnieżynkami.
      for (int j=0; j<sniezynki; j++) {
        kolumna[poczatek_segmentu+j+puste] = '*';
      }
      // Następnie ustawiamy nowy segment.
      poczatek_segmentu = i+1;
      sniezynki = 0;
      puste = 0;
    }
  }
  return kolumna;
}

int main() {
  int N, M;
  cin >> N >> M;
  for (int i=0; i<N; i++) {
    cin >> obrazek[i];
  }
  for (int i=0; i<M; i++) {
    // Generujemy napis dla każdej kolumny.
    string kolumna = "";
    for (int j=0; j<N; j++) kolumna += obrazek[j][i];
    // Wywołujemy funkcję, aby zasumulować opadanie śnieżynek
    // dla tej kolumny.
    kolumna = symuluj(kolumna);
    // A następnie przypisujemy wynik tej funkcji
    // do oryginalnego obrazka.
    for (int j=0; j<N; j++) obrazek[j][i] = kolumna[j];
  }
  for (int i=0; i<N; i++) {
    cout << obrazek[i] << "\n";
  }
}