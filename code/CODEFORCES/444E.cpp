#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for (int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for (int i = x, _ = y; i >= _; i --)
const int MAXN = 3000 + 1000;
int n, sum;
int in[MAXN], out[MAXN];
struct Union_Find_Set {
	int f[MAXN];
	void Init(int N)
	{
		REP (i, 1, N)
			f[i] = i;
	}
	int Find(int x) { return x == f[x]? x : f[x] = Find(f[x]); }
	bool Union(int x, int y)
	{
		x = Find(x);
		y = Find(y);
		if (x == y)
			return 0;
			
		in[x] += in[y];
		out[x] += out[y];
		f[y] = x;
		
		if (in[x] + out[x] > sum)
			return 1;
		return 0;
	}
} t;
struct Edge {
	int u, v, w;
	Edge() {}
	Edge(int u, int v, int w):
		u(u), v(v), w(w){}
	bool operator < (const Edge &a) const {
		return w < a.w;
	}
} G[MAXN];
void Init()
{
	int u, v, w;
	
	scanf("%d", &n);
	t.Init(n);
	
	REP (i, 1, n - 1) {
		scanf("%d%d%d", &u, &v, &w);
		G[i] = Edge(u, v, w);
	}
	
	REP (i, 1, n) {
		scanf("%d", &out[i]);
		sum += out[i];
		in[i] = 1;
	}
}
void Solve()
{
	if (n == 1) {
		puts("0");
		return ;
	}
	
	int u, v;
	std::sort(G + 1, G + n);
	
	REP (i, 1, n - 1) {
		if (t.Union(G[i].u, G[i].v)) {
			printf("%d\n", G[i].w);
			return ;
		}
	}
}
int main()
{
	Init();
	Solve();
}
