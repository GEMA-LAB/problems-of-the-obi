#include <iostream>

using namespace std;

int main(){
	int A, B, C, X, Y, Z;
	cin >> A >> B >> C >> X >> Y >> Z;
	int ret = (X/A) * (Y/B) * (Z/C);
	cout << ret << endl;
	return 0;
}

