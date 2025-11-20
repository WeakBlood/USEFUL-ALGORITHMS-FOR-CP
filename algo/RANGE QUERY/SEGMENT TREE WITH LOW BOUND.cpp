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
static int nextPow2(int x){
    int p = 1;
    while(p < x) p <<= 1;
    return p;
}
struct SegmentTree{
    int N;
    vector<ll> tree;
    function<ll(ll,ll)> cmp;
    SegmentTree(const vector<ll> &v, function<ll(ll,ll)> cmp):cmp(cmp){
        N = nextPow2(v.size());
        tree.resize(N*2,-inf);
        for(int i = 0; i < v.size(); i++){
            tree[i+N]=v[i];
        }

        for(int i = N-1; i > 0; i--){
            tree[i]=cmp(tree[i<<1],tree[i<<1|1]);
        }
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

    ll lowBound(ll x){
        int pos = 1; 
        if(tree[pos] < x) return -1;
        while(pos < N){
            pos<<=1;
            if((tree[pos]) < x) pos++;
        }
        return pos-N;
    }
};


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifdef LOCAL
    ifstream cin("input.txt");
    #endif
    int N,Q;
    cin >> N  >> Q;
    vector<ll> v(N);

    for(int i = 0; i < N; i++){
        cin >> v[i];
    }  

    SegmentTree tree(v,[](ll a, ll b){
        return max(a,b);
    });

    
    while(Q--){
        ll x;
        cin >> x;
        int q = tree.lowBound(x);
        if(q!=-1){
            v[q]-=x;
            tree.update(q,v[q]);
        }
        cout << q+1 << ' ';
    }
    return 0;
}
