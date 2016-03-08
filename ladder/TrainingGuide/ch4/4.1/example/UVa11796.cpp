// UVa11796
// Fuboat
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
typedef double LD;
using namespace std;
/*Vector and Point--------------------------------------------------------------------------------------*/
const LD eps = 1e-10;
const int MAXN = 100 + 1;
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
LD DisToSegment(Point P, Point A, Point B)
{
	if(A == B) return Length(P - A);
	Vector v1 = B - A, v2 = P - A, v3 = P - B;
	if(Dcmp(Dot(v1, v2) < 0)) return Length(v2);
	else if(Dcmp(Dot(v1, v3)) > 0) return Length(v3);
	else return fabs(Cross(v1, v2)) / Length(v1);
}
/*Special Situation----------------------------------------------------------------------------------*/
LD minx, maxx;
void Update(Point P, Point A, Point B)
{
	Chkmin(minx, DisToSegment(P, A, B));
	Chkmax(maxx, Length(P - A));
	Chkmax(maxx, Length(P - B));
}
/*Main Program---------------------------------------------------------------------------------------*/
int n, m;
Point LA[MAXN], LB[MAXN];
LD lena, lenb;
void Init()
{
	lena = lenb = 0;
	double x, y;
	scanf("%d%d", &n, &m);
	REP(i, 1, n){
		scanf("%lf%lf", &x, &y), LA[i] = Point(x, y);
		if(i != 1) lena += Length(LA[i - 1] - LA[i]);
	}
	REP(i, 1, m){
		scanf("%lf%lf", &x, &y), LB[i] = Point(x, y);
		if(i != 1) lenb += Length(LB[i - 1] - LB[i]);
	}
}
void Solve()
{
	minx = 1e10, maxx = 0;
	LD disa, disb, T;
	Vector addA, addB;
	Point A = LA[1], B = LB[1];
	int x = 1, y = 1;
	while(x < n && y < m){
		disa = Length(A - LA[x + 1]);
		disb = Length(B - LB[y + 1]);
		T = min(disa / lena, disb / lenb);
		// 该次操作的总时间（将a的速度设为lena，b的速度设为lenb） 
		addA = (LA[x + 1] - A) / disa * T * lena;
		// '(LA[x + 1] - A) / disa'相当于把向量缩为单位1
		// 而'T * lena'表示移动的距离
		// 得到移动向量
		addB = (LB[y + 1] - B) / disb * T * lenb;
		Update(A, B, B + addB - addA);
		A = A + addA;
		B = B + addB;
		if(A == LA[x + 1]) x ++;
		if(B == LB[y + 1]) y ++;
	}
	printf("%.0lf\n", maxx - minx);
}
int main()
{
	int T;
	scanf("%d", &T);
	REP(i, 1, T){
		printf("Case %d: ", i);
		Init();
		Solve();
	}
}
