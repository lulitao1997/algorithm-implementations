#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;
const int MAXN = 100100;

char S[MAXN];
int len;
int sa[MAXN],rnk[MAXN],tsa[MAXN],trnk[MAXN],sum[MAXN],H[MAXN];

void jssort(int d)
{
    for (int i=0; i<=len; i++) sum[i]=0;
    for (int i=1; i<=len; i++) sum[rnk[i+d]]++;
    for (int i=1; i<=len; i++) sum[i]+=sum[i-1];
    for (int i=len; i>=1; i--) tsa[sum[rnk[i+d]]--]=i;

    for (int i=0; i<=len; i++) sum[i]=0;
    for (int i=1; i<=len; i++) sum[rnk[i]]++;
    for (int i=1; i<=len; i++) sum[i]+=sum[i-1];
    for (int i=len; i>=1; i--) sa[sum[rnk[tsa[i]]]--]=tsa[i];

    trnk[sa[1]]=1;
    for (int i=2; i<=len; i++)
        trnk[sa[i]]=trnk[sa[i-1]]+(rnk[sa[i]]!=rnk[sa[i-1]]||rnk[sa[i]+d]!=rnk[sa[i-1]+d]);
    for (int i=1; i<=len; i++)
        rnk[i]=trnk[i];
}

int main()
{
    scanf("%s",S+1);
    len=strlen(S+1);
    //reverse(S+1,S+1+len);
    for (int i=1; i<=len; i++) sum[S[i]]++;
    for (int i=1; i<=255; i++) sum[i]+=sum[i-1];
    for (int i=len; i>=1; i--) sa[sum[S[i]]--]=i;
    rnk[sa[1]]=1;
    for (int i=2; i<=len; i++) rnk[sa[i]]=rnk[sa[i-1]]+(S[sa[i]]!=S[sa[i-1]]);

    for (int j=0; (1<<j)<=len; j++) jssort(1<<j);

    for (int i=1; i<=len; i++)
    {
        if (rnk[i]==len) continue;
        int o=rnk[i],n=sa[o+1];
        while (S[i+H[o]]==S[n+H[o]])
            H[o]++;
        H[rnk[i+1]]=max(H[o]-1,0);
    }
    for (int i=1;i<=len;i++)
    {
        string tmps(S+sa[i]);
        //reverse(tmps.begin(),tmps.end());
        printf("%d %s\n",H[i],tmps.data());
    }
    //for (int i=1;i<=len;i++) printf("%d %s\n",H[i],S+sa[i]);
}


















