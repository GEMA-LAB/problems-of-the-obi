#include<bits/stdc++.h>
using namespace std ; 
 
int main(){
 
    int n ; cin >> n ; 
 
    int resp = 0 ; 
 
    for(int i = 1 ; i <= n ; i++){
        int a, b ; cin >> a >> b ;
        if(a == 1) resp++ ; 
        else if(b == 0) resp++ ;  
    }
 
    cout << resp << "\n" ;
 
    return 0 ; 
 
}
