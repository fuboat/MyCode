// LA2531
// Network flow -- Dinic
// Fuboat
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T> bool Chkmax(T& x, T y){ return x < y? x = y, true : false; }
template <typename T> bool Chkmin(T& x, T y){ return x > y? x = y, true : false; }
using namespace std;
/*Public-------------------------------------------*/
const int MAXN = 2000, oo = 0x3f3f3f3f;
/*-------------------------------------------------*/
struct Edge{
	int u, v, cap, flow;
	Edge(){}
	Edge(int u, int v, int cap, int flow):
		u(u), v(v), cap(cap), flow(flow){}
};
struct Dinic{
	vector<Edge> edges;
	vector<int> G[MAXN];
	int d[MAXN], cur[MAXN], vis[MAXN];
	int S, T;

	void AddEdge(int u, int v, int cap)
	{
		edges.push_back(Edge(u, v, cap, 0));
		edges.push_back(Edge(v, u, 0, 0));
		int tote = edges.size();
		G[u].push_back(tote - 2);
		G[v].push_back(tote - 1);
	}
	
	void Init(int N)
	{
		REP(i, 1, N) G[i].clear();
		edges.clear();
	}

	bool Bfs(int x)
	{
		vis[S] = x;
		queue<int> q;
		q.push(S);
		int u, v;
	
		while(!q.empty()){
			u = q.front();
			q.pop();
			REP(i, 0, G[u].size() - 1){
				Edge &e = edges[G[u][i]];
				v = e.v;
				if(vis[v] != x && e.cap > e.flow){
					vis[v] = x;
					d[v] = d[u] + 1;
					q.push(v);
				}
			}
		}
		
		return vis[T] == x;
	}
	
	int Dfs(int u, int has)
	{
		if(u == T || has == 0) return has;
		int flow(0), v, t;
		for(int &i = cur[u]; i < G[u].size(); i ++){
			Edge &e = edges[G[u][i]];
			v = e.v;
			if(d[v] == d[u] + 1 && e.cap - e.flow > 0){
				t = Dfs(v, min(has, e.cap - e.flow));
				flow += t;
				e.flow += t;
				edges[G[u][i] ^ 1].flow -= t;
				has -= t;
				if(has == 0) break;
			}
		}
		return flow;
	}
	
	int Maxflow(int s, int t, int need)
	{
		CLEAR(vis);
		int flow(0), cnt(0);
		S = s, T = t;
		
		while(Bfs(++ cnt)){
			CLEAR(cur);
			flow += Dfs(S, need - flow);
			if(flow == need) break;
		}
		return flow;
	}
	
	bool Check(int s)
	{
		Edge e;
		REP(i, 0, edges.size() - 1){
			e = edges[i];
			if(e.u == s && e.cap > e.flow)
				return false;
		}
		return true;
	}
}Q;

/*Main Program-------------------------------*/
int PK[MAXN][MAXN], win[MAXN], lose[MAXN], more[MAXN];
int n;
void Init()
{
	REP(i, 1, n)
		scanf("%d%d", &win[i], &lose[i]);
	REP(i, 1, n){
		more[i] = 0;
		REP(j, 1, n){
			scanf("%d", &PK[i][j]);
			more[i] += PK[i][j];
		}
	}
}

void Solve()
{
	int S = n * (n + 1) + n, T = S + 1, u, t;
	bool first = true;
	
	REP(i, 1, n){
		Q.Init(T);
		REP(j, 1, n){
			if(j == i)
				continue;
			REP(k, j + 1, n){
				if(k == i)
					continue;
				u = j * n + k;
				Q.AddEdge(u, j, oo);
				Q.AddEdge(u, k, oo);
				Q.AddEdge(S, u, PK[j][k]);
			}
			t = win[i] + more[i] - win[j];
			if(t >= 0) Q.AddEdge(j, T, t);
			// 可以并列: 't >= 0';
			// 不可以并列: 't > 0'; 
			else goto fail;
		}
		Q.Maxflow(S, T, oo);
		if(Q.Check(S)){
			if(first) first = false;
			else putchar(' ');
			printf("%d", i);
		}
		fail:;
	}
	puts("");
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		Init();
		Solve();
	}
}
