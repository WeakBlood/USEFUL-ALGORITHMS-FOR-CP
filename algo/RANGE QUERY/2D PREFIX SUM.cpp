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

struct Prefix2D{
    vector<vector<ll>> pfx;
    Prefix2D(const vector<vector<int>> &mtx){
        int N = mtx.size();
        int M = mtx[0].size();
        pfx.resize(N,vector<ll>(M,0));
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                pfx[i][j]=mtx[i][j];

                if(i > 0) pfx[i][j]+=pfx[i-1][j];
                if(j > 0) pfx[i][j]+=pfx[i][j-1];
                if(i > 0 && j > 0) pfx[i][j]-=pfx[i-1][j-1];
            }
        }
    }

    ll query(int i1, int j1, int i2, int j2){
        ll tot = pfx[i2][j2];
        ll top = i1 > 0LL ? pfx[i1-1][j2]:0LL;
        ll left = j1 > 0LL ? pfx[i2][j1-1]:0LL;
        ll overlap = (i1 > 0 && j1 > 0) ? pfx[i1-1][j1-1]:0LL;
        return tot-top-left+overlap;
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
    vector<vector<int>> v(N,vector<int>(N,1));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            char c;
            cin >> c;
            if(c=='.') v[i][j]=0;
        }
    }

    Prefix2D pfx(v);
    while(Q--){
        int i1,j1,i2,j2;
        cin >> i1 >> j1 >> i2 >> j2;
        cout << pfx.query(i1-1,j1-1,i2-1,j2-1) << '\n';
    }



    return 0;
}
