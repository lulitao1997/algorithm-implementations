#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

struct node {
    int c,rev,size,ch[2],fa,lr;
} T[101000];
int nn,root;

void setch(int f,int x,int lr) {
    T[x].fa=f;
    T[x].lr=lr;
    T[f].ch[lr]=x;
    T[f].size=T[T[f].ch[0]].size+T[T[f].ch[1]].size+1;
}

void pushdown(int x) {
    if (!T[x].rev) return;
    T[x].rev=0;
    swap(T[x].ch[0],T[x].ch[1]);
    T[T[x].ch[0]].rev^=1;
    T[T[x].ch[1]].rev^=1;
    T[T[x].ch[0]].lr=0;
    T[T[x].ch[1]].lr=1;
}

void rot(int f,int lr) {
    int g=T[f].fa,x=T[f].ch[lr];
    if (f==root) {T[x].fa=T[x].lr=0;root=x;}
    else setch(g,x,T[f].lr);
    setch(f,T[x].ch[lr^1],lr);
    setch(x,f,lr^1);
}

int stk[101000],top;

void splay(int x,int b) {
    int f=x,g;
    top=0;
    while (f) {stk[++top]=f;f=T[f].fa;}
    while (top) pushdown(stk[top--]);

    while (T[x].fa!=b) {
        f=T[x].fa;g=T[f].fa;
        if (f==root||g==b) {rot(f,T[x].lr);return;}
        if (T[x].lr==T[f].lr) rot(g,T[f].lr);
        rot(f,T[x].lr);
    }
}

int findkth(int x,int k) {
    pushdown(x);
    int ls=T[T[x].ch[0]].size;
    if (ls==k-1) return x;
    if (ls>=k) return findkth(T[x].ch[0],k);
    return findkth(T[x].ch[1],k-ls-1);
}

int N,M;

void prt(int o) {
    if (!o) return;
    pushdown(o);
    prt(T[o].ch[0]);
    if (T[o].c<=N&&T[o].c>=1)
        printf("%d ",T[o].c);
    prt(T[o].ch[1]);
}

int build(int l,int r) {
    if (l>r) return 0;
    int mid=l+r>>1,o=++nn;
    T[o].c=mid;T[o].size=1;
    setch(o,build(l,mid-1),0);
    setch(o,build(mid+1,r),1);
    return o;
///       ***
}

int main(){
    scanf("%d%d",&N,&M);
    root=build(0,N+1);
    while (M--) {
        cerr<<"tot:"<<T[root].size<<endl;
        int l,r,lp,rp;
        scanf("%d%d",&l,&r);
        l++;r++;
        lp=findkth(root,l-1);rp=findkth(root,r+1);
        splay(lp,0);splay(rp,root);
        T[T[T[root].ch[1]].ch[0]].rev^=1;
    }
    prt(root);
}
