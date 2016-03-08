// UVa11419
// Bitpartitle
// Fuboat
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
/*Public----------------------------------*/
const int MAXN = 2000, MAXM = MAXN * MAXN;
int n, m, cnt;
int used[MAXN], ok[MAXN];
/*Graph-----------------------------------*/
int head[MAXN];
int next[MAXM], to[MAXM];
int tote;
void AddEdge(int u, int v)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
}
/*Hungray---------------------------------*/
int cur;
int vis[MAXN], link[MAXN];
bool Dfs(int u)
{
	used[u] = true;
	int v;
	for(int i = head[u]; i; i = next[i]){
		v = to[i];
		if(vis[v] == cur)
			continue;
		else vis[v] = cur;
		if(!link[v] || Dfs(link[v])){
			link[v] = u;
			return ok[u] = true;
		}
	}
	return false;
}

int Hungary(bool flag)
{
	CLEAR(vis);
	
	cur = 0;
	int tot = 0;
	REP(i, 1, n){
		cur ++;
		if(Dfs(i))
			tot ++;
	}
	return tot;
}

void Init()
{
	CLEAR(link);
	CLEAR(head);
	CLEAR(used);
	CLEAR(ok);
	tote = 0;
	int x, y;
	REP(i, 1, cnt){
		scanf("%d%d", &x, &y);
		AddEdge(x, y);
	}
}

void Solve()
{
	int ans = Hungary(0);
	printf("%d", ans);
	CLEAR(used);
	
	cur = n + 1;
	REP(i, 1, n)
		if(head[i] && !ok[i])
		// The node is not matched;
			Dfs(i);
			
	REP(i, 1, n)
		if(!head[i]) continue;
		else if(!used[i])
			printf(" r%d", i);

	REP(i, 1, m)
		if(vis[i] == cur)
		// The node is visited this time;
			printf(" c%d", i);

	puts("");
}

int main()
{
	while(~scanf("%d%d%d", &n, &m, &cnt) && n && m && cnt){
		Init();
		Solve();
	}
}
