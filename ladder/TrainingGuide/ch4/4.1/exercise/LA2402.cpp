#include <stdio.h>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
template <typename T> bool Chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool Chkmax(T &x, T y){return y > x? (x = y, true) : false;}
typedef double LD;
using namespace std;
/*Vector and Point--------------------------------------------------------------------------------------*/
const LD eps = 1e-10;
const int MAXN = 50;
struct Point{
	LD x, y;
	Point(LD x = 0, LD y = 0):x(x), y(y){}
};
typedef Point Vector;
Vector operator + (const Vector &a, const Vector &b){ return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (const Point &a, const Point &b){ return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (const Vector &a, const LD &x){ return Vector(a.x * x, a.y * x); }
Vector operator / (const Vector &a, const LD &x){ return Vector(a.x / x, a.y / x); }
LD Cross(Vector a, Vector b){ return a.x * b.y - a.y * b.x; }
LD Dot(Vector a, Vector b){ return a.x * b.x + a.y * b.y; }
LD Length(Vector a){ return sqrt(Dot(a, a)); }
LD Area2(Point o, Point a, Point b){ return Cross(a - o, b - o); }
Point GetLineInter(Point P, Vector v, Point Q, Vector w)
{
	Vector u = P - Q;
	return P + v * Cross(w, u) / Cross(v, w);
}
LD Area(Point a, Point b, Point c, Point d){ return (fabs(Area2(a, b, c)) + fabs(Area2(c, d, a))) / 2.0; }
/*Save Data----------------------------------------------------------------------------*/
int n;
LD maxx;
Point P[MAXN][MAXN], Q[4][MAXN];
Vector V[2][MAXN];
/*Main program-------------------------------------------------------------------------*/ 
void Init()
{
	maxx = 0;
	double x, y;
	Q[1][0] = Point(0, 0);
	Q[1][n + 1] = Point(1, 0);
	Q[3][0] = Point(0, 0);
	Q[3][n + 1] = Point(0, 1);
	REP(i, 1, 2) REP(j, 1, n){
		scanf("%lf", &x);
		Q[i][j] = Point(x, i - 1);
	}
	REP(i, 3, 4) REP(j, 1, n){
		scanf("%lf", &y);
		Q[i][j] = Point(i - 3, y);
	}
	V[0][0] = V[0][n + 1] = Vector(1, 0);
	V[1][0] = V[1][n + 1] = Vector(0, 1);
	REP(i, 1, n) V[1][i] = Vector(Q[1][i] - Q[2][i]);
	REP(i, 1, n) V[0][i] = Vector(Q[3][i] - Q[4][i]);
}
void Solve()
{
//	REP(i, 1, n) P[n + 1][i] = Q[1][i];
//	REP(i, 1, n) P[0][i] = Q[2][i];
//	REP(i, 1, n) P[i][0] = Q[3][i];
//	REP(i, 1, n) P[i][n + 1] = Q[4][i];
//	P[0][0] = Point(0, 1);
//	P[0][n + 1] = Point(1, 1);
//	P[n + 1][0] = Point(0, 0);
//	P[n + 1][n + 1] = Point(1, 0);
	REP(i, 0, n + 1) REP(j, 0, n + 1)
		P[i][j] = GetLineInter(Q[3][i], V[0][i], Q[1][j], V[1][j]);
	REP(i, 1, n + 1) REP(j, 1, n + 1){
		Chkmax(maxx, Area(P[i][j], P[i][j - 1], P[i - 1][j - 1], P[i - 1][j]));
	}
	printf("%.6f\n", maxx);
}
int main()
{
	while(scanf("%d", &n) == 1 && n){
		Init();
		Solve();
	}
}

