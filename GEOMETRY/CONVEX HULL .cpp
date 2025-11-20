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

struct pt {
  ll x, y;
  pt() {}
  pt(ll _x, ll _y) : x(_x), y(_y) {}
};
pt operator+(pt a, pt b) { return pt(a.x+b.x, a.y+b.y); }
pt operator-(pt a, pt b) { return pt(a.x-b.x, a.y-b.y); }
ll operator^(pt a, pt b) { return a.x*b.y - b.x*a.y; }
int sign(ll x) { return (int)(x > 0) - (int)(x < 0); }
bool ccw(const pt& A, const pt& B, const pt& C, bool collinear = true) {
  return collinear ? ((A-C)^(B-C)) > 0:((A-C)^(B-C)) >=0;
}
bool cw(const pt& A, const pt& B, const pt& C, bool collinear = true) {
  return collinear ? ((A-C)^(B-C)) < 0:((A-C)^(B-C)) <=0;
}


istream& operator>>(istream& is, pt& a) { return is >> a.x >> a.y; }
ostream& operator<<(ostream& os, const pt a) { return os << a.x << ' ' << a.y; }

vector<pt> upper_half(const vector<pt>& P) {
  vector<pt> hull;
  for (int i = 0; i < int(P.size()); ++i) {
    while (hull.size() >= 2) {
      pt A = hull[hull.size() - 2];
      pt B = hull.back();
      pt C = P[i];
      if (ccw(A,B,C)) {
        hull.pop_back();
      } else {
        break;
      }
    }
    hull.push_back(P[i]);
  }
  return hull;
};

vector<pt> lower_half(const vector<pt>& P) {
  vector<pt> hull;
  for (int i = 0; i < int(P.size()); ++i) {
    while (hull.size() >= 2) {
      pt A = hull[hull.size() - 2];
      pt B = hull.back();
      pt C = P[i];
      if (cw(A,B,C)) {
        hull.pop_back();
      } else {
        break;
      }
    }
    hull.push_back(P[i]);
  }
  return hull;
};

vector<pt> convexHull(vector<pt> P){
    sort(P.begin(),P.end(),[](const pt a, const pt b){
        if(a.x != b.x) return a.x < b.x;
        else return a.y < b.y;
    });

    vector<pt> upper;
    upper.push_back(P[0]);
    vector<pt> lower;
    lower.push_back(P[0]);

    int N = P.size();
    for(int i = 1; i < N-1; i++){
        if(!cw(P[0],P[N-1],P[i])) upper.push_back(P[i]);
        if(!ccw(P[0],P[N-1],P[i])) lower.push_back(P[i]);
    }
    upper.push_back(P[N-1]);
    lower.push_back(P[N-1]);

    auto cupper = upper_half(upper);
    auto clower = lower_half(lower);
    auto hull = cupper;
    for(int i = clower.size()-2; i > 0; i--) hull.push_back(clower[i]);
    return hull;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifdef LOCAL
    ifstream cin("input.txt");
    #endif
    int N;

        cin >> N;

        vector<array<ll,2>> p(N);
        for(int i = 0; i < N; i++){
            cin >> p[i][0] >> p[i][1];
        }
        sort(p.begin(),p.end());
        vector<pt> a;
        a.push_back({p[0][0],p[0][1]});
        for(int i = 1; i < N; i++){
            a.push_back({p[i][0],p[i][1]});
        }

        auto hull = convexHull(a);
        cout << hull.size() << '\n';
        for(pt h:hull){
            cout << h.x << ' ' << h.y << '\n';
        }

    return 0;
}
