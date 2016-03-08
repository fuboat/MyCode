#include <cstdio>
#include <iostream>
#include <algorithm>
#define REP(i, x, y) for (int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for (int i = x, _ = y; i >= _; i --)
#define LL long long
const int MAXN = 1e5 + 1e3, MOD = 1000007;
int n, p;
int a[MAXN], next[MAXN], vis[MAXN];
struct HashTable{
	int totn;
	LL number[MAXN];
	int head[MOD], next[MAXN], id[MAXN];
	void Insert(LL x, int flag)
	{
		int tmp = x % MOD;
		number[++ totn] = x;
		id[totn] = flag;
		next[totn] = head[tmp];
		head[tmp] = totn;
	}
	int Find(LL x)
	{
		for (int i = head[x % MOD]; i; i = next[i])
			if (number[i] == x)
				return id[i];
		return 0;
	}
} hash;
void Init()
{
	scanf("%d%d", &n, &p);
	REP (i, 1, n)
		scanf("%d", &a[i]);
	std::sort(a + 1, a + n + 1);
	REP (i, 1, n) {
		next[i] = hash.Find(a[i]);
		hash.Insert(1LL * a[i] * p, i);
	}
}
void Solve()
{
	int length, ans = 0, j;
	rep (i, n, 1)
		if (!vis[i]) {
			length = 0;
			j = i;
			while (j) {
				vis[j] = true;
				length ++;
				j = next[j];
			}
			ans += length / 2 + (length & 1);
		}
	printf("%d\n", ans);
}
int main()
{
	Init();
	Solve();
}
