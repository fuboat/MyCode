// BZOJ 1016
// Fuboat
// Kruskal
// O(m*2^d)

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define CLEAR(a) memset(a, 0,sizeof(a))
#define LL long long
const int MAXN = 100 + 10, MAXM = 1000 + 10, MOD = 31011;
struct Edge{
	int u, v, w;
	bool operator < (const Edge &a)
	const { return w < a.w; }
	Edge(){}
	Edge(int u, int v, int w):
		u(u), v(v), w(w) {}
}E[MAXM];
int tote;

void AddEdge(int u, int v, int w)
{
	E[++ tote] = Edge(u, v, w); 
}

struct Union_Find{
	int f[MAXN];
	int Find(int x)
	{
		return x == f[x]? x : f[x] = Find(f[x]);
	}

	bool Union(int x, int y)
	{
		if((x = Find(x)) == (y = Find(y)))
			return false;

		f[x] = f[y] = std::min(x, y);
		return true;
	}

	void Init(int N)
	{
		REP(i, 1, N)
			f[i] = i; 
	}
}g;

int tot, need;
int dp[MAXN][MAXN];
Union_Find tmp;

void Search(int now, int to, int cnt, Union_Find G)
{
	if(now > to) {
		tot += (need == cnt);
		return;
	}
	
	int u = E[now].u, v = E[now].v;
	Union_Find tmp = G;

	if(tmp.Union(u, v))
		Search(now + 1, to, cnt + 1, tmp);
	Search(now + 1, to, cnt, G);
}

void Check(int from, int to, int N)
{
	int u, v;
	need = 0;
	tot = 0;

	REP(i, 1, N)
		g.Find(i);
	// Why it is need here?
	// If doing this first, the work in 'Search()' will be faster;

	tmp = g;
	REP(i, from, to) {
		if(g.Union(E[i].u, E[i].v))
			need ++;
	}

	Search(from, to, 0, tmp);
}

void Init(int N, int M)
{
	int u, v, w;
	REP(i, 1, M) {
		scanf("%d%d%d", &u, &v, &w);
		AddEdge(u, v, w); 
	}
}

void Kruskal(int N, int M)
{
	int u, v, j, ans = 1, all = 0;
	std::sort(E + 1, E + M + 1);
	
	REP(i, 1, M) {
		for(j = i; j <= M; j ++)
			if(j == M || E[j].w != E[j + 1].w)
				break;

		Check(i, j, N);
		ans = 1LL * ans * tot % MOD;
		i = j;
		all += need;
	}

	if(all != N - 1)
		ans = 0;
	// Special situation;
	// If all the edge can't make the graph a tree, there is no solution;
	printf("%d\n", ans); 
}

int main()
{
	int n, m, u, v;
	scanf("%d%d", &n, &m);
	g.Init(n);
	Init(n, m);
	Kruskal(n, m);
}
