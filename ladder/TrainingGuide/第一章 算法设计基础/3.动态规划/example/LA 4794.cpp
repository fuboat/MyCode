/*
	mistake:
	1. Forget to delete the code for debuging;
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 15, MAXX = 100, MAXY = 100, MAXA = 10000;
#define REP(i, x, y) for(int i = x; i <= y; i ++)
int f[MAXX + 10][1 << MAXN], sum[1 << MAXN], to[MAXN + 10], n, all;
bool vis[MAXX + 10][1 << MAXN];
void init()
{
	all = (1 << n) - 1;
	REP(i, 0, n - 1)  scanf("%d", &to[i]);
	REP(i, 1, all){
		sum[i] = 0;
		REP(j, 0, n - 1)
			if(i & 1 << j) sum[i] += to[j];
	}
}

int bitcount(int x){return x == 0? 0 : bitcount(x >> 1) + (x & 1);}

bool dp(int x, int sta)
{
	if(bitcount(sta) == 1) return f[x][sta] = 1;
	if(vis[x][sta]) return f[x][sta];
	vis[x][sta] = 1;
	int &ans = f[x][sta];
	int S = sum[sta], y = S / x;
	for(int i = (sta - 1) & sta; i; i = (i - 1) & sta){
		int s = sum[i];
		if(s % x == 0 && dp(min(x, s / x), i) && dp(min(x, (S - s) / x), sta - i))
			return ans = 1;
		else if(s % y == 0 && dp(min(y, s / y), i) && dp(min(y, (S - s) / y), sta - i))
			return ans = 1;
	}
	
	return ans = 0;
}

int main()
{
	int now = 0;
	while(scanf("%d", &n) && n){
		memset(f, 0, sizeof(f));
		memset(vis, 0, sizeof(vis));
		memset(sum, 0, sizeof(sum));
		int x, y;
		scanf("%d%d", &x, &y);
		init();
		printf("Case %d: ", ++ now);
		if(x * y != sum[all] || !dp(min(x, y), all)) printf("No\n");
		else printf("Yes\n");
	}
}
