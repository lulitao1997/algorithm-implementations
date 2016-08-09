#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 2001000,INF = 1099999999;

int idx;
struct node {
    int lc,rc,max[2],min[2],a[2];
    node(){max[0]=max[1]=-INF;min[0]=min[1]=INF;lc=rc=a[0]=a[1]=0;}
    node(int x,int y) {a[0]=max[0]=min[0]=x;a[1]=max[1]=min[1]=y;lc=rc=0;}
    bool operator<(node b) const {return a[idx]<b.a[idx]||a[idx]==b.a[idx]&&a[!idx]<b.a[!idx];}
} T[MAXN];

inline void update(int o) {
    T[o].min[0]=min(T[o].min[0],min(T[T[o].lc].min[0],T[T[o].rc].min[0]));
    T[o].min[1]=min(T[o].min[1],min(T[T[o].lc].min[1],T[T[o].rc].min[1]));
    T[o].max[0]=max(T[o].max[0],max(T[T[o].lc].max[0],T[T[o].rc].max[0]));
    T[o].max[1]=max(T[o].max[1],max(T[T[o].lc].max[1],T[T[o].rc].max[1]));
}

int nn,root;
int build(int l,int r,int d) {
    if (l>r) return 0;
    int mid=(l+r)>>1;
    idx=d;
    nth_element(T+l,T+mid,T+r+1);
    T[mid]=node(T[mid].a[0],T[mid].a[1]);
    T[mid].lc=build(l,mid-1,!d);
    T[mid].rc=build(mid+1,r,!d);
    update(mid);
    return mid;
}

int dis(node p,const node&o) {
    long long ans=0;
    if (p.a[0]<=o.min[0]) ans+=o.min[0]-p.a[0];
    if (p.a[0]>=o.max[0]) ans+=p.a[0]-o.max[0];
    if (p.a[1]<=o.min[1]) ans+=o.min[1]-p.a[1];
    if (p.a[1]>=o.max[1]) ans+=p.a[1]-o.max[1];
    return ans>INF?INF:ans;
}

int query(int o,const node&p) {
    if (!o) return INF;
    int ans=abs(p.a[0]-T[o].a[0])+abs(p.a[1]-T[o].a[1]),
        dl=dis(p,T[T[o].lc]),dr=dis(p,T[T[o].rc]);
    if (dl<dr) {
        if (dl<ans) ans=min(ans,query(T[o].lc,p));
        if (dr<ans) ans=min(ans,query(T[o].rc,p));
    }
    else {
        if (dr<ans) ans=min(ans,query(T[o].rc,p));
        if (dl<ans) ans=min(ans,query(T[o].lc,p));
    }
    return ans;
}

void insert(node p) {
    T[++nn]=p;
    int np=root;idx=0; ///root!=1 !!!
    while (np) {
        T[np].min[0]=min(T[np].min[0],T[nn].min[0]);
        T[np].min[1]=min(T[np].min[1],T[nn].min[1]);
        T[np].max[0]=max(T[np].max[0],T[nn].max[0]);
        T[np].max[1]=max(T[np].max[1],T[nn].max[1]);
        if (p<T[np]) {
            if (!T[np].lc) {T[np].lc=nn;break;}
            np=T[np].lc;
        }
        else {
            if (!T[np].rc) {T[np].rc=nn;break;}
            np=T[np].rc;
        }
        idx=!idx;
    }
}

int N,M;
int main () {
    freopen("2648.in","r",stdin);freopen("2648.out","w",stdout);
    scanf("%d%d",&N,&M);
    for (int i=1,x,y;i<=N;i++) {
        scanf("%d%d",&x,&y);
        T[i]=node(x,y);
    }
    root=build(1,N,0);nn=N;
    int ch,x,y,haha=0;
    while (M--) {
        scanf("%d%d%d",&ch,&x,&y);
        node p=node(x,y);
        if (ch==1)
            insert(p);
        if (ch==2) printf("%d\n",query(root,p));
    }
}
