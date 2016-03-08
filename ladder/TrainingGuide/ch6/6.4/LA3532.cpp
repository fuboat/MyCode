// LA 3532
// Fuboat
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstring>	
#include <vector>
#define X first
#define Y second
#define MK(a, b) make_pair(a, b)
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
using namespace std;
typedef double LD;
const LD eps = 1e-4;
const int MAXN = 1000;
int n, m;
int Dcmp(LD x){ return fabs(x) < eps? 0 : (x < 0? -1 : 1); }
struct Point{
	LD x, y;
	Point(){}
	Point(int x, int y):x(x), y(y){}
	Point operator + (const Point &P) const{ return Point(x + P.x, y + P.y); }
	Point operator - (const Point &P) const{ return Point(x - P.x, y - P.y); }
	Point operator * (const LD &d) const{ return Point(x * d, y * d); }
	LD Angle(){ return atan2(y, x); }
};
typedef Point Vector;

struct Circle{
	Point c;
	LD r;
	Circle(){}
	Circle(Point c, LD r):c(c), r(r){}
	Point point(LD ang){ return c + Vector(r * cos(ang), r * sin(ang)); }
	void LineInter(LD b, vector<pair<LD, int> > &p) // y = b;
	{
		if(b < 0 || b > m) return ;
		// Avoid out of this land;
		LD d, len, L, R; 
		// Don't use 'r'; we should use 'R';
		// 'r' have been used in the circle;
		d = fabs(b - c.y);
		if(Dcmp(d - r) >= 0) return ;
		len = sqrt(r * r - d * d);
		L = std::max(0.0    , c.x - len);
		R = std::min(1.0 * m, c.x + len);
		// Avoid out of this land;
		p.push_back(MK(L,  1));
		p.push_back(MK(R, -1));
	}
	void Scan(){ scanf("%lf%lf", &c.x, &c.y); }
	LD Up(){ return c.y + r; }
	LD Down(){ return c.y - r; }
	bool operator < (const Circle &S) const{ return c.y - r < S.c.y - S.r; }
}cir[MAXN];

int head, tail;
LD F(LD x)
{
	int tot, flag;
	LD ans(0);
	vector<pair<LD, int> > p;
	REP(i, head, tail)
		cir[i].LineInter(x, p);
	if(!p.size()) return 0;
	std::sort(p.begin(), p.end());
	tot = p.size();
	flag = p[0].Y;
	REP(i, 1, tot - 1){
		if(flag > 0)
			ans += p[i].X - p[i - 1].X;
		flag += p[i].Y;
	}
	return ans;
}
LD Simpson(LD l, LD r, LD fl, LD fr, LD &fmid)
{
	LD mid = l + (r - l) / 2;
	fmid = F(mid);
	return (fl + 4 * fmid + fr) * (r - l) / 6;
}
LD asr(LD l, LD r, LD fl, LD fr, LD fmid, LD A)
{
	LD mid = l + (r - l) / 2;
	// warning!
	// 'l + (r - l) / 2'!
	LD flmid, frmid, L, R;
	L = Simpson(l, mid, fl, fmid, flmid);
	R = Simpson(mid, r, fmid, fr, frmid);
	if(abs(L + R - A) <= eps)
		return L + R;
	return asr(l, mid, fl, fmid, flmid, L) + asr(mid, r, fmid, fr, frmid, R);
}
int ks, k1, N;
void Init()
{
	int now;
	REP(i, 1, ks){
		cir[i].Scan();
		cir[i].r = 0.58;
	}
	REP(i, 1, k1){
		now = i + ks;
		cir[now].Scan();
		cir[now].r = 1.31;
	}
	std::sort(cir + 1, cir + ks + k1 + 1);
	N = ks + k1;
}
LD Work(LD l, LD r)
{
	LD mid = l + (r - l) / 2;
	LD fmid;
	LD A = Simpson(l, r, 0, 0, fmid);
	return asr(l, r, 0, 0, fmid, A);
}
void Solve()
{
	head = 1;
	LD ans(0), maxx = cir[1].Up(), minx = cir[1].Down();
	REP(i, 2, N){
		Circle &C = cir[i];
		if(C.Down() > maxx){
			ans += Work(minx, maxx);
			head = i;
			maxx = C.Up();
			minx = C.Down();
		}else{
			Chkmax(maxx, C.Up());
			Chkmin(minx, C.Down());
		}tail = i;
	}
	ans += Work(minx, maxx);
	printf("%.2lf\n", 1.0 * n * m - ans);
}
int main()
{
	while(scanf("%d%d%d%d", &n, &m, &ks, &k1)){
		if(!(n || m || ks || k1))
			break;
		Init();
		Solve();
	}
}
