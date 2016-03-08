// LA2218
// HalfplaneIntersection
// Fuboat
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#define LD double
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const LD eps = 1e-8, ADD = 1000000;
const int MAXN = 100 + 100;
struct Point{
	LD x, y;
	Point(){}
	Point(LD x, LD y):
		// Not 'int';
		x(x), y(y){}
	Point operator + (const Point &A) const{ return Point(x + A.x, y + A.y); }
	Point operator - (const Point &A) const{ return Point(x - A.x, y - A.y); }
	Point operator * (const LD &k) const{ return Point(x * k, y * k); }
};
typedef Point Vector;
LD Cross(Vector a, Vector b){ return a.x * b.y - b.x * a.y; }
struct Line{
	Point P;
	Vector v;
	LD ang;
	Line(){}
	Line(Point P, Vector v):P(P), v(v){ ang = atan2(v.y, v.x); }
	bool Onleft(Point A){ return Cross(v, A - P) > 0; }
	bool operator < (const Line &a) const{ return ang < a.ang; }
//	void Print(){ printf("Point(%lf,%lf),Vector(%lf,%lf)\n", P.x, P.y, v.x, v.y); }
};
Point GetLineInter(Line a, Line b)
{
	Vector u = a.P - b.P;
	LD t = Cross(b.v, u) / Cross(a.v, b.v);
	return a.P + a.v * t;
}
int HalfplaneInter(Line *L, int N)
{
	int first(1), last(1);
	std::sort(L + 1, L + N + 1);
	Point *p = new Point[N + 2];
	Line *q = new Line[N + 2];
//	REP(i, 1, n)
//		L[i].Print();
	q[1] = L[1];
	REP(i, 2, N){
		while(first < last && !L[i].Onleft(p[last - 1])) -- last;
		while(first < last && !L[i].Onleft(p[first])) ++ first;
		if(fabs(Cross(L[i].v, q[last].v)) < eps){
			if(!L[i].Onleft(q[last].P))
				q[last] = L[i];
		}else q[++ last] = L[i]; // Don't forget this;
		if(first < last) p[last - 1] = GetLineInter(q[last - 1], q[last]);
	}
	while(first < last && !q[first].Onleft(p[last - 1])) -- last;
	
	if(last - first <= 1) return 0;
	return 1;
}
/*Main Program----------------------------------------*/
int n;
int V[MAXN], U[MAXN], W[MAXN];
LD vi[MAXN], ui[MAXN], wi[MAXN];
Line L[MAXN];
void Init()
{
	REP(i, 1, n){
		scanf("%d%d%d", &V[i], &U[i], &W[i]);
		vi[i] = ADD / V[i];
		ui[i] = ADD / U[i];
		wi[i] = ADD / W[i];
	}
}
void Solve()
{
	int tot = 0;
	bool flag;
	LD A, B, C;
	// Ax + By + C = 0;
	REP(i, 1, n){
		tot = 0;
		flag = true;
		REP(j, 1, n) if(i != j){
			if(V[j] >= V[i] && U[j] >= U[i] && W[j] >= W[i]){ flag = false; break; }
			if(V[j] <= V[i] && U[j] <= U[i] && W[j] <= W[i]) continue;
			A = (vi[j] - wi[j]) - (vi[i] - wi[i]);
			B = (ui[j] - wi[j]) - (ui[i] - wi[i]);
			C = wi[j] - wi[i];
			L[++ tot] = Line(-C / B < eps? Point(-C / A, 0) : Point(0, -C / B), Vector(B, -A));
			// Warning! If (A == 0 || B == 0), the other should be chosen;
		}
		if(flag){
			L[++ tot] = Line(Point(0, 0), Vector( 0, -1));  // x = 0;
			L[++ tot] = Line(Point(0, 0), Vector( 1,  0));  // y = 0;
			L[++ tot] = Line(Point(0, 1), Vector(-1,  1));  // - x - y + 1 = 0;
			if(!HalfplaneInter(L, tot)) flag = false;
		}
		puts(flag? "Yes" : "No");
	}
}
int main()
{
	while(scanf("%d", &n) == 1 && n){
		Init();
		Solve();
	}
}
