/* 
@author WeakBlood<3
*/
#include <bits/stdc++.h>

#define ll long long int
#define inf 1e9
using namespace std;

//!!!EXPLANATION!!!:
/* 

*/

//Cases
// INCLUSIVE VERSION [L,R]
struct Fenwick{
    vector<ll> bits;
    int N;

    Fenwick(int N, const vector<ll> &v):N(N){
        bits.resize(N);
        for(int i = 0; i < N; i++){
            bits[i]+=v[i];
            int r  = i|(i+1);
            if(r < N) bits[r]+=bits[i];
        }
    }
    Fenwick(int N):N(N){
        bits.assign(N,0);
    }

    ll sum(int r){
        ll ans = 0;
        for(; r >= 0; r = (r&(r+1))-1) ans+=bits[r];
        return ans;
    }

    ll sum(int l, int r){
        return sum(r)-sum(l-1);
    }
    void add(int pos, ll delta){
        for(; pos < N; pos = pos | (pos+1)) bits[pos]+=delta;
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifdef LOCAL
    ifstream cin("input.txt");
    #endif
    int N,Q;
    cin >> N >> Q;
    vector<ll> v(N);
    for(int i = 0; i < N; i++) cin >> v[i];

    Fenwick fen(N,v);
    while(Q--){
        int t;
        cin >> t;
        if(t==1){
            int k;
            ll u;
            cin >> k >> u;
            k--;
            fen.add(k,-v[k]);
            v[k]=u;
            fen.add(k,v[k]);
        } else{
            int l,r;
            cin >> l >> r;
            cout << fen.sum(l-1,r-1) << '\n';
        }
    }
    return 0;
}
