#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T> inline bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> inline bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXY = 1e7 + 1e3, MAXN = 1e6 + 1e3, oo = 0x3f3f3f3f;
struct Sta{
	int flag, x, y, p;
	Sta() {}
	Sta(int flag, int x, int y, int p):
		flag(flag), x(x), y(y), p(p){}
	bool operator < (const Sta &a) const {
		if(x != a.x) return x < a.x;
		return flag < a.flag;
	}
}s[MAXN], T[MAXN], a[MAXN];
using namespace std;
int maxy, n, m;
int ans[MAXN];
struct Fenwick{
	int f[MAXY];
	Fenwick()
	{
		memset(f, 0x3f, sizeof(f));
	}
	void Add(int x, int p)
	{
		for (; p <= maxy; p += p & -p)
			Chkmin(f[p], x);
	}
	void CLEAR(int p)
	{
		for (; p <= maxy; p += p & -p)
			f[p] = oo;
	}
	int Query(int p)
	{
		int minx = oo;
		for (; p > 0; p -= p & -p)
			Chkmin(minx, f[p]);
		return minx;
	}
}t1, t2, t3, t4;

void Work(int tail)
{
	if(!tail)
		return ;
	
	int flag, x, y, p;

	sort(T + 1, T + tail + 1);

	REP(i, 1, tail) {
		flag = T[i].flag;
		x = T[i].x;
		y = T[i].y;
		p = T[i].p;
		if (flag != 2) {
			t1.Add(- x + y, maxy - y);
			t2.Add(- x - y, y);
		} else {
			Chkmin(ans[p], t1.Query(maxy - y) + x - y);
			Chkmin(ans[p], t2.Query(y) + x + y);
			// x - x0 + y0 - y
			// x - x0 + y - y0
		}
	}
	
	rep(i, tail, 1) {
		flag = T[i].flag;
		x = T[i].x;
		y = T[i].y;
		p = T[i].p;
		if (flag != 2) {
			t3.Add(x + y, maxy - y);
			t4.Add(x - y, y);
		} else {
			Chkmin(ans[p], t3.Query(maxy - y) - x - y);
			Chkmin(ans[p], t4.Query(y) - x + y);
			// x0 - x + y0 - y
			// x0 - x + y - y0
		}
	}
	
	REP(i, 1, tail) {
		flag = T[i].flag;
		x = T[i].x;
		y = T[i].y;
		p = T[i].p;
		if(flag != 2) {
			t1.CLEAR(maxy - y);
			t2.CLEAR(y);
			t3.CLEAR(maxy - y);
			t4.CLEAR(y);
		}
	}
}

void CDQ(int l, int r)
{
	int mid = (l + r) >> 1;
	if(l == r)
		return ;

	CDQ(l, mid);
	CDQ(mid + 1, r);
	
	int tail = 0;
	REP (i, l, mid)
		if(s[i].flag != 2)
			T[++ tail] = s[i];

	REP (i, mid + 1, r)
		if(s[i].flag == 2)
			T[++ tail] = s[i];

	Work(tail);
}
void Init()
{
	int x, y, flag;
	REP (i, 1, n) {
		scanf("%d%d", &x, &y);
		a[i] = Sta(1, x, y, 0);
		Chkmax(maxy, y);
	}
	REP(i, 1, m) {
		scanf("%d%d%d", &flag, &x, &y);
		s[i] = Sta(flag, x, y, i);
		Chkmax(maxy, y);
	}
	maxy ++;
}
void Special()
{
	int cnt = 0;
	REP(i, 1, n)
		T[++ cnt] = a[i];

	REP(i, 1, m)
		if(s[i].flag == 2)
			T[++ cnt] = s[i];

	Work(cnt);
}
void Solve()
{
	memset(ans, 0x7f, sizeof(ans));
	CDQ(1, m);
	Special();
	REP(i, 1, m)
		if(s[i].flag == 2)
			printf("%d\n", ans[i]);
}
main()
{
	scanf("%d%d", &n, &m);
	Init();
	Solve();
}
