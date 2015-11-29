/*
	ID: 60303451
	TASK: rect1
	LANG: C++
*/
/*
	mistake:
	1. otnx[0] and otny[0] must be 0;
*/
#include <cstdio>
#define REP(i, x, y) for(int i = x; i <= y; i ++)

const int MAXX = 10000, MAXY = 10000, MAXC = 2500, MAXN = 1000;
short c[MAXN * 2 + 10][MAXN * 2 + 10], otnx[MAXX + 1], otny[MAXX + 1], ntox[MAXX + 1], ntoy[MAXX + 1];
int ans[MAXC + 10];
int nx_cnt, ny_cnt;
int m, n, color;
struct node{
	int xl, yl, xr, yr, co;
}que[MAXN + 10];
int que_cnt;

void Init()
{
	scanf("%d%d%d", &m, &n, &color);
	que[++ que_cnt] = (node){0, 0, m, n, 1};
	otnx[m] = 1;
	otny[n] = 1;
	REP(i, 1, color){
		int xl, xr, yl, yr, C;
		scanf("%d%d%d%d%d", &xl, &yl, &xr, &yr, &C);
		que[++ que_cnt] = (node){xl, yl, xr, yr, C};
		otnx[xl] = otnx[xr] = 1;
		otny[yl] = otny[yr] = 1;
	}
	otnx[0] = otny[0] = 0;
	REP(i, 1, m) if(otnx[i]){
		ntox[++ nx_cnt] = i;
		otnx[i] = nx_cnt;
	}
	REP(i, 1, n) if(otny[i]){
		ntoy[++ ny_cnt] = i;
		otny[i] = ny_cnt;
	}
}

void Color()
{
	int xl, yl, xr, yr, co;
	REP(i, 1, que_cnt){
		node now = que[i];
		xl = otnx[now.xl];
		xr = otnx[now.xr];
		yl = otny[now.yl];
		yr = otny[now.yr];
		co = now.co;
		REP(x, xl + 1, xr)
			REP(y, yl + 1, yr)
				c[x][y] = co;
	}
}

int main()
{
	freopen("rect1.in", "r", stdin);
	freopen("rect1.out", "w", stdout);
	Init();
	Color();
	REP(x, 1, nx_cnt) REP(y, 1, ny_cnt)
		ans[c[x][y]] += (ntox[x] - ntox[x - 1]) * (ntoy[y] - ntoy[y - 1]);
	REP(i, 1, 2500) if(ans[i])
		printf("%d %d\n", i, ans[i]);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
