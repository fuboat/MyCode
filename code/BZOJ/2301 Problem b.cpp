// BZOJ #2301
// Fuboat
// Math
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0)
#define LL long long
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
const int MAXN = 50000 + 1000;
int mu[MAXN], presum[MAXN];
void GetPreSum(int *a, int N)
{
	REP (i, 1, N)
		presum[i] = presum[i - 1] + a[i];
}
void GetMu(int N)
{
	static int pri[MAXN];
	static bool vis[MAXN];
	int totpri = 0;
	// Give 'totpri' the value '0' in the start;
	
	mu[1] = 1;
	REP (i, 2, N) {
		if (!vis[i]) {
			pri[++ totpri] = i;
			mu[i] = -1;
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
int k;
LL Work(int N, int M)
// The function should return 'long long';
{
	N /= k, M /= k;
	int last;
	LL tot = 0;
	if (N > M)
		std::swap(N, M);
	
	for (int i = 1; i <= N; i = last + 1) {
		last = std::min(N / (N / i), M / (M / i));
		tot += 1LL * (N / i) * (M / i) * (presum[last] - presum[i - 1]);
		// Don't forget the '()'!
	}
	
	return tot;
}
void Init()
{
	GetMu(MAXN - 1000);
	GetPreSum(mu, MAXN - 1000);
}
int main()
{
	int T, a, b, c, d;
	scanf("%d", &T);
	Init();
	while (T --) {
		scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
		printf("%lld\n", Work(b, d) - Work(a - 1, d) - Work(b, c - 1) + Work(a - 1, c - 1));
	}
}
