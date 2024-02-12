#include "bits/stdc++.h"

using namespace std;

void funkcja(int n, int b, int d, int f) {
    int a = (n - f*f) % f;
    int c = ((n - f*f) / f) % f;
    int e = (n - f*f) / (f*f);
    cout << "OI";
    cout << string(a, 'J');
    cout << string(b, 'I');
    cout << string(c, 'J');
    cout << string(d, 'O');
    cout << string(e, 'I');
    cout << string(f, 'J');
    cout << "\n";
}

int main() {
    int n;
    cin >> n;

    if (n >= 1000000) {
        funkcja(n, 999, 999, 1000);
    }
    else if (n >= 10000) {
        funkcja(n, 99, 99, 100);
    }
    else if (n >= 100) {
        funkcja(n, 9, 9, 10);
    }
    else {
        cout << "OI";
        cout << string(n, 'J');
        cout << "\n";
    }

    return 0;
}
