// LA4287
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
/*Public---------------------------------------------------------------*/
const int MAXN = 20000 + 100, MAXM = 50000 + 1000;
int n, m, scc_cnt;
int sccno[MAXN], Out[MAXN], In[MAXN];
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
			for(; st[top + 1] != u; top --)
				sccno[st[top]] = scc_cnt;
		}
	}
}
/*Edge between SCC-----------------------------------------------------*/
void Find(int u)
{
	int v, scc = sccno[u];
	for(int i = pre[u]; i; i = next[i]){
		v = sccno[to[i]];
		if(v != scc){
			In[v] ++;
			Out[scc] ++;
		}
	}
}
void Init()
{
	CLEAR(sccno);
	CLEAR(Tarjian::vis);
	CLEAR(Tarjian::low);
	CLEAR(Tarjian::dfn);
	CLEAR(Tarjian::st);
	CLEAR(next);
	CLEAR(to);
	CLEAR(pre);
	CLEAR(Out);
	CLEAR(In);
	scc_cnt = Tarjian::dfn_clock = Tarjian::top = edge_cnt = 0;
	int u, v;
	scanf("%d%d", &n, &m);
	REP(i, 1, m){
		scanf("%d%d", &u, &v);
		Add(u, v);
	}
}
/*Main Program---------------------------------------------------------*/
void Solve()
{
	REP(i, 1, n) if(!Tarjian::vis[i])
		Tarjian::Dfs(i);
	if(scc_cnt == 1){ puts("0"); return ; }
	// Work out the scc_cnt first;
	// Then check if 'scc_cnt == 1';
	REP(i, 1, n) Find(i);
	int num1 = 0, num2 = 0;
	REP(i, 1, scc_cnt){
		if(In[i] == 0) num1 ++;
		if(Out[i] == 0) num2 ++;
	}
	printf("%d\n", std::max(num1, num2));
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
