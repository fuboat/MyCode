// BZOJ #1093
// Fuboat
// SCC
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
#include <vector>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
bool Chkmax(int &x, int y) { return y > x? x = y, true : false; }
bool Chkmin(int &x, int y) { return y < x? x = y, true : false; }
const int MAXN = 1e5 + 1e3, MAXM = 1e6 + 1e3;

int n, m;
int MOD;

int tote;
int head[MAXN], to[MAXM], next[MAXM];

std::vector<int> E[MAXN];
int in[MAXN], f[MAXN];
int ans[MAXN];

void AddEdge(int u, int v)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
}

int dfs_clock, totscc;
int dfn[MAXN], low[MAXN], sccid[MAXN], size[MAXN], vis[MAXN];
std::stack<int> st;

void Dfs(int u)
{
	int v;

	dfn[u] = low[u] = ++ dfs_clock;
	st.push(u);

	for(int i = head[u]; i; i = next[i]) {
		v = to[i];
		if(!dfn[v]) {
			Dfs(v);
			Chkmin(low[u], low[v]);
		} else if(!sccid[v])
			Chkmin(low[u], dfn[v]);
	}

	if(dfn[u] == low[u]) {
		++ totscc;
		while(!st.empty()) {
			v = st.top();
			st.pop();
			sccid[v] = totscc;
			if(v == u)
				break;
		}
	}
}

int main()
{
	int u, v, now, best = 0, sum = 0;
	scanf("%d%d%d", &n, &m, &MOD);
	REP(i, 1, m) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}

	REP(i, 1, n)
		if(!dfn[i])
			Dfs(i);
	
	REP(u, 1, n) {
		now = sccid[u];
		size[now] ++;
		for(int i = head[u]; i; i = next[i]) {
			v = sccid[to[i]];
			if(v != now) {
				E[now].push_back(v);
				in[v] ++;
			}
		}
	}

	REP(i, 1, totscc) {
		if(in[i] == 0)
			st.push(i);
		ans[i] = 1;
		f[i] = size[i];
	}

	while(!st.empty()) {
		u = st.top();
		st.pop();
		for(int i = 0; i < (int)E[u].size(); i ++) {
			v = E[u][i];
			in[v] --;
			if(in[v] == 0)
				st.push(v);

			if(vis[v] == u)
				continue;
			vis[v] = u;
			// This is necessary, or you may update the ans twice!

			if(Chkmax(f[v], f[u] + size[v]))
				ans[v] = ans[u];
			else if(f[v] == f[u] + size[v])
				(ans[v] += ans[u]) %= MOD;
		}
	}
	
	REP(i, 1, totscc) {
		if(Chkmax(best, f[i]))
			sum = ans[i];
		else if(best == f[i])
			(sum += ans[i]) %= MOD;
	}
	
	printf("%d\n%d\n", best, sum);
}
