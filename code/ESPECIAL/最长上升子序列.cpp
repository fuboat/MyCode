#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXL = 100000, oo = 0x3f3f3f3f;
int a[MAXL + 2], g[MAXL + 2], up, down;
int main()
{
	int n;
	scanf("%d", &n);
	REP(i, 1, n)
		scanf("%d", &a[i]);
	memset(g, 0x7f, sizeof(g));
	for(int i = 1; i <= n;i ++)
	{
		int k = lower_bound(g + 1, g + n + 1, a[i]) - g;
		g[k] = a[i];
		up = max(up, k);
	}
	printf("%d\n", up);
}
		
