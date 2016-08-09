#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXE = 300010,MAXN = 51010;

struct graph{
    struct edge{
        int t,n;
    } E[MAXE];
    int st[MAXN],en;
    void ade(int a,int b) {
        E[++en]=(edge){b,st[a]};
        st[a]=en;
    }
} Z,F,dom,T;

int clk,dfn[MAXN],fa[MAXN],xl[MAXN];
void dfs(int x) {
    dfn[x]=++clk;
    xl[clk]=x;
    for (int i=Z.st[x];i;i=Z.E[i].n) if (fa[x]!=Z.E[i].t&&!dfn[Z.E[i].t]) {
        fa[Z.E[i].t]=x;
        dfs(Z.E[i].t);
    }
}
int idom[MAXN],semi[MAXN];

struct UFS{
    int F[MAXN],bestp[MAXN];
    int ff(int x) {
        if (!F[x]) return x;
        int tmp=ff(F[x]);
        if (dfn[semi[bestp[x]]]>dfn[semi[bestp[F[x]]]]) bestp[x]=bestp[F[x]];
        return F[x]=tmp;
    }
    int getbestp(int x) {
        ff(x);
        return bestp[x];
    }
} ufs;

int N,M,flag[MAXN];

int main() {
    scanf("%d%d",&N,&M);
    for (int i=1,a,b;i<=M;i++) {
        scanf("%d%d",&a,&b);
        Z.ade(a,b);F.ade(b,a);
        /// edge a->b
    }
    dfs(1);
    for (int i=1;i<=N;i++) ufs.bestp[i]=semi[i]=i;
    for (int i=N;i>1;i--) {
        int x=xl[i],tmp=0x7fffffff;
        for (int j=F.st[x];j;j=F.E[j].n)
            tmp=min(tmp,dfn[semi[ufs.getbestp(F.E[j].t)]]);
        semi[x]=xl[tmp];
        dom.ade(semi[x],x);
        int f=fa[x];
        for (int j=dom.st[f];j;j=dom.E[j].n) {
            if (dfn[semi[ufs.getbestp(dom.E[j].t)]]<dfn[f])
                idom[dom.E[j].t]=ufs.getbestp(dom.E[j].t);
            else idom[dom.E[j].t]=semi[dom.E[j].t];
        }
        dom.st[f]=0;
        ufs.F[x]=fa[x];
    }
    for(int i=2;i<=N;i++)
        if(idom[xl[i]]!=semi[xl[i]])
            idom[xl[i]]=idom[idom[xl[i]]];
    /// idom[x] is the nearest dominator of x
    /// 1 is the source of the whole graph
}
