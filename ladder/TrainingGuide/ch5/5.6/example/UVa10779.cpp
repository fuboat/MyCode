// UVa10779
// Network flow -- Dinic
// Fuboat
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#ifdef WIN32
	#define ll "%I64d"
#else
	#define ll "%lld"
#endif
#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#define LD double
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXN = 200, MAXM = 25 + 10, oo = 0x7fffffff;
/*Graph---------------------------------------*/
struct Edge{
	int u, v, cap, flow;
	Edge(){}
	Edge(int u, int v, int cap, int flow):
		u(u), v(v), cap(cap), flow(flow){}
};
vector<Edge> edges;
vector<int> G[MAXN];
int tote;
void AddEdge(int u, int v, int cap)
{
	edges.push_back(Edge(u, v, cap, 0));
	edges.push_back(Edge(v, u, 0, 0));
	tote = edges.size();
	G[u].push_back(tote - 2);
	G[v].push_back(tote - 1);
}
/*Dinic---------------------------------------*/
struct Dinic{
	int d[MAXN], cur[MAXN], vis[MAXN];
	int S, T;
	
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
		MSET(vis, 0);
		int flow(0), cnt(0);
		S = s, T = t;
		
		while(Bfs(++ cnt)){
			MSET(cur, 0);
			flow += Dfs(S, need - flow);
			if(flow == need) break;
		}
		return flow;
	}
}Q;

int toticket[MAXN][MAXM];
int m, n;

void Init()
{
	int k, t;
	MSET(toticket, 0);
	REP(i, 0, n - 1)
	{
		scanf("%d", &k);
		REP(j, 1, k){
			scanf("%d", &t);
			toticket[i][t] ++;
		}
	}
}

void Solve()
{
	int S = m + n, T = S + 1, sum;
	G[S].clear();
	G[T].clear();
	REP(i, 1, m){
		G[i].clear();
		AddEdge(S, i, toticket[0][i]);
		AddEdge(i, T, 1);
	}
	REP(i, 1, n - 1){
		G[m + i].clear();
		REP(j, 1, m){
			sum = toticket[i][j];
			if(sum == 0) AddEdge(j, m + i, 1);
			else AddEdge(m + i, j, sum - 1);
		}
	}
	printf("%d\n", Q.Maxflow(S, T, oo));
}

int main()
{
	int T;
	scanf("%d", &T);
	REP(i, 1, T){
		scanf("%d%d", &n, &m);
		// How did you forget this sentences? So silly!
		Init();
		printf("Case #%d: ", i);
		Solve();
	}
}
