// LA3211
// 2-SAT
// Fuboat
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
template<typename T>bool Chkmax(T &x, T y){ return y > x? x = y, true : false; }
/*Public-------------------------------------------------------------*/
const int MAXN = 2000 + 500, MAXM = 4 * MAXN * MAXN;
int n;
int T[MAXN][2];
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
int st[MAXN * 2];// 'int', not 'bool'!
bool mark[MAXN * 2];
void AddSta(int u, bool s1, int v, bool s2){
	u = (u - 1) << 1 | s1;
	v = (v - 1) << 1 | s2;
	AddEdge(u ^ 1, v);
	AddEdge(v ^ 1, u);
	// s1 == 0, u ^ 1 is a true node;
	// s1 == 1, u ^ 1 is a false node;
}
bool Dfs(int u)
{
	// Try marking the node 'u';
	if(mark[u ^ 1]) 
		return false;
	if(mark[u])
		return true;

	st[++ top] = u;
	mark[u] = true;
	for(int i = head[u]; i; i = next[i])
		if(!Dfs(to[i]))
		// contradiction appears;
			return false;
	return true;
}
bool Check(int k)
{
	CLEAR(head);
	//CLEAR(next);
	//CLEAR(to);
	CLEAR(mark);
	//CLEAR(st);
	tote = 0;
	REP(i, 1, n) REP(j, i + 1, n)
	REP(x, 0, 1) REP(y, 0, 1)
		if(abs(T[i][x] - T[j][y]) < k)
			AddSta(i, x ^ 1, j, y ^ 1);

	for(int i = 0; i < n * 2; i += 2)
		if(!mark[i] && !mark[i ^ 1]){
		// If both true node and false node haven't been marked, we need to try;
		// because a node must be true or false, we should decide it;
			top = 0;
			if(!Dfs(i)){
			// If marking true node is leading to no solution;
				while(top) mark[st[top --]] = false;
				// Repeal the wrong decision;
				if(!Dfs(i ^ 1)) return false;
				// If the node always lead to no solution, then the whole question is no solution;
			}
		}
	return true;
}
/*Main Program--------------------------------------------------------*/
int all;
int Init()
{
	//CLEAR(T);
	all = 0;
	REP(i, 1, n) REP(j, 0, 1){
		scanf("%d", &T[i][j]);
		Chkmax(all, T[i][j]);
	}
}
int Solve()
{
	int l, r, mid;
	l = 0, r = all + 1;
	while(l + 1 < r){
		mid = (l + r) >> 1;
		if(Check(mid))
			l = mid;
		else r = mid;
	}
	printf("%d\n", l);
}
int main()
{
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	while(scanf("%d", &n) != EOF && n){
		Init();
		Solve();
	}
}
