#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct node {
    int fa,go[26],max,val;
} T[530000];
int nn=1,last=1,root=1;

void extend(int x) {
    int p=last,np=last=++nn;
    T[np].max=T[p].max+1;
    T[np].val=T[p].val+1;
    while (!T[p].go[x]&&p) {
        T[p].go[x]=np;
        p=T[p].fa;
    }
    if (p==0) T[np].fa=root;
    else {
        int q=T[p].go[x];
        if (T[q].max==T[p].max+1)
            T[np].fa=q;
        else {
            int nq=++nn;
            T[nq].max=T[p].max+1;
            for (int i=0;i<26;i++) T[nq].go[i]=T[q].go[i];
            T[nq].fa=T[q].fa;
            T[q].fa=T[np].fa=nq;
            while (p&&T[p].go[x]==q) {
                T[p].go[x]=nq;
                p=T[p].fa;
            }
        }
    }
}

char S1[260000],S2[260000];
int l1,l2,nowpos=1,ans,len;
int main (){
    scanf("%s%s",S1,S2);
    l1=strlen(S1);l2=strlen(S2);
    for (int i=0;i<l1;i++) extend(S1[i]-'a');
    for (int i=1;i<=nn;i++) cerr<<T[i].fa<<' '<<T[i].val<<' '<<T[i].max<<endl;


    for (int i=0;i<l2;i++) {
        if (T[nowpos].go[S2[i]-'a']) {len++;nowpos=T[nowpos].go[S2[i]-'a'];}
        else {
            while (nowpos&&!T[nowpos].go[S2[i]-'a'])  nowpos=T[nowpos].fa;
            if (!nowpos) {
                len=0;
                nowpos=1;
            }
            else {
                len=min(len+1,T[nowpos].max+1);
                nowpos=T[nowpos].go[S2[i]-'a'];
            }
        }
        ans=max(ans,len);
        printf("%d>",len);
    }
    printf("%d\n",ans);
}
