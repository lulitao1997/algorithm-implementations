#include <bits/stdc++.h>
using namespace std;

typedef complex<double> cplx;
const double PI = M_PI;
const int MAXN = 4.1e5;
void rader(cplx F[],int n) {
    int j=n>>1;
    for (int i=1;i<n-1;i++) {
		if (i<j) swap(F[i],F[j]);
		int k=n>>1;
		while (j>=k) {j-=k;k>>=1;}
		if (j<k) j+=k;
    }
}
void FFT(cplx F[],int n,int typ=1) { ///1 for DFT,-1 for IDFT
	rader(F,n);
	for (int h=2;h<=n;h<<=1) {
		cplx wn=polar(1.,typ*2*PI/h);
		for (int i=0;i<n;i+=h) {
			cplx w(1);
			for (int j=i;j<i+h/2;j++) {
				cplx u=F[j],v=w*F[j+h/2];
				F[j]=u+v;
				F[j+h/2]=u-v;
				w*=wn;
			}
		}
	}
	if (typ==-1) for (int i=0;i<n;i++) F[i]/=n;
}
void Convolution(const vector<double>& A,const vector<double>& B,vector<double>& C) {
	static cplx Fa[MAXN],Fb[MAXN];
	size_t len=1;
	while (len<2*max(A.size(),B.size())) len<<=1;
	for (size_t i=0;i<len;i++) Fa[i]=i<A.size()?A[i]:0;
	for (size_t i=0;i<len;i++) Fb[i]=i<B.size()?B[i]:0;
	FFT(Fa,len,1);FFT(Fb,len,1);
    for (size_t i=0;i<len;i++) Fa[i]*=Fb[i];
    FFT(Fa,len,-1);
    C.resize(A.size()+B.size());
    for (size_t i=0;i<A.size()+B.size();i++) C[i]=Fa[i].real();
}

int main() {

}
