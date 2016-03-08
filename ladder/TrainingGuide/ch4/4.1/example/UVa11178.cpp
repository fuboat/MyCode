// UVa11178
// Fuboat
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
typedef double LD;
using namespace std;
/*Vector and Point--------------------------------------------------------------------------------------*/
const LD eps = 1e-10;
struct Point{
	LD x, y;
	Point(LD x = 0, LD y = 0):x(x), y(y){}
};
typedef Point Vector;
int Dcmp(LD x){ return fabs(x) < eps? 0 : (x < 0? -1 : 1); }
Vector operator + (Vector a, Vector b){ return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Point a, Point b){ return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (Vector a, LD x){ return Vector(a.x * x, a.y * x); }
LD Cross(Vector a, Vector b){ return a.x * b.y - a.y * b.x; }
LD Dot(Vector a, Vector b){ return a.x * b.x + a.y * b.y; }
LD Length(Vector a){ return sqrt(Dot(a, a)); }
LD Angle(Vector a, Vector b){ return acos(Dot(a, b) / Length(a) / Length(b)); }
Vector Rotate(Vector a, LD rad){ return Vector(a.x * cos(rad) - a.y * sin(rad), a.y * cos(rad) + a.x * sin(rad)); }
Point GetInter(Point P, Vector v, Point Q, Vector w)
{
	Vector u = P - Q;
	LD t1 = Cross(w, u), t2 =  Cross(v, w), t = t1 / t2;
	return P + v * t;
}
/*Main Program--------------------------------------------------------------------------------------------*/
Vector AB, BC, CB, AC, CA, BA, BD, CD, CE, AE, AF, BF;
Point A, B, C, D, E, F;
int main()
{
	LD rad;
	int x, y;
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%d%d", &x, &y); A = Vector(x, y);
		scanf("%d%d", &x, &y); B = Vector(x, y);
		scanf("%d%d", &x, &y); C = Vector(x, y);
		BC = B - C;
		BA = B - A;
		AB = A - B;
		CB = C - B;
		AC = A - C;
		CA = C - A;
		rad = Angle(BC, BA) / 3;
		BD = Rotate(BC, rad);
		BF = Rotate(BA, - rad);
		rad = Angle(CB, CA) / 3;
		CE = Rotate(CA, rad);
		CD = Rotate(CB, - rad);
		rad = Angle(AB, AC) / 3;
		AF = Rotate(AB, rad);
		AE = Rotate(AC, - rad);
		D = GetInter(B, BD, C, CD);
		E = GetInter(A, AE, C, CE);
		F = GetInter(A, AF, B, BF);
		printf("%.6lf %.6lf %.6lf %.6lf %.6lf %.6lf\n", D.x, D.y, E.x, E.y, F.x, F.y);
	}
}
