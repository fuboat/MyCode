// BZOJ #1036
// Fuboat
// LCT (for the first time)
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#define lc ch[o][0]
#define rc ch[o][1]
#define LL long long 
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int MAXN = 30000 + 1000, MAXQ = 200000 + 100, MAXVAL = 0x3f3f3f3f;
int ch[MAXN][2], fa[MAXN], st[MAXN], maxv[MAXN], val[MAXN];
bool lazy[MAXN];
LL sumv[MAXN];

inline bool IsRoot(int o)
// Check if the node is the root of the splay-tree that it belongs to;
{
	return ch[fa[o]][0] != o && ch[fa[o]][1] != o;
}

inline void Build(int pa, int o, int d)
{
	if(o)
		fa[o] = pa;
	if(pa)
		ch[pa][d] = o;
}

void Pushdown(int o)
{
	if(lazy[o]) {
		lazy[o] = false;
		lazy[lc] ^= 1;
		lazy[rc] ^= 1;
		std::swap(lc, rc);
	}
}

void Pushup(int o)
{
	if(!o)
		return ;
	maxv[o] = val[o];
	Chkmax(maxv[o], maxv[lc]);
	Chkmax(maxv[o], maxv[rc]);
	sumv[o] = sumv[lc] + sumv[rc] + val[o];
}

void Rotate(int o)
{
	int pa = fa[o], up = fa[pa], d = (ch[pa][1] == o);

	fa[o] = up;
	if(!IsRoot(pa)) // if 'pa' is Root of the splay tree, 'up' and 'pa' are not in the same splay-tree;
		Build(up, o, ch[up][1] == pa);
	Build(pa, ch[o][!d], d);
	Build(o, pa, !d);

	Pushup(pa);
	Pushup(o);
}

void Splay(int o)
{
	int pa, up, top = 0;
	
	st[++ top] = o;
	// Don't forget this!
	for(int i = o; !IsRoot(i); i = fa[i])
		st[++ top] = fa[i];
	while(top)
		Pushdown(st[top --]);
	
	while(!IsRoot(o)) {
		pa = fa[o];
		up = fa[pa];
		if(!IsRoot(pa)) { 
			if((ch[pa][0] == o) ^ (ch[up][0] == pa))
				Rotate(o);
			else Rotate(pa);
		}
		Rotate(o);
	}
}

void Access(int o)
{
	for(int i = 0; o; i = o, o = fa[o]) {
		Splay(o);
		ch[o][1] = i;
		Pushup(o);
	}
}

void MakeRoot(int o)
{
	Access(o);
	Splay(o);
	lazy[o] ^= 1;
}

void ChangeVal(int o, int x)
{
	Splay(o);
	val[o] = x;
	Pushup(o);
}

void Link(int u, int v)
{
	MakeRoot(u);
	fa[u] = v;
}

int GetMax(int u, int v)
{
	MakeRoot(u);
	Access(v);
	Splay(v);
	return maxv[v];
}

LL GetSum(int u, int v)
{
	MakeRoot(u);
	Access(v);
	Splay(v);
	return sumv[v];
}

int from[MAXN], to[MAXN];
char s[100];
main()
{
	int u, v, n, q, x, y;

	maxv[0] = - MAXVAL;
	// Remember!
	// 'maxv[0] = -inf'!
	// 'val[0] = -inf' is useless!
	scanf("%d", &n);
	REP(i, 1, n - 1) {
		scanf("%d%d", &u, &v);
		from[i] = u;
		to[i] = v;
		// Pay attention!
		// We can't use 'fa[u] = v' here!
		// Or a node may have two father?
	}

	REP(i, 1, n) {
		scanf("%d", &val[i]);
		Pushup(i);
	}

	REP(i, 1, n - 1)
		Link(from[i], to[i]);

	scanf("%d", &q);
	REP(i, 1, q) {
		scanf("%s%d%d", s, &x, &y);
		switch(s[1]) {
			case 'H': ChangeVal(x, y); break;
			case 'M': printf("%d\n", GetMax(x, y)); break;
			case 'S': printf("%lld\n", GetSum(x, y)); break;
		}
	}
}
