// Codeforces #19E
// Fuboat
// Tree

/*
  Begin: 2016/2/1, around 19:30
  Spend: 3 hours    <----- Didn't understand the problem completely;
  Experience: Think about special situations in problems about graph, such as unconnected graph;
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 10000 + 100, MAXM = MAXN * 2;
int n, m, tote, tot;
int head[MAXN], next[MAXM], to[MAXM], flag[MAXN][2], deep[MAXN];
int FaWay[MAXN];
int work[MAXN];
int vis[MAXN];
std::vector<int> ans, BadEdge;

void AddEdge(int u, int v)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
}

void Build(int u, int fa, int D)
{
	int v, d;
	vis[u] = 1;
	deep[u] = D;

	for(int i = head[u]; i != 0; i = next[i]) {
		v = to[i];
		if(v == fa)
			continue ;
		if(!vis[v]) {
			FaWay[v] = (i + 1) / 2;
			Build(v, u, D + 1);
		} else if(deep[v] < deep[u]) {
			d = (deep[u] + deep[v]) % 2;
			flag[u][!d] ++;
			flag[v][!d] --;
			if(!d)
				BadEdge.push_back((i + 1) / 2);
		}
	}
}

void DDfs(int u)
{
	int v;
	for(int i = head[u]; i != 0; i = next[i]) {
		v = to[i];
		if(deep[v] == deep[u] + 1) {
			DDfs(v);
			flag[u][0] += flag[v][0];
			flag[u][1] += flag[v][1];
		}
	}

	if(flag[u][0] == 0 && flag[u][1] == tot)
		ans.push_back(FaWay[u]);
}

void Init()
{
	int u, v;
	scanf("%d%d", &n, &m);
	REP(i, 1, m) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
		AddEdge(v, u);
	}
}
void Solve()
{
	REP(i, 1, n)
		if(vis[i] == 0)
			Build(i, 0, 0);
			// ***!
			// It is possible that a node can't reaches another node!
			// ***!

	CLEAR(vis);
	tot = (int) BadEdge.size();
	if(tot == 0) {
		REP(i, 1, m)
			ans.push_back(i);
	} else {
		if(tot == 1)
			ans = BadEdge;
		REP(i, 1, n)
			if(deep[i] == 0)
				DDfs(i);
		std::sort(ans.begin(), ans.end());
	}

	printf("%d\n", (int) ans.size());
	REP(i, 0, (int) ans.size() - 1)
		printf(i? " %d" : "%d", ans[i]);
	puts("");
}
int main()
{
	Init();
	Solve();
}
