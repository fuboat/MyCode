#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 1000 + 200;
int vis[MAXN], f[MAXN], a[MAXN], ff[MAXN];
int cur, minx;
int Update(int x)
{
	int tot(0), mina(0x7fffffff), cnt(0);
	while(vis[x] != cur) {
		vis[x] = cur;
		tot += f[x];
		mina = std::min(mina, f[x]);
		x = a[x];
		cnt ++;
	}
	return std::min(tot + mina * (cnt - 2), tot + minx * (cnt + 1) + mina);
}
int main()
{
	int n, ans, kase(0);
	while(scanf("%d", &n) == 1) {
		ans = 0;
		minx = 0x7fffffff;
		cur ++;
		
		REP(i, 1, n){
			scanf("%d", &a[i]);
			f[i] = a[i];
			minx = std::min(minx, f[i]);
		}
		std::sort(f + 1, f + n + 1);
		REP(i, 1, n)
			ff[f[i]] = i;
		REP(i, 1, n)
			a[i] = ff[a[i]];
		
		REP(i, 1, n)
			if(vis[i] != cur)
				ans += Update(i);
		
		if(ans == 0)
			break;
		printf("Case %d: %d\n", ++ kase, ans);
	}
	return 0;
}
