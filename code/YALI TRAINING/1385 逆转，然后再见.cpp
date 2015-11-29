#include <cstdio>
#include <cstring>
#include <iostream>

inline void update(int &x, int y)
{
	if(y < x) x = y;
	return;
}

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const  int MAXN = 100, oo = 0x7fffffff;
int f[MAXN + 1][MAXN + 1][MAXN + 1], d[MAXN + 1][MAXN + 1], n;
int main()
{
	scanf("%d", &n);
	REP(i, 1, n)
		REP(j, i + 1, n)
			scanf("%d", &d[i][j]);
	memset(f, 0x7f, sizeof(f));
	f[1][1][1] = 0;

	REP(i, 1, n)
		REP(j, 1, i)
			REP(k, 1, j){
				int tmp = f[i][j][k];
				update(f[i + 1][j][k], tmp + d[i][i + 1]);
				update(f[i + 1][i][k], tmp + d[j][i + 1]);
				update(f[i + 1][i][j], tmp + d[k][i + 1]);
			}
	int ans = oo;
	REP(i, 1, n)
		REP(j, 1, i - 1)
			update(ans, f[n][i][j]);
	printf("%d\n", ans);
	return 0;
}
				
				
