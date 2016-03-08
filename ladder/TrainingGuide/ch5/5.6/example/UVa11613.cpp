// UVa11613
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
#define int long long
#define LL long long
#define LD double
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXN = 1e6;
const LL oo = 1LL << 60;
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
	
	bool Spfa(int S, int T, int &flow, int &cost)
	{
		REP(i, 1, T) d[i] = oo;
		queue<int> q;
		q.push(S);
		Edge e;
		vis[S] = cur;
		f[S] = oo;
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
		if(d[T] >= 0) return false;
		
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
	
	int Mincost(int s, int t)
	{
		MSET(vis, 0);
		int flow = 0, cost = 0;
		cur = 1;
		while(Spfa(s, t, flow, cost)) cur ++;
		return cost;
	}
}Q;

int m[MAXN], n[MAXN], p[MAXN], s[MAXN], E[MAXN];
// m: 成本   n:产量   p:销售价 s:销售量 E:存放时间 
int M, I, S, T;

void Init()
{
	S = M * 2 + 1, T = S + 1;
	Q.Init(T);
	REP(i, 1, M){
		scanf(ll""ll""ll""ll""ll, &m[i], &n[i], &p[i], &s[i], &E[i]);
		Q.AddEdge(S, i, n[i], m[i]);
		Q.AddEdge(i, i + M, n[i], 0);
		// The objects can be sold without staying for a period;
		Q.AddEdge(i + M, T, s[i], - p[i]);
		REP(j, 1, E[i]){
			if(j + i > M) break;
			Q.AddEdge(i, i + j + M, n[i], I * j);
		}
	}
}

main()
{
	int kase;
	scanf(ll, &kase);
	for(int i = 1; i <= kase; i ++){
		scanf(ll""ll, &M, &I);
		Init();
		printf("Case "ll": "ll"\n", i, -Q.Mincost(S, T));
	}
}
