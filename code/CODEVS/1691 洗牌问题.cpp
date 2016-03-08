#include <cstdio>
#include <iostream>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 20000 + 1000;
bool vis[MAXN];
int f[MAXN];
int n;
void Init()
{
	int cnt(0);
	REP(i, 1, n) {
		f[++ cnt] = i + n;
		f[++ cnt] = i;
	}
}
int Find(int x)
{
	int cnt(0);
	while(!vis[x]) {
		vis[x] = true;
		x = f[x];
		cnt ++;
	}
	return cnt;
}
int Gcd(int a, int b)
{
	int r;
	while(b){
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}
int Lcm(int a, int b) { return a / Gcd(a, b) * b; }
void Solve()
{
	int ans(1);
	REP(i, 1, n * 2)
		if(!vis[i])
			ans = Lcm(ans, Find(i));
	printf("%d\n", ans);
}
int main()
{
	scanf("%d", &n);
	Init();
	Solve();
}
