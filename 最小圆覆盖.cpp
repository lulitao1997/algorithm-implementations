#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 500001;
const double eps=1e-8;
int N;

struct point {
    double x,y;
} P[MAXN];

struct circle {
    point o;double r;
};

double dis(point a,point b) {
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
bool eq(point a,point b) {return abs(a.x-b.x)<eps&&abs(a.y-b.y)<eps;}
circle haha(point a,point b) {return (circle){(point){(a.x+b.x)/2,(a.y+b.y)/2},dis(a,b)/2};}
circle haha(point a,point b,point c) {
    if (eq(a,b)) return haha(b,c);
    if (eq(a,c)) return haha(b,c);
    if (eq(b,c)) return haha(a,c);
    point ret;
    double a1=b.x-a.x,b1=b.y-a.y,c1=(a1*a1+b1*b1)/2;
    double a2=c.x-a.x,b2=c.y-a.y,c2=(a2*a2+b2*b2)/2;
    double d=a1*b2-a2*b1;
    ret=(point){a.x+(c1*b2-c2*b1)/d,a.y+(a1*c2-a2*c1)/d};
    return (circle){ret,dis(ret,c)};
}

int main () {
    //freopen("1.in","r",stdin);
    srand(25458);
    while (scanf("%d",&N)!=EOF&&N) {
        for (int i=0;i<N;i++) scanf("%lf%lf",&P[i].x,&P[i].y);
        //cerr<<"read complete"<<endl;
        random_shuffle(P,P+N);
        circle now=haha(P[0],P[0]);
        for (int i=1;i<N;i++)
            if (dis(P[i],now.o)>now.r) {
                now=haha(P[i],P[i]);
                for (int j=0;j<i;j++) {
                    if (dis(P[j],now.o)>now.r) {
                        now=haha(P[i],P[j]);
                        for (int k=0;k<j;k++)
                            if (dis(P[k],now.o)>now.r)
                                now=haha(P[i],P[j],P[k]);
                    }
                }
            }
        printf("%.2lf %.2lf %.2lf\n",now.o.x,now.o.y,now.r);
    }
}
