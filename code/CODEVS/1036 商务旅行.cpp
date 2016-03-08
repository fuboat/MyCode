// CodeVS1036 
// Fuboat 
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define X first
#define Y second
using std::pair;
using std::vector;
const int MAXN = 40000 + 100;
int ans[MAXN], deep[MAXN], lca[MAXN];
int head[MAXN], to[MAXN], next[MAXN];
int tote;
void AddEdge(int u, int v)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
}
struct Tarjan{
	vector<int> with[MAXN], number[MAXN];
	int f[MAXN];
	int Find(int x){ return x == f[x]? x : f[x] = Find(f[x]); }
	void Dfs(int u, int d)
	{
		int v;
		deep[u] = d;
		f[u] = u;
		REP(i, 0, with[u].size() - 1){
			v = with[u][i];
			if(f[v])
				lca[number[u][i]] = Find(f[v]);
		}
		for(int i = head[u]; i; i = next[i]){
			v = to[i];
			if(!f[v]){
				Dfs(v, d + 1);
				f[v] = u;
				// Warning!
				//use this When (!f[v]) == true(写在这个大括号里面).
			}
		}
	}
	void Init(int *que, int N)
	{
		int x, y;
		REP(i, 1, N - 1){
			x = que[i];
			y = que[i + 1];
			with[x].push_back(y);
			with[y].push_back(x);
			number[x].push_back(i);
			number[y].push_back(i);
		}
	}
}t;
int que[MAXN];
int n, m;
void Init()
{
	int u, v;
	scanf("%d", &n);
	REP(i, 1, n - 1){
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
		AddEdge(v, u);
	}
	scanf("%d%", &m);
	REP(i, 1, m)
		scanf("%d", &que[i]);
}
void Solve()
{
	int x, y, ans(0);
	t.Init(que, m);
	t.Dfs(1, 1);
	REP(i, 1, m - 1){
		x = que[i];
		y = que[i + 1];
		ans += deep[x] - deep[lca[i]] + deep[y] - deep[lca[i]];
	}
	printf("%d\n", ans);
}
int main()
{
	Init();
	Solve();
}
