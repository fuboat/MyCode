// Codeforces #383D
// Fuboat
#include <cstdio>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 1000 + 100, MAXSUM = 100000, MOD = 1000000007;
int F[MAXSUM], G[MAXSUM];
int main()
{
	int n, x, ans = 0, *f = F + 20000, *g = G + 20000;
	
	scanf("%d", &n);
	REP(i, 1, n) {
		scanf("%d", &x);
		REP(j, - 10000, 10000) {
			(g[j + x] += f[j]) %= MOD;
			(g[j - x] += f[j]) %= MOD;
		}
		g[x] ++;
		g[- x] ++;
		REP(j, - 10000, 10000) {
			f[j] = g[j];
			g[j] = 0;
			// Don't forget!
		}
		(ans += f[0]) %= MOD;
	}
	printf("%d\n", ans);
}
