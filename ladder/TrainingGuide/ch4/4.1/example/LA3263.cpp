// LA3263
// Fuboat
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
typedef double LD;
using namespace std;
/*Vector and Point--------------------------------------------------------------------------------------*/
const LD eps = 1e-10;
const int MAXN = 10000;
struct Point{
	LD x, y;
	Point(LD x = 0, LD y = 0):x(x), y(y){}
};
typedef Point Vector;
int Dcmp(LD x){ return fabs(x) < eps? 0 : (x < 0? -1 : 1); }
Vector operator + (const Vector &a, const Vector &b){ return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (const Point &a, const Point &b){ return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (const Vector &a, const LD &x){ return Vector(a.x * x, a.y * x); }
Vector operator / (const Vector &a, const LD &x){ return Vector(a.x / x, a.y / x); }
bool operator == (const Point &a, const Point &b){ return Dcmp(a.x - b.x) == 0 && Dcmp(a.y - b.y) == 0; }
bool operator < (const Point &a, const Point &b){ return a.x < b.x || (a.x == b.x && a.y < b.y); }
LD Cross(Vector a, Vector b){ return a.x * b.y - a.y * b.x; }
LD Dot(Vector a, Vector b){ return a.x * b.x + a.y * b.y; }
LD Length(Vector a){ return sqrt(Dot(a, a)); }
LD Angle(Vector a, Vector b){ return acos(Dot(a, b) / Length(a) / Length(b)); }
LD Area2(Point o, Point a, Point b){ return Cross(a - o, b - o); }
Vector Rotate(Vector a, LD rad){ return Vector(a.x * cos(rad) - a.y * sin(rad), a.y * cos(rad) + a.x * sin(rad)); }
Vector Normal(Vector a){ LD L = Length(a); return Vector(- a.y / L, a.x / L); }
Point GetLineInter(Point P, Vector v, Point Q, Vector w)
{
	Vector u = P - Q;
	LD t = Cross(w, u) / Cross(v, w);
	return P + v * t;
}
bool OnSegment(Point O, Point A, Point B){ return Dcmp(Cross(A - O, B - O)) == 0 && Dcmp(Dot(A - O, B - O)) < 0; }
bool IsSegmentInter(Point A1, Point A2, Point B1, Point B2)
{
	LD c1 = Cross(A2 - A1, B2 - A1), c2 = Cross(A2 - A1, B1 - A1), 
	   c3 = Cross(B2 - B1, A1 - B1), c4 = Cross(B2 - B1, A2 - B1);
	return Dcmp(c1) * Dcmp(c2) < 0 && Dcmp(c3) * Dcmp(c4) < 0;
}
Point V[MAXN], P[MAXN];
int main()
{
	int cnt, e, n, kase = 0;
	LD x, y;
	while(scanf("%d", &n) == 1 && n)
	{
		REP(i, 0, n - 1){
			scanf("%lf%lf", &x, &y);
			V[i] = P[i] = Point(x, y);
		}
		n --;
		cnt = e = n;
		REP(i, 0, n - 1)
			REP(j, i + 1, n - 1)
				if(IsSegmentInter(P[i], P[i + 1], P[j], P[j + 1]))
					V[cnt ++] = GetLineInter(P[i], P[i + 1] - P[i], P[j], P[j + 1] - P[j]);
		sort(V, V + cnt);
		cnt = unique(V, V + cnt) - V;
		REP(i, 0, cnt - 1) REP(j, 0, n - 1)
			if(OnSegment(V[i], P[j + 1], P[j])) e ++;
		printf("Case %d: There are %d pieces.\n", ++ kase, e + 2 - cnt);
	}
}
