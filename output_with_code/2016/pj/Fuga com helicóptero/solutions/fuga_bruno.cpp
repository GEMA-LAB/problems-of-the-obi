#include <bits/stdc++.h>
using namespace std;

int h, p, f, d;

bool good()
{
	int ff = f;
	while (ff != h)
	{
		if (ff == p) return 0;
		ff += d;
		if (ff == -1) ff = 15;
		if (ff == 16) ff = 0;	
	}
	return 1;
}

int main()
{
	cin >> h >> p >> f >> d;
	assert(h != p);
	assert(h != f);
	assert(p != f);
	if (good()) cout << "S" << endl;
	else cout << "N" << endl;
}

