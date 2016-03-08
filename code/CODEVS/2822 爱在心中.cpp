#include <cstdio>
#include <stack>
#include <vector>
#include <iostream>
using std::stack;
using std::vector;
const int MAXN = 1000, MAXM = 10000;
int next[MAXM], to[MAXM];
int head[MAXN], sccid[MAXN], dfn[MAXN], low[MAXN];
int dfs_clock, tote, totscc;
stack<int> S;
vector<int> E[MAXN], scc[MAXN];
void AddEdge(int u, int v)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
}
void Dfs(int u)
{
	int v;
	low[u] = dfn[u] = ++ dfs_clock;
	S.push(u);
	
	for(int i = head[u]; i; i = next[i]){
		v = to[i];
		if(!dfn[v]){
			Dfs(v);
			low[u] = std::min(low[u], low[v]);
		}else if(!sccid[v])
			low[u] = std::min(low[u], dfn[v]);
	}
	
	if(low[u] == dfn[u]){
		totscc ++;
		while(true){
			sccid[S.top()] = totscc;
			scc[totscc].push_back(S.top());
			S.pop();
			if(sccid[u]) break;
		}
	}
}
int main()
{
	int n, m, u, v, cnt(0), ans(0);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; i ++){
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
	}
	
	for(int i = 1; i <= n; i ++)
		if(!dfn[i])
			Dfs(i);
	for(int i = 1; i <= totscc; i ++)
		if(scc[i].size() > 1)
			cnt ++;
	printf("%d\n", cnt);

	vector<int> out(totscc + 1, 0);
	for(u = 1; u <= n; u ++)
		for(int j = head[u]; j; j = next[j]){
			v = to[j];
			if(sccid[u] != sccid[v])
				out[sccid[u]] ++;
		}

	ans = 0;
	for(int i = 1; i <= totscc; i ++)
		if(out[i] == 0 && scc[i].size() >= 2)
			if(!ans) ans = i;
			else ans = -1;
	if(ans <= 0) puts("-1");
	else for(int i = 1; i <= n; i ++)
		if(sccid[i] == ans)
			printf("%d ", i);

	puts("");
	return 0;
}
