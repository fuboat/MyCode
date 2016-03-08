// LA3268
// Network flow -- Dninc
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
const int MAXN = 3000, MAXM = 3000, oo = 0x3f3f3f3f;
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
	
	bool Check(int from, int to, int s, int t, int w)
	{
		Edge e;
		vector<Edge> E(edges);
		bool result = true;
		REP(i, from, to)
			AddEdge(i, t, w);
		Maxflow(s, t, oo);
		REP(i, 0, E.size() - 1){
			e = edges[i];
			if(e.u == s && e.cap > e.flow){
				result = false;
				break;
			}
		}
		
		edges = E;
		REP(i, from, to){
			G[i].pop_back();
			G[t].pop_back();
		}
		
		return result;
	}
}Q;
/*Main Program----------------------------*/
int n, m, S, T;
char s[100];
void Init()
{
	char c;
	int v;
	S = m + n + 1, T = S + 1;
	Q.Init(T);
	
	REP(i, 1, n) AddEdge(S, i, 1);
	REP(i, 1, n){
		scanf("%s", s);
		while(true){
			if(getchar() == '\n')
				break;
			scanf("%s", s);
			sscanf(s, "%d", &v);
			AddEdge(i, n + v + 1, 1);
		}
	}
}

void Solve()
{
	int l = 1, r = n, mid, ans;
	while(l <= r){
		mid = (l + r) >> 1;
		if(Q.Check(n + 1, n + m + 1, S, T, mid)){
			r = mid - 1;
			ans = mid;
		}else l = mid + 1;
	}
	printf("%d\n", ans);
}

int main()
{
	while(scanf("%d %d", &n, &m) == 2 && n && m){
		Init();
		Solve();
	}
}
