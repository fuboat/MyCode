// UVa11294
// 2-SAT
// Fuboat
// Experience:
// 1.
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
void AddSta(int u, bool v)
{
	u = (u - 1) << 1 | v;
	AddEdge(u ^ 1, u);
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
int Idx()
{
	int x = 0;
	char c = getchar();
	while(c < '0' || c > '9') c = getchar();
	while('0' <= c && c <= '9'){
		(x *= 10) += c - '0';
		c = getchar();
	}
	return x + 1 + (c == 'w'? n : 0);
}
int old[MAXN];
bool is_old[MAXN];
int Init()
{
	tote = 0;
	CLEAR(head);
	CLEAR(mark);
	char s[3];
	int x, y;
	AddSta(1, true);
	AddSta(n + 1, false);
	REP(i, 2, n){
		AddSta(i, true, i + n, true);
		AddSta(i, false, i + n, false);
	}
	REP(i, 1, m){
		x = Idx();
		y = Idx();
		AddSta(x, false, y, false);
	}
}
bool Solve()
{
	bool first = 1;
	for(int i = 0; i <= n * 4 - 1; i += 2){
		top = 0;
		if(!Dfs(i)){
			while(top) mark[st[top --]] = false;
			if(!Dfs(i ^ 1)) return false;
		}
	}
	REP(i, 2, n){
		if(mark[i - 1 << 1]){
			if(!first) putchar(' ');
			else first = false;
			printf("%dh", i - 1);
		}
		if(mark[(i + n) - 1 << 1]){
			if(!first) putchar(' ');
			else first = false;
			printf("%dw", i - 1);
		}
	}
	puts("");
	return true;
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n && m){
		Init();
		if(!Solve()) puts("bad luck");
	}
}
