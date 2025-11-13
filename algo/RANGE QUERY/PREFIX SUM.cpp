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

struct PrefixSum{
    int N;
    vector<ll> pfx;

    PrefixSum(int N, const vector<ll> &v):N(N){
        pfx.assign(N+1,0);
        for(int i = 0; i < N; i++){
            pfx[i+1]=pfx[i]+v[i];
        }
    }   

    ll query(int l, int r){
        return pfx[r]-pfx[l-1];
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifdef LOCAL
    ifstream cin("input.txt");
    #endif
    int T;
    T = 1;
    while(T--){
        int N,Q;
        cin >> N >> Q;
        vector<ll> v(N);
        for(int i = 0; i < N; i++) cin >> v[i];

        PrefixSum pfx(N,v);
        while(Q--){
            int l,r;
            cin >> l >> r;
            cout << pfx.query(l,r) << '\n';
        }
    }
    return 0;
}
