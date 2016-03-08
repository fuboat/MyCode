#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i <= _; i ++)
template <typename T> bool Chkmax(T &x, T y){ return y > x? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y){ return y < x? x = y, true : false; }
const int MAXN = 200 + 100, MAXP = 200 + 100;
const LL MAXX = 1e9;
bool vis[MAXN];
int f[MAXP][MAXN];
int n, p;
int Gcd(int a, int b)
{
	int r;
	while(b != 0){
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}
LL Lcm(int a, int b){ return 1LL * a / Gcd(a, b) * b; }
int Find(int x, int y, int *rod)
{
	int cnt(0), from(x);
	
	while(!cnt || x != y){
		if(cnt && x == from)
			return MAXX;
		x = rod[x];
		cnt ++;
	}
	return cnt;
}
void Init()
{
	REP(i, 1, n)
		REP(j, 1, p)
			scanf("%d", &f[j][i]);
}
void Update(int *rod, int *F)
{
	static int tmp[MAXN];
	REP(i, 1, n)
		tmp[i] = F[rod[i]];
	REP(i, 1, n)
		rod[i] = tmp[i];
}
LL Work(int x)
{
	static int rod[MAXN], tmp[MAXN];
	bool flag(true);
	int pos(x + 1), cnt(0), temp;
	LL tot(1);
	
	REP(i, 1, n)
		tmp[i] = rod[i] = i;
	REP(i, 1, x)
		Update(tmp, f[i]);
	REP(i, 1, n)
		if(tmp[i] != i) {
			flag = 0;
			break;
		}
	if(flag && x)
		return x;
	
	while(cnt < p) {
		Update(rod, f[pos]);
		cnt ++;
		pos ++;
		if(pos > p)
			pos -= p;
	}
	
	memset(vis, 0, sizeof(vis));
	REP(i, 1, n) {
		temp = Find(tmp[i], i, rod);
		if(temp)
			tot = Lcm(tot, temp);
	}
	
	return tot * p + x;
}
void Solve()
{
	bool flag(true);
	LL ans(1LL << 50);

	REP(i, 0, p - 1)
		Chkmin(ans, Work(i));
	
	if(ans <= MAXX)
		printf("%d\n", int(ans));
	else puts("No one knows.");
}
int main()
{
	scanf("%d%d", &n, &p);
	Init();
	Solve();
}
