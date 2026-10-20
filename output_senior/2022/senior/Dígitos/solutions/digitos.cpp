#include <iostream>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;

string add1(string s){
    string res = s;
    int carry=1;
    for(int i=int(res.size())-1;i>=0;i--){
        int nv = (res[i]-'0')+carry;
        carry=0;
        if(nv>=10)carry=1,nv-=10;
        res[i]=char('0'+nv);
    }
    if(carry)res = "1"+res;
    return res;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string X;
    int d;
    cin >> d;
    assert(d>0);
    while(d--){
        char c;
        cin >> c;
        X+=c;
    }
    assert(X[0]!='0');
    for(int t=1;t<=X.size();t++){
        string A = X.substr(0,t);
        int curPos = 0;
        int ok = 1;
        string num = A;
        while(curPos < X.size()){
            if(curPos + num.size() - 1 >= X.size()){
                ok=0;
                break;
            }
            for(int i=curPos;i<curPos + num.size();i++){
                if(X[i]!=num[i-curPos]){
                    ok=0;
                    break;
                }
            }
            if(!ok)break;
            curPos+=num.size();
            num = add1(num);
        }
        if(ok){
            cout << A << "\n";
            return 0;
        }
    }
}