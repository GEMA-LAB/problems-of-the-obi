#include <iostream>

using namespace std; 

int main(){
    int N;
    cin >> N;

    if(N == 1958 || N == 1962 || N == 1970 || N == 1994 || N == 2002) cout << "S" << endl;
    else cout << "N" << endl;

    return 0;
}