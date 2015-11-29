/*
	ID: 60303451
	TASK: subset
	LANG: C++
*/
#include <cstdio>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 39 + 10;
long long f[MAXN * MAXN];

int main()
{
	freopen("subset.in", "r", stdin);
	freopen("subset.out", "w", stdout);
	int n;
	scanf("%d", &n);
	if(n % 4 != 0 && (n + 1) % 4 != 0){
		printf("0\n");
		return 0;
	}
	f[0] = 1;
	REP(i, 1, n) Rep(j, (i * (i + 1)) >> 1, 0)
		f[j + i] += f[j];
	printf("%d\n", f[(n * (n + 1)) >> 2] >> 1);
}
