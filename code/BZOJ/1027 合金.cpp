// BZOJ #1027
// Fuboat
// Floyd
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#define REP(i, x, y) for (int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for (int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0)
#define LL long long
#define LD double
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int oo = 0x3f3f3f3f, MAXN = 1000 + 100;
const LD eps = 1e-7;
int Dcmp(LD x)
{
	if (fabs(x) < eps)
		return 0;
	return x > 0? 1 : -1;
}
struct Point{
	LD x, y;
	int num;
	Point() {}
	Point(LD x, LD y, int num = 0):
		x(x), y(y) {}
	Point operator - (const Point &a) const {
		return Point(x - a.x, y - a.y);
	}
	bool operator == (const Point &a) const {
		return Dcmp(a.x - x) == 0 && Dcmp(a.y - y) == 0;
	}
	bool operator != (const Point &a) const {
		return !(*this == a);
	}
	void Scan()
	{
		LD z;
		scanf("%lf%lf%lf", &x, &y, &z);
	}
} p[MAXN], q[MAXN];

typedef Point Vector;
LD Cross(Vector u, Vector v) { return u.x * v.y - v.x * u.y; }
LD Dot(Vector u, Vector v) { return u.x * v.x + u.y * v.y; }

struct Line{
	Point P, Q;
	Line() {}
	Line(Point P, Point Q):
		P(P), Q(Q) {}
	bool OnLeft(Point O)
	{
		return Dcmp(Cross(Q - P, O - P)) > 0;
	}
	bool OnLine(Point O)
	{
		return Dcmp(Cross(Q - P, O - P)) == 0 && (Dcmp(Dot(O - P, O - Q)) < 0 || Q == O || P == O);
	}
};

int m, n;
int dis[MAXN][MAXN];
int Floyd()
{
	int minx = oo;
	
	REP (k, 1, m)
		REP (i, 1, m)
			REP (j, 1, m)
				Chkmin(dis[i][j], dis[i][k] + dis[k][j]);

	REP (i, 1, m)
		Chkmin(minx, dis[i][i]);
	
	return minx;
}
void Init() 
{
	Line tmp;
	bool flag;
	MSET(dis, 0x3f);
	
	scanf("%d%d", &m, &n);
	REP (i, 1, m)
		p[i].Scan();
	REP (i, 1, n)
		q[i].Scan();
		
	REP (i, 1, m)
		REP (j, 1, m) if (i != j) {
			tmp = Line(p[i], p[j]);
			flag = true;
			
			REP (k, 1, n)
				if (!tmp.OnLeft(q[k]) && !tmp.OnLine(q[k])) {
					flag = false;
					break;
				}
			
			if (flag)
				dis[i][j] = 1;
		}
}
void Solve()
{	
	Line tmp;
	bool flag;
	int ans;

	Solve1:
		REP (i, 1, m) { 
			flag = true;
			REP (j, 1, n)
				if (p[i] != q[j]) { 
					flag = false; 
					break;
				}
			
			if (flag) {
				puts("1");
				return ;
			}
		}
	
	Solve2:
		REP (i, 1, m)
			REP (j, i + 1, m) {
				flag = true;
				tmp = Line(p[i], p[j]); 
				
				REP (k, 1, n)
					if (!tmp.OnLine(q[k])) {
						flag = false;
						break;
					}
				
				if (flag) { 
					puts("2"); 
					return ;
				}
			}
		
	Solve3:
		ans = Floyd();
		if (ans > m)
			ans = -1;
		printf("%d\n", ans); 
}
int main()
{
	Init();
	Solve();
}
