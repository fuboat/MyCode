// UVa11021
// Fuboat
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 1000 + 10, MAXM = 1000 + 10, MAXK = 1000 + 10;
// n: How many child is possible;
// m: Which day the question needs;
// k: How many tribles in the start;
typedef double LD;
int n, k, m;
LD p[MAXN];
void Init()
{
	REP(i, 0, n - 1)
		scanf("%lf", &p[i]);
}
LD func(LD x)
{
	LD ans = p[0], tmp(1.0);
	REP(i, 1, n - 1)
		ans += (tmp *= x) * p[i];
	return ans;
}
void Solve()
{
	LD tmp, ans(0);
	REP(i, 1, m)
		ans = func(ans);
	printf("%.7lf\n", pow(ans, k));
}
int main()
{
	int kase;
	scanf("%d", &kase);
	REP(i, 1, kase){
		printf("Case #%d: ", i);
		scanf("%d%d%d", &n, &k, &m);
		Init();
		Solve();
	}
}
