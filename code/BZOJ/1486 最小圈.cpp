#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>
#define REP(i, x, y) for (int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for (int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0)
#define LL long long
#define LD double
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
const int oo = 0x3f3f3f3f, MAXN = 3000 + 100, MAXM = 10000 + 1000;
const double eps = 3 * 1e-9;
void Readin(int &x)
{
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9')
		c = getchar();
	while ('0' <= c && c <= '9') {
		(x *= 10) += c - '0';
		c = getchar();
	}
}
int Dcmp(double x)
{
	if (x < eps)
		return 0;
	return x > 0? 1 : -1;
}
int n, m, cur, tote;
double minv = oo, maxv = -oo;
int head[MAXN], next[MAXM], to[MAXM];
LD val[MAXM], ValInBegin[MAXM], dis[MAXN];
bool Spfa(int u)
{
	static int in[MAXN];
	int v;
	
	if (in[u] == cur)
		return false;
		
	in[u] = cur;
	for (int i = head[u]; i; i = next[i]) {
		v = to[i];
		if (Chkmin(dis[v], dis[u] + val[i]) && !Spfa(v))
			return false;
//		if (Dcmp(dis[v] - dis[u] - val[i]) > 0) {
//			dis[v] = dis[u] + val[i];
//			if (!Spfa(v))
//				return false;
//		}
	}
	in[u] = 0;
	
	return true;
}
void AddEdge(int u, int v, double w)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
	ValInBegin[tote] = w;
}
bool Check(double x)
{
	cur ++;
	
	REP (i, 1, n)
		dis[i] = 0;
		// The dis must be '0' in the begin;
		
	REP (i, 1, tote)
		val[i] = ValInBegin[i] - x;
	
	REP (i, 1, n) {
	// Try every node;
		if (!Spfa(i))
			return true;
	}
	return false;
}
void Solve()
{
	double l = minv, r = maxv, mid;
	
	while (r - l > eps) {
		mid = l + (r - l) / 2;
		if (Check(mid))
			r = mid;
		else l = mid;
	}
	
	printf("%.8lf\n", l + (r - l) / 2);
}
void Init()
{
	int u, v;
	double w;
	REP (i, 1, m) {
		Readin(u);
		Readin(v);
		scanf("%lf", &w);
		AddEdge(u, v, w);
		Chkmin(minv, w);
		Chkmax(maxv, w);
	}
}
int main()
{
	scanf("%d%d", &n, &m);
	Init();
	Solve();
}
