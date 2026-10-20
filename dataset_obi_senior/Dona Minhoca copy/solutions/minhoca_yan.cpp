#include <iostream>
#include <vector>

using namespace std;

const int maxn = 300010;
const int inf = 1000000010;

int n, k;

vector<int> adj[maxn];

#define f first
#define s second
#define pii pair<int,int>
#define pip pair<int,pii>

pip dfs(int node, int anc, int r)
{
    int ans = 0, mxUp = -inf, mnDown = 0;

    for(int neighbor: adj[node])
    {
        if( neighbor == anc )
            continue;

       // auto [curAns, curUp, curDown] = dfs(neighbor, node, r);
        pip x = dfs(neighbor, node, r);
        int curAns = x.f;
        int curUp = x.s.f;
        int curDown = x.s.s;

        ans += curAns;
        mxUp = max(mxUp, curUp - 1);
        mnDown = min(mnDown, curDown - 1);
    }

    if( mxUp + mnDown < 0 )
    {
        if( mnDown == -r || node == 1 )
            //return {ans + 1, r, inf};
            return pip(ans + 1, {r, inf});
        else
            //return {ans, mxUp, mnDown};
            return pip (ans, {mxUp, mnDown} );
    }
    else
       // return {ans, mxUp, inf};
		return pip (ans, {mxUp, inf} );
}

bool test(int r)
{
	pip x = dfs(1, 1, r);
    int curAns = x.f;
    int curUp = x.s.f;
    int curDown = x.s.s;
   // auto [ans, up, down] = dfs(1, 1, r);
    return (curAns <= k);
}

int bs()
{
    int l = 1, r = n;

    while( l < r )
    {
        int m = ( l + r )/2;

        if( test(m) )
            r = m;
        else
            l = m + 1;
    }

    return r;
}

int main()
{
    cin >> n >> k;

    for(int i = 1 ; i < n ; i++)
    {
        int u, v;
        cin >> u >> v;

        adj[u].push_back( v );
        adj[v].push_back( u );
    }

    cout << bs() << endl;
}
