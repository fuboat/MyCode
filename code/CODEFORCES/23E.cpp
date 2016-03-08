#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream> 
#define REP(i, x, y) for (int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for (int i = x, _ = y; i >= _; i --)
#define LL long long
#define TreeREP(i, u) for (int i = head[u]; i; i = next[i])
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0)
template <typename T> bool Chkmax(T &x, T y) { return x < y? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int MAXN = 700 + 100, MAXM = MAXN * 2, MOD = 1e8, BIT = 8;
int n, tote;
bool vis[MAXN];
int head[MAXN], to[MAXM], next[MAXM], size[MAXN];
struct Bignum{
	int n;
	LL s[20];
	Bignum() { CLEAR(s); }
	Bignum(int i)
	{
		CLEAR(s);
		s[0] = i;
		n = 1;
	}
	Bignum operator * (const Bignum &x) const {
		Bignum y;
		int now;
		REP (i, 0, n - 1)
			REP (j, 0, x.n - 1) {
				now = i + j;
				y.s[now] += s[i] * x.s[j]; 
				y.s[now + 1] += y.s[now] / MOD;
				y.s[now] %= MOD;
			}
		y.n = n + x.n;
		while (!y.s[y.n - 1])
			y.n --;
		return y;
	}
	bool operator < (const Bignum &x) const {
		if (n != x.n)
			return n < x.n;
		rep (i, n - 1, 0)
			if (s[i] != x.s[i])
				return s[i] < x.s[i];
		return 0;
	}
} dp[MAXN][MAXN];
void Print(const Bignum &x, char *s = "")
{
	bool flag = false;
	rep (i, x.n, 0) {
		if (x.s[i] == 0 && !flag)
			continue;
		printf(flag? "%.8d" : "%d", (int) x.s[i]);
		flag = true;
	}
	if (!flag)
		putchar('0');
	printf("%s", s);
}
void AddEdge(int u, int v)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
}
void Dfs(int u)
{
	int v;
	vis[u] = true;
	dp[u][1] = size[u] = 1;

	TreeREP (i, u) {
		v = to[i];
		if (vis[v])
			continue;
		Dfs(v);

		// dp[u][i]表示u的父亲的连通块在子树u中有i个时的最大值（不考虑这i个的贡献）; 
		rep (j, size[u], 0)
			rep (k, size[v], 0)
				Chkmax(dp[u][j + k], dp[u][j] * dp[v][k]);

		size[u] += size[v];
	}
	
	// 父亲不选该子树，那么dp[u][i] * i 便是方案的一种（考虑了这i个的贡献）;  
	REP (i, 1, size[u])
		Chkmax(dp[u][0], dp[u][i] * i);
}
void Init()
{
	int u, v;
	
	scanf("%d", &n);
	REP (i, 1, n - 1) {
		scanf("%d%d", &u, &v);
		AddEdge(u, v);
		AddEdge(v, u);
	}
}
void Solve()
{
	int maxx = 0;
	Dfs(1);
	Print(dp[1][0], "\n"); 
}
int main()
{
	Init();
	Solve();
}
