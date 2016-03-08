// BZOJ #1040
// Fuboat
// DP-in-tree
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define LL long long
#define REP(i, x, y) for (int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for (int i = x, _ = y; i >= _; i --)
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
const int MAXN = 1000000 + 1000, MAXM = MAXN;
using std::max;
using std::vector;
struct Edge{
	int u, v, flag;
	Edge() {}
	Edge(int u, int v):
		u(u), v(v), flag(0){}
	int Get(int x)
	{ return u != x? u : v; }
} edges[MAXM];
vector<int> G[MAXN];
LL dp[MAXN][2];
int s[MAXN], vis[MAXN];
int tote, n, cur = 1;
LL ans;

void AddEdge(int u, int v)
{
	static int tote;
	edges[++ tote] = Edge(u, v);
	G[u].push_back(tote);
	G[v].push_back(tote);
}

void Dfs(int u)
{
	//printf("Dfs(u = %d, fa = %d)\n", u, fa);
	int v;
	vis[u] = cur;
	dp[u][0] = 0;
	dp[u][1] = s[u];
	
	REP (i, 0, G[u].size() - 1) {
		Edge &E = edges[G[u][i]];
		v = E.Get(u);
		if (vis[v] == cur)
			continue;
			
		Dfs(v);
		dp[u][0] += max(dp[v][0], dp[v][1]);
		dp[u][1] += dp[v][0];
	}
}

LL TreeDP(int u)
{
	//printf("TreeDP(%d)\n", u);
	int v;
	cur ++;
	dp[u][0] = 0;
	vis[u] = cur;
	// Don't forget!
	
	REP (i, 0, G[u].size() - 1) {
		Edge &E = edges[G[u][i]];
		v = E.Get(u);	
		
		if (vis[v] != cur) {
			Dfs(v);
			dp[u][0] += max(dp[v][0], dp[v][1]);
		}
	}
	return dp[u][0];
}

bool FindCircle(int u)
{
	vis[u] = cur;
	int v;
	
	REP (i, 0, G[u].size() - 1) {
		Edge &E = edges[G[u][i]];
		if (E.flag == 1)
			continue;
			
		E.flag = 1;
		v = E.Get(u);
		if (vis[v]) { 
			ans += max(TreeDP(u), TreeDP(v)); 
			return true;	
		} else if (FindCircle(v))
			return true;
	}
	return false;
}

main()
{
	#ifndef ONLINE_JUDGE
		freopen("1040.in", "r", stdin);
		freopen("1040.out", "w", stdout);
	#endif
	int v;
	
	scanf("%d", &n);
	REP (u, 1, n) {
		scanf("%d%d", &s[u], &v);
		AddEdge(u, v);
		// Don't Add Edges twice!
	}
	
	REP (u, 1, n)
		if (!vis[u])
			FindCircle(u);
			
	printf("%lld\n", ans);
	
	#ifndef ONLINE_JUDGE
		fclose(stdin);
		fclose(stdout);
	#endif
}
