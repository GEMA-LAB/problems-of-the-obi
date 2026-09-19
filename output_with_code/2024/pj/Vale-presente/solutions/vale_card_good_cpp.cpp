#include <iostream>
// #include <iomanip>

using namespace std;
int main() {

    int n;
    cin >> n;

    if (n < 100) {
        cout << n << endl;
    } else {
        // double resultado = n * 0.15;

        // cout << fixed;
        // cout.precision(2);
        cout << n + 15 << endl;
    }

    return 0;
}