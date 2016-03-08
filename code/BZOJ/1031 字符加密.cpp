#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXS = 200, MAXN = 100000;
void jsort(int *a, int *b, int *sa, int m, int n)
{
	static int c[MAXN];
	
	REP(i, 0, m - 1)
		c[i] = 0;
	REP(i, 0, n - 1)
		c[a[b[i]]] ++;
	REP(i, 1, m - 1)
		c[i] += c[i - 1];
	rep(i, n - 1, 0)
		sa[-- c[a[b[i]]]] = b[i];
}
namespace suffix_array{
	char T[MAXN], ans[MAXN];
	int sa[MAXN], s[MAXN], rank[MAXN], height[MAXN];
	void GetSa(int m, int n)
	{
		static int tmp[MAXN], t1[MAXN], t2[MAXN];
		
		int *x = t1, *y = t2, p, now, last;
		REP(i, 0, n - 1)
			tmp[i] = i;
		REP(i, 0, n - 1)
			x[i] = s[i];
		jsort(x, tmp, sa, m, n);
		for(int k = 1; k <= n; k <<= 1) {
			p = 0;
			REP(i, n - k, n - 1)
				y[p ++] = i;
			REP(i, 0, n - 1)
				if(sa[i] >= k)
					y[p ++] = sa[i] - k;
			jsort(x, y, sa, m, n);
			std::swap(x, y);
			p = 1;
			x[sa[0]] = 0;
			REP(i, 1, n - 1) {
				now = sa[i], last = sa[i - 1];
				x[now] = (y[now] == y[last] && y[now + k] == y[last + k])? p - 1 : p ++;
			}

			if(p >= n)
				break ;
			m = p;
		}
	}
	void Solve(int n)
	{
		int cnt = 0;
		REP(i, 0, n * 2 - 1)
			if(sa[i] < n)
				ans[cnt ++] = s[sa[i] + n - 1] + '!';
		ans[cnt] = 0;
		printf("%s\n", ans);
	}

	void Init()
	{
		scanf("%s", T);
		int n = strlen(T);
		REP(i, 0, n - 1)
			s[i] = s[i + n] = T[i] - '!';
		GetSa(200, n * 2);
		Solve(n);
	}
}
int main()
{
	using namespace suffix_array;
	Init();
}
