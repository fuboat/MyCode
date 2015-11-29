/*
	ID: 60303451
	TASK: castle
	LANG: C++
*/
#include <cstdio>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T>bool chkmax(T &x, T y){return y > x? (x = y, true):false;}
template <typename T>bool chkmin(T &x, T y){return y < x? (x = y, true):false;}
const int MAXN = 50 + 10, MAXM = 50 + 10;
bool sta[MAXN][MAXM][5];
int s[MAXN * MAXM], num[MAXN][MAXM];
int m, n, ans, X, Y, cnt;
char D;
int d[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
// 1:west
// 2.north
// 4.east
// 8.south
void Init()
{
	int x;
	scanf("%d%d", &m, &n);
	REP(i, 1, n) REP(j, 1, m){
		scanf("%d", &x);
		REP(k, 0, 3) if(x >> k & 1) sta[i][j][k] = 1;
	}
}

void dfs(int x, int y)
{
	if(x <= 0 || y <= 0 || x > n || y > m) return ;
	num[x][y] = cnt;
	s[cnt] ++;
	REP(i, 0, 3)
		if(!sta[x][y][i] && !num[x + d[i][0]][y + d[i][1]])
			dfs(x + d[i][0], y + d[i][1]);
}

void solve()
{
	cnt = 0;
	int S = 0;
	REP(i, 1, n) REP(j, 1, m)
		if(!num[i][j]){
			cnt ++;
			dfs(i, j);
			chkmax(S, s[cnt]);
		}
	printf("%d\n%d\n", cnt, S);
	REP(j, 1, m) rep(i, n, 1){
			if(j != 1 && sta[i][j][0] && num[i][j] != num[i + d[0][0]][j + d[0][1]] && chkmax(ans, s[num[i][j]] + s[num[i + d[0][0]][j + d[0][1]]]))
				X = i, Y = j - 1, D = 'E';
			if(i != n && sta[i][j][3] && num[i][j] != num[i + d[3][0]][j + d[3][1]] && chkmax(ans, s[num[i][j]] + s[num[i + d[3][0]][j + d[3][1]]]))
				X = i + 1, Y = j, D = 'N';
		}
	printf("%d\n%d %d %c\n", ans, X, Y, D);
}

int main()
{
	freopen("castle.in", "r", stdin);
	freopen("castle.out", "w", stdout);
	Init();
	solve();
}
