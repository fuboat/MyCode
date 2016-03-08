/*
	ID: 60303451
	TASK: money
	LANG: C++11
*/
#include <cstdio>
int a[26];
long long f[10001];
int main()
{
	freopen("money.in", "r", stdin);
	freopen("money.out", "w", stdout);
	f[0] = 1;
	int l, n;
	scanf("%d%d", &n, &l);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	for(int j = 1; j <= n; j ++)
		for(int i = 1; i <= l; i ++)
			if(i - a[j] >= 0) f[i] += f[i - a[j]];
	printf("%lld\n", f[l]);
}
