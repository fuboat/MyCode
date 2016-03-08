// BZOJ #3994
// Fuboat
// Math
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0)
using std::min;
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int MAXN = 50000 + 1000;
int f[MAXN], PreSum[MAXN], mu[MAXN], sum[MAXN];
int GetF(int N)
{
	if (f[N])
		return f[N];
	int last = 0;
		
	for (int i = 1; i <= N; i = last + 1) {
		last = N / (N / i);
		f[N] += (N / i) * (last - i + 1);
		// 'last - i + 1', not 'last - i'!
	}
	return f[N];
}
void GetMu(int N)
{
	static int pri[MAXN] = {};
	static bool vis[MAXN] = {};
	int totpri = 0;
	
	mu[1] = 1;
	REP (i, 2, N) {
		if (!vis[i]) {
			mu[i] = -1;
			pri[++ totpri] = i;
		}
		REP (j, 1, totpri) {
			if (i * pri[j] > N)
				break;
			
			vis[i * pri[j]] = true;
			if (i % pri[j] == 0) {
				mu[i * pri[j]] = 0;
				break;
			} else
				mu[i * pri[j]] = -mu[i];
		}
	}
}
int main()
{
	int T, n, m, last;
	long long ans;
	GetMu(MAXN - 1000);
	PreSum[0] = sum[0] = 0;
	REP (i, 1, MAXN - 1000) {
		PreSum[i] = PreSum[i - 1] + mu[i];
		sum[i] = sum[i - 1] + i;
	}
	
	scanf("%d", &T);
	while (T --) {
		ans = 0;
		scanf("%d%d", &n, &m);
		if (n > m)
			std::swap(n, m);
			
		for (int i = 1; i <= n; i = last + 1) {
			last = min(n / (n / i), m / (m / i));
			ans += 1LL * GetF(n / i) * GetF(m / i) * (PreSum[last] - PreSum[i - 1]);
		}
		printf("%lld\n", ans);
	}
}
