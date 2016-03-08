// LA3523
// BCC
// Fuboat
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <cstring>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T> bool Chkmax(T &x, T y){ return x < y? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y){ return x > y? x = y, true : false; }
/*Public-------------------------------------------------------------*/
const int MAXN = 1e3 + 1e2, MAXM = 1e6 + 1e2;
bool iscut[MAXN];
int n, m, totbcc;
int bccid[MAXN];
std::vector<int> bcc[MAXN];
/*Edge---------------------------------------------------------------*/
int head[MAXN];
int to[MAXM], next[MAXM];
int tote;
void AddEdge(int u, int v)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
}
/*Bcc----------------------------------------------------------------*/
namespace Tarjian{
	int dfs_clock, dfn[MAXN], low[MAXN];
	std::pair<int, int> st[MAXM];
	// The size of 'st' is 'MAXM'.
	int top;
	
	void dfs(int u, int fa)
	{
		low[u] = dfn[u] = ++ dfs_clock;
		int tot_child = 0;
		for (int i = head[u]; i; i = next[i]) {
			int v = to[i];
			std::pair<int, int> cur = std::make_pair(u, v);
	
			if (dfn[v] == 0) {
	            ++ tot_child;
	            st[++ top] = cur;
				dfs(v, u);
	            Chkmin(low[u], low[v]);
	
	            if (low[v] >= dfn[u]) {
	                iscut[u] = true;
	                bcc[++ totbcc].clear();
	                for (;;) {
	                    std::pair<int, int> x = st[top--];
	                    if (Chkmax(bccid[x.first], totbcc))
	                        bcc[totbcc].push_back(x.first);
	                    if (Chkmax(bccid[x.second], totbcc))
	                        bcc[totbcc].push_back(x.second);

	                    if (x == cur)
	                        break;
	                }
	            }
			} else if (dfn[v] < dfn[u] && v != fa) {
	            st[++top] = cur;
	            Chkmin(low[u], dfn[v]);
			}
		}

		if (fa == 0 && tot_child < 2)
	        iscut[u] = false;
	}
	
	void exec(int N)
	{
	    top = dfs_clock = totbcc = 0;
		CLEAR(dfn);
	    CLEAR(bccid);
		CLEAR(iscut);
		for (int i = 1; i <= N; ++i)
			if (dfn[i] == 0)
	            dfs(i, 0);
	}
}
/*Hungry-------------------------------------------------------------*/
int color[MAXN];
bool Bipartite(int u, int d)
{
	int v;
	for(int i = head[u]; i; i = next[i]){
		v = to[i];
		if(bccid[v] != d)
			continue;
		if(color[u] == color[v])
			return false;
		else if(!color[v]){
			color[v] = 3 - color[u];
			if(!Bipartite(v, d))
				return false;
		}
	}
	return true;
}
bool Hungry(int b)
{
	CLEAR(color);
	int u = bcc[b][0];
	REP(i, 0, bcc[b].size() - 1)
		bccid[bcc[b][i]] = b;
	color[u] = 1;
	return Bipartite(u, b);
}
/*Main Program--------------------------------------------------------*/
bool hate[MAXN][MAXN], can_join[MAXN];
void Init()
{
	REP(i, 1, totbcc)
		bcc[i].clear();
	CLEAR(head);
	CLEAR(can_join);
	CLEAR(hate);
	totbcc = tote = 0;
	int x, y;
	REP(i, 1, m){
		scanf("%d%d", &x, &y);
		hate[x][y] = true;
	}
	REP(i, 1, n) REP(j, i + 1, n)
		if(!hate[i][j]){
			AddEdge(i, j);
			AddEdge(j, i);
		}
}
void Solve()
{
	int ans = 0;
	Tarjian::exec(n);
	REP(i, 1, totbcc) if(!Hungry(i))
			REP(j, 0, bcc[i].size() - 1)
				can_join[bcc[i][j]] = true;
	REP(i, 1, n) if(!can_join[i])
		ans ++;
	printf("%d\n", ans);
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n && m){
		Init();
		Solve();
	}
}
