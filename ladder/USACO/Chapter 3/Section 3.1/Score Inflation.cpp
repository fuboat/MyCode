/*
	ID: fuboat
	TASK: inflate
	LANG: C++
	ALGORITHM: Dynamic Programming
*/ 
#include <cstdio>
#include <iostream>
using std::max;
const int MAXM = 10000 + 1000;
int f[MAXM]; 
int main()
{
	freopen("inflate.in", "r", stdin);
	freopen("inflate.out", "w", stdout);
	int n, w, c, m;
	scanf("%d%d", &m, &n);
	for(int i = 1; i <= n; i ++){
		scanf("%d%d", &w, &c);
		for(int j = c; j <= m; j ++)
			f[j] = max(f[j], f[j - c] + w);
	}
	printf("%d\n", f[m]);
}
