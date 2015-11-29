#include <iostream>
#include <cstdio>
#define pii pair<int, int>
#define REP(i, x, y)  for(int i = x, _ = y ; i <= _; i ++)
#define Rep(i, x, y)  for(int i = x, _ = y ; i >= _; i --)
#define LL long long
#define LD long double
using std::min;
using std::max;
const int MAXL = 1000000000, MAXM = 500000, MAXN = 500000;
const int oo = 0x7fffffff;
int m, n, ans = -oo;
int p[MAXN + 100];

void Begin()
{
	freopen("stone.in", "r", stdin);
	freopen("stone.out", "w", stdout);
}

void Init()
{
	int x;
	scanf("%d%d%d", &x, &n, &m);
	REP(i, 1, n)  scanf("%d", &p[i]);
	p[n + 1] = x;
}

int Work(int mid)
{
	int from = 0, sum = 0;
	REP(i, 1, n + 1)
		if(p[i] - p[from] < mid) sum ++;
		else from = i;
	return sum;
}

void End()
{
	fclose(stdin);
	fclose(stdout);
}

int main()
{
	//Begin();
	Init();
	int l = 0, r = p[n + 1], ans = 0;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(Work(mid) > m)  r = mid - 1;
		else l = mid + 1, ans = mid;
	}
	printf("%d\n", ans);
	//End();
}

