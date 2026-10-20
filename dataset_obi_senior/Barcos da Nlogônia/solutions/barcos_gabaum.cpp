#include <stdio.h>
#include <set>
#include <algorithm>
using namespace std;
#define MAXN 100100
#define MAXM 100100

struct aresta{
	int a, b, c;
	aresta(){}
	aresta( int aa, int bb , int cc ){
		a=aa; b=bb; c=cc;	
	}
	void read(){
		scanf("%d %d %d",&a,&b,&c);
	}	
	bool operator < ( aresta a ) const {
		return c > a.c;
	}	
};

int n, m, q, atual;
aresta v[MAXM];
int pai[MAXN];
set<int> s[MAXN];
int resp[MAXM];

int find( int a ){
	if( pai[a]==a ){
		return a;	
	}	
	return pai[a]=find(pai[a]);
}

void join( int a, int b ){
	int i=find(a);
	int j=find(b);
	if( i!=j ){
		if( s[i].size() < s[j].size() ){
			swap(i,j);	
		}
		pai[j]=i;
		set<int>::iterator it;
		for( it=s[j].begin() ; it!=s[j].end() ; it++ ){
			if( s[i].count(*it)>0 ){
				resp[*it]=atual;
				s[i].erase(*it);	
			}	
			else{
				s[i].insert(*it);	
			}
		}
		s[j].clear();
	}	
}

int main(){
  int i, a, b;
  scanf("%d %d",&n,&m);
  for( i=0 ; i<m ; i++ ){
    v[i].read();	
  }
  sort(v,v+m);
  for( i=1 ; i<=n ; i++ ){
    pai[i]=i;
    s[i].clear();
  }
  scanf("%d", &q);
  for( i=0 ; i<q ; i++ ){
    scanf("%d %d",&a,&b);
    s[a].insert(i);
    s[b].insert(i);
  }
  for( i=0 ; i<m ; i++ ){
    atual=v[i].c;
    if( find(v[i].a)!=find(v[i].b) ){
      join(v[i].a,v[i].b);
    }	
  }
  for( i=0 ; i<q ; i++ ){
    printf("%d\n",resp[i]);	
  }
  
  return 0;
}
