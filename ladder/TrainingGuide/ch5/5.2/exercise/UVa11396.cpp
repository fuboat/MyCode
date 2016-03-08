#include <cstdio>
#include <iostream>
#include <stack>
#include <algorithm>
#include <cstring>
#include <vector>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 20000 + 1000, MAXM = MAXN * 10 * 2;
int n, m;
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }

int tote;
int iscut[MAXN];
/*Graph-----------------------------------------------------------------------*/
int head[MAXN];
int to[MAXM], next[MAXM];
void AddEdge(int u, int v)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
}
/*Tarjan----------------------------------------------------------------------*/
namespace Tarjan {

	int dfs_clock, dfn[MAXN], low[MAXN];
	// The size of the stack is at least 'MAXM', because maybe all most every edge will be put into the stack;
	int top;

	void dfs(int u, int fa)
	{
		low[u] = dfn[u] = ++ dfs_clock;
		int tot_child = 0, v;
		for (int i = head[u]; i; i = next[i]) {
			v = to[i];

			if (dfn[v] == 0) {
	            ++ tot_child;
				dfs(v, u);
	            Chkmin(low[u], low[v]);
	
	            if (low[v] >= dfn[u])
	                iscut[u] ++;
			} else if (dfn[v] < dfn[u] && v != fa) {
	            Chkmin(low[u], dfn[v]);
			}
		}
	
		if (fa == 0 && tot_child < 2)
	        iscut[u] = 0;
	}
	
	void exec(int N)
	{
	    top = dfs_clock = 0;
	    CLEAR(dfn);
	    CLEAR(iscut);
		
		REP(i, 1, N)
			if (dfn[i] == 0)
	            dfs(i, 0);
	}

}
/*Main Program------------------------------------------------------------*/
void Init()
{
	int u, v;
	CLEAR(head);
	tote = 0;
	while(scanf("%d%d", &u, &v) && u != -1 && v != -1){
		u ++;
		v ++;
		AddEdge(u, v);
		AddEdge(v, u);
	}
}
std::pair<int, int> ans[MAXN];
void Solve()
{
	Tarjan::exec(n);
	REP(i, 1, n)
		ans[i] = std::make_pair(-(iscut[i]), i);
		// The '-' is for 'sort()', which puts the smaller element to front;
	sort(ans + 1, ans + n + 1);
	REP(i, 1, m){
		printf("%d %d\n", ans[i].second - 1, - ans[i].first + 1);
	}
}
int main()
{
	// There is no need to use union set;
	// At the beginning, the node in the graph can reach any node;
	while(scanf("%d%d", &n, &m) == 2 && n && m){
		Init();
		Solve();
		puts("");
	}
}
