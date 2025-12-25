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

struct Pt{
    ll x,y;
    bool operator<(Pt p){
        return x < p.x || (x == p.x && y < p.y);
    }
};

ll crossProduct(Pt O, Pt A, Pt B){
    return ((A.x - O.x) * (B.y - O.y))-((A.y-O.y)*(B.x-O.x));
}

vector<Pt> convexHull(vector<Pt> A){
    int N = A.size();
    int K = 0;
    if(N <= 3) return A;
    vector<Pt> ans(2*N);
    sort(A.begin(),A.end());
    for(int i = 0; i < N; i++){
        while(K >= 2 && crossProduct(ans[K-2],ans[K-1],A[i]) <= 0) K--;
        ans[K++]=A[i];
    }
    for(size_t i = N-1, t = K+1; i > 0; i--){
        while(K >= t && crossProduct(ans[K-2],ans[K-1],A[i-1]) <= 0) K--;
        ans[K++]=A[i-1];
    }
    ans.resize(K-1);
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifdef LOCAL
    ifstream cin("input.txt");
    #endif
    int N;
    cin >> N;
    vector<Pt> a(N);
    for(int i = 0; i < N; i++){
        cin >> a[i].x >> a[i].y;
    }

    auto hull = convexHull(a);
    for(auto h:hull){
        cout << h.x << ' ' << h.y << '\n';
    }
    return 0;
}
