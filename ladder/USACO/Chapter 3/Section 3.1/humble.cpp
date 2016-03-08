/*
	ID: fuboat
	TASK: humble
	LANG: C++
*/
#include <cstdio>
#include <algorithm>
#include <iostream>
const int MAXN = 100000 + 100, MAXK = 100 + 100, oo = 0x7fffffff;
int ans[MAXN], s[MAXK], n, k;
void Init()
{
	scanf("%d%d", &k, &n);
	for(int i = 1; i <= k; i ++)
		scanf("%d", &s[i]);
}
void Solve()
{
	int last = ans[0] = 1, minx;
	for(int t = 1; t <= n; t ++){
		last = ans[t - 1]; minx = oo;
		for(int i = 1; i <= k; i ++){
			int next = std::lower_bound(ans, ans + t, last / s[i] + 1) - ans;
			minx = std::min(minx, ans[next] * s[i]);
		}
		last = ans[t] = minx;
	}
	printf("%d\n", ans[n]);
}
int main()
{
	freopen("humble.in", "r", stdin);
	freopen("humble.out", "w", stdout);
	Init();
	Solve();
	fclose(stdin);
	fclose(stdout);
}
