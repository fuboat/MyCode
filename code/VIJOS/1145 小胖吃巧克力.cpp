#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
typedef double LD;
const int MAXN = 1000 + 100;
int c, n, m;
LD f[MAXN][MAXN];
bool vis[MAXN][MAXN];
LD DP(int i, int j)
{
	if(i > n || j > c)
		return 0.0;
	if(i == 0)
		return 1.0 * (j == 0);
	if(j < 0)
		return 0.0;
	if(vis[i][j]) return f[i][j];
	vis[i][j] = true;
	
	f[i][j] = DP(i - 1, j - 1) * (c - j + 1) / c + DP(i - 1, j + 1) * (j + 1) / c;
	//printf("f[%d][%d] = %3.lf\n", i, j, f[i][j]);
	return f[i][j];
}
int main()
{
	while(scanf("%d", &c) == 1 && c){
		memset(vis, 0, sizeof(vis));
		scanf("%d%d", &n, &m);
		if(n > 1000)
			n = 1000 + (n & 1);
		printf("%.3lf\n", DP(n, m));
	}
}
