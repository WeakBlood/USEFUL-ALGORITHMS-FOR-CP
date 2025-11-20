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

struct SegmentTree{
    int N;
    vector<ll> tree;
    function<ll(ll,ll)> cmp;
    SegmentTree(int N, const vector<ll> &v, function<ll(ll,ll)> cmp):N(N),cmp(cmp){
        tree.resize(N*2);
        for(int i = 0; i < N; i++){
            tree[i+N]=v[i];
        }

        for(int i = N-1; i > 0; i--){
            tree[i]=cmp(tree[i<<1],tree[i<<1|1]);
        }
    }
    SegmentTree(int N){
        tree.assign(N*2,0);
    }

    void update(int pos, ll val){
        for(tree[pos+=N]=val; pos > 1; pos>>=1){
            tree[pos>>1]=cmp(tree[pos],tree[pos^1]);
        }
    }

    ll query(int l, int r, ll base){
        ll ans = base;
        for(l+=N,r+=N; l < r; l>>=1,r>>=1){
            if(l&1)ans=cmp(tree[l++],ans);
            if(r&1)ans=cmp(tree[--r],ans);
        }
        return ans;
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

    SegmentTree myFavoriteTree(N,v,[](ll a, ll b){
        return min(a,b);
    });
    while(Q--){
        int t;
        cin >> t;
        if(t == 1){
            int k;
            ll u;
            cin >> k >> u;
            k--;
            myFavoriteTree.update(k,u);
        } else{
            int l,r;
            cin >> l >> r;
            l--;
            cout << myFavoriteTree.query(l,r,LLONG_MAX) << '\n';
        }
    }
    return 0;
}
