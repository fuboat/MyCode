// BZOJ #1257
// Fuboat
// Math

// 这题和积性函数有什么关系？
// 表示我是用打表观察法做的……
// 肯定是上课走神了，没仔细听积性函数的做法（大雾）…… 
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
int min(int x, int y) { return x < y? x : y; }

int main()
{
	int mid, head, tail, n, m;
	long long ans = 0;

	scanf("%d%d", &n, &m);
	mid = sqrt(m);

	REP(i, 1, mid) {
		head = m / (i + 1) + 1;
		tail = min(m / i, n);
		if(head > n)
			continue;

		ans += 1LL * (m % head + m % tail) * (tail - head + 1) / 2;
	}

	tail = min(n, m / (mid + 1));
	REP(i, 1, tail)
		ans += m % i;

	if(n > m)
		ans += 1LL * (n - m) * m;
		// '1LL' is necessary!

	printf("%lld\n", ans);
}
