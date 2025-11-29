/* 
@author WeakBlood<3
*/
#include <bits/stdc++.h>

#define ll long long int
using namespace std;

/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N)
 * Status: stress-tested
 */
// TOOK BY THIS GUY https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h 
//( THANK YOU SO FUCKING MUCH) https://www.codechef.com/problems/CYCLRACE?tab=statement
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {

	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { 
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};
// TESTED ON THIS PROBLEM 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifdef LOCAL
    ifstream cin("input.txt");
    #endif
    int N,Q;
    cin >> N >> Q;
    LineContainer myFirstDHT;
    vector<ll> curK(N,0);
    vector<ll> curM(N,0);
    while(Q--){
        int t;
        cin >> t;
        if(t == 1){
            ll time,c,newSpeed;
            cin >> time >> c >> newSpeed;
            c--;
            ll pos = curK[c] * time + curM[c];
            ll k = newSpeed;
            ll m = pos-newSpeed * time;
            curK[c]=k;
            curM[c]=m;
            myFirstDHT.add(k,m);
        } else{
            ll time;
            cin >> time;
            cout << myFirstDHT.query(time) << '\n';
        }
    }
    return 0;
}
