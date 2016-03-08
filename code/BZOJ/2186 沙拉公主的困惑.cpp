// BZOJ #2186
// Fuboat
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 1e7 + 1e3;

int totpri;
int pri[MAXN], ans[MAXN], inv[MAXN];
bool flag[MAXN];

int ExGcd(int a, int b, int& x, int& y)
{
	if (!b)  {
		x = 1;
		y = 0;
		return;
	} else {
		ExGcd(b, a % b, y, x);
		y -= a / b * x; 
	}
}

int GetInv(int s)
{
	int x, y;
	ExGcd(s, MOD, x, y);
	return (x + MOD) % MOD; 
}

void GetPrime(int N)
{
	int prime;
	
	REP(i, 2, N) {
		if(!flag[i]) { 
			pri[++ totpri] = i;
			inv[i] = GetInv(i);
		}

		REP(j, 1, totpri) {
			prime = pri[j];
			if(i * prime > N)
				break;
			flag[i * prime] = true;
			inv[i * prime] = inv[i] * inv[prime]; 
			if(i % prime == 0)
				break;
		}
	}
}

int fac[MAXN];
void GetFac(int N)
{
	fac[0] = 1;
	REP(i, 1, N)
		fac[i] = 1LL * fac[i - 1] * i % MOD;
}

void GetAns(int N)
{
	ans[1] = 1;
	REP(i, 2, N) {
		ans[i] = ans[i - 1];
		if(!flag[i])
			ans[i] = 1LL * ans[i] * (i - 1) % MOD * inv[i] % MOD;
			// Pay attention!
			// mod twice, or 'long long' is not enough!
	}
}

int main()
{
	int T, n, m;
	scanf("%d%d", &T, &MOD);
	GetPrime(1e7);
	GetInv(1e7);
	GetFac(1e7);
	GetAns(1e7);

	while(T --) {
		scanf("%d%d", &n, &m);
		printf("%d\n", int(1LL * fac[n] * ans[m] % MOD));
	}
}
