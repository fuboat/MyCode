// LA3126
// Bitpartitle
// Fuboat
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define Pii pair<int, int>
#define LL long long
#define LD double
#define X first
#define Y second
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXN = 1000 + 10, MAXM = MAXN * MAXN;
int n;
/*Edge----------------------------------*/
int head[MAXN];
int next[MAXM], to[MAXM];
int tote;
void AddEdge(int u, int v)
{
	u <<= 1;
	(v <<= 1) |= 1;
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
}
/*Init----------------------------------*/
int Getnum()
{
	int x = 0;
	char c = getchar();
	while(!('0' <= c && c <= '9')) c = getchar();
	while('0' <= c && c <= '9'){
		(x *= 10) += c - '0';
		c = getchar();
	}
	return x;
}
inline int Dis(Pii  a, Pii b){ return abs(a.X - b.X) + abs(a.Y - b.Y); }
struct Task{
	Pii u, v;
	int time;
	bool Ok(Task a){ return Dis(u, v) + Dis(v, a.u) + time + 1 <= a.time; }
	bool operator < (const Task &a) const{ return time < a.time; }
	void Get(){
		time = Getnum() * 60 + Getnum();
		scanf("%d%d%d%d", &u.X, &u.Y, &v.X, &v.Y);
	}
}S[MAXN];
/*Bitpartite----------------------------*/
int cur;
int vis[MAXN], link[MAXN];
bool Dfs(int u)
{
	int v;
	for(int i = head[u]; i; i = next[i]){
		v = to[i];
		if(vis[v] == cur) continue;
		vis[v] = cur;
		if(!link[v] || Dfs(link[v])){
			link[v] = u;
			return true;
		}
	}
	return false;
}
/*Main program--------------------------*/
void Init()
{
	CLEAR(head);
	CLEAR(link);
	CLEAR(vis);
	tote = 0;
	REP(i, 1, n)
		S[i].Get();
	//sort(S + 1, S + n + 1);
	REP(i, 1, n) REP(j, 1, n)
		if(S[i].Ok(S[j]))
			AddEdge(i, j);
}
void Solve()
{
	int tot = 0;
	cur = 0;
	REP(i, 1, n){
		cur ++;
		if(Dfs(i << 1))
			tot ++;
	}
	printf("%d\n", n - tot);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		Init();
		Solve();
	}
}
