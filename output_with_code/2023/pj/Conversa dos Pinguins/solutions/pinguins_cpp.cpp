#include <bits/stdc++.h>

using namespace std;

int main() {
    char eA, eB;
    float tA, tB;

    cin >> eA >> eB;
    cin >> tA >> tB;

    if (eA == 'F') {
        tA = (tA - 32.0) * 5.0 / 9.0;
    }

    if (eB == 'F') {
        tB = (tB - 32.0) * 5.0 / 9.0;
    }

    if (tA < tB) {
        cout << "A" << endl;
    }
    else {
        cout << "B" << endl;
    }
}
