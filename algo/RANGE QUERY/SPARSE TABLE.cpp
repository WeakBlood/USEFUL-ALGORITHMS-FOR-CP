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
struct SparseTable{
    vector<vector<int>> val;
    vector<vector<int>> id;
    vector<int> lgs;
    function<bool(int,int)> comp;
    int N;
    int LG;
    SparseTable(int N, const vector<int> &v, function<bool(int,int)> cmp):N(N),comp(cmp){
        lgs.resize(N+1);
        lgs[1]=0;
        for(int i = 2; i <= N; i++){
            lgs[i]=lgs[i>>1]+1;

        }
        LG = lgs[N];

        val.resize(LG+1,vector<int>(N+1));
        id.resize(LG+1,vector<int>(N+1));

        for(int i = 0; i < N; i++){
            val[0][i]=v[i];
            id[0][i]=i;
        }

        for(int i = 1; i <= LG; i++){
            for(int j = 0; j+(1<<i) <= N; j++){
                if(comp(val[i-1][j],val[i-1][j+(1<<(i-1))])){
                    val[i][j]=val[i-1][j];
                    id[i][j]=id[i-1][j];
                } else{
                    val[i][j]=val[i-1][j+(1<<(i-1))];
                    id[i][j]=id[i-1][j+(1<<(i-1))];
                }
            }
        }
    }
    int queryVal(int l, int r){
        int i = lgs[r-l+1];
        if(comp(val[i][l],val[i][r-(1<<i)+1])) return val[i][l];
        else return val[i][r-(1<<i)+1];
    }

    int queryId(int l, int r){
        int i = lgs[r-l+1];
        if(comp(val[i][l],val[i][r-(1<<i)+1])) return id[i][l];
        else return id[i][r-(1<<i)+1];
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
    vector<int> v(N);
    for(int i = 0; i < N; i++) cin >> v[i];
    SparseTable sparse(N,v,[](int a, int b){
        return a < b;
    });

    while(Q--){
        int l,r;
        cin >> l >> r;
        cout << sparse.queryVal(l-1,r-1) << '\n';
    }
    return 0;
}
