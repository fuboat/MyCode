// UVa10906
// Network flow -- MCMF
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
const int MAXN = 1e6, oo = 0x3f3f3f3f;
/*Graph---------------------------------------*/
struct Edge{
	int u, v, cap, flow, cost;
	Edge(){}
	Edge(int u, int v, int cap, int flow, int cost):
		u(u), v(v), cap(cap), flow(flow), cost(cost){}
};
/*Network Flow--------------------------------*/
struct MCMF{
	vector<Edge> edges;
	vector<int> G[MAXN];
	int vis[MAXN], d[MAXN], f[MAXN], p[MAXN];
	int cur;
	
	void Init(int N){
		REP(i, 1, N) G[i].clear();
		edges.clear();
	}
	
	void AddEdge(int u, int v, int cap, int cost){
		edges.push_back(Edge(u, v, cap, 0, cost));
		edges.push_back(Edge(v, u, 0, 0, -cost));
		int tote = edges.size();
		G[u].push_back(tote - 2);
		G[v].push_back(tote - 1);
	}
	
	bool Spfa(int S, int T, int &flow, int &cost, int need)
	{
		MSET(d, 0x3f);
		queue<int> q;
		q.push(S);
		Edge e;
		vis[S] = cur;
		f[S] = need;
		d[S] = 0;
		
		int u, v;
		while(!q.empty()){
			u = q.front();
			q.pop();
			vis[u] = 0;
			REP(i, 0, G[u].size() - 1){
				e = edges[G[u][i]];
				v = e.v;
				if(e.cap > e.flow && Chkmin(d[v], d[u] + e.cost)){
					p[v] = G[u][i];
					f[v] = min(f[u], e.cap - e.flow);
					if(vis[v] != cur){
						q.push(v);
						vis[v] = cur;
					}
				}
			}
		}
		if(d[T] >= oo) return false;
		
		flow += f[T];
		cost += d[T] * f[T];
		u = T;
		while(u != S){
			edges[p[u]].flow += f[T];
			edges[p[u] ^ 1].flow -= f[T];
			u = edges[p[u]].u;
		}
		return true;
	}
	
	void Mincost(int s, int t, int &flow, int &cost, int need)
	{
		cur = 1;
		MSET(vis, 0);
		while(Spfa(s, t, flow, cost, need - flow)){
			cur ++;
			if(flow == need)
				break;
		}
	}
}Q;

int n, m;
void Init()
{
	Q.Init(n);
	int u, v, w;
	REP(i, 1, m){
		scanf("%d%d%d", &u, &v, &w);
		Q.AddEdge(u, v, 1, w);
		Q.AddEdge(v, u, 1, w);
	}
}
void Solve()
{
	int flow0(0), flow1(0), cost0(0), cost1(0);
	Q.Mincost(1, n, flow1, cost1, 1);
	Q.Mincost(1, n, flow0, cost0, 1);
	if(flow1 + flow0 < 2)
		puts("Back to jail");
	else printf("%d\n", cost0 + cost1);
}
int main()
{
	while(scanf("%d", &n) == 1 && n){
		scanf("%d", &m);
		Init();
		Solve();
	}
}
