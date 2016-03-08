// BZOJ #2005
// Fuboat
#include <cstdio>
#include <iostream>
#define LL long long
const int MAXN = 100000 + 1000;
int n, m, min;
LL f[MAXN];
int main()
{
	LL ans = 0;
	scanf("%d%d", &n, &m);
	min = std::min(n, m);
	
	for(int i = min; i >= 1; i --) {
		f[i] = 1LL * (n / i) * (m / i);
		// The '()' is necessary!
		for(int j = 2 * i; j <= min; j += i)
			f[i] -= f[j];
	}
	
	for(int i = 1; i <= min; i ++)
		ans += 1LL * f[i] * (2 * (i - 1) + 1);
		printf("%lld\n", ans);
}
