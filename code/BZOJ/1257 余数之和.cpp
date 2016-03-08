// BZOJ #1257
// Fuboat
// Math

// ����ͻ��Ժ�����ʲô��ϵ��
// ��ʾ�����ô��۲취���ġ���
// �϶����Ͽ������ˣ�û��ϸ�����Ժ������������������� 
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
