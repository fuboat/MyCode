// BZOJ #1064
// Fuboat
// Graph
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define CLEAR(a) memset(a, 0, sizeof(a))
#define LL long long
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int MAXN = 100000 + 1000, MAXM = 2000000 + 1000, oo = 0x3f3f3f3f;
int n, m;
std::vector<int> cir;

int Gcd(int a, int b)
{
	int r;
	while(b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int maxx, minx;
namespace Graph{
	int dis[MAXN], head[MAXN], next[MAXM], to[MAXM], val[MAXM];
	int tote;
	bool vis[MAXN];
	
	void AddEdge(int u, int v, int w)
	{
		to[++ tote] = v;
		val[tote] = w;
		next[tote] = head[u];
		head[u] = tote;
	}
	
	void Dfs(int u)
	{
		vis[u] = true;
		Chkmin(minx, dis[u]);
		Chkmax(maxx, dis[u]);
		
		int v, w, x;
		for(int i = head[u]; i; i = next[i]) {
			v = to[i];
			w = val[i];
			if(vis[v]) {
				x = abs(dis[v] - dis[u] - w);
				if(x)
					cir.push_back(x);
			} else {
				dis[v] = dis[u] + w;
				Dfs(v);
			}
		}
	}
}

void Init()
{
	int u, v;
	scanf("%d%d", &n, &m);
	REP(i, 1, m) {
		scanf("%d%d", &u, &v);
		Graph::AddEdge(u, v, 1);
		Graph::AddEdge(v, u, -1);
	}
}

int length = 0;

void Solve()
{
	using namespace Graph;
	REP(i, 1, n) {
		if(!vis[i]) {
			minx = oo;
			maxx = -oo;
			Dfs(i);
			length += maxx - minx + 1;  // <----- '+=', not 'Chkmax(...)';
		}
	}
}

void Print()
{
	if(cir.size() == 0)
	{
		if(length < 3)
			puts("-1 -1");
		else printf("%d %d\n", length, 3);
		return ;
	}
	
	int from = 0, Min = oo, Max = -oo;
	for(int i = 0; i < cir.size(); i ++)
		from = Gcd(from, cir[i]);

	for(int i = 3; i <= n; i ++) {
		if(from % i == 0) {
			Chkmax(Max, i);
			Chkmin(Min, i);
		} else if(i > from)
			break;
	}

	if(Min == oo && Max == -oo)
		Min = Max = -1;
	printf("%d %d\n", Max, Min);
}

int main()
{
	Init();
	Solve();
	Print();
}
