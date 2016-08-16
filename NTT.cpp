#include <bits/stdc++.h>
using namespace std;
const int MAXN = 4.1e5; /// 4 times larger

const int MOD = 998244353;
const int NR = 42;

/// MOD-1 is the first number satisfying NR^x = 1
/// w_n ^ N =1
/// w_n = NR^( (MOD-1) / n ), noticed that (MOD-1) | 2^k
/// w means w^k_n , k_th root of unity

//! remember to call "get_wn()" at the beginning
typedef long long ll;

inline int fapow(int a, int b)
{
    int ans=1;
    for(;b;b>>=1,a=(ll)a*a%MOD)
        if(b&1) ans=(ll)ans*a%MOD;
    return ans;
}

int w_n[30];
void get_wn() {
	for (int i=0;i<30;i++)
		w_n[i]=fapow(NR,(MOD-1)/(1<<i));
}

inline void rader(int F[],int n) {
    int j=n>>1;
    for (int i=1;i<n-1;i++) {
		if (i<j) swap(F[i],F[j]);
		int k=n>>1;
		while (j>=k) {j-=k;k>>=1;}
		if (j<k) j+=k;
    }
}
void NTT(int F[],int n,int typ=1) { ///1 for DFT,-1 for IDFT
	rader(F,n);
	for (int h=2,p=1;h<=n;h<<=1,p++) {
		int wn=(typ==1)?w_n[p]:fapow(w_n[p],MOD-2);
		for (int i=0;i<n;i+=h) {
			int w=1;
			for (int j=i;j<i+h/2;j++) {
				int u=F[j],v=(ll)w*F[j+h/2]%MOD;
				F[j]=(u+v)%MOD;
				F[j+h/2]=(u-v+MOD)%MOD;
				w=(ll)w*wn%MOD;
			}
		}
	}
	if (typ==-1) {
		int invn=fapow(n,MOD-2);
		for (int i=0;i<n;i++) F[i]=(ll)F[i]*invn%MOD;
	}
}
void Convolution(const vector<int>& A,const vector<int>& B,vector<int>& C) {
	static int Fa[MAXN],Fb[MAXN];
	size_t len=1;
	while (len<2*max(A.size(),B.size())) len<<=1;
	for (size_t i=0;i<len;i++) Fa[i]=i<A.size()?A[i]:0;
	for (size_t i=0;i<len;i++) Fb[i]=i<B.size()?B[i]:0;
	NTT(Fa,len,1);NTT(Fb,len,1);
    for (size_t i=0;i<len;i++) Fa[i]=(ll)Fa[i]*Fb[i]%MOD;
    NTT(Fa,len,-1);
    C.resize(A.size()+B.size());
    for (size_t i=0;i<A.size()+B.size();i++) C[i]=Fa[i];
}

int main() {
	get_wn();
}
//#pragma GCC pop_options
