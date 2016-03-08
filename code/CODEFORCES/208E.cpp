// coeforces #208C
// Fuboat
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#define int long long // <--- 'int' is not enough...
using namespace std;
#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#define LD double
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXN = 1000, MAXM= 2 * MAXN * MAXN, oo = 0x3f3f3f3f;
int tote;
int dis[MAXN], way[2][MAXN];
int head[MAXN], to[MAXM], next[MAXM], in[MAXN];
int G[MAXN][MAXN];
void AddEdge(int u, int v)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
	G[u][v] = 1;
}

int n, m;

void Dp1(int u)
{
	static int vis[MAXN] = {0};
	if(u == 1)
		return ;
	if(vis[u])
		return ;
	vis[u] = true;
	
	REP(v, 1, n)
		if(G[u][v] && dis[v] + 1 == dis[u]) {
			Dp1(v);
			way[0][u] += way[0][v];
		}
}

void Dp2(int u)
{
	static int vis[MAXN] = {0};
	if(u == n)
		return ;
	if(vis[u])
		return ;
	vis[u] = true;
	
	REP(v, 1, n)
		if(G[u][v] && dis[u] + 1 == dis[v]) {
			Dp2(v);
			way[1][u] += way[1][v];
		}
}

void Spfa(int from)
{
	static int in[MAXN] = {0};
	int u, v;
	REP(i, 1, n)
		dis[i] = oo;
	std::queue<int> q;
	q.push(from);
	in[from] = 1;
	dis[from] = 0;
	
	while(!q.empty()) {
		u = q.front();
		q.pop();
		in[u] = 0;
		
		for(int i = head[u]; i; i = next[i]) {
			v = to[i];
			if(Chkmin(dis[v], dis[u] + 1))
				if(!in[v]) {
					q.push(v);
					in[v] = 1;
				}
		}
	}
}

void Init()
{
	int u, v;
	scanf("%I64d%I64d", &n, &m);
	REP(i, 1, m) {
		scanf("%I64d%I64d", &u, &v);
		AddEdge(u, v);
		AddEdge(v, u);
	}
}

void Solve()
{
	Spfa(1);
	way[0][1] = 1;
	way[1][n] = 1;

	int ans = 0;
	REP(i, 1, n) {
		Dp1(i);
		Dp2(i);
		if(i != 1 && i != n)
			Chkmax(ans, 2 * way[0][i] * way[1][i]);
	}
	Chkmax(ans, way[1][1]);
	printf("%.10lf\n", 1.0 * ans / way[1][1]);
}

main()
{
	Init();
	Solve();
}
