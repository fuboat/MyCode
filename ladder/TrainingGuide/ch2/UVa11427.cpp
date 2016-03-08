// UVa11427
// Fuboat
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define CLEAR(a) memset(a, 0, sizeof(a))
#define LD double
const int MAXN = 100 + 100;
int X, Y, n;
LD f[MAXN][MAXN];
double p;
void Solve()
{
	CLEAR(f);
	int j;
	LD ans = 0;
	f[0][0] = 1;
	REP(i, 1, n){
		j = 0;
		while(X * i >= j * Y){
			// Don't forget the 
			f[i][j] = f[i - 1][j - 1] * p + f[i - 1][j] * (1 - p);
			if(i == n) ans += f[i][j];
			j ++;
		}
	}
	printf("%d\n", int(1 / ans));
	// 'int()' is similar to 'floor()'
}
int main()
{
	int T;
	scanf("%d", &T);
	REP(i, 1, T){
		scanf("%d/%d%d", &X, &Y, &n);
		p = 1.0 * X / Y;
		printf("Case #%d: ", i);
		Solve();
	}
}
