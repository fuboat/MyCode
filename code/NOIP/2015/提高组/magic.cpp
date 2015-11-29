#include <iostream>
#include <cstdio>
#define pii pair<int, int>
#define X first
#define Y second
#define REP(i, x, y) for(int i = x, _ =y; i <= _; i ++)
using namespace std;
const int  MAXN = 50;
int ans[MAXN + 1][MAXN + 1], n;
pii p[(MAXN + 1) * (MAXN + 1)];
void Begin()
{
    freopen("magic.in", "r",stdin);
    freopen("magic.out", "w", stdout);
    return;
}

void Init()
{
	scanf("%d", &n);
	p[1] = make_pair(1, n / 2 + 1);
	ans[p[1].X][p[1].Y] = 1;
	return;
}

void Work(int i)
{
	int x0 = p[i - 1].X, y0 = p[i - 1].Y, x, y;
	if(x0 == 1)
		if(y0 == n)
			x = 2, y = n;
		else x = n, y = y0 + 1;
	else if(y0 == n)
		x = x0 - 1, y = 1;
	else if(!ans[x0 - 1][y0 +  1])
		x = x0 - 1, y = y0 + 1;
	else x = x0 + 1, y = y0;
	p[i] = make_pair(x, y);
	ans[x][y] = i;
	return;
}

void Print()
{
	REP(i, 1, n){
		printf("%d", ans[i][1]);
		REP(j, 2, n)
			printf(" %d", ans[i][j]);
		putchar('\n');
	}
	return;
}
		
void End()
{
    fclose(stdin);
    fclose(stdout);
    return;
}

int main()
{
    //Begin();
    Init();
    REP(i, 2, n * n)
	    Work(i);
    Print();
	//End();
    return 0; 
}
