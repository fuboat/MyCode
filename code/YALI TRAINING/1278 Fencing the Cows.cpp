#include <cstdio>
  #include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#define X first
#define Y second
#define pdd pair<double, double>
#define MK(x, y) make_pair(x, y)
#define REP(i, x, y) for(int i = x; i <= y; i ++)
#define Rep(i, x, y) for(int i = x; i >= y; i --)
using std::pair;
using std::make_pair;

double cj(pdd a, pdd b){return a.X * b.Y - a.Y * b.X;}

double cross(pdd o, pdd a, pdd b){return cj(MK(o.X - a.X, o.Y - a.Y), MK(o.X - b.X, o.Y - b.Y));}

double dis(pdd a, pdd b){return sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y));}


const int MAXN = 10000;
pdd a[MAXN + 100], s[MAXN + 100];

int main(){
	int n;
	scanf("%d", &n);
	REP(i, 1, n) scanf("%lf%lf", &a[i].X, &a[i].Y);
	sort(a + 1, a + n + 1);
	int top = 0;
	REP(i, 1, n){
		while(top >= 2 && cross(s[top - 1], s[top], a[i]) <= 0)
			top --;
		s[++ top] = a[i];
	}
	
	int t = top;
	Rep(i, n - 1, 1){
		while(top > t && cross(s[top - 1], s[top], a[i]) <= 0)
			top --;
		s[++ top] = a[i];
	}
	
	double ans = 0;
	
	REP(i, 2, top) ans += dis(s[i], s[i - 1]);
	
	printf("%.2lf\n", ans);
	return 0;
}
