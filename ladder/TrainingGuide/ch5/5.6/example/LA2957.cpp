// LA2957
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
#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define Pii pair<int, int>
#define X first
#define Y second
#define LL long long
#define LD double
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXN = 10000, MAXM = 100000, oo = 0x3f3f3f3f;
int n, m, k;
/*Graph---------------------------------------*/
struct Edge{
	int u, v, cap, flow;
	Edge(){}
	Edge(int u, int v, int cap, int flow):
		u(u), v(v), cap(cap), flow(flow){}
};
vector<Edge> edges;
vector<int> G[MAXN];
Pii road[MAXN];

int tote;
void AddEdge(int u, int v, int cap)
{
	edges.push_back(Edge(u, v, cap, 0));
	edges.push_back(Edge(v, u, 0, 0));
	// There is 'Edge(v, u, 0, 0)', not 'Edge(u, v,...)'!
	// It is the second time you has made this mistake!
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
		static bool vis[MAXN] = {0};
		queue<int> q;
		MSET(vis, 0);
		vis[S] = true;
		d[S] = 0;
		
		q.push(S);
		while(!q.empty()){
			u = q.front();
			q.pop();
			REP(i, 0, G[u].size() - 1){
				Edge &E = edges[G[u][i]];
				v = E.v;
				if(!vis[v] && E.cap > E.flow){
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
		for(int &i = cur[u]; i < G[u].size(); i ++){
			Edge &E = edges[G[u][i]];
			v = E.v;
			if(d[v] == d[u] + 1 && (t = Dfs(v, min(a, E.cap - E.flow))) > 0){
				a -= t;
				flow += t;
				E.flow += t;
				edges[G[u][i] ^ 1].flow -= t;
				if(a == 0) break;
			}
		}
		return flow;
	}
	
	void Maxflow(int s, int t, int& flow)
	{
		S = s, T = t;
		while(Bfs()){
			MSET(cur, 0);
			flow += Dfs(S, k - flow);
			if(flow == k){
				flow = k;
				break;
			}
		}
	}
}Q;
/*Main program------------------------------------------*/
int S, T;
int Init()
{
	int u, v;
	edges.clear();
	REP(i, 1, n)
		G[i].clear();
	REP(i, 1, m)
		scanf("%d%d", &road[i].X, &road[i].Y);
}

int day;
void Solve()
{	
	day = 0;
	int flow(0), add0, add1, u, v, w1, w2;
	while(true){
		++ day;
		add0 = n * (day - 1);
		add1 = n * day;
		REP(i, 1, n){
			G[i + add1].clear();
			// Every node we use should be clear first;
			AddEdge(i + add0, i + add1, oo);
			// They can stay where they are;
		}
		REP(i, 1, m){
			u = road[i].X;
			v = road[i].Y;
			AddEdge(u + add0, v + add1, 1);
			AddEdge(v + add0, u + add1, 1);
		}
	
		Q.Maxflow(S, add1 + T, flow);
		// From the node 'S' to node 'T' after seval days(the time is 'day' days);
		if(flow == k) break;
	}
}

void Print()
{
	int cnt, num, w1, w2, u, v;
	static int pos[MAXN];
	static int moved[MAXN];
	
	printf("%d\n", day);
	REP(i, 1, k) pos[i] = S;
	REP(I, 1, day){
		vector<int> from, to;
		num = (I - 1) * m * 4 + I * n * 2;
		REP(i, 1, m){
			w1 = edges[num + (i - 1) * 4].flow;
			w2 = edges[num + (i - 1) * 4 + 2].flow;
			u = road[i].X, v = road[i].Y;
			if(w1 == 1 && w2 == 0){
				from.push_back(u);
				to.push_back(v);
			}else if(w1 == 0 && w2 == 1){
				from.push_back(v);
				to.push_back(u);
			}
		}
		
		REP(i, 1, k) moved[i] = false;
		cnt = 0;
		
		REP(i, 0, from.size() - 1){
			REP(j, 1, k){
				if(!moved[j] && pos[j] == from[i]){
					moved[j] = true;
					cnt ++;
					pos[j] = to[i];
					break;
				}
			}
		}
		
		printf("%d", cnt);
		REP(i, 1, k) if(moved[i])
			printf(" %d %d", i, pos[i]);
		puts("");
	}
}

int main()
{
	while(scanf("%d%d%d%d%d", &n, &m, &k, &S, &T) == 5){
		Init();
		Solve();
		Print();
	}
}
