// UVa11722
// Fuboat
// 注意，在这份代码里,为了方便,我将所有的面积[*2]; 
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
int t1, t2, s1, s2, w, S;
int kill1, kill2;
int f(int x){ return x + w; }
int ff(int y){ return y - w; }
bool In(int x, int l, int r){ return x >= l && x <= r; }
int Work()
{
	int kill(0);
	if(In( f(t1), s1, s2) && In(ff(s2), t1, t2))
		kill = (s2 - f(t1)) * (ff(s2) - t1);
	if(In(ff(s1), t1, t2) && In(ff(s2), t1, t2))
		kill = ((ff(s1) - t1) + (ff(s2) - t1)) * (s2 - s1);
	if(In( f(t1), s1, s2) && In( f(t2), s1, s2))
		kill = ((s2 -  f(t1)) + (s2 -  f(t2))) * (t2 - t1);
	if(In(ff(s1), t1, t2) && In( f(t2), s1, s2))
		kill = S - (t2 - ff(s1)) * (f(t2) - s1);
	if(f(t2) < s1)
		kill = S;
	return kill;
}
void Solve()
{
	int kill1, kill2, ans = S;
	kill1 = Work();
	w = -w;
	kill2 = Work();
	ans = kill2 - kill1;
	if(ans < 0) ans = 0;
	if(ans > S) ans = S;
	printf("%.8lf\n", 1.0 * ans / S);
}
int main()
{
	int T;
	scanf("%d", &T);
	REP(i, 1, T){
		printf("Case #%d: ", i);
		scanf("%d%d%d%d%d", &t1, &t2, &s1, &s2, &w);
		S = 2 * (t1 - t2) * (s1 - s2);
		Solve();
	}
}

