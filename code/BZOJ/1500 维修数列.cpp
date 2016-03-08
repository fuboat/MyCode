// BZOJ #1500
// Fuboat
 
// Begin: 2016/2/2, 8:20
// Spend: 7 hours
// Finished before 10:00, then spent 5 hours to debug (&*^%&$^#%^#&$#@%*@!@%*%#!$!!!)
 
// - In some special situation, we need to use a node twice after deleted, because the space is not enough.
// - BUT!
// - Did you clear every node completely?
// - NO, I didn't...
// \(*_*)/...
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define CLEAR(a) memset(a, 0, sizeof(a))
#define MSET(a, x) memset(a, x, sizeof(a)) 
#define lc ch[o][0]
#define rc ch[o][1]
#define Set setv[o]
#define Flag flag[o]
#define Lmax lmax[o]
#define Rmax rmax[o]
#define Max  maxv[o]
#define Val  val[o]
#define Size size[o]
#define Sum  sumv[o]
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int MAXN = 1000000 + 100, oo = 3000;
void Readin(int &x)
{
    x = 0;
    int k = 1;
    char c = getchar();
    while(c < '0' || c > '9') {
        if(c == '-')
            k = -1;
        c = getchar();
    }
    while('0' <= c && c <= '9') {
        (x *= 10) += (int) c - '0';
        c = getchar();
    }
    x *= k;
}
namespace Splay_tree{
    using std::max;
    using std::min;
    using std::swap;
    int root, top, sz;
    int ch[MAXN][2];
    int sumv[MAXN], lmax[MAXN], rmax[MAXN], maxv[MAXN], size[MAXN], flag[MAXN], val[MAXN], fa[MAXN], st[MAXN], setv[MAXN];
    void Init(int N)
    {
        sz = N + 10;
        MSET(setv, 0x7f);
    }
    inline void Clear(int o)
    {
        Flag = Size = Sum = Lmax = Rmax = Val = Max = lc = rc = fa[o] = 0;
        Set = oo; //<--- 'Set' is 'oo', not '0'!
    }
    inline void GetFlag(int o)
    {
        Flag ^= 1;
        std::swap(Lmax, Rmax);
    }
    inline void GetSet(int o, int x)
    {
        int k = x < 0? 1 : Size;
        Val = Set = x;
        Sum = x * Size; //<------------- 'x * Size' !
        Lmax = Rmax = Max = x * k;
        // Don't forget 'Sum'!
    }
    void Pushdown(int o)
    {
        if(!o)
            return ;
        if(Flag) {
            Flag = 0;
            std::swap(lc, rc);
            GetFlag(lc);
            GetFlag(rc);
        }
        if(Set < oo) {
            GetSet(lc, Set);
            GetSet(rc, Set);
            Val = Set;
            Set = oo;
        }
    }
    void Pushup(int o)
    {
        if(!o)
            return ; 
        Pushdown(o);
        Size = size[lc] + size[rc] + 1;
        Sum = sumv[lc] + sumv[rc] + val[o];
        if(lc == 0 && rc == 0) {
            Sum = Lmax = Rmax = Max = Val;
        } else if(lc == 0) {
            Lmax = Val + max(lmax[rc], 0);
            Rmax = max(rmax[rc], sumv[rc] + Val);
            Max = max(maxv[rc], max(Lmax, Rmax));
        } else if(rc == 0) {
            Rmax = Val + max(rmax[lc], 0);
            Lmax = max(lmax[lc], sumv[lc] + Val);
            Max = max(maxv[lc], max(Rmax, Lmax));
        } else if(lc != 0 && rc != 0) {
            Rmax = max(rmax[rc], sumv[rc] + Val + max(rmax[lc], 0));
            Lmax = max(lmax[lc], sumv[lc] + Val + max(lmax[rc], 0));
            Max = max(max(maxv[lc], maxv[rc]), max(Rmax, Lmax));
        }
        Chkmax(Max, max(rmax[lc], 0) + Val + max(lmax[rc], 0));
    }
    void FaSon(int pa, int o, int d)
    {
        if(pa)
            ch[pa][d] = o;
        if(o)
            fa[o] = pa;
    }
    void Rotate(int o)
    {
        int pa = fa[o], up = fa[pa], d;
        Pushdown(pa);
        Pushdown(o);
         
        d = (ch[pa][1] == o);
        FaSon(up, o, ch[up][1] == pa);
        FaSon(pa, ch[o][!d], d);
        FaSon(o, pa, !d);
         
        Pushup(pa);
        Pushup(o);
    }
    void Splay(int o, int F)
    {
        int pa, up;
        Pushup(o);
        while(fa[o] != F) {
            pa = fa[o];
            up = fa[pa];
            if(up != F) {
                if(ch[up][0] == pa ^ ch[pa][0] == o)
                    Rotate(o);
                else Rotate(pa);
            }
            Rotate(o);
        }
        Pushdown(o);
        if(!F)
            root = o;
    }
    int Get(int o, int k)
    {
        Pushdown(o);
        while(size[lc] + 1 != k) {
            if(k <= size[lc]) {
                o = lc;
            } else {
                k -= size[lc] + 1;
                o = rc;
            }
            Pushdown(o);
        }
        return o;
    }
    void Insert(int o, int *a, int N)
    {
        int son, now, next;
        o = Get(root, o + 1);
        Splay(o, 0);
        son = Get(rc, 1);
        Splay(son, 0);
        now = o;
         
        REP(i, 1, N) {
            next = top? st[top --] : ++ sz; 
            val[next] = a[i];
            FaSon(now, next, 1);
            now = next;
        }
        Splay(now, 0);
    }
    void Remove(int o)
    {
        if(!o)
            return ;
 
        Remove(lc);
        Remove(rc);
        Clear(o);
        st[++ top] = o;
    }
    void Delete(int o, int N)
    {
        int son;
        o = Get(root, o);
        Splay(o, 0);
        son = Get(rc, N + 1);
        Splay(son, o);
        Remove(ch[son][0]);
        ch[son][0] = 0;
        Pushup(son);
        Pushup(o);
    }
    void Reverse(int o, int N)
    {
        int son;
        o = Get(root, o);
        Splay(o, 0);
        son = Get(rc, N + 1);
        Splay(son, o);
        GetFlag(ch[son][0]);
        Pushup(son);
        Pushup(o);
    }
    void Modify(int o, int N, int x)
    {
        int son;
        o = Get(root, o);
        Splay(o, 0);
        son = Get(rc, N + 1);
        Splay(son, o); 
        GetSet(ch[son][0], x);
        Pushup(son);
        Pushup(o);
    }
    void Build(int *a, int l, int r, int pa, int d)
    {
        if(l > r)
            return ;
        int mid = (l + r) / 2;
        if(!pa)
            root = mid;
        FaSon(pa, mid, d);
        if(l != r) {
            Build(a, l, mid - 1, mid, 0);
            Build(a, mid + 1, r, mid, 1);
        }
        Pushup(mid);
    }
    int GetSum(int o, int N)
    {
        int son;
        o = Get(root, o);
        Splay(o, 0);
        son = Get(rc, N + 1);
        Splay(son, o);
        return sumv[ch[son][0]];
    }
    int GetMax()
    {
        int u = Get(root, 1);
        int v = Get(root, size[root]);
        Splay(u, 0);
        Splay(v, u);
        return maxv[ch[v][0]];
    }
    void Print(int o)
    {
        if(!o)
            return ;
        Pushdown(o);
        Print(lc);
        Print(rc);
    }
}
 
int n, m;
int a[MAXN]; 
char s[100];
int main()
{
    int x, y, pos;
    using namespace Splay_tree;
    Readin(n);
    Readin(m);
    Init(n);
    REP(i, 1, n)
        Readin(val[i + 1]);
    val[1] = val[n + 2] = -oo;
    Build(a, 1, n + 2, 0, 0);
    REP(i, 1, m) {
        scanf("%s", s);
        switch(s[2]) {
            case 'S': 
                Readin(pos);
                Readin(x);
                REP(i, 1, x)
                    Readin(a[i]);
                Insert(pos, a, x);
                break;
            case 'L':
                Readin(pos);
                Readin(x);
                Delete(pos, x);
                break;
            case 'K':
                Readin(pos);
                Readin(x);
                Readin(y);
                Modify(pos, x, y);
                break;
            case 'V':
                Readin(pos);
                Readin(x);
                Reverse(pos, x);
                break;
            case 'T':
                Readin(pos);
                Readin(x);
                printf("%d\n", GetSum(pos, x));
                break;
            case 'X':
                printf("%d\n", maxv[root]);
                break;
        }
    }
}
