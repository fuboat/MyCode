#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdlib>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long 
#define LD long double
const int oo = 0x7fffffff, MAXN = 100, MAXM = 100;
int a[MAXN  + 10][MAXM + 10];
int n, m;

void Begin()
{
	freopen("mine.in", "r", stdin);
	freopen("mine.out", "w", stdout);
}

void End()
{
	fclose(stdin);
	fclose(stdout);
}

int main()
{
	//Begin();
	scanf("%d%d", &n, &m);
	REP(i, 1, n) REP(j, 1, m){
		char x = getchar();
		while(x == ' ' || x == '\n')
			x = getchar();
		if(x == '*') a[i][j] = -1;
		else a[i][j] = 0;
	}
	REP(i, 1, n) REP(j, 1, m){
		if(a[i][j] == -1) continue;
		REP(i0, -1, 1) REP(j0, -1, 1)
			if(a[i + i0][j + j0] == -1)
				a[i][j] ++;
	}
	REP(i, 1, n){
		REP(j, 1, m)
			if(a[i][j] == -1) putchar('*');
			else printf("%d",a[i][j]);
		putchar('\n');
	}
	//End();
	return 0;
}
