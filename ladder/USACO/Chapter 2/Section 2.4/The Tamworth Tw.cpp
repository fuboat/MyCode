/*
	ID: 60303451
	TASK: ttwo
	LANG: C++
*/
#include <cstdio>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 10 + 10;
const int d[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int a[MAXN][MAXN];
int d1, d2, x1, x2, y1, y2;
void Init()
{
	char c;
	REP(i, 1, 10)  REP(j, 1, 10){
		c = getchar();
		while(c == ' ' || c == '\n') c = getchar();
		switch(c){
			case '*': a[i][j] = -1; break;
			case 'F': x1 = i, y1 = j; break;
			case 'C': x2 = i, y2 = j; break;
		}
	}
}

bool ok(int x, int y)
{
	if(x <= 0 || y <= 0 || x > 10 || y > 10) return 0;
	return 1;
}

void next(int &xx, int &yy, int &dd)
{
	int x = xx + d[dd][0], y = yy + d[dd][1];
	if(!ok(x, y) || a[x][y] == -1) dd = (dd + 1) % 4;
	else xx = x, yy = y;
}
void Solve()
{
	int cnt = 0;
	while((x1 != x2 || y1 != y2) && ++cnt <= 160000){
		next(x1, y1, d1);
		next(x2, y2, d2);
	}
	printf("%d\n", cnt > 160000? 0 : cnt);
}

int main()
{
	freopen("ttwo.in", "r", stdin);
	freopen("ttwo.out", "w", stdout);
	Init();
	Solve();
}
