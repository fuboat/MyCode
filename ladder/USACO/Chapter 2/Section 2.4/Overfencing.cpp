/*
	ID: 60303451
	TASK: maze1
	LANG: C++11
*/
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
bool chkmax(int &x, int y){return y > x? x = y, true : false;}
bool chkmin(int &x, int y){return y < x? x = y, true : false;}
const int MAXN = 100 + 10;
const int d[][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int s[MAXN][MAXN][4], f[MAXN][MAXN], n, m, ans;
bool vis[MAXN][MAXN];

void Init()
{
	memset(f, 0x7f, sizeof(f));
	char c;
	scanf("%d%d", &n, &m);
	REP(i, 1, m * 2 + 1)
		REP(j, 1, n * 2 + 1){
			c = getchar();
			while(c == '\n') c = getchar();
			if(i % 2 == 0 && j % 2 == 1 && c == '|')
				s[i >> 1][j >> 1][1] = s[i >> 1][(j >> 1) + 1][3] = 1;
			else if(i % 2 == 1 && j % 2 == 0 && c == '-')
				s[i >> 1][j >> 1][2] = s[(i >> 1) + 1][j >> 1][0] = 1;
		}
//	REP(i, 1, m) REP(j, 1, n) REP(k, 0, 3)
//		if(s[i][j][k]) printf("s[%d][%d][%d]\n", i, j, k);
//	puts("");
}

bool ok(int x, int y)
{
	if(x <= 0 || y <= 0 || x > m || y > n) return false;
	vis[x][y] = 1;
	return true;
}

void update(int x, int y, int dis)
{
	if(!f[x][y] || f[x][y] > dis)
		f[x][y] = dis;
//	printf("f[%d][%d]=%d\n", x, y, f[x][y]);
}
void dfs(int x, int y, int dis)
{
//	printf("x = %d, y = %d, dis = %d\n", x, y, dis);
	if(!ok(x, y) || !chkmin(f[x][y], dis)) return;
	REP(i, 0, 3) if(!s[x][y][i])
		dfs(x + d[i][0], y + d[i][1], dis + 1);
}
void clean(){memset(vis, 0, sizeof(vis));}
void Solve()
{
	REP(i, 1, m){
		if(!s[i][1][3]){dfs(i, 1, 1); clean();}
		if(!s[i][n][1]){dfs(i, n, 1); clean();}
	}
	REP(i, 2, n - 1){
		if(!s[1][i][0]){dfs(1, i, 1); clean();}
		if(!s[m][i][2]){dfs(m, i, 1); clean();}
	}
	REP(i, 1, m) REP(j, 1, n) chkmax(ans, f[i][j]);
	printf("%d\n", ans);
}

int main()
{
	freopen("maze1.in", "r", stdin);
	freopen("maze1.out", "w", stdout);
	Init();
	Solve();
}
