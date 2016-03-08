// BZOJ #1010
// Fuboat
#include <cstdio>
#include <queue>
#define LL long long
#define REP(i, x, y) for (int i = x, _ = y; i <= _; i ++)
const int MAXN = 50000 + 1000;
int q[MAXN];
LL sum[MAXN], f[MAXN], dp[MAXN];
int n, l, head, tail;

LL F(int x)
{
	return dp[x] + (f[x] + l) * (f[x] + l);
}
double Slop(int i, int j)
{
	return (F(j) - F(i)) / 2.0 / (f[j] - f[i]);
}
void Init()
{
	REP (i, 1, n) {
		scanf("%lld", &sum[i]);
		sum[i] += sum[i - 1];
		f[i] = sum[i] + i;
	}
}
void Solve()
{
	int u;
	q[++ tail] = 0;
	head = 1;
	REP (i, 1, n) {
		while (head < tail && Slop(q[head], q[head + 1]) <= f[i])
			head ++;
		dp[i] = f[i] - f[q[head]] - l;
		dp[i] *= dp[i];
		dp[i] += dp[q[head]];
		while (head < tail && Slop(q[tail - 1], q[tail]) > Slop(q[tail], i))
			tail --;
		q[++ tail] = i;
	}
	printf("%lld\n", dp[n]);
}
int main()
{
	scanf("%d%d", &n, &l);
	l ++;
	Init();
	Solve();
}
