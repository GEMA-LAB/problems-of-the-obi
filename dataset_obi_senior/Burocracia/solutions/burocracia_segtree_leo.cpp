#include<bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define ff first
#define ss second
#define O_O
using namespace std;
template <typename T>
using bstring = basic_string<T>;
template <typename T>
using matrix = vector<vector<T>>;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef double dbl;
typedef long double dbll; 
const ll INFL = 4e18+25;
const int INF = 1e9+42;
const double EPS = 1e-7;
const int MOD = (1<<23)*17*7 + 1; // 998244353
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
const int MAXN = 1e6+1;

// TODO: Make build accept elements of type seg like iterativesegtree.hpp

/*
from https://github.com/defnotmee/definitely-not-a-lib

Declaration: SegTree(size)
Update: update(l, r, {mult, add}), for l <= i <= r, v[i] = v[i]*mult+add
Query: query(l,r), returns seg object equivalent to the sum of all values on range [l,r]

=============================================================================

If a lazy segtree is not needed I recommend going for an iterativesegtree.hpp .
You can erase the parts where it does lazy propagation also.

Segtree for affine transformations and range sums in O(log(n)).
Made to be as customizable and copy-pasteable as possible, speed 
and code size is not a concern. 

0-indexed by default.

The parts you'll commonly edit will be commented.
*/

#ifndef O_O
#include"template.cpp"
#endif

struct SegTree{
    struct seg{
        ll x = INFL; // "identity value" of the operation
    };

    struct lazy{
        ll mult = 1, add = INFL; // "identity value" of lazy tag

        bool operator==(lazy b) const {
            return mult == b.mult && add == b.add;
        } 
        // Here is where you edit how to propagate the lazy tag for the children
        // of a segtree node
        void operator+=(const lazy& a){
            add = min(add, a.add);
        }
    };

    vector<seg> tree; // yes, this is all for the pun
    vector<lazy> lz;

    int sz, ql, qr;
    lazy val;

    // Here is where you change how to merge nodes
    inline seg merge(seg a, seg b){
        return {min(a.x,b.x)};
    }

    SegTree(int n = 0){
        sz = n;
        tree = vector<seg>(4*n);
        lz = vector<lazy>(4*n);
    }
    
    
    // Comment the next two functions if you dont need a O(n) builder

    void build(int id, int l, int r, vector<ll> & v){
        if(l == r){
            tree[id].x = {v[l]};
            return;
        }

        const int e = id*2+1, d = id*2+2, m = (l+r)>>1;

        build(e,l,m,v);
        build(d,m+1,r,v);
        tree[id] = merge(tree[e],tree[d]);

    }

    SegTree(vector<ll> v){
        *this = SegTree(v.size());
        build(0,0,sz-1,v);
    }

    void refresh(int id, int l, int r){
        if(lz[id] == lazy())
            return;
        
        if(l != r){
            const int e = id*2+1, d = id*2+2, m = (l+r)>>1;

            lz[e]+=lz[id];
            lz[d]+=lz[id];
        }

        // Here is where you update the value of the current node based on the lazy tag
        tree[id] = {min(tree[id].x, lz[id].add)};
        lz[id] = lazy();
    }

    void update(int l, int r, lazy x){
        ql = l, qr = r, val = x;

        upd(0,0,sz-1);
    }

    seg query(int l, int r){
        ql = l, qr = r;

        return qry(0,0,sz-1);
    }

    private:
    
    void upd(int id, int l, int r){
        refresh(id,l,r);

        if(ql <= l && r <= qr){
            lz[id] += val;
            refresh(id,l,r);
            return;
        }
        if(ql > r || l > qr)
            return;

        const int e = id*2+1, d = id*2+2, m = (l+r)>>1;

        upd(e,l,m);
        upd(d,m+1,r);

        tree[id] = merge(tree[e], tree[d]);
    }

    seg qry(int id, int l, int r){
        refresh(id,l,r);

        if(ql <= l && r <= qr)
            return tree[id];
        
        if(ql > r || l > qr)
            return seg();
        
        const int e = id*2+1, d = id*2+2, m = (l+r)>>1;
        return merge(qry(e,l,m), qry(d,m+1,r));
    }
};


/*
from https://github.com/defnotmee/definitely-not-a-lib

Stores a rooted tree with relevant information like height,
dfs order (tin and tout), height, the parent (pai) the size of the 
subtrees (sub). 

Intended to be inherited or composed for other algos.

Usage:

Tree(n,root): prepares tree of size n with vertices from 0 to n-1

add_edge(a,b): adds edge between a and b

After adding all edges, call calc_tree().
*/

