// BZOJ #3309
// Fuboat
// Math
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for (int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for (int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0)
#define LL long long
const int MAXN = 1e7 + 1e3;
int g[MAXN];
void GetG(int N = MAXN - 1000)
{
	static int pri[MAXN / 5], cnt[MAXN], last[MAXN];
	static bool vis[MAXN];
	
	int totpri = 0, now, j;
	cnt[1] = g[1] = last[1] = 0;
	
	REP (i, 2, N) {
		if (!vis[i]) {
			pri[++ totpri] = i;
			g[i] = 1;
			cnt[i] = 1;
			last[i] = 1;
		}
		
		j = 0;
		do {
			j ++;
			if (i * pri[j] > N)
				break;
			
			now = i * pri[j];
			vis[now] = true;
			if (i % pri[j] == 0) {
				cnt[now] = cnt[i] + 1;
				last[now] = last[i];
				if (last[now] == 1) {
				// Special situation...
				// 'now' only have one prime-divisor...
				// In this case, 'g[now] = 1'...
					g[now] = 1;
					break;
				}
			} else {
				cnt[now] = 1;
				last[now] = i;
			}
			g[now] = cnt[now] == cnt[last[now]]? - g[last[now]] : 0;
		} while (i % pri[j] != 0);
	}
	REP (i, 2, N)
		g[i] += g[i - 1];
}
LL Work(int M, int N)
{
	int last;
	LL tot = 0;
	if (N > M)
		std::swap(N, M);
	
	for (int i = 1; i <= N; i = last + 1) {
		last = std::min(M / (M / i), N / (N / i));
		tot += 1LL * (M / i) * (N / i) * (g[last] - g[i - 1]);
	}
	return tot;
}
int main()
{
	GetG();
	
	int T, x, y; 
	scanf("%d", &T);
	while (T --) {
		scanf("%d%d", &x, &y);
		printf("%lld\n", Work(x, y));
	}
}
