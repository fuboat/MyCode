// BZOJ #1004
// Fuboat
// Burnside
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector> 
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#define CLEAR(a) memset(a, 0, sizeof(a))
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int MAXS = 20 + 2, MAXN = 60 + 10;

int sum1, sum2, sum3, m, MOD, n;
int f[MAXS][MAXS][MAXS];
int Dp(int x, int *sz)
{
	CLEAR(f);
	f[0][0][0] = 1;

	REP(z, 1, x)
		rep(i, sum1, 0)
			rep(j, sum2, 0)
				rep(k, sum3, 0)
				// ÈýÎ¬01±³°ü 
				{
					if(i >= sz[z])
						(f[i][j][k] += f[i - sz[z]][j][k]) %= MOD;
					if(j >= sz[z])
						(f[i][j][k] += f[i][j - sz[z]][k]) %= MOD;
					if(k >= sz[z])
						(f[i][j][k] += f[i][j][k - sz[z]]) %= MOD;
				}

	return f[sum1][sum2][sum3];
}

int next[MAXN], sz[MAXN];
bool vis[MAXN];
void Find(int x, int cur)
{
	sz[cur] = 0;

	while(!vis[x]) {
		vis[x] = true;
		x = next[x];
		sz[cur] ++;
	}
}
int Update()
{
	int sum = 0;
	CLEAR(vis);

	REP(i, 1, n)
		scanf("%d", &next[i]);

	REP(i, 1, n)
		if(!vis[i])
			Find(i, ++ sum);

	return sum;
}

int GetInv(int x)
{
	if(x == 1)
		return 1;
	return MOD - 1LL * MOD / x * GetInv(MOD % x) % MOD;
}

int main()
{
	int ans = 0;
	scanf("%d%d%d%d%d", &sum1, &sum2, &sum3, &m, &MOD);
	n = sum1 + sum2 + sum3;

	REP(i, 1, m)
		ans = (0LL + ans + Dp(Update(), sz)) % MOD;

	REP(i, 1, n)
		sz[i] = 1;
	ans = (0LL + ans + Dp(n, sz)) % MOD;
	// Doing nothing is also one thing of all;
	printf("%d\n", int(ans * GetInv(m + 1)) % MOD);
}
