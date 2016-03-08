#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
typedef double LD;
using namespace std;
/*Vector and Point--------------------------------------------------------------------------------------*/
const LD eps = 1e-10, MAXN = 1000;
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
Point GetLineInter(Point P, Vector v, Point Q, Vector w)
{
	Vector u = P - Q;
	LD t = Cross(w, u) / Cross(v, w);
	return P + v * t;
}
int main()
{
	puts("INTERSECTING LINES OUTPUT");
	int n, x, y;
	Point P[4];
	Vector AB, CD, ans;
	scanf("%d", &n);
	REP(i, 1, n){
		REP(j, 0, 3){
			scanf("%d%d", &x, &y);
			P[j] = Point(x, y);
		}
		AB = P[0] - P[1];
		CD = P[2] - P[3];
		if(Dcmp(Cross(AB, CD)) == 0){
			if(Dcmp(Cross(P[0] - P[2], P[0] - P[3])) == 0) puts("LINE");
			else puts("NONE");
		}else{
			ans = GetLineInter(P[0], AB, P[2], CD);
			printf("POINT %.2lf %.2lf\n", ans.x, ans.y);
		}
	}
	puts("END OF OUTPUT");
}
