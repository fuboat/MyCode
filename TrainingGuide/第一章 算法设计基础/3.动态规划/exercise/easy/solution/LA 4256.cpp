/*
	FROM: LA
	TASK: 4256
	ID: fuboat
	DATE: 2015.11.28
	ALGORITHM: Dynamic Programming
	DATA STRUCTURE: default
	MISTAKE:
	1.(line 21, 22) Array is too small;
	2.(line 60) Forget to delete the code for debugging;
	EXPERIENCE: (Sorry, there is nothing)
*/
#include <cstdio>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 100, MAXM = 4950, MAXL = 200, oo = 0x7fffffff;
bool g[MAXN + 10][MAXN + 10];
int f[MAXL + 10][MAXN + 10];
int a[MAXL + 10], m, n, L;

void Init()
{
	int from, to;
	scanf("%d%d", &n, &m);
	memset(g, 0, sizeof(g));
	REP(i, 1, n) g[i][i] = 1;
	REP(i, 1, m){
		scanf("%d%d", &from, &to);
		g[from][to] = g[to][from] = 1;
	}
	scanf("%d", &L);
	REP(i, 1, L) scanf("%d", &a[i]);
}

void Solve()
{
	REP(i, 1, L)
		REP(j, 1, n){
			int &now = f[i][j];
			bool sta = (j != a[i]);
			now = oo;
			REP(k, 1, n)
				if(g[k][j] && f[i - 1][k] != oo)
					chkmin(now, f[i - 1][k] + sta);
		}
	int ans = L;
	REP(i, 1, n) chkmin(ans, f[L][i]);
	printf("%d\n", ans);
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
