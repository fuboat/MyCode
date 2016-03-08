/*
	mistake:
	1. The condition of 'chkmax(f[i], f[j] + 1)' is 'g[i ^ j] == all', not 'g[i ^ j] > 0';
	2. all = '(1 << n) - 1', not '1 << n - 1';
	3. '(i | j) == i' is different from 'i | j == i';
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 1 << 16;
#define REP(i, x, y) for(int i = x; i <= y; i ++)
#define Rep(i, x, y) for(int i = x; i >= y; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
int n, all;
int sta[MAXN + 10], f[MAXN + 10], g[MAXN + 10], tmp[20], tmp_cnt;

void init()
{
	REP(i, 0, all){
		g[i] = 0;
		REP(j, 0, n - 1)
			if(i & (1 << j))
				g[i] |= sta[j];
	}
}

void dfs(int old, int now, int cnt)
{
	if(cnt == tmp_cnt){
		if(now && g[now] == all) chkmax(f[old], f[old ^ now] + 1);
		return ;
	}
	dfs(old, now ^ tmp[cnt], cnt + 1);
	dfs(old, now, cnt + 1);
}

int main()
{
	int cnt, x, now = 0;
	while(scanf("%d", &n) && n){
		all = (1 << n) - 1;
		REP(i, 0, n - 1){
			scanf("%d", &cnt);
			sta[i] = 1 << i;
			while(cnt --){
				scanf("%d", &x);
				sta[i] |= 1 << x;
			}
		}
		init();
		REP(i, 1, all){
			f[i] = 0;
			/*
			int j = i;
			tmp_cnt = 0;
			REP(j, 0, n - 1)
				if(i & 1 << j)
					tmp[tmp_cnt ++] = 1 << j;
			dfs(i, i, 0);
			*/
			for(int j = i; j; j = (j - 1) & i)
				if(g[j] == all) chkmax(f[i], f[i ^ j] + 1);
		}
		printf("Case %d: %d\n", ++ now, f[all]);
	}
}
