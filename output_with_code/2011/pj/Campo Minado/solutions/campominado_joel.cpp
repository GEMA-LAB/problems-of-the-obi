#include <iostream>
using namespace std;
int main(){
    int n;
    int v[] = {0, 0, 0};
    cin >> n;
    for (int i = 0; i < n + 1; ++i) {
        if (i < n) cin >> v[i%3]; else v[i%3] = 0;
        if (i > 0) cout << v[0]+v[1]+v[2] << endl;
    }
    return 0;
}
