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


ll f(ll a, ll b, ll N,ll ans){
    ll natu = ((ans-1)*ans)/2;
    return ans*b-natu + (N-ans)*a;
}
ll ternarySearchMax(ll a, ll b, ll N){
    ll l = 0;
    ll r = min(b,N);
    while(r-l >= 3){
        ll m1 = l+(r-l)/3;
        ll m2 = r-(r-l)/3;
        ll f1 = f(a,b,N,m1);
        ll f2 = f(a,b,N,m2);
        if(f1 < f2){
            l = m1;
        } else{
            r = m2;
        }
    }

    ll ans = f(a,b,N,l);
    for(ll md = l; md <= r; md++){
        ans = max(ans,f(a,b,N,md));
    }
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifdef LOCAL
    ifstream cin("input.txt");
    #endif
    int T;
    cin >> T;
    while(T--){
        ll N,a,b;
        cin >> N >> a >> b;
        ll ans = ternarySearchMax(a,b,N);
        cout << ans << '\n';
    }
    return 0;
}
