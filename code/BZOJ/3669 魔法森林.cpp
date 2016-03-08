// BZOJ #3669
// Fuboat
// LCT (Edge)
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define lc ch[o][0]
#define rc ch[o][1]
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; } 
const int MAXN = 200000 + 1000, oo = 0x3f3f3f3f;
int n, m;
int ch[MAXN][2], maxv[MAXN][2], val[MAXN][2], node[MAXN], fa[MAXN], st[MAXN];
bool lazy[MAXN];

bool IsRoot(int o) 
{ return ch[fa[o]][0] != o && ch[fa[o]][1] != o; }

void Build(int pa, int o, int d)
{
	if(o)
		fa[o] = pa;
	if(pa)
		ch[pa][d] = o;
}

void Pushup(int o)
{
	maxv[o][1] = val[o][1];
	node[o] = o;
	if(Chkmax(maxv[o][1], maxv[lc][1]))
		node[o] = node[lc];
	if(Chkmax(maxv[o][1], maxv[rc][1]))
		node[o] = node[rc];
	// Don't mix 'maxv[o][1]' and 'maxv[o][0]' together!

	maxv[o][0] = val[o][0];
	Chkmax(maxv[o][0], maxv[lc][0]);
	Chkmax(maxv[o][0], maxv[rc][0]);
}

void Pushdown(int o)
{
	if(lazy[o]) {
		lazy[o] ^= 1;
		lazy[lc] ^= 1;
		lazy[rc] ^= 1;
		std::swap(lc, rc);
	}
}

void Rotate(int o)
{
	int pa, up, son, d;
	pa = fa[o];
	up = fa[pa];
	d = (ch[pa][1] == o);
	son = ch[o][!d];
	fa[o] = up;
	if(!IsRoot(pa))
		ch[up][ch[up][1] == pa] = o;
	
	Build(pa, son, d);
	Build(o, pa, !d);
	
	Pushup(pa);
	Pushup(o);
}
void Splay(int o)
{
	int top = 0, pa, up;
	st[++ top] = o;
	for(int i = o; !IsRoot(i); i = fa[i])
		st[++ top] = fa[i];
	rep(i, top, 1)
		Pushdown(st[i]);
	
	while(!IsRoot(o)) {
		pa = fa[o];
		up = fa[pa];
		if(!IsRoot(pa)) {
			if(ch[pa][0] == o ^ ch[up][0] == pa)
				Rotate(o);
			else 
				Rotate(pa);
		}
		Rotate(o);
	}
}

void Access(int o)
{
	int son = 0;
	while(o) {
		Splay(o);
		ch[o][1] = son;
		Pushup(o);
		son = o;
		// Don't foret the sentence above!
		o = fa[o];
	}
}

void MakeRoot(int o)
{
	Access(o);
	Splay(o);
	lazy[o] ^= 1;
}

void Link(int u, int v)
{
	MakeRoot(u);
	Splay(u);
	fa[u] = v;
}

void Cut(int o)
{
	MakeRoot(o);
	Splay(o);
	fa[lc] = fa[rc] = 0;
	lc = rc = 0;
}

void Split(int u, int v)
{
	MakeRoot(u);
	Access(v);
	Splay(v);
}

int FindRoot(int u)
{
	Access(u);
	Splay(u);
	while(ch[u][0])
		u = ch[u][0];
	return u;
}

void Link(int u, int v, int o)
{
	Link(u, o);
	Link(o, v);
}

struct Edge{
	int u, v, w1, w2;
	Edge(){}
	Edge(int u, int v, int w1, int w2):
		u(u), v(v), w1(w1), w2(w2){}
	bool operator < (const Edge &E) const {
		if(w1 != E.w1)
			return w1 < E.w1;
		return w2 < E.w2;
	}
} s[MAXN];

void Init()
{
	int u, v, w1, w2;

	scanf("%d%d", &n, &m);
	REP(i, 1, n)
		node[i] = i;
	REP(i, 1, m) {
		scanf("%d%d%d%d", &u, &v, &w1, &w2);
		s[i] = Edge(u, v, w1, w2);
	}

	std::sort(s + 1, s + m + 1);
	REP(i, 1, m) {
		val[i + n][0] = s[i].w1;
		val[i + n][1] = s[i].w2;
	}
}

void Solve()
{
	int u, v, w, o, ans = oo;
	REP(i, 1, m) {
		u = s[i].u;
		v = s[i].v;
		w = s[i].w2;
		o = i + n;
		
		if(FindRoot(u) == FindRoot(v)) {
			Split(u, v);
			if(maxv[v][1] <= w)
				continue;
			else
				Cut(node[v]);
		}
		Link(u, v, i + n);
		if(FindRoot(1) == FindRoot(n)) {
			Split(1, n);
			Chkmin(ans, maxv[n][0] + maxv[n][1]);
		}
	}
	if(ans == oo)
		ans = -1;
	printf("%d\n", ans);
}

int main()
{
	Init();
	Solve();
}
