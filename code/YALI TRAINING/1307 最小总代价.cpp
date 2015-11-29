#include <cstdio>

inline int min(int x, int y)
{
	return x < y? x : y;
}

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 16, oo = 0x3f3f3f3f;
int f[1 << (MAXN + 1)][MAXN + 1], a[MAXN + 1][MAXN + 1], n, ans = oo;
bool vis[1 << (MAXN + 1)][MAXN + 1]; 

int find(int sta, int now)
{
	if(sta == 0) return 0;
	if(vis[sta][now]) return f[sta][now];
	vis[sta][now] = 1;
	int minx = oo;
	REP(i, 1, n)
		if(sta & 1 << (i - 1))
			minx = min(minx, find(sta ^ 1 << (i - 1), i) + a[now][i]);
	return f[sta][now] = minx;
}
int main()
{
	scanf("%d", &n);
	REP(i, 1, n)
		REP(j, 1, n)
			scanf("%d", &a[i][j]);

	printf("%d\n", find((1 << n) - 1, 0));
	return 0; 
}
	
