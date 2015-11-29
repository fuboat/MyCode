/*
	ID: 60303451
	TASK: holstein
	LANG: C++
*/
#include <cstring>
#include <cstdio>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXV = 25, MAXG = 15, oo = 0x7fffffff;
int v, g, need[MAXV + 1], has[MAXG + 1][MAXV + 1], ans[MAXG + 1], now[MAXG + 1], minx = oo;

void Begin()
{
	freopen("holstein.in", "r", stdin);
	freopen("holstein.out", "w", stdout);
}

void Init()
{
	scanf("%d", &v);
	REP(i, 1, v)
		scanf("%d", &need[i]);
	scanf("%d", &g);
	REP(i, 1, g)
		REP(j, 1, v)
			scanf("%d", &has[i][j]);
}

void ANS(int x)
{
	if(x >= minx) return;
	minx = x;
	memcpy(ans, now, sizeof(int) * (x + 1));
	return;
}

void Dfs(int use, int pre)
{
	int zzz;
	for(zzz = 1; zzz <= v; zzz ++)
		if(need[zzz] > 0) break;
	if(zzz == v + 1){
		ANS(use);
		return;
	}
	REP(i, pre + 1, g){
		REP(j, 1, v)
			need[j] -= has[i][j];
		now[use + 1] = i;
		Dfs(use + 1, i);
		REP(j, 1, v)
			need[j] += has[i][j];
	}
	return;
}		

void Print()
{
	printf("%d", minx);
	REP(i, 1, minx)
		printf(" %d", ans[i]);
	putchar('\n');
	return;
}

void End()
{
	fclose(stdin);
	fclose(stdout);
}

int main()
{
	Begin();
	Init();
	Dfs(0, 0);
	Print();
	End();
}
