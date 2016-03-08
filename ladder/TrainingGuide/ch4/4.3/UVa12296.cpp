#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
typedef double LD;
const LD eps = 1e-8;
const int MAXN = 200;
LD Dcmp(LD x){ return fabs(x) < eps? 0 : (x > 0? 1 : -1); }
struct Point{
	LD x, y;
	Point(LD x = 0, LD y = 0): x(x), y(y){}
	Point operator + (const Point &P) const{ return Point(x + P.x, y + P.y); }
	Point operator - (void)const { return Point(-x, -y); }
	Point operator - (const Point &P) const{ return Point(x - P.x, y - P.y);  }
	Point operator * (const LD &d) const{ return Point(x * d, y * d); }
	Point operator / (const LD &d) const{ return Point(x / d, y / d); }
	void Scan(){ scanf("%lf%lf", &x, &y); }
};
typedef Point Vector;
typedef std::vector<Point> Polygon;
LD Dot(Vector a, Vector b){ return a.x * b.x + a.y * b.y; }
LD Cross(Vector a, Vector b){ return a.x * b.y - b.x * a.y; }
LD Length(Vector v){ return sqrt(Dot(v, v)); }
LD Area2(Point P, Point A, Point B){ return Cross(A - P, B - P); }
LD DisToLine(Point P, Point A, Point B){ return fabs(Area2(P, A, B)) / Length(A - B); }
Vector Normal(Vector v){ return Vector(-v.y, v.x); }
Point GetLineInter(Point P, Vector v, Point Q, Vector w)
{
	Vector u = P - Q;
	LD t = Cross(w, u) / Cross(v, w);
	return P + v * t;
}
LD Area(Polygon poly)
{
	LD area = 0;
	int tot = poly.size();
	REP(i, 1, tot - 2){
		area += Area2(poly[0], poly[i], poly[i + 1]);
	}
	return area / 2;
}
LD DisToSegment(Point P, Point A, Point B)
{
	Vector v1 = B - A, v2 = P - A, v3 = P - B;
	if(Dcmp(Dot(v1, v2)) < 0) return Length(v2);
	if(Dcmp(Dot(v1, v3)) > 0) return Length(v3);
	return DisToLine(P, A, B);
}
bool OnSegment(Point P, Point A, Point B){ return Dcmp(Cross(P - A, P - B)) == 0 && Dcmp(Dot(P - A, P - B)) < 0; }
// Don't forget the 'Dcmp()' in 'OnSegment()'!
int PointInPolygon(Point P, Polygon poly)
{
	int wn = 0, tot = poly.size(), d1, d2, k;
	Point now, front;
	REP(i, 0, tot - 1){
		now = poly[i];
		front = poly[(i + 1) % tot];
		if(OnSegment(P, now, front)) return 1;
		k = Dcmp(Cross(front - now, P - now));
		d1 = Dcmp(now.y - P.y);
		d2 = Dcmp(front.y - P.y);
		if(k > 0 && d1 <= 0 && d2 > 0) wn ++;
		if(k < 0 && d2 <= 0 && d1 > 0) wn --;
	}
	return wn != 0;
}
struct Circle{
	Point C;
	LD r;
	Circle(){}
	Circle(Point c, LD r): C(c), r(r){}
	bool InCircle(Point P){ return Dcmp(r - Length(P - C)) > 0; }
	bool OnCircle(Point P){ return Dcmp(r - Length(P - C)) == 0; }
	int LineCircleInter(Point A, Point B, LD& t1, LD& t2){
		LD a = B.x - A.x, b = A.x - C.x, c = B.y - A.y, d = A.y - C.y;
		LD e = a * a + c * c, f = 2 * (a * b + c * d), g = b * b + d * d - r * r;
		LD delta = f * f - 4 * e * g;
		if(Dcmp(delta) < 0) return 0;
		if(Dcmp(delta) == 0){
   			t1 = t2 = -f / (2 * e);
   		 	return 1;
		}
  		t1 = (-f - sqrt(delta)) / (2 * e);
  		t2 = (-f + sqrt(delta)) / (2 * e);
  		return 2;
	}
	bool CircleSegmentInter(Point A, Point B)
	{
		Point P1, P2;
		LD t1, t2;
		int k = LineCircleInter(A, B, t1, t2);
		if(k <= 1)
			return false;
		P1 = (A + (B - A) * t1);
		P2 = (A + (B - A) * t2);
		return OnSegment(P1, A, B) || OnSegment(P2, A, B);
		// 只要有一个交点,即为规范相交,请注意; 
	}
	bool CirclePolygonInter(Polygon poly)
	{
		Point A, B;
		int tot = poly.size();
		if(PointInPolygon(C, poly)) // Circle is in the polygon; 
			return true;
		REP(i, 0, tot - 1){
			A = poly[i], B = poly[(i + 1) % tot];
			if(InCircle(A) || InCircle((A + B) * 0.5) || CircleSegmentInter(A, B))
				return true;
		}
		return false;
	}
};
Polygon CutPolygon(Polygon poly, Point A, Point B)
{
	Point C, D, P;
	Polygon newpoly;
	int tot = poly.size();
	REP(i, 0, tot - 1){
		C = poly[i];
		D = poly[(i + 1) % tot];
		if(Dcmp(Cross(B - A, C - A)) >= 0)
			newpoly.push_back(C);
		if(Dcmp(Cross(D - C, B - A)) != 0){
			P = GetLineInter(A, B - A, C, D - C);
			if(OnSegment(P, C, D))
				newpoly.push_back(P);
		}
	}
	return newpoly;
}
/*Main Program-----------------------------------------------*/
int n, m, L, W;
std::vector<Polygon> all;
std::vector<LD> ans[MAXN];
Point S[MAXN][2];
Circle cir[MAXN];
LD area[MAXN];
void Init()
{
	all.clear();
	Polygon poly;
	poly.push_back(Point(0, 0));
	poly.push_back(Point(L, 0));
	poly.push_back(Point(L, W));
	poly.push_back(Point(0, W));
	all.push_back(poly);
	REP(i, 1, n){
		S[i][0].Scan();
		S[i][1].Scan();
	}
	REP(i, 1, m){
		cir[i].C.Scan();
		scanf("%lf", &cir[i].r);
	}
}
void Solve()
{
	Polygon poly, new1, new2;
	REP(i, 1, n){
		std::vector<Polygon> temp;
		REP(j, 0, all.size() - 1){
			poly = all[j];
			new1 = CutPolygon(poly, S[i][0], S[i][1]);
			new2 = CutPolygon(poly, S[i][1], S[i][0]);
			if(new1.size() >= 3 && Dcmp(Area(new1)) != 0) temp.push_back(new1);
			if(new2.size() >= 3 && Dcmp(Area(new2)) != 0) temp.push_back(new2);
		}
		all = temp;
	}
	REP(i, 0, all.size() - 1)
		area[i] = Area(all[i]);
	REP(i, 1, m){
		ans[i].clear();
		REP(j, 0, all.size() - 1)
			if(cir[i].CirclePolygonInter(all[j]))
				ans[i].push_back(area[j]);
	}
	REP(i, 1, m){
		printf("%d", ans[i].size());
		std::sort(ans[i].begin(), ans[i].end());
		REP(j, 0, ans[i].size() - 1)
			printf(" %.2lf", ans[i][j]);
		puts("");
	}
	puts("");
}
int main()
{
	while(scanf("%d%d%d%d", &n, &m, &L, &W) == 4){
		if(!(n | m || L || W)) break;
		Init();
		Solve();
	}
}
