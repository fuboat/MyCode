// LA3218
// Fuboat
// warning!
// 请注意精度问题！ 
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#define LD double
#define Vector Point
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const LD eps = 1e-5, PI = 3.1415926535897932384626;
// 'eps == 1e-5' is OK!
// If it is too small, there will be some problems!
const int MAXN = 200;
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
int Dcmp(LD x){ return fabs(x) < eps? 0 : (x > 0? 1 : -1); }
struct Point{
	LD x, y;
	Point(LD x = 0, LD y = 0):x(x), y(y){}
};
typedef Point Vector;
Vector operator + (const Vector &a, const Vector &b){ return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (const Point &a, const Point &b){ return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (const Vector &a, const LD &x){ return Vector(a.x * x, a.y * x); }
Vector operator / (const Vector &a, const LD &x){ return Vector(a.x / x, a.y / x); }
bool operator == (const Point &a, const Point &b){ return Dcmp(a.x - b.x) == 0 && Dcmp(a.y - b.y) == 0; }
bool operator < (const Point &a, const Point &b){ return a.x < b.x || (a.x == b.x && a.y < b.y); }

LD Cross(Vector a, Vector b){ return a.x * b.y - a.y * b.x; } // 叉积 
LD Dot(Vector a, Vector b){ return a.x * b.x + a.y * b.y; } // 点积，二者长度的乘积乘上他们夹角的余弦值 
LD Length(Vector a){ return sqrt(Dot(a, a)); } // 向量长度 
LD Angle(Vector a, Vector b){ return acos(Dot(a, b) / Length(a) / Length(b)); } // 夹角 
LD Angle(Vector a){ return atan2(a.y, a.x); }
LD Area2(Point o, Point a, Point b){ return Cross(a - o, b - o); }
Vector Rotate(Vector a, LD rad){ return Vector(a.x * cos(rad) - a.y * sin(rad), a.y * cos(rad) + a.x * sin(rad)); }
Vector Normal(Vector a){ LD L = Length(a); return Vector(- a.y / L, a.x / L); } // 以1为单位
Vector Std(Vector a){ LD L = Length(a); return Vector(a.x / L, a.y / L); }
LD DisToLine(Point O, Point A, Point B){ return fabs(Cross(A - O, A - B)) / Length(A - B); }
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
/*Main Program---------------------------------------------*/
int n;
int Round(int y)
{
	while(y <= 0) y += n;
	while(y > n) y -= n;
	return y;
}
Point P[MAXN];
LD Rad(Vector a, Vector b)
{
	LD ang = Angle(a, b);
	return (Dcmp(Cross(a, b)) < 0? ang/*顺时针*/ : PI * 2 - ang/*逆时针*/);
}
LD far2(Point a, Point b)
{
	LD x = a.x - b.x, y = a.y - b.y;
	return x * x + y * y;
}
Point NextNode(Point now, Point front)
{
	int j, k;
	Vector v = front - now, v0;
	REP(i, 1, n) if(P[i] == front){
		j = Round(i + 1);
		k = Round(i - 1);
		return OnSegment(now, P[i], P[j]) || now == P[j]? P[k] : P[j];	
	}
}
void Go(Point &now, Point &front)
{
	bool flag(false);
	Point from, to, next, temp, NewFront;
	const Vector v = front - now;
	Vector v0, v1;
	LD ang = 0, mindist = 1e20, dist, rad;
	REP(i, 1, n){
		from = P[i], to = P[Round(i + 1)], v0 = from - to, v1 = to - from;
		//if(from == front || to == front) continue;
		if(IsSegmentInter(now, front, from, to)){
			temp = GetLineInter(now, v, from, v0);
			dist = far2(now, temp);
			if(Dcmp(Rad(v, v0) - Rad(v, v1)) < 0)
			// 判断转向哪个方向'向右转'得更厉害;
				std::swap(from, to), std::swap(v0, v1);
			rad = Rad(v, v0);
			if(Dcmp(mindist - dist) > 0 || (Dcmp(mindist - dist) == 0 && Chkmax(ang, rad))){
				// Don't use 'Chkmin()' for mindist!
				// They are 'double'!
				// This is why the 'eps' can't be too small!
				mindist = dist;
				flag = true;
				NewFront = to;
				next = temp;
				ang = rad;
			}
		}
	}
	if(!flag){
		temp = front;
		front = NextNode(now, front);
		now = temp;
	}else now = next, front = NewFront;
}
void Init()
{
	REP(i, 1, n)
		scanf("%lf%lf", &P[i].x, &P[i].y);
}
void Solve()
{
	std::vector<Point> ans;
	Point front, now, v0, v1;
	int num = -1, up, down;
	REP(i, 1, n){
		if(num == -1 || P[i] < now){
			num = i;
			now = P[i];
			v0 = P[Round(i + 1)] - P[i];
			v1 = P[Round(i - 1)] - P[i];
		}
	}
	if(Dcmp(Cross(v0, v1)) > 0)
		front = P[Round(num + 1)];
	else front = P[Round(num - 1)];
	while(true){
		Go(now, front);
		ans.push_back(now);
		if(now == P[num]) break;
	}
	printf("%d\n", ans.size());
	REP(i, 0, ans.size() - 1)
		printf("%.4lf %.4lf\n", ans[i].x, ans[i].y);
}
int main()
{
	while(~scanf("%d", &n) && n){
		Init();
		Solve();
	}
}
