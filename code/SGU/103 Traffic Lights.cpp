#include <cstdio>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 300 + 100, MAXM = 14000 + 6000, oo = 0x7fffffff;
int n, m, be, ed;
int s[MAXN][MAXN], head[MAXN], lft[MAXN], rht[MAXN];

bool cal(int num, int time)
{
	int tmp = time % (lft[num], rht[num);
	if(tmp > lft[num]) return !head[num];
	else return head[num];
}

void Init()
{
	scanf("%d%d", &n, &m);
	char c;
	int from, to, w;
	REP(i, 1, n){
		c = getchar();
		while(c != 'B' && c != 'P') c = getchar();
		head[i] = c == 'B'? 0 : 1;
		scanf("%d%d", &lft[i], &rht[i]);
	}
	REP(i, 1, m){
		scanf("%d%d%d", &from, &to, &w);
		s[from][to] = w;
	}
}
void Spfa()
{
	
}
void Solve()
{
	Spfa();
}
int main()
{
	Init();
	Solve();
}
