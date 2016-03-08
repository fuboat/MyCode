// Codeforces #459D
// fuboat
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
typedef long long LL;
const int MAXN = 1e6 + 1e3;
int a[MAXN], f[MAXN], g[MAXN];

void Gsort(int *h, int l, int r)
{
	static int tmp[MAXN];

	int mid = (l + r) >> 1, i = l, j = mid + 1, cnt = l;
	while (i <= mid || j <= r)
		if(i <= mid && (j > r || h[i] < h[j]))
			tmp[cnt ++] = h[i ++];
		else tmp[cnt ++] = h[j ++];
		
	for(i = l; i <= r; i ++)
		h[i] = tmp[i];
}

LL Msort(int l, int r)
{
	if (l == r)
		return 0;

	LL tot = 0, cnt(0);
	int mid = (l + r) >> 1;
	tot += Msort(l, mid);
	tot += Msort(mid + 1, r);
	int i = l, j = mid + 1;

	while (j <= r || i <= mid) {
		if(j <= r && (i > mid || f[i] > g[j])) {
			tot += mid - i + 1;
			j ++;
		} else i ++;
	}

	Gsort(g, l, r);
	Gsort(f, l, r);
	//printf("%d %d %d\n", l, r, tot);
	return tot;
}

int n;
void Init()
{
	static int tmp[MAXN];
	
	int tot;
	scanf("%d", &n);
	REP(i, 1, n) {
		scanf("%d", &a[i]);
		tmp[i] = a[i];
	}
	
	std::sort(tmp + 1, tmp + n + 1);
	tot = std::unique(tmp + 1, tmp + n + 1) - tmp;
	REP(i, 1, n)
		a[i] = std::lower_bound(tmp + 1, tmp + tot, a[i]) - tmp;
}

void Solve()
{
	static int t1[MAXN], t2[MAXN];
	REP(i, 1, n)
		f[i] = ++ t1[a[i]];
	rep(i, n, 1)
		g[i] = ++ t2[a[i]];
		
	printf("%I64d\n", Msort(1, n));
}

int main()
{
	Init();
	Solve();
}
