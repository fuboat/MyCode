/*
	ID: fuboat
	TASK: 1125
	DATE: 2015.11.23
*/
/*
	mistake:
	1. The distant of two node is counted in a wrong way;
	2. Write the code before understanding the problem;
	3. count 'pi' in a wrong way;
*/
#include <cstdio>
#include <cmath>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
const int MAXN = 1000, oo = 0x7fffffff;
const double pi = 3.1415926535;
double ans = oo;

struct node{
	double x, y;
}s[MAXN + 10];
int n;

double dis(node a, node b)
{
	return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}	

int main()
{
	scanf("%d", &n);
	REP(i, 1, n) scanf("%lf%lf", &s[i].x, &s[i].y);
	REP(i, 1, n){
		double tmp = 0;
		REP(j, i, n)
			chkmax(tmp, dis(s[i], s[j]));
		chkmin(ans, tmp);
	}	
	printf("%.4lf", ans * pi);
	return 0;
}	
