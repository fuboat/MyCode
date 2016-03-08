// LA3989
// Bitpartitle
// Fuboat
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
template <typename T> bool Chkmax(T &x, T y){ return x < y? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y){ return x > y? x = y, true : false; }
const int MAXN = 1000 + 100;
int hus[MAXN], wife[MAXN], next[MAXN];
int pre[MAXN][MAXN], order[MAXN][MAXN];
int n;
std::queue<int> q;
void Engage(int u, int v)
{
	int old = hus[v];
	if(old){
		wife[old] = 0;
		q.push(old);
	}
	wife[u] = v;
	hus[v] = u;
}
void Init()
{
	int x;
	CLEAR(hus);
	CLEAR(wife);
	CLEAR(next);
	CLEAR(pre);
	CLEAR(order);
	REP(u, 1, n){
		q.push(u);
		REP(i, 1, n)
			scanf("%d", &pre[u][i]);
	}
	REP(v, 1, n){
		REP(i, 1, n){
			scanf("%d", &x);
			order[v][x] = i;
		}
	}
}
void Solve()
{
	int u, v;
	while(!q.empty()){
		u = q.front();
		q.pop();
		v = pre[u][++ next[u]];
		if(!hus[v] || order[v][u] < order[v][hus[v]])
			Engage(u, v);
		else q.push(u);
	}
	while(!q.empty()) q.pop();
	REP(i, 1, n)
		printf("%d\n", wife[i]);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		Init();
		Solve();
		if(T) puts("");
	}
}
