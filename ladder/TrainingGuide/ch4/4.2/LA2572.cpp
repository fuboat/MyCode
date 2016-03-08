// LA2572
// Circle
// Fuboat
#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
typedef double LD;
/*Public----------------------------------------------*/
const int MAXN = 100 + 100;
int n;
bool CanBeLooked[MAXN];
/*Circle----------------------------------------------*/
const LD eps = 1e-13, PI = 3.141592653589793238462643383279502884197169399;
// After trying many times, 'eps = 1e-12' is also not enough;
struct Point{
	LD x, y;
	Point(LD x = 0, LD y = 0): x(x), y (y){}
	void Scan(){ scanf("%lf%lf", &x, &y); }
};
typedef Point Vector;
Vector operator + (const Vector &A, const Vector &B){ return Vector(A.x + B.x, A.y + B.y); }
Vector operator - (const Vector &A, const Vector &B){ return Vector(A.x - B.x, A.y - B.y); }
int Dcmp(LD x){ return fabs(x) < eps? 0 : (x < 0? -1 : 1); }
LD Dot(Vector a, Vector b){ return a.x * b.x + a.y * b.y; }
LD Angle(Vector a){ return atan2(a.y, a.x); }
LD Length(Vector a){ return sqrt(Dot(a, a)); }
LD Std(LD ang){  
	if(Dcmp(ang + PI) < 0) ang += PI * 2;
	else if(Dcmp(ang - PI) > 0) ang -= PI * 2;
	return ang;
}
struct Circle{
	Point c;
	LD r;
	vector<LD> sol;
	Circle(Point c = Point(0, 0), LD r = 0): c(c), r(r){}
	Point point(LD ang){ return Point(c.x + r * cos(ang), c.y + r * sin(ang)); }
	void CircleInter(Circle C)
	{
		LD d, a, da;
		d = Length(c - C.c);
		if(Dcmp(d) == 0 || Dcmp(r + C.r - d) < 0 || Dcmp(fabs(r - C.r) - d) > 0)
			return ;
			
		a = Angle(C.c - c);
		da = acos((r * r + d * d - C.r * C.r) / (2 * r * d));
		if(Dcmp(da) == 0) return ;
		sol.push_back(Std(a - da));
		sol.push_back(Std(a + da));
	}
	void Scan(){ c.Scan(); scanf("%lf", &r); }
}cir[MAXN];
/*Main Program------------------------------------------*/
void Update(int num)
{
	static Circle C, D, E;
	static vector<LD> sol;
	static LD tmp, last, now;
	static Point P[2];
	C = cir[num];
	E = D = C;
	D.r += eps * 10;
	E.r -= eps * 10;
	sol = C.sol;
	int tot = sol.size();
	REP(i, 0, tot - 1) REP(j, i + 1, tot - 1){
		last = sol[i];
		now = sol[j];
		if(Dcmp(last - now) == 0) continue;
		P[0] = D.point((now + last) / 2);
		P[1] = E.point((now + last) / 2);
		REP(k, 0, 1) rep(w, n, 1){
			tmp = cir[w].r - Length(cir[w].c - P[k]);
			if(Dcmp(tmp) > 0){
				CanBeLooked[w] = true;
				break;
			}
		}
	}
}
void Init()
{
	CLEAR(CanBeLooked);
	CLEAR(cir);
	REP(i, 1, n){
		cir[i].Scan();
		cir[i].sol.push_back( PI);
		cir[i].sol.push_back(-PI);
		// If the circle has no Intersection, this will be helpful;
	}
	REP(i, 1, n) REP(j, 1, n)
		cir[i].CircleInter(cir[j]);
}
void Solve()
{
	int ans = 0;
	REP(i, 1, n)
		Update(i);
	REP(i, 1, n)
		if(CanBeLooked[i])
			ans ++;
	printf("%d\n", ans);
}
int main()
{
	while(scanf("%d", &n) == 1 && n){
		Init();
		Solve();
	}
}