#ifndef O_O
#include"template.cpp"
#endif

struct Tree{
    int n, root;
    vector<int> tin, tout, sub, pai, height;
    vector<bstring<int>> g;
    int m = 0;

    Tree(int n = 0, int root = 0) : n(n), root(root), 
    tin(n), tout(n), sub(n,1), pai(n,root), height(n), g(n){}

    // Takes a tree, changes the root and preprocesses it
    Tree(Tree& t, int root) : Tree(t.n, root){
        g = t.g;
        calc_tree();
    }

    void add_edge(int a, int b){
        g[a].push_back(b);
        g[b].push_back(a);
        m++;
    }

    void calc_tree(){
        assert(m == n-1);
        prec(root);
    }

    // call only after calc_tree
    pii find_centroids(){
        int id = root;

        while(true){
            for(int v : g[id]){
                if(pai[id] != v && sub[v]*2 >= n){
                    id = v;
                    goto NEXT;
                }
            }
            break;
            NEXT:;
        }
        if(sub[id]*2 == n)
            return {pai[id], id};
        return {id,id};
    }

    protected:
    void prec(int id){
        tout[id] = tin[id];
        for(int v : g[id]){
            if(v == pai[id])
                continue;
            pai[v] = id;
            height[v] = height[id]+1;
            tin[v] = tout[id]+1;
            prec(v);
            tout[id] = tout[v];
            sub[id]+=sub[v];
        }
    }
};

/*
from https://github.com/defnotmee/definitely-not-a-lib
*/

#ifndef O_O
#include"../../template.cpp"
#include"rooted_tree.hpp"
#include"../../data structures/segtree_lazy.hpp"
#endif

struct HLD : Tree {
    private:
    SegTree st;
    vector<int> head;

    public:

    HLD(int n, int root = 0) : Tree(n, root), st(n), head(n) {}

    void calc_tree(){
        assert(m == n-1);
        prec(root);
        hld(root,root);

        vector<ll> v2(n);
        for(int i = 0; i < n; i++)
            v2[tin[i]] = height[pai[i]];
        st = SegTree(v2);
    }

    int lca(int a, int b){
        while(head[a] != head[b]){
            if(tin[a] < tin[b])
                swap(a,b);
            a = pai[head[a]];
        }
        return min(a,b,[&](int a, int b){
            return tin[a] < tin[b];
        });
    }

    int dist(int a, int b){
        return height[a] + height[b] - 2*height[lca(a,b)];
    }

    using lazy = SegTree::lazy;
    using seg = SegTree::seg;

    void update_point(int id, SegTree::lazy upd){
        st.update(tin[id], tin[id], upd);
    }

    // if no_root = 1, the root won't be included in the update;
    void update_subtree(int id, SegTree::lazy upd, int no_root = 0){
        st.update(tin[id]+no_root, tout[id], upd);
    }

    // if no_root = 1, the root won't be included in the update;
    void update_path(int a, int b, SegTree::lazy upd, int no_root = 0){
        while(head[a] != head[b]){
            if(tin[a] < tin[b])
                swap(a,b);
            st.update(tin[head[a]], tin[a], upd);
            a = pai[head[a]];
        }
        if(tin[a] > tin[b])
            swap(a,b);
        st.update(tin[a]+no_root, tin[b], upd);
    }

    seg query_point(int id){
        return st.query(tin[id],tin[id]);
    }

    // if no_root = 1, the root won't be included in the query;
    seg query_subtree(int id, int no_root = 0){
        return st.query(tin[id]+no_root,tout[id]);
    }
    
    // if no_root = 1, the root won't be included in the query;
    // this query will work even if the query is non commutative
    seg query_path(int a, int b, int no_root = 0){
        seg retl = seg(), retr = seg();

        while(head[a] != head[b]){
            seg& ret = tin[a] > tin[b] ? retl : retr;
            int& v = tin[a] > tin[b] ? a : b;
            ret = st.merge(ret,st.query(tin[head[v]], tin[v]));
            v = pai[head[v]];
        }

        if(tin[a] > tin[b])
            swap(a,b);

        return st.merge(st.merge(retl,st.query(tin[a]+no_root,tin[b])), retr);

    }

    private:
    
