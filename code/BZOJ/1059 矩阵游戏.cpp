// BZOJ #1059
// Fuboat
// Hungrary
#include <cstdio>
#include <iostream>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 400 + 100, MAXM = MAXN * MAXN;
int n;

int head[MAXN], next[MAXM], to[MAXM];
int tote;
void AddEdge(int u, int v)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
}

int match[MAXN], vis[MAXN];
int cur;
bool Dfs(int u)
{
	int v;
	for(int i = head[u]; i; i = next[i]) {
		v = to[i];
		if(vis[v] == cur)
			continue;
		vis[v] = cur;

		if(!match[v] || Dfs(match[v])) {
			match[v] = u;
			return true;
		}
	}
	return false;
}

void Init()
{
	memset(match, 0, sizeof(match));
	memset(head, 0, sizeof(head));
	tote = 0;

	int x;
	scanf("%d", &n);
	REP(i, 1, n)
		REP(j, 1, n) {
			scanf("%1d", &x);
			if(x)
				AddEdge(i, j);
		}
}

void Solve()
{
	int tot = 0;
	REP(i, 1, n) {
		cur ++;
		if(Dfs(i))
			tot ++;
	}
	
	puts(tot == n? "Yes" : "No");
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T --) {
		Init();
		Solve();
	}
}
