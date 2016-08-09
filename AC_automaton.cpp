
struct node {
    int c,fa,son[4],fail,isend;
} T[110000];
int nn;

int TR[256];

void addstr(const char s[],int l) {
    int np=0;
    for (int i=0; i<l; i++) {
        int&o=T[np].son[TR[s[i]]];
        if (!o) {
            o=++nn;
            T[o].c=TR[s[i]];
            T[o].fa=np;
        }
        np=o;
    }
    T[np].isend=true;
}
void build_fail() {
    queue<int> Q;
    Q.push(0);
    while (!Q.empty()) {
        int f=Q.front();
        Q.pop();
        if (T[f].fa) {
            int t=T[f].fa;
            do {
                t=T[t].fail;
                int o=T[t].son[T[f].c];
                if (o) {
                    T[f].fail=o;
                    T[f].isend|=T[o].isend;
                    break;
                }
            } while(t);
        }
        for (int i=0; i<4; i++) if (T[f].son[i])
            Q.push(T[f].son[i]);
    }
}

int next(int x,int c) {
    while (!T[x].son[c]&&x) {
        x=T[x].fail;
    }
    return T[x].son[c];
}
