// BZOJ #1488
// Fuboat
// polya
#include <cstdio>
#include <iostream>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a)  MSET(a, 0)
#define LL long long
const int MAXN = 60 + 10, MOD = 997;
int n, ans;
int sum[MAXN * 100], fac[MAXN * 100];
int inv[MOD * 10];
int Ksm(int a, int k, int p = MOD)
{
	int ans = 1;
	while(k) {
		// There is 'k', not 'p'!
		if(k & 1)
			ans = 1LL * ans * a % p;
		a = 1LL * a * a % p;
		k >>= 1;
	}
	return ans;
}
void GetInv(int N = MOD - 1)
{
	inv[1] = 1;
	REP(i, 2, N)
		inv[i] = Ksm(i, MOD - 2);
}
void GetFac(int N = MAXN - 1)
{
	fac[0] = 1;
	REP(i, 1, N)
		fac[i] = fac[i - 1] * i % MOD;
}
int Gcd(int a, int b)
{
	int r;
	while(b) {
		 r = a % b;
		 a = b;
		 b = r;
	}
	return a;
}
int Check(int N)
{
	int tot = 1, cnt = 0;
			
	REP(i, 1, N) {
		cnt ++;
		(tot *= inv[sum[i]]) %= MOD;
		
		if(i == N || sum[i] != sum[i + 1]) {
			(tot *= inv[fac[cnt]]) %= MOD;
			cnt = 0;
		}
	}
	return tot;
}

int Cal(int N)
{
	int tot = 0, down = Check(N);

	REP(i, 1, N) {
		tot += sum[i] / 2;
		REP(j, i + 1, N)
			tot += Gcd(sum[i], sum[j]);
		// Attention!
		// No need to mod when counting 'tot'!
		// (A^k mod p != A^(k mod p) mod p)
	}
	
	return 1LL * fac[n] * Ksm(2, tot) * down % MOD;
}

void Dfs(int N, int last, int had)
{
	if(had == 0) {
		(ans += Cal(N - 1)) %= MOD;
		return ;
	}
	
	REP(i, last, had) {
		sum[N] = i;
		Dfs(N + 1, i, had - i);
	}
}
main()
{
	GetInv();
	GetFac();
	
	scanf("%d", &n);
	Dfs(1, 1, n);
	(ans *= inv[fac[n]]) %= MOD;
	printf("%d\n", ans);
}
