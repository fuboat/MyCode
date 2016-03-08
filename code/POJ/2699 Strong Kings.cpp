#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define REP(i, x, y) for (int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for (int i = x, _ = y; i >= _; i --) 
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0)
#define LL long long
using std::vector;
using std::min;
template <typename T> bool Chkmax(T &x, T y) { return x < y? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int MAXN = 3000 + 100, oo = 0x3f3f3f3f;
struct Edge {
	int u, v, flow, cap;
	Edge(int u0, int v0, int flow0, int cap0):
		u(u0), v(v0), flow(flow0), cap(cap0) {}
};

int n, S, T;
int win[MAXN];
vector<Edge> edges;
vector<int> G[MAXN];

void AddEdge(int u, int v, int flow, int cap)
{
	int m = edges.size();
	edges.push_back(Edge(u, v, 0, cap));
	edges.push_back(Edge(v, u, 0, 0));
	G[u].push_back(m);
	G[v].push_back(m + 1);
}

int GetEdge(int u, int v)
{
	if (v < u)
		std::swap(u, v);
	
	return u * n + v;
}

namespace Dinic {
	int S, T;
	int cur[MAXN], dis[MAXN];
	
	bool Bfs()
	{
		static int vis[MAXN], cnt;
		queue<int> q;
		int u, v;
		
		cnt ++;
		q.push_back(S);
		
		while (!q.empty()) {
			u = q.front();
			q.pop();
			
			REP (i, 0, (int) G[u].size() - 1) {
				Edge &E = edges[G[u][i]], v = E.v;
				if (vis[v] != cnt && E.flow < E.cap) {
					vis[v] = cnt;
					dis[v] = dis[u] + 1;
					q.push(v);
				}
			}
		}
		
		return vis[T];
	}
	
	int Dfs(int u, int a)
	{
		if (u == T || a == 0)
			return a;
		
		int t, v, flow = 0;
		for (int &i = cur[u]; i < G[u].size(); i ++) {
			Edge &E = edges[G[u][i]], v = E.v;
			if (E.flow < E.cap && (t = Dfs(v, min(E.cap - E.flow, a)))) {
				E.flow += t;
				flow += t;
				edges[G[u][i] ^ 1].flow -= t;
				a -= t;
				if (a == 0)
					break;
			}
		}
		
		return flow;
	}
	
	void Work(int s, int t, int need = oo)
	{
		S = s;
		T = t;
		while (Bfs()) {
			CLEAR(cur);
			oo -= Dfs(S, oo);
		}
	}
}

void Init()
{
	scanf("%d", &n);
	REP (i, 1, n)
		scanf("%d", &win[i]);

	S = n * n, T = n * n + 1;
	REP (i, 1, n)
		REP (j, i + 1, n) {
			AddEdge(i, GetEdge(i, j), 1);
			AddEdge(j, GetEdge(i, j), 1);
			AddEdge(GetEdge(i, j), T, 1);
		}
}

void Solve()
{
}
