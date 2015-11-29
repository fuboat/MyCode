#include <cstdio>
#include <cstring>
#include <cstdlib>
#define REP(i, x, y)  for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y)  for(int i = x, _ = y; i >= _; i --)
const int MAXN = 16, MAXM = 16, oo = 0x7fffffff;
int a[MAXN + 1][MAXN + 1], s[MAXN + 1][MAXN + 1], t[MAXN + 1][MAXN + 1], dp[MAXN + 2];
int n, m ,r, c, ans = oo;

int min(int x, int y)
{
	return x < y ? x : y;
}

void build(void)
{
	memset(t, 0, sizeof(t));
	REP(i, 1, m)
		REP(j, 1, r - 1)
			t[0][i] += abs(s[j][i] - s[j + 1][i]);
	REP(i, 1, m)
		REP(j, i + 1, m){
			t[i][j] += t[0][j];
			REP(k, 1, r)
				t[i][j] += abs(s[k][i] - s[k][j]);
		}
}

void DP()
{
	memset(dp, 0, sizeof(dp));
	REP(i, 1, m) dp[i] = t[0][i];
	REP(i, 2, c)
		rep(j, m, i){
			dp[j] = oo;
			REP(k, i - 1, j - 1)
				dp[j] = min(dp[j], dp[k] + t[k][j]);
		}
	REP(i, c, m)
		ans = min(ans, dp[i]);
}

void dfs(int has, int biggest)
{
	if(has == r){
		build();
		DP();
		return ;
	}
	if(n - biggest < r - has) return ;
	REP(i, biggest + 1, n){
		//memcpy(s + has + 1, s + i, sizeof(a)/(MAXN + 1));
		REP(j, 1, m) s[has + 1][j] = a[i][j];
		dfs(has + 1, i);
	}
}

int main()
{
	scanf("%d %d %d %d", &n, &m, &r, &c);
	REP(i, 1, n) REP(j, 1, m)
		scanf("%d", &a[i][j]);
	dfs(0, 0);
	printf("%d\n", ans);
}

