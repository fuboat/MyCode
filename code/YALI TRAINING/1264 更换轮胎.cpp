#include <cstdio>
void _min(int &x, int y){if(y < x) x = y;}
void _max(int &x, int y){if(y > x) x = y;}
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 1000, MAXM = 1000, MAXC = 1000000, oo = 0x7fffffff;
int f[MAXN + 10][MAXM + 10], t[MAXN + 10][MAXM + 10];
int n, m, c;
int main()
{
	scanf("%d%d%d", &n, &m, &c);
	REP(i, 1, n) REP(j, 1, m)
		scanf("%d", &t[i][j]);
	REP(i, 1, m) f[1][i] = t[1][i];
	REP(i, 1, n - 1){
		int minx = oo;
		REP(j, 1, m){
			f[i + 1][j] = f[i][j] + t[i + 1][j];
			_min(minx, f[i][j]);
		}
		REP(j, 1, m)
			_min(f[i + 1][j], minx + c + t[i + 1][j]);
	}
	int ans = oo;
	REP(i, 1, m) _min(ans, f[n][i]);
	printf("%d\n", ans);
	return 0;
}
		
