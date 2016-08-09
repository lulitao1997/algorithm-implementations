#include <cstdio>
#include <algorithm>
using namespace std;


const int MAXN = 100010;

namespace tarjan {
    void upd(int&x,int y){if (y<x) x=y;}
    int N,M;

    struct edge
    {
        int to,nex;
    } E[50001];
    int st[50001],en;

    void add_edge(int a,int b)
    {   E[++en]=(edge){b,st[a]};
        st[a]=en;
    }

    int stk[50001],vis[50001],idx[50001],low[50001],bel[50001],tot,cnt,top;
    bool ins[50001];
    void tarjan(int x)
    {   idx[x]=low[x]=++cnt;
        ins[x]=vis[x]=true;stk[++top]=x;
        for (int i=st[x];i;i=E[i].nex)
        {   if (!vis[E[i].to])
            {   tarjan(E[i].to);
                upd(low[x],low[E[i].to]);
            }
            else if (ins[E[i].to]) upd(low[x],idx[E[i].to]);
        }
        if (low[x]==idx[x])
        {   ++tot;
            int j;
            do{
                j=stk[top--];
                ins[j]=false;
                bel[j]=tot;
            }
            while(j!=x);
        }
    }
}

int main(){

}
