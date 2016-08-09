#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll INF = 0x7fffffff;
ll A[10002][1002],nex[10002],R,C;
void pivot(int l,int o) {
    ll n=10001,t;
    for (int i=0;i<=R;i++) if (A[l][i]) {nex[n]=i;n=i;}nex[n]=-1;
    for (int i=0;i<=C;i++)
        if (i!=l&&(t=A[i][o])) {
            A[i][o]=0;
            for (int j=nex[10001];j!=-1;j=nex[j])
                A[i][j]+=A[l][j]*t;
        }

}
ll simplex() {
    for (;;) {
        ll outv=0,inl=0,minv=INF;
        for (int i=1;i<=R;i++) if (A[0][i]>0) {outv=i;break;}
        if (!outv) return A[0][0];
        for (int i=1;i<=C;i++) if (A[i][outv]<0&&A[i][0]<minv)
            minv=A[inl=i][0];
        pivot(inl,outv);
    }
}

int N,M;

int main(){
    scanf("%d%d",&N,&M);
    for (int i=1;i<=N;i++) scanf("%lld",&A[0][i]);
    for (int i=1,k;i<=M;i++) {
        scanf("%d",&k);
        while(k--) {
            int l,r;
            scanf("%d%d",&l,&r);
            for (int j=l;j<=r;j++) A[i][j]=-1;
        }
        scanf("%lld",&A[i][0]);
    }
    R=N;C=M;
    printf("%lld\n",simplex());
}







void pivot(int l,int o) {

    ///get_so-called_chain_table
    for (int i=1,t;i<=C;i++)
        if (i==l&&(t=A[i][o])) {
            A[i][o]=0;
            for (int j=next[MAXN];j!=-1;j=next[j])
                A[i][j]+=A[l][j]*t;
        }

}


void simplex(){
    for (;;) {
        int outv=0,minv=INF;
        for (int i=1;i<=R;i++) if (A[0][i]<0){outv=i;break;}
        if (!outv) return A[0][0];
        for (int i=1;i<=C;i++)
            if (A[i][outv]<0&&A[i][0]<minv)
                minv=A[inl=i][0];
        pivot(inl,outv);
    }
}
