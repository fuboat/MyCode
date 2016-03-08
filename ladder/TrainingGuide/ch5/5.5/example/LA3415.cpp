// LA3415
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
#define LL long long
#define LD double
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXN = 500 + 10, MAXL = 100 + 10, MAXM = MAXN * MAXN;
int totm, totf, n;
/*Edge---------------------------------------*/
int head[MAXN], next[MAXM], to[MAXM];
int tote;
void AddEdge(int u, int v)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
}
/*hungary------------------------------------*/
int ok[MAXN], link[MAXN], vis[MAXN];
int cur;
bool Dfs(int u)
{
	int v;
	for(int i = head[u]; i; i = next[i]){
		v = to[i];
		if(vis[v] == cur) continue;
		vis[v] = cur;
		if(!link[v] || Dfs(link[v])){
			link[v] = u;
			ok[u] = v;
			return true;
		}
	}
	return false;
}
/*Init---------------------------------------*/
struct Student{
	bool sex;
	int tall;
	char s[2][MAXL];
	bool Together(Student a){
		if(abs(tall - a.tall) > 40 || sex == a.sex || strcmp(s[0], a.s[0]) || !strcmp(s[1], a.s[1]))
			return true;
		return false;
	}
	bool Get(){
		char c[10];
		scanf("%d%s%s%s", &tall, c, s[0], s[1]);
		sex = (c[0] == 'M'? false : true);
		return sex;
	}
}s[MAXN], boy[MAXN], girl[MAXN];

void Init()
{
	CLEAR(head);
	CLEAR(vis);
	CLEAR(link);
	CLEAR(ok);
	tote = totm = totf = 0;
	REP(i, 1, n)
		if(s[i].Get()) girl[++ totf] = s[i];
		else boy[++ totm] = s[i];

	REP(i, 1, totm)
		REP(j, 1, totf)
			if(!boy[i].Together(girl[j]))
				AddEdge(i, j);
}

void Solve()
{
	cur = 0;
	int ans = 0;
	REP(i, 1, totm)
		if(!ok[i]){
			cur ++;
			if(Dfs(i))
				ans ++;
		}
	printf("%d\n", n - ans);
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
