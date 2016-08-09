#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXE = 1000010,MAXN = 10010,INF = 0x7fffffff>>2;

struct graph{
    struct edge{
        int t,n,v,f;
    } E[MAXE];
    int st[MAXN],en,vn,cur[MAXN],vis[MAXN],d[MAXN];
    
    graph() {en=1;}

    void clear() {
        en=1;
        for (int i=1;i<=vn;i++) st[i]=d[i]=0;
        vn=0;
    }
    void ade(int a,int b,int v) {
        vn=max(vn,max(a,b));
        E[++en]=(edge){b,st[a],v,0};
        st[a]=en;
        E[++en]=(edge){a,st[b],v,v};
        st[b]=en;
    }

    int S,T;queue<int> Q;

    bool BFS() {
        for(int i=1;i<=vn;i++) {vis[i]=0;cur[i]=st[i];}
        Q.push(S);
        vis[S]=1;d[S]=0;
        while (!Q.empty()) {
            int f=Q.front();Q.pop();
            for (int i=st[f];i;i=E[i].n) if (!vis[E[i].t]&&(E[i].v-E[i].f)) {
                d[E[i].t]=d[f]+1;
                vis[E[i].t]=1;
                Q.push(E[i].t);
            }
        }
        return vis[T];
    }

    int DFS(int x,int flow) {
        if (x==T||!flow) return flow;
        int t,res=0;
        for (int&i=cur[x];i;i=E[i].n)
            if (d[E[i].t]==d[x]+1&&(t=DFS(E[i].t,min(flow,E[i].v-E[i].f)))) {
                res+=t;
                E[i].f+=t;
                E[i^1].f-=t;
                flow-=t;
                if (!flow) return res;
            }
        return res;
    }

    int maxflow(int s,int t) {
        S=s;T=t;int res=0;
        while (BFS()) res+=DFS(S,INF);
        return res;
    }
} G;

int N,M,a,b,v;

int main(){
    scanf("%d%d",&M,&N);
    while (M--) {
        scanf("%d%d%d",&a,&b,&v);
        G.ade(a,b,v);
    }
    G.vn=N;
/// ******
    printf("%d\n",G.maxflow(1,N));
}
