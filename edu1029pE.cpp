#include<iostream>
#include<queue>
#include<vector>

#define int long long
#define mod 1000000007
#define endl '\n'
#define pii pair<int,int>
#define Mikari_My_Wife ios::sync_with_stdio(0),cin.tie(0);
using namespace std;
const int MXN=1000;
struct Dinic
{
      struct Edge
      {
            int v, f, re;
      };
      int n, s, t, level[MXN];
      vector<Edge> E[MXN];
      void init(int _n, int _s, int _t)
      {
            n = _n;
            s = _s;
            t = _t;
            for (int i = 0; i < n; i++)
                  E[i].clear();
      }
      void addEdge(int u, int v, int f)
      {
            E[u].push_back({v, f, (int)(E[v].size())});
            E[v].push_back({u, 0, (int)(E[u].size())-1});
      }
      bool BFS()
      {
            for (int i = 0; i < n; i++)
                  level[i] = -1;
            queue<int> que;
            que.push(s);
            level[s] = 0;
            while (!que.empty())
            {
                  int u = que.front();
                  que.pop();
                  for (auto it : E[u])
                  {
                        if (it.f > 0 && level[it.v] == -1)
                        {
                              level[it.v] = level[u] + 1;
                              que.push(it.v);
                        }
                  }
            }
            return level[t] != -1;
      }
      int DFS(int u, int nf)
      {
            if (u == t)
                  return nf;
            int res = 0;
            for (auto &it : E[u])
            {
                  if (it.f > 0 && level[it.v] == level[u] + 1)
                  {
                        int tf = DFS(it.v, min(nf, it.f));
                        res += tf;
                        nf -= tf;
                        it.f -= tf;
                        E[it.v][it.re].f += tf;
                        if (nf == 0)
                              return res;
                  }
            }
            if (!res)
                  level[u] = -1;
            return res;
      }
      int flow(int res = 0)
      {
            while (BFS())
                  res += DFS(s, 2147483647);
            return res;
      }
} flow;
void sol(){
    int n;
    cin>>n;
    int all[n+1];
    for(int i=1;i<=n;i++)cin>>all[i];
    int ss=0,tt=n+60+1;
    flow.init(tt+1,ss,tt);
    for(int i=1;i<=n;i++){
        flow.addEdge(ss,i,1);
    }
    for(int i=n+1;i<=n+60;i++){
        flow.addEdge(i,tt,1);
    }
    for(int i=1;i<=n;i++){
        int now=all[i];
        for(int j=0;j<=59;j++){
            if((now>>j)&1){
                flow.addEdge(i,n+j+1,1e9);
            }
        }
    }
    
    flow.flow();
    int a=0,b=0;
    for(auto [vv,ff,rere]:flow.E[ss]){
        if(vv>=1){
            if(ff==1){
                b++;
            }else a++;
        }
    }
    int c=0,d=0;
    for(int i=n+1;i<=n+60;i++){
        for(auto [vv,ff,rere]:flow.E[i]){
            if(vv==tt){
                if(ff==0){
                    c++;
                }else {
                    d++;
                }
            }
        }
    }
    cout<<b<<endl;
    //cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
}
signed main(){
    //注意多筆測資輸入！！！
    Mikari_My_Wife
    int t=1;
    cin>>t;
    while(t--){
        sol();
    }
}