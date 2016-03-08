#include <cstdio>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cstring>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
using namespace std;
template<typename T>bool Chkmax(T &x, T y){ return y > x? x = y, true : false; }
template<typename T>bool Chkmin(T &x, T y){ return y < x? x = y, true : false; }
const int MAXN = 1500 + 100, MAXM = 50000 + 1000;
/*Graph----------------------------------------------------*/
bool vis[MAXN];
int edge_cnt;
int dis[MAXN], pre[MAXN];
struct edge{ int to, w, next; } s[MAXM];
void Add(int from, int to, int w)
{
	s[++ edge_cnt] = (edge){to, w, pre[from]};
	pre[from] = edge_cnt;
}
void Spfa(int from)
{
	int to, w;
	queue<int>q;
	q.push(from);
	CLEAR(vis);
	vis[from] = true;
	dis[from] = 0;
	while(!q.empty()){
		from = q.front(); q.pop();
		vis[from] = false;
		for(int i = pre[from]; i; i = s[i].next){
			to = s[i].to, w = s[i].w;
			if(Chkmax(dis[to], dis[from] + w) && !vis[to])
				q.push(to);
		}
	}
}
/*Main program--------------------------------------------*/
int n, m;
void Init()
{
	int from, to, w;
	edge_cnt = 0;
	REP(i, 1, n) dis[i] = -0x7fffffff;
	REP(i, 1, m){
		scanf("%d%d%d", &from, &to, &w);
		if(from > to) swap(from, to);
		Add(from, to, w);
	}
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n){
		Init();
		Spfa(1);
		printf("%d\n", dis[n] == -0x7fffffff? -1 : dis[n]);
	}
}
