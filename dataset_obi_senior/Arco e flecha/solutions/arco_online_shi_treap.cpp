#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <list>
#include <ctime>

using namespace std;

typedef long long int ll;

struct node {
	
	int c;
	ll x, y;
	node *l, *r;

	node(ll x) : x(x), l(NULL), r(NULL), c(1) { y = rand(); }
};

void update(node *t)
{
	if(t == NULL) return;
	t->c = 1;
	if(t->l) t->c += t->l->c;
	if(t->r) t->c += t->r->c;
}

void splitValue(node *n, ll x, node * &l, node * &r)
{
	if(n == NULL) l = r = NULL;
	else if(x <= n->x) {
		splitValue(n->l, x, l, n->l);
		r = n;
	} else {
		splitValue(n->r, x, n->r, r);
		l = n;
	}
	update(l), update(r);
	update(n);
}	

node * merge(node *l, node *r)
{
	if(l == NULL) return r;
	if(r == NULL) return l;

	node * t;

	if(l->y > r->y) {
		l->r = merge(l->r, r);
		t = l;
	} else {
		r->l = merge(l, r->l);
		t = r;
	}

	update(t);
	return t;
}

node * add(node *t, node *n)
{
	if(t == NULL || n->y > t->y) {
		splitValue(t, n->x, n->l, n->r);
		t = n;
	} else if(n->x < t->x) t->l = add(t->l, n);
	else t->r = add(t->r, n);
	
	update(t);
	return t;
}

ll query (node* &root, ll a, ll b) {
	if (root == 0) {
		return 0LL;
	}
	node * l, *r, *tmp, *m;
	splitValue (root, a, l, tmp);
	splitValue (tmp, b+1, m, r);
	ll res = 0;
	if (m != NULL) res = m->c;
	tmp = merge (m, r);
	root = merge (l, tmp);
	return res;
}

node * root ;

ll dist (ll x, ll y) {
	return x*x + y*y;
}

int main (void) {
	root = NULL;
	int n, m;
	scanf ("%d", &n);
	ll r = 0;
	for (int i = 0; i < n; ++i) {
		ll x, y;
		scanf ("%lld %lld", &x, &y); 
		ll d = dist (x + r, y + r);
		ll ans = query (root, 0LL, d);
		cout << ans << endl;
		r = ans;
		root = add (root, new node (d));
	}

}
