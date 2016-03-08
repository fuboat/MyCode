// LA2797
// Fuboat
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <iostream>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
typedef double LD;
using namespace std;
/*Public---------------------------------------------------------------------*/
const int MAXN = 500 + 100;
/*Vector and Point-----------------------------------------------------------*/
const LD eps = 1e-6;
struct Point{
	LD x, y;
	Point(LD x = 0, LD y = 0):x(x), y(y){}
	void Scan(){ scanf("%lf%lf", &x, &y); }
};
typedef Point Vector;
int Dcmp(LD x){ return fabs(x) < eps? 0 : (x < 0? -1 : 1); }
Vector operator + (const Vector &a, const Vector &b){ return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (const Point &a, const Point &b){ return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (const Vector &a, const LD &x){ return Vector(a.x * x, a.y * x); }
Vector operator / (const Vector &a, const LD &x){ return Vector(a.x / x, a.y / x); }
bool operator == (const Point &a, const Point &b){ return Dcmp(a.x - b.x) == 0 && Dcmp(a.y - b.y) == 0; }
bool operator < (const Point &a, const Point &b){ return a.x < b.x || (a.x == b.x && a.y < b.y); }

LD Cross(Vector a, Vector b){ return a.x * b.y - a.y * b.x; } // 叉积 
LD Dot(Vector a, Vector b){ return a.x * b.x + a.y * b.y; } // 点积，二者长度的乘积乘上他们夹角的余弦值 
LD Length(Vector a){ return sqrt(Dot(a, a)); } // 向量长度 
Vector Std(Vector a){ LD L = Length(a); return Vector(a.x / L, a.y / L); }
bool OnSegment(Point O, Point A, Point B){ return Dcmp(Cross(A - O, B - O)) == 0 && Dcmp(Dot(A - O, B - O)) < 0; }
bool IsSegmentInter(Point A1, Point A2, Point B1, Point B2)
{
	LD c1 = Cross(A2 - A1, B2 - A1), c2 = Cross(A2 - A1, B1 - A1), 
	   c3 = Cross(B2 - B1, A1 - B1), c4 = Cross(B2 - B1, A2 - B1);
	return Dcmp(c1) * Dcmp(c2) < 0 && Dcmp(c3) * Dcmp(c4) < 0;
}
void Update(Point &A, Point &B)
{
	Vector v = Std(A - B);
	A = A + v * 0.1;
	B = B - v * 0.1;
	// ***!
	// 0.1! so large (for eps)!
	// I have tried too many times!
}
/*Union Set----------------------------------------------------------*/
int f[MAXN * 2];
int Find(int x){ return x == f[x]? x : f[x] = Find(f[x]); }
/*Main Program-------------------------------------------------------*/
int totnode, n;
Point P[MAXN * 2], Q[MAXN * 2];
int from[MAXN * 2], home[MAXN];
void Init()
{
	int now;
	bool flag;
	REP(i, 1, n){
		now = i << 1;
		Q[now].Scan();
		Q[now ^ 1].Scan();
		Update(Q[now], Q[now ^ 1]);
		from[now] = from[now ^ 1] = i;
	}
	totnode = 2;
	P[1] = Point(0, 0);
	P[2] = Point(60, 60);
	REP(i, 2, n << 1|1){
		flag = true;
		REP(j, 1, n) if(from[i] != j){
			now = j << 1;
			if(OnSegment(Q[i], Q[now], Q[now ^ 1])){
				flag = false;
				break;
			}
		}
		if(flag){
			P[++ totnode] = Q[i];
			home[totnode] = from[i];
		}
	}
	REP(i, 1, totnode)
		f[i] = i;
}
void Solve()
{
	int now;
	bool flag;
	REP(i, 1, totnode)
		REP(j, 1, totnode){
			flag = true;
			REP(k, 1, n){
				if(home[i] == k || home[j] == k)
					continue;
				now = k << 1;
				if(IsSegmentInter(P[i], P[j], Q[now], Q[now | 1])){
					flag = false;	
					break;
				}
			}
			if(flag)
				f[Find(i)] = Find(j);
		}
	puts(Find(1) == Find(2)? "no" : "yes");
}
int main()
{
	while(scanf("%d", &n) && n){
		Init();
		Solve();
	}
}