    void prec(int id){
        // tout[id] = tin[id];
        if(g[id].size() && g[id][0] == pai[id]) // not on rooted_tree.hpp
            swap(g[id][0], g[id].back());// not on rooted_tree.hpp
        for(int& v : g[id]){ // & not in rooted_tree.hpp
            if(v == pai[id])
                continue;
            pai[v] = id;
            height[v] = height[id]+1;
            // tin[v] = tout[id]+1;
            prec(v);
            // tout[id] = tout[v];
            sub[id]+=sub[v];
            if(sub[v] > sub[g[id][0]]) // not on rooted_tree.hpp
                swap(v,g[id][0]); // not on rooted_tree.hpp
        }
    }

    void hld(int id, int hd){
        tout[id] = tin[id];
        head[id] = hd;
        if(g[id].size() && g[id][0] != pai[id]){
            tin[g[id][0]] = tout[id]+1;
            hld(g[id][0],hd);
            tout[id] = tout[g[id][0]];
        }
        for(int i = 1; i < g[id].size(); i++){
            int v = g[id][i];
            if(v == pai[id])
                continue;
            tin[v] = tout[id]+1;
            hld(v, v);
            tout[id] = tout[v];
        }
    }
};

/*
from https://github.com/defnotmee/definitely-not-a-lib

Given an array of ancestors (next), is able to get information
about starting on a certain node and going to the ancestor of the
current node k steps in a row in O(log(k)) per query. Is able to work with
any functional graph, but the lca function just works for trees.

Usage: 

- BinLift(next): constructs the structure. next is assumed to be 0-indexed
- lift: an auxiliary class that stores information about the path (for example
what is the maximum edge on the path). By default only stores the vertex you will end
up in after going up a certain number of times.
- k_up(id,k): returns a lift structure of starting on id and going to the ancestor
k times in a row. 
- lca(a,b,h): assuming the functional graph given is a tree, if h is a vector representing
the height of the nodes in a tree, returns the lift structure of the path between a and b.
The .to member of the return value will be the lca between a and b. If you are storing more
information about the path, it needs to be commutative (for example, you can store max).
*/

#ifndef O_O
#include"template.cpp"
#endif

struct BinLift{
    
    int n, lg;

    struct lift{
        int to = 0;
    };

    // what happens when you go through a, and then go through b?
    static lift merge(lift a, lift b){
        return {b.to};
    }

    matrix<lift> jmp;

    BinLift(vector<ll> next) : n(next.size()), lg(1){

        for(int tmp = 1; tmp < n; tmp*=2, lg++);

        jmp = matrix<lift>(lg,vector<lift>(next.size()));
        
        // initialize jmp[0][i]
        for(int i = 0; i < next.size(); i++)
            jmp[0][i] = {(int)next[i]};


        for(int i = 1; i < lg; i++){
            for(int j = 0; j < next.size(); j++){
                jmp[i][j] = merge(jmp[i-1][j], jmp[i-1][jmp[i-1][j].to]);
            }
        }
    }

    lift k_up(int id, int k){
        k = min(n-1,k);
        lift ret{id}; // needs to be an identity element through merge
        for(int i = 0; i < lg; i++){
            if((k>>i)&1)
                ret = merge(ret, jmp[i][ret.to]);
        }
        return ret;
    }

    lift lca(int a, int b, vector<int>& h){
        if(h[a] < h[b])
            swap(a,b);
        
        int d = h[a]-h[b];
        lift la = k_up(a,d), lb = {b}; // needs to be an identity element through merge

        if(la.to == lb.to)
            return la;
        
        for(int i = lg-1; i >= 0; i--){
            if(jmp[i][la.to].to != jmp[i][lb.to].to)
                la = merge(la,jmp[i][la.to]), lb = merge(lb,jmp[i][lb.to]);
        }

        la = merge(la, jmp[0][la.to]);
        lb = merge(lb, jmp[0][lb.to]);


        return merge(la,lb);
    }

};

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;

    vector<ll> pai(n);
    HLD tree(n);

    for(int i = 1; i < n; i++){
        cin >> pai[i];
        pai[i]--;
        tree.add_edge(pai[i],i);
    }


    tree.calc_tree();


    int q;
    cin >> q;

    BinLift lift(pai);
    vector<int> rec(n);


    while(q--){
        int t;
        cin >> t;

        if(t == 1){
            int v, k;
            cin >> v >> k;
            v--;
            // cerr << tree.height[v] << ' ' << tree.query_point(v).x << '\n';
            cout << lift.k_up(v, k+tree.height[v]-tree.query_point(v).x-1).to+1 << '\n';
        } else {
            int v;
            cin >> v;
            v--;
            tree.update_subtree(v,{0,tree.height[v]}, 1);
        }
    }
    
    
    return 0;

}
