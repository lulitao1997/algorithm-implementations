#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;


const int INF=0x7fffffff;
void upd(int&x,int y){if(y>x) x=y;}
struct graph{
	struct edge{
		int nex,to,flow,v,c;
	} E[81000];
	int st[500],d[500],pre[500],pmin[500],en,vn,S,T;bool inq[500];

	int maxflow,mincost;

	void clear(){
		en=vn=S=T=maxflow=mincost=0;
		memset(st,0,sizeof(st));
		memset(d,0,sizeof(d));
	}
	graph(){
		clear();
	}

	void add_edge(int a,int b,int v,int cost){
		E[++en]=(edge){st[a],b,0,v,cost};
		st[a]=en;
		E[++en]=(edge){st[b],a,v,v,-cost};
		st[b]=en;///               ^
		upd(vn,a);upd(vn,b);
	}
	inline int rev(int x){if (x&1) return x+1;return x-1;}

	bool SPFA(){
		queue<int> Q;
		for (int i=0;i<=vn;i++) {d[i]=INF;pre[i]=0;}

		Q.push(S);inq[S]=true;d[S]=0;pmin[S]=INF;pre[S]=0;
		while (!Q.empty()){
			int f=Q.front();
			for (int i=st[f];i;i=E[i].nex)
				if ((E[i].v-E[i].flow)&&d[f]+E[i].c<d[E[i].to]){
					d[E[i].to]=d[f]+E[i].c;
					pre[E[i].to]=rev(i);
					pmin[E[i].to]=min(E[i].v-E[i].flow,pmin[f]);
					if (!inq[E[i].to]){
						Q.push(E[i].to);
						inq[E[i].to]=true;
					}
				}
			Q.pop();
			inq[f]=false;
		}

		if (d[T]==INF) return false;

		maxflow+=pmin[T];
		mincost+=d[T]*pmin[T];

		int now=T;
		while (now!=S){
			E[pre[now]].flow-=pmin[T];
			E[rev(pre[now])].flow+=pmin[T];
			now=E[pre[now]].to;
		}
		return true;
	}

	void maxflow_mincost(int s,int t){
		S=s;T=t;
		maxflow=mincost=0;
		while (SPFA());
	}
} G;

int main(){

}
