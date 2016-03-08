#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
#define LD double
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const LD eps = 1e-10;
const int MAXN = 200;
struct Point{
	LD x, y;
	Point(LD x = 0, LD y = 0):x(x), y(y){}
};
typedef Point Vector;
struct Line{
	Point P;
	Vector v;
	LD ang;
	Line(){}
	Line(Point P, Vector v):P(P), v(v){ ang = atan2(v.y, v.x); }
	bool operator < (const Line& L)const{ return ang < L.ang; }
};
int Dcmp(LD x){ return fabs(x) < eps? 0 : (x < 0? -1 : 1); }
Vector operator + (const Vector &a, const Vector &b){ return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (const Point &a, const Point &b){ return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (const Vector &a, const LD &x){ return Vector(a.x * x, a.y * x); }
Vector operator / (const Vector &a, const LD &x){ return Vector(a.x / x, a.y / x); }
bool operator == (const Point &a, const Point &b){ return Dcmp(a.x - b.x) == 0 && Dcmp(a.y - b.y) == 0; }
bool operator < (const Point &a, const Point &b){ return a.x < b.x || (a.x == b.x && a.y < b.y); }
LD Cross(Vector a, Vector b){ return a.x * b.y - a.y * b.x; }
bool OnLeft(Line L, Point P){ return Cross(L.v,P-L.P) > 0; }
LD Dot(Vector a, Vector b){ return a.x * b.x + a.y * b.y; }
LD Length(Vector a){ return sqrt(Dot(a, a)); }
Vector Normal(Vector a){ LD L = Length(a); return Vector(- a.y / L, a.x / L); }
Point GetLineInter(Line a, Line b)
{
	Vector u = a.P - b.P;
	LD t = Cross(b.v, u) / Cross(a.v, b.v);
	return a.P + a.v * t;
}
int HalfplaneInter(Line* L, int n){
	std::sort(L, L + n);
	int first = 0, last = 0;
	Point *p = new Point[n];
	Line *q = new Line[n];
	q[0] = L[0];
	REP(i, 1, n - 1){
		while(first < last && !OnLeft(L[i], p[last-1]))
			last --;
		while(first < last && !OnLeft(L[i], p[first]))
			first ++;
		q[++ last] = L[i];
		if(fabs(Cross(q[last].v, q[last-1].v)) < eps){
			last --;
			if(OnLeft(q[last], L[i].P)) q[last] = L[i];
		}
		if(first < last)
			p[last - 1] = GetLineInter(q[last - 1], q[last]);
	}
	while(first < last && !OnLeft(q[first], p[last-1]))
		last --;
	if(last - first <= 1)
		return 0;
	return 1;
}
int n;
Point P[MAXN];
Vector v[MAXN], vv[MAXN];
Line L[MAXN];
void Init()
{
	REP(i, 1, n)
		scanf("%lf%lf", &P[i].x, &P[i].y);
	REP(i, 1, n){
		v[i] = (i == n? P[1] : P[i + 1]) - P[i];
		vv[i] = Normal(v[i]);
	}
}
void Solve()
{
	LD l = 0, r = 1e5, mid;
	while(r - l > 1e-6){
		mid = (l + r) / 2;
		REP(i, 1, n)
			L[i] = Line(P[i] + vv[i] * mid, v[i]);
		if(HalfplaneInter(L + 1, n))
			l = mid;
		else r = mid;
	}
	printf("%lf\n", l);
}
int main()
{
	while(scanf("%d", &n) == 1 && n){
		Init();
		Solve();
	}
}
