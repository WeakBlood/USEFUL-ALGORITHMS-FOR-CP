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
     
    struct Vertex{
        Vertex *l, *r;
        int sum;
        Vertex(int val) : l(nullptr), r(nullptr),sum(val){
     
        }
        Vertex(Vertex *l, Vertex *r):l(l),r(r),sum(0){
            if(l) sum+= l->sum;
            if(r) sum+= r->sum;
        }
    };
     
     
    Vertex* build(const vector<int> &a,int l, int r){
        if(l == r) return new Vertex(a[l]);
     
        int mid = (l+r)/2;
        return new Vertex(build(a,l,mid),build(a,mid+1,r));
    }
     
    int get_sum(Vertex* v, int tl, int tr, int l, int r){
        if(l > r) return 0;
        if(l == tl && r == tr) return v->sum;
        int tm = (tl+tr)/2;
        return get_sum(v->l,tl,tm,l,min(r,tm))+get_sum(v->r,tm+1,tr,max(l,tm+1),r);
    }
     
    Vertex* update(Vertex* v, int tl, int tr, int pos, int newVal){
        if(tl == tr) return new Vertex(newVal);
        int tm = (tl+tr)/2;
        if(pos <= tm){
            return new Vertex(update(v->l,tl,tm,pos,newVal),v->r);
        } else{
            return new Vertex(v->l,update(v->r,tm+1,tr,pos,newVal));
        }
    }
     
    int main(){
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        #ifdef LOCAL
        ifstream cin("input.txt");
        #endif
     
        
        int N;
        cin >> N;
        string tmp;
        getline(cin,tmp);
        vector<int> a(N,0);
        Vertex* base = build(a,0,N-1);
        vector<Vertex*> days(N+1,base);
        for(int i = 0; i < N; i++){
            string line;
            getline(cin,line);
            days[i+1]=days[i];
            if(line.empty()) continue;
            stringstream ss(line);
            string tok;
            while(ss >> tok){
                if(tok.size() < 2) continue;
                char sign = tok[0];
                int val = stoi(tok.substr(1));
                if(sign == '+'){
                    days[i] = update(days[i],0,N-1,val,1);
                } else{
                    days[i] = update(days[i],0,N-1,val,0);
                }
            }
            days[i+1]=days[i];
        }
     
     
        vector<int> ans(N+1,0);
        vector<int> y(N,0);
        for(int i = 0; i < N; i++){
            int d;
            cin >> d;
            d--;
            y[i] = d >= 0 ? get_sum(days[d],0,N-1,ans[i],N-1):0;
            ans[i+1]=(ans[i]+y[i])%N;
        }
        cout << ans[N] << '\n';
        return 0;
    }
