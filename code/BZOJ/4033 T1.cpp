// BZOJ #4033
// Fuboat
// DP-in-tree
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#define LL long long
#ifdef WIN32
#define ll "%I64d"
#else
#define ll "%lld"
#endif
#define REP(i, x, y) for (int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for (int i = x, _ = y; i >= _; i --)
inline bool Chkmax(LL &x, LL y) { return y > x? x = y, true : false; }
using std::min;
const int MAXN = 2000 + 100, MAXM = MAXN * 2;
LL f[MAXN][MAXN];
int size[MAXN], head[MAXN], to[MAXM], val[MAXM], next[MAXM];
bool vis[MAXN];
int n, k, tote;

void AddEdge(int u, int v, int w)
{
	to[++ tote] = v;
	val[tote] = w;
	next[tote] = head[u];
	head[u] = tote;
}

void Dfs(int u, int w)
{
	int v;
	LL *F = f[u];
	size[u] = 1;
	vis[u] = true;
	for (int it = head[u]; it; it = next[it]) {
		v = to[it];
		if (vis[v])
			continue;
			
		Dfs(v, val[it]);
		rep (i, min(k, size[u]), 0)
			rep (j, min(size[v], k - i), 0)
				Chkmax(F[i + j], F[i] + f[v][j]);

		size[u] += size[v];
	}
	
	REP (i, 0, min(k, size[u]))
		F[i] += 1LL * (1LL * i * (k - i) + 1LL * (size[u] - i) * (n - k - (size[u] - i))) * w;
}

int main()
{
	int u, v, w = 0;
	scanf("%d%d", &n, &k);
	
	REP (i, 1, n - 1) {
		scanf("%d%d%d", &u, &v, &w);
		AddEdge(u, v, w);
		AddEdge(v, u, w);
	}
	
	Dfs(1, 0);
	printf(ll"\n", f[1][k]);
	
	return 0;
}
