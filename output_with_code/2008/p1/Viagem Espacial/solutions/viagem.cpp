#include <inttypes.h>

#include <iostream>

using namespace std;

int64_t dot(int64_t a[2], int64_t b[2]) {
  return a[0]*b[0] + a[1]*b[1];
}

int64_t p[1000][2][2];

int main () {

  int64_t c[2], r;
  int n;

  cin >> n >> c[0] >> c[1] >> r;
  for (int i = 0; i < n; i++) {
    cin >> p[i][0][0] >> p[i][0][1] >> p[i][1][0] >> p[i][1][1]; 
  }
 
  int resp = 0;
  for (int i = 0; i < n; i++) {
    int64_t a[2], b[2], d[2];
    
    a[0] = p[i][1][0] - p[i][0][0];
    a[1] = p[i][1][1] - p[i][0][1];
    b[0] = c[0] - p[i][0][0];
    b[1] = c[1] - p[i][0][1];
    
    d[0] = b[0]*dot(a,a) - a[0]*dot(a,b);
    d[1] = b[1]*dot(a,a) - a[1]*dot(a,b);
    
    if (dot(d, d) <= r * r * dot(a, a) * dot(a, a)) resp++;
  }

  cout << resp << endl;
  return 0;
};
