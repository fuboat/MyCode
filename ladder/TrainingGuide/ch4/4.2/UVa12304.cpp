#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
typedef double LD;
using namespace std;
/*Vector and Point--------------------------------------------------------------------------------------*/
const LD eps = 1e-6, PI = acos(-1);
struct Point{
	LD x, y;
	Point(LD x = 0, LD y = 0):x(x), y(y){}
	void Scan(){ scanf("%lf%lf", &x, &y); }
	void Print(){ printf("(%.6lf,%.6lf)", x, y); }
};
typedef Point Vector;
struct Circle{
	LD r;
	Point c;
	Circle(){}
	Circle(Point c, LD r):c(c), r(r){}
	Point point(LD a){ return Point(c.x + r * cos(a), c.y + r * sin(a)); }
	void Scan(){ c.Scan(); scanf("%lf", &r); }
	void Print(){ printf("(%.6lf,%.6lf,%.6lf)", c.x, c.y, r); }
};
int Dcmp(LD x){ return fabs(x) < eps? 0 : (x < 0? -1 : 1); }
bool cmp(Vector a, Vector b)
{
	if(Dcmp(a.x - b.x)) return Dcmp(a.x - b.x) < 0;
	return Dcmp(a.y - b.y) < 0;
}
Vector operator + (const Vector &a, const Vector &b){ return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (const Point &a, const Point &b){ return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (const Vector &a, const LD &x){ return Vector(a.x * x, a.y * x); }
Vector operator / (const Vector &a, const LD &x){ return Vector(a.x / x, a.y / x); }
bool operator == (const Point &a, const Point &b){ return Dcmp(a.x - b.x) == 0 && Dcmp(a.y - b.y) == 0; }
bool operator < (const Point &a, const Point &b){ return Dcmp(a.x - b.x) < 0 || (Dcmp(a.x - b.x) == 0 && Dcmp(a.y - b.y) < 0); }
LD Cross(Vector a, Vector b){ return a.x * b.y - a.y * b.x; } // 叉积 
LD Dot(Vector a, Vector b){ return a.x * b.x + a.y * b.y; } // 点积，二者长度的乘积乘上他们夹角的余弦值 
LD Length(Vector a){ return sqrt(Dot(a, a)); } // 向量长度 
LD Angle(Vector a, Vector b){ return acos(Dot(a, b) / Length(a) / Length(b)); } // 夹角 
LD Angle(Vector a){ return atan2(a.y, a.x); }
LD RadToAngle(LD rad)
{
	rad = rad * 180 / PI;
	if(Dcmp(rad) < 0)
		rad += 180;
	else if(Dcmp(rad - 180) >= 0)
		rad -= 180;
	return rad;
}
LD Area2(Point o, Point a, Point b){ return Cross(a - o, b - o); }
Vector Rotate(Vector a, LD rad){ return Vector(a.x * cos(rad) - a.y * sin(rad), a.y * cos(rad) + a.x * sin(rad)); } //逆时针 
Vector Std(Vector a){ LD L = Length(a); return Vector(a.x / L, a.y / L); } // 以1为单位
Vector Normal(Vector a){ return Vector(- a.y, a.x); }
LD DisToLine(Point O, Point A, Point B){ return fabs(Cross(A - O, A - B)) / Length(A - B); }
struct Line{
	Point P;
	Vector v;
	Line(){}
	Line(Point P, Vector v): P(P), v(v){}
	Point point(LD a){ return P + v * a; }
};
Point GetLineInter(Point P, Vector v, Point Q, Vector w)
{
	Vector u = P - Q;
	LD t = Cross(w, u) / Cross(v, w);
	return P + v * t;
}
int GetLineCircleInter(Line L, Circle C, vector<Point>& sol)
{
	LD t1, t2;
	LD a = L.v.x, b = L.P.x - C.c.x;
	LD c = L.v.y, d = L.P.y - C.c.y;
	LD e = a * a + c * c;
	LD f = 2 * (a * b + c * d);
	LD g = b * b + d * d - C.r * C.r;
	LD delta = f * f - 4 * e * g;
	if(Dcmp(delta) < 0)
		return 0;
	if(Dcmp(delta) == 0){
		t1 = t2 = -f / (2 * e);
		sol.push_back(L.point(t1));
		return 1;
	}
	t1 = (-f - sqrt(delta)) / (2 * e);
	t2 = (-f + sqrt(delta)) / (2 * e);
	sol.push_back(L.point(t1));
	sol.push_back(L.point(t2));
}
Circle CircumscribedCircle(Point A, Point B, Point C)
{
	Point Mid1 = (A + B) / 2, Mid2 = (B + C) / 2;
	Point O = GetLineInter((A + B) / 2.0, Normal(A - B), (B + C) / 2.0, Normal(B - C));
	return Circle(O, Length(O - A));
}
Circle InscribedCircle(Point A, Point B, Point C)
{
	Vector L1, L2;
	LD ang1, ang2, r;
	Point O;
	if(Cross(B - A, C - A) < 0)
		std::swap(B, C);
	// When I code these, A, B, C is in Counter-clockwise(逆时针顺序), so if they are not, swap; 
	ang1 = Angle(C - A, B - A) / 2.0;
	ang2 = Angle(C - B, A - B) / 2.0;
	L1 = Rotate(B - A, ang1);
	L2 = Rotate(C - B, ang2);
	O = GetLineInter(A, L1, B, L2);
	r = DisToLine(O, A, B);
	return Circle(O, r);
}
int GetTangents(Point P, Circle C, LD *ans)
{
	Vector u = C.c - P;
	LD dist = Length(u);
	if(dist < C.r) return 0;
	else if(Dcmp(dist - C.r) == 0){
		ans[0] = RadToAngle(Angle(Normal(u)));
		return 1;
	}else{
		LD ang = asin(C.r / dist);
		ans[0] = RadToAngle(Angle(Rotate(u,  ang)));
		ans[1] = RadToAngle(Angle(Rotate(u, -ang)));
		return 2;
	}
}
vector<Point> Work4(Point P, Point A, Point B, LD r)
{
	Vector v0, v1, v2;
	vector<Point> ans;
	v0 = B - A;
	v1 = Std(Normal(v0)) * r;
	GetLineCircleInter(Line(A + v1, v0), Circle(P, r), ans);
	GetLineCircleInter(Line(A - v1, v0), Circle(P, r), ans);
	return ans;
}
Point Work5(Point A, Vector a, Vector b, LD r)
{
	if(Cross(a, b) < 0)
		std::swap(a, b);
	Vector v, L1, L2;
	Point P;
	LD ang, L;
	ang = Angle(a, b) / 2;
	L = r / sin(ang);
	v = Rotate(a, ang);
	v = Std(v);
	v = v * L;
	P = A + v;
	return P;
}
vector<Point> Work6(Circle A, Circle B, LD r)
{
	vector<Point> ans;
	LD L, a, b, c, ang, S;
	Vector v0, v1, v2;
	a = A.r + r;
	b = B.r + r;
	c = Length(A.c - B.c);
	LD maxx = std::max(a, std::max(b, c));
	int tt = Dcmp(a + b + c - 2 * maxx);
	if(tt < 0) return ans;
	else if(tt == 0){
		Vector C = A.c - B.c;
		C = Std(C) * (B.r + r);
		ans.push_back(B.c + C);
		return ans;
	}
	L = (a + b + c) / 2;
	S = sqrt(L * (L - a) * (L - b) * (L - c));
	ang = asin(2 * S / a / c);
	v0 = (A.c - B.c);
	v1 = Std(Rotate(v0,  ang)) * a;
	v2 = Std(Rotate(v0, -ang)) * a;
	Point P = A.c + v1;
	if(Dcmp(Length(A.c - P) - a) || Dcmp(Length(B.c - P) - b)){
		// In some special situation, 'v0 = A.c - B.c' will be causing mistake;
		// So we should make sure that the ans is OK;
		v0 = (B.c - A.c);
		v1 = Std(Rotate(v0,  ang)) * a;
		v2 = Std(Rotate(v0, -ang)) * a;
	}
	ans.push_back(A.c + v1);
	ans.push_back(A.c + v2);
	return ans;
}
void Print_ans(vector<Point> ans)
{
	int tot = ans.size();
	sort(ans.begin(), ans.end());
	REP(i, 0, tot - 1){
		if(i != 0) 
			putchar(',');
		ans[i].Print();
	}
}
void Solve1()
{
	Circle ans;
	Point A, B, C;
	A.Scan();
	B.Scan();
	C.Scan();
	ans = CircumscribedCircle(A, B, C);
	ans.Print();
}
void Solve2()
{
	Circle ans;
	Point A, B, C;
	A.Scan();
	B.Scan();
	C.Scan();
	ans = InscribedCircle(A, B, C);
	ans.Print();
}
void Solve3()
{
	Point O, P;
	LD r;
	O.Scan();
	scanf("%lf", &r);
	P.Scan();
	LD ans[2] = {0};
	int tot = GetTangents(P, Circle(O, r), ans);
	sort(ans, ans + tot);
	REP(i, 0, tot - 1){
		printf("%.6lf", ans[i]);
		if(i != tot - 1)
			putchar(',');
	}
}
void Solve4()
{
	Point P, A, B;
	LD r;
	P.Scan();
	A.Scan();
	B.Scan();
	scanf("%lf", &r);
	vector<Point> ans = Work4(P, A, B, r);
	Print_ans(ans);
}
void Solve5()
{
	Point A, B, C, D, P;
	LD r;
	vector<Point> ans;
	A.Scan();
	B.Scan();
	C.Scan();
	D.Scan();
	P = GetLineInter(A, A - B, C, C - D);
	scanf("%lf", &r);
	ans.push_back(Work5(P, A - B, C - D, r));
	ans.push_back(Work5(P, B - A, C - D, r));
	ans.push_back(Work5(P, A - B, D - C, r));
	ans.push_back(Work5(P, B - A, D - C, r));
	int tot = ans.size();
	Print_ans(ans);
}
void Solve6()
{
	Circle A, B;
	LD r;
	A.Scan();
	B.Scan();
	scanf("%lf", &r);
	vector<Point> ans = Work6(A, B, r);
	int tot = ans.size();
	Print_ans(ans);
}
char T[200];
// String is a little slow;
// There, I choose char[];
int main()
{
	while(scanf("%s", T) == 1){
		if(strcmp(T, "CircumscribedCircle") == 0)
			Solve1();
		else if(strcmp(T, "InscribedCircle") == 0)
			Solve2();
		else{
			putchar('[');
			if(strcmp(T, "TangentLineThroughPoint") == 0)
			Solve3();
			else if(strcmp(T, "CircleThroughAPointAndTangentToALineWithRadius") == 0)
				Solve4();
			else if(strcmp(T, "CircleTangentToTwoLinesWithRadius") == 0)
				Solve5();
			else Solve6();
			putchar(']');
		}
		puts("");
	}
}
