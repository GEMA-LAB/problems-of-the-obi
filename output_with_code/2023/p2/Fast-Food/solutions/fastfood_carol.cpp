#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Rectangle {
  int x_min, x_max;
  int y_min, y_max;

  Rectangle(int x_min, int y_min, int x_max, int y_max): x_min(x_min), y_min(y_min), 
                                                          x_max(x_max), y_max(y_max) {}

  bool contains(int x, int y){
    if(x > x_max || x < x_min) return false;
    if(y > y_max || y < y_min ) return false;
    return true;
  }
};

bool works(vector<int> &X, vector<int> &Y, int d, int mx_x, int mx_y){
  Rectangle green = Rectangle(mx_x-d, 0, mx_x, d);
  Rectangle blue = Rectangle(0, mx_y-d, d, mx_y);
  for(int i = 0; i < X.size(); i++){
    if(!green.contains(X[i], Y[i]) && !blue.contains(X[i], Y[i])){
      return false;
    }
  }
  return true;
}

void clean(vector<int> &X, vector<int> &Y){
  int mn_x = *min_element(X.begin(),X.end());
  int mn_y = *min_element(Y.begin(), Y.end());

  for(int i = 0; i < X.size(); i++){
    X[i] -= mn_x;
    Y[i] -= mn_y;
  }
}

int getMinimumDistance(int N, vector<int> X, vector<int> Y) {
  for(int i= 0, x, y; i < N; i++){
      x = X[i]+Y[i];
      y = X[i]-Y[i];
      X[i] = x;
      Y[i] = y;
  }

  int ans = 2e9+5;

  for(int i =0; i < 2; i++){
    int hi = 2e9+5, lo = 0, mid;

    clean(X,Y);
    int mx_y = *max_element(Y.begin(), Y.end());
    int mx_x = *max_element(X.begin(), X.end());

    while(lo < hi){
      mid = lo+((hi-lo)>>1);
      if(works(X, Y, mid, mx_x, mx_y)){
        hi = mid;
      }
      else{
        lo = mid+1;
      }
    }
    ans = min(ans, lo);

    for(int j = 0; j < N; j++){
      X[j] = mx_x-X[j];
    }
  }
  return ans;
  
}

int main(){
  int N;
  cin >> N;
  vector<int> X(N), Y(N);
  for(int i = 0; i < N; i++){
    cin >> X[i];
  }
  for(int i = 0; i < N; i++){
    cin >> Y[i];
  }
  cout << getMinimumDistance(N, X, Y) << "\n";
}