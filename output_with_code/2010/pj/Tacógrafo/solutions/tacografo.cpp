#include <iostream>

using namespace std;

int main(void){
	int n;
	cin >> n;
	int tot = 0;
	for(int i = 0; i < n; i++){
		int t, v;
		cin >> t >> v;
		tot += t*v;
	}

	cout << tot << endl;

	return 0;

}
