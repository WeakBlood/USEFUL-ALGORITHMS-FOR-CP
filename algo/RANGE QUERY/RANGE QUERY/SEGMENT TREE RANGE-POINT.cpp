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
    function<ll(ll,ll)> comp;

    SegmentTree(int N, vector<ll> &v, function<ll(ll,ll)> cmp):N(N),comp(cmp){
        tree.resize(N*2,0);
        for(int i = 0; i < N; i++){
            tree[i+N]=v[i];
        }
    }

    void update(int l, int r, ll val){
        for(l+=N, r+=N; l < r; l>>=1, r>>=1){
            if(l&1){
                tree[l]=comp(tree[l],val);
                l++;
            }
            if(r&1){
                --r; 
                tree[r]=comp(tree[r],val);
            }
        }
    }

    ll query(int pos){
        ll ans = 0;
        for(pos+=N; pos > 0; pos>>=1){
            ans=comp(ans,tree[pos]);
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
    for(int i = 0; i < N; i++){
        cin >> v[i];
    }

    SegmentTree tree(N,v,[](ll a, ll b){
        return a+b;
    });
    while(Q--){
        int t;
        cin >> t;
        if(t == 1){
            int l,r;
            ll u;
            cin >> l >> r >> u;
            tree.update(l-1,r,u);
        } else{
            int k;
            cin >> k;
            cout << tree.query(k-1) << '\n';
        }
    }
    return 0;
}

