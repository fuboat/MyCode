// LA4992
// Halfplane intersection
// Fuboat
// warning!
// 我原先这道题的理解有偏差
// 这道题是询问至少要炸掉几个瞭望塔时必然可以使总部暴露 
// 而我把它错误地理解为了保证总部安全的情况下敌人可以炸几个 
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#define REP(i, x, y) for(int i = x, _ = y; i <= _;i ++)
typedef double LD;
const int MAXN = 50000 + 5000;
/*计算几何----------------------------------------------*/ 
struct Point{
	LD x, y;
	Point(){}
	Point(LD x, LD y):
		// Not 'int';
		x(x), y(y){}
	Point operator + (const Point &P) const{ return Point(x + P.x, y + P.y); }
	Point operator - (const Point &P) const{ return Point(x - P.x, y - P.y); }
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
};
Point GetLineInter(Line a, Line b)
{
	Vector u = a.P - b.P;
	LD t = Cross(b.v, u) / Cross(a.v, b.v);
	return a.P + a.v * t;
}
Point p[MAXN];
Line q[MAXN];
int HalfplaneInter(Line *L, int N)
{
	int first(1), last(1);
	std::sort(L + 1, L + N + 1);
	q[1] = L[1];
	REP(i, 2, N){
		while(first < last && !L[i].Onleft(p[last - 1])) -- last; 
		while(first < last && !L[i].Onleft(p[first])) ++ first;
		if(L[i].v.x == q[last].v.x && L[i].v.y == q[last].v.y){
			// warning!
			// 由于都是用整数输入,计算得出的向量也是整数级别的;
			// 几乎无需考虑精度;
			// 直接用'==', 'eps' is useless;  
			// 这是这道题最需要注意的地方,没有之一; 
			if(!L[i].Onleft(q[last].P))
				q[last] = L[i];
		}else q[++ last] = L[i]; // Don't forget this;
		if(first < last) p[last - 1] = GetLineInter(q[last - 1], q[last]);
	}
	while(first < last && !q[first].Onleft(p[last - 1])) -- last;
	
	if(last - first <= 1) return 0;
	return 1;
}
/*Main Program--------------------------------------------*/
int n;
Point P[MAXN];
Line L[MAXN];
bool Check(int x)
{
	int next;
	REP(i, 1, n){
		next = i + x + 1;
		if(next > n) next -= n;
		L[i] = Line(P[i], P[i] - P[next]);
	}
	return !HalfplaneInter(L, n);
}
void Init()
{
	REP(i, 1, n)
		scanf("%lf%lf", &P[i].x, &P[i].y);
}
void Solve()
{
	int l = 0, r = n, mid;
	while(l + 1 < r){
		mid = l + (r - l) / 2;
		if(Check(mid)) // Kill the enemy successfully;
			r = mid;
		else l = mid;
	}
	printf("%d\n", r);
}
int main()
{
	while(scanf("%d", &n) == 1){
		Init();
		Solve();
	}
}
