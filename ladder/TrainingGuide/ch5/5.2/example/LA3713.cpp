// LA3713
// 2-SAT
// Fuboat
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdlib>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
/*Public-------------------------------------------------------------*/
const int MAXN = 200000 + 1000, MAXM = 400000 + 1000; // MAXM = 300000 is not enough!
int n, m;
/*Edge---------------------------------------------------------------*/
int to[MAXM], next[MAXM], head[MAXN * 2];
int tote;
inline void AddEdge(int u, int v)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
}
/*2-SAT--------------------------------------------------------------*/
int top;
int st[MAXN * 2];
bool mark[MAXN * 2];
void AddSta(int u, bool s1, int v, bool s2){
	u = (u - 1) << 1 | s1;
	v = (v - 1) << 1 | s2;
	AddEdge(u ^ 1, v);
	AddEdge(v ^ 1, u);
}
bool Dfs(int u)
{
	if(mark[u ^ 1]) 
		return false;
	if(mark[u])
		return true;

	st[++ top] = u;
	mark[u] = true;
	for(int i = head[u]; i; i = next[i])
		if(!Dfs(to[i]))
			return false;
	return true;
}
/*Main Program--------------------------------------------------------*/
int old[MAXN];
bool is_old[MAXN];
int Init()
{
	//CLEAR(T);
	tote = 0;
	CLEAR(head);
	CLEAR(mark);
	int x, y, tot = 0;
	REP(i, 1, n){
		scanf("%d", &old[i]);
		tot += old[i];
	}
	REP(i, 1, n)
		is_old[i] = (old[i] * n >= tot);
		// There must be '()'!
		
	REP(i, 1, m){
		scanf("%d%d", &x, &y);
		if(is_old[x] == is_old[y])
		AddSta(x, true, y, true);
		AddSta(x, false, y, false);
	}
}
bool Solve()
{
	for(int i = 0; i < n * 2; i += 2){
		if(!mark[i] && !mark[i ^ 1]){
			top = 0;
			if(!Dfs(i)){
				while(top) mark[st[top --]] = false;
				if(!Dfs(i ^ 1)) return false;
			}
		}
	}
	REP(i, 1, n){
		if(mark[i - 1 << 1])
			puts(is_old[i]? "A" : "B");
		else puts("C");
	}
	return true;
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n && m){
		Init();
		if(!Solve()) puts("No solution.");
	}
}
