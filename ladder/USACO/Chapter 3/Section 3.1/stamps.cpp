/*
	ID: fuboat
	TASK: stamps
	LANG: C++
*/
#include <cstdio>
#include <iostream>
using std::min;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXK = 200 + 100, MAXN = 50 + 20;
int s[MAXN], n, k;
int f[2000000 + 100];
void Init()
{
	scanf("%d%d", &k, &n);
	REP(i, 1, n) scanf("%d", &s[i]);
}

void Solve()
{
	f[0] = 0;
	int i = 0;
	do{
		i ++;
		f[i] = k + 1;
		REP(j, 1, n) if(i - s[j] >= 0)
			f[i] = min(f[i], f[i - s[j]] + 1);
	}while(f[i] <= k);
	printf("%d\n", i - 1);
}

int main()
{
	freopen("stamps.in", "r", stdin);
	freopen("stamps.out", "w", stdout);
	Init();
	Solve();
}
