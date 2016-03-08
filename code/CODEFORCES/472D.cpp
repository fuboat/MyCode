// codeforces #472D
// Fuboat

// Begin: 2016/2/2, 15:38
// End:   2016/2/2, 16:26
// Spend: 50 min

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; } 
const int MAXN = 2000 + 100, MAXM = 4000 + 200, oo = 0x3f3f3f3f;
int G[MAXN][MAXN], far[MAXN][MAXN], fa[MAXN], dist[MAXN];
int n;
void Readin(int &x)
{
	x = 0;
	char c = getchar();
	while(c < '0' || c > '9')
		c = getchar();
	while('0' <= c && c <= '9') {
		(x *= 10) += c - '0';
		c = getchar();
	}
}
struct Edge{
	int from, w;
	Edge(){}
	Edge(int from, int w):
		from(from), w(w){}
	bool operator < (const Edge &E) const{
		return w < E.w;
	}
};
namespace Prim{
	Edge dis[MAXN];
	bool used[MAXN];
	void Work()
	{
		int p;
		Edge minx;
		REP(i, 1, n)
			dis[i] = Edge(0, oo);
		dis[1] = Edge(0, 0);
		
		REP(i, 1, n) {
			p = 0;
			minx = Edge(0, oo);
			REP(i, 1, n)
				if(!used[i] && Chkmin(minx, dis[i]))
					p = i;
			fa[p] = minx.from;
			dist[p] = minx.w;
			used[p] = true;
			
			REP(i, 1, n)
				if(!used[i])
					Chkmin(dis[i], Edge(p, G[i][p]));
		}
	}
}

namespace DFS{
	int head[MAXN], next[MAXM], to[MAXM], st[MAXN], val[MAXN];
	int top, tote;
	void AddEdge(int u, int v, int w)
	{
		to[++ tote] = v;
		val[tote] = w;
		next[tote] = head[u];
		head[u] = tote;
	}
	
	void Dfs(int u)
	{
		int v, w, now;
		st[++ top] = u;
		far[u][u] = 0;
		for(int i = head[u]; i; i = next[i]) {
			v = to[i];
			w = val[i];
			far[u][v] = far[v][u] = w;
			REP(j, 1, top) {
				now = st[j];
				if(now != u)
					far[now][v] = far[v][now] = w + far[now][u];
					// 'v', not 'u'!
			}
			Dfs(v);
		}
	}
	
	void Work()
	{
		REP(i, 2, n)
			AddEdge(fa[i], i, dist[i]);
		Dfs(1);
	}
}

bool Check() 
{
	REP(i, 1, n) {
		if(G[i][i] != 0)
			return false;
		REP(j, i + 1, n)
			if(G[i][j] != G[j][i] || !G[i][j])
				return false;
	}
	return true;
}

void Init()
{
	Readin(n);
	REP(i, 1, n)	
		REP(j, 1, n)
			Readin(G[i][j]);
}

bool Solve()
{
	Prim::Work();
	DFS::Work();
	REP(i, 1, n)
		REP(j, 1, n)
			if(G[i][j] != far[i][j])
				return false;
	return true;
}

int main()
{
	Init();
	puts((Check() && Solve())? "YES" : "NO");
}

