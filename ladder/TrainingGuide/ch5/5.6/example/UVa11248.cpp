// UVa11348
// Network flow
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
#define LD double
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXN = 1000 + 10, MAXM = 20000 + 100, oo = 0x7fffffff;
int tote, n, m, need;
/*Graph---------------------------------------*/
struct Edge{
	int u, v, cap, flow;
	Edge(){}
	Edge(int u, int v, int cap, int flow):
		u(u), v(v), cap(cap), flow(flow){}
	bool operator < (const Edge &e) const{
		if(u != e.u) return u < e.u; 
		return v < e.v;
		// 'return u < e.u || v < u.v' is wrong;
		// Don't be to lazy;
	}
};
vector<Edge> edges, E;
vector<int> G[MAXN];
void AddEdge(int u, int v, int cap)
{
	edges.push_back(Edge(u, v, cap, 0));
	edges.push_back(Edge(v, u, 0, 0));
	// 此处须反向; 
	tote = edges.size();
	G[u].push_back(tote - 2);
	G[v].push_back(tote - 1);
}
/*Dinic---------------------------------------*/
struct Dinic{
	int d[MAXN], cur[MAXN];
	int S, T;
	bool Bfs()
	{
		int u, v;
		static bool vis[MAXN];
		queue<int> q;
		REP(i, 1, n)
			vis[i] = false;
		vis[S] = true;
		
		q.push(S);
		while(!q.empty()){
			u = q.front();
			q.pop();
			REP(i, 0, G[u].size() - 1){
				Edge &e = edges[G[u][i]];
				v = e.v;
				if(!vis[v] && e.cap > e.flow){
					vis[v] = true;
					d[v] = d[u] + 1;
					q.push(v);
				}
			}
		}
		return vis[T];
	}
	
	int Dfs(int u, int a)
	{
		if(u == T || a == 0) return a;
		int flow = 0, v, t;
		for(int i = 0; i < G[u].size(); i ++){
			Edge &e = edges[G[u][i]];
			v = e.v;
			if(d[v] == d[u] + 1 && (t = Dfs(v, min(a, e.cap - e.flow))) > 0){
				a -= t;
				flow += t;
				e.flow += t;
				edges[G[u][i] ^ 1].flow -= t;
				if(a == 0) break;
			}
		}
		return flow;
	}
	
	int Maxflow(int s, int t, int flow)
	{
		S = s, T = t;
		while(Bfs()){
			REP(i, 1, n)
				cur[i] = 0;
			flow += Dfs(S, oo);
			if(flow >= need) break;
		}
		return flow;
	}
}Q;
/*Main program---------------------------------*/
vector<Edge>ans;
void Init()
{
	int u, v, cap;
	edges.clear();
	ans.clear();
	REP(i, 1, n)
		G[i].clear();
	REP(i, 1, m){
		scanf("%d%d%d", &u, &v, &cap);
		AddEdge(u, v, cap);
	}
}

void Solve()
{
	int maxflow = Q.Maxflow(1, n, 0);
	if(maxflow >= need){
		puts("possible");
		return ;
	}
	E = edges;
	for(int i = 0; i < edges.size(); i ++){
		if(!E[i].cap || E[i].cap > E[i].flow)
			continue;
		edges = E;
		edges[i].cap = need;
		if(Q.Maxflow(1, n, maxflow) >= need)
			ans.push_back(E[i]);
	}
	if(!ans.size())
		puts("not possible");
	else{
		printf("possible option:");
		sort(ans.begin(), ans.end());
		REP(i, 0, ans.size() - 1)
			printf(i < ans.size() - 1? "(%d,%d)," : "(%d,%d)\n", ans[i].u, ans[i].v);
	}
}
int main()
{
	int kase = 0;
	while(~scanf("%d%d%d", &n, &m, &need)){
		if(n + m + need == 0) break;
		printf("Case %d: ", ++ kase);
		Init();
		Solve();
	}
}
