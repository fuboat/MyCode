// UVa 11324
// Tarjian
// Fuboat
#include <cstdio>
#include <iostream>
#include <stack>
#include <algorithm>
#include <cstring>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
template <typename T> bool Chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool Chkmax(T &x, T y){return y > x? (x = y, true) : false;}
//using namespace std;
/*Public---------------------------------------------------------------*/
const int MAXN = 1000 + 100, MAXM = 50000 + 1000;
int n, m, scc_cnt;
int sccno[MAXN], big[MAXN];
/*Edge-----------------------------------------------------------------*/
int next[MAXM], to[MAXM], pre[MAXN];
int edge_cnt;
void Add(int u, int v)
{
	edge_cnt ++;
	to[edge_cnt] = v;
	next[edge_cnt] = pre[u];
	pre[u] = edge_cnt;
}
/*Tarjian--------------------------------------------------------------*/
namespace Tarjian
{
	bool vis[MAXN];
	int low[MAXN], dfn[MAXN], st[MAXN];
	int dfn_clock, top;
	void Dfs(int u)
	{
		vis[u] = true;
		low[u] = dfn[u] = ++ dfn_clock;
		st[++ top] = u;
		int v;
		for(int i = pre[u]; i; i = next[i]){
			v = to[i];
			if(!vis[v]){
				Dfs(v);
				Chkmin(low[u], low[v]);
			}else if(sccno[v] == 0)
				Chkmin(low[u], dfn[v]);
		}
		if(low[u] == dfn[u]){
			++ scc_cnt;
			for(; st[top + 1] != u; top --){
				big[scc_cnt] ++;
				sccno[st[top]] = scc_cnt;
			}
		}
	}
}
/*Graph to DAG-------------------------------------------------------*/
struct SpecialEdge{
	int to, next;
}s[MAXM];
int head[MAXN], In[MAXN], f[MAXN];
int EdgeCnt;
void Find(int u)
{
	int v, scc = sccno[u];
	for(int i = pre[u]; i; i = next[i]){
		v = sccno[to[i]];
		if(v != scc){
			s[++ EdgeCnt].to = v;
			s[EdgeCnt].next = head[scc];
			head[scc] = EdgeCnt;
			In[v] ++;
		}
	}
}
/*Dynamic------------------------------------------------------------*/
void Solve(){
	int u, v, ans = 0;
	std::stack<int>q;
	REP(i, 1, n) Find(i);
	REP(i, 1, scc_cnt) if(In[i] == 0) q.push(i);
	while(!q.empty()){
		u = q.top(); q.pop();
		for(int i = head[u]; i; i = s[i].next){
			v = s[i].to;
			Chkmax(f[v], f[u] + big[u]);
			In[v] --;
			if(In[v] == 0) q.push(v);
		}
	}
	REP(i, 1, scc_cnt)
		Chkmax(ans, f[i] + big[i]);
	printf("%d\n", ans);
}
/*Main Program-------------------------------------------------------*/
void Init()
{
	CLEAR(f);
	CLEAR(Tarjian::vis);
	CLEAR(Tarjian::low);
	CLEAR(Tarjian::dfn);
	CLEAR(Tarjian::st);
	CLEAR(sccno);
	CLEAR(big);
	CLEAR(In);
	CLEAR(pre);
	CLEAR(head);
	CLEAR(s);
	CLEAR(next);
	CLEAR(to);
	Tarjian::dfn_clock = edge_cnt = EdgeCnt = scc_cnt = Tarjian::top = 0;
	int u, v;
	scanf("%d%d", &n, &m);
	REP(i, 1, m){
		scanf("%d%d", &u, &v);
		Add(u, v);
	}
	REP(i, 1, n) if(!Tarjian::vis[i])
		Tarjian::Dfs(i);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		Init();
		Solve();
	}
}
