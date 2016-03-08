// BZOJ #2154
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
#define LL long long
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int MAXN = 1e7 + 1e3;
const LL MOD = 20101009;
int mu[MAXN];
void GetMu(int N = MAXN - 1000)
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
int n, m;
int pre2[MAXN], pre[MAXN];
inline int Sum(int x, int y)
{
	return (1LL * x * (x + 1) / 2) % MOD * (1LL * y * (y + 1) / 2 % MOD) % MOD;
	// Pay attention there!
	// Which writing style is OK?
	// (Of course this...)
}
int GetF(int x, int y)
{
	int last, tot = 0;
	if (x > y)
		std::swap(x, y);
	
	for (int i = 1; i <= x; i = last + 1) {
		last = std::min(x / (x / i), y / (y / i));
		(tot += 1LL * (pre2[last] - pre2[i - 1]) * Sum(x / i, y / i) % MOD) %= MOD;
	}
	return tot;
}
void Init()
{
	int N;
	scanf("%d%d", &n, &m);
	N = std::max(n, m);
	GetMu(N);
	
	REP (i, 1, N) {
		pre[i] = (pre[i - 1] + i) % MOD;
		pre2[i] = (pre2[i - 1] + 1LL * i * i * mu[i] % MOD) % MOD;
		// 'pre[]' and 'pre2[]' is easy to mix up when coding.
		// Don't be confused again.
	}
}
void Solve()
{
	int last, tot = 0;
	
	if (n > m)
		std::swap(n, m);
		
	for (int i = 1; i <= n; i = last + 1) {
		last = std::min(n / (n / i), m / (m / i));
		(tot += 1LL * (pre[last] - pre[i - 1]) % MOD * GetF(n / i, m / i) % MOD) %= MOD;
	}
	
	if (tot < 0)
		tot += MOD;
	printf("%d\n", tot);
}
int main()
{
	Init();
	Solve();
}
