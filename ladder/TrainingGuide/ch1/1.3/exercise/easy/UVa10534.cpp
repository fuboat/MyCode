/*
	FROM: UVa
	TASK: 10534
	ID: fuboat
	ALGORITHM: Dynamic Programming
	DATA STRUCTURE: 
	MISTAKE:
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 10000 + 100, oo = 0x7fffffff;
int a[MAXN], f[MAXN], g[MAXN], m, n;

int main()
{
	while(scanf("%d", &n) == 1){
		int ans = -oo;
		REP(i, 1, n) scanf("%d", &a[i]);
		memset(g, 0x7f, sizeof(g));
		REP(i, 1, n){
			f[i] = lower_bound(g + 1, g + n + 1, a[i]) - g;
			g[f[i]] = a[i];
		}
		memset(g, 0x7f, sizeof(g));
		int tmp;
		Rep(i, n, 1){
			tmp = lower_bound(g + 1, g + n + 1, a[i]) - g;
			chkmax(ans, min(f[i], tmp) * 2 - 1);
			g[tmp] = a[i];
		}
		printf("%d\n", ans);
	}
}
