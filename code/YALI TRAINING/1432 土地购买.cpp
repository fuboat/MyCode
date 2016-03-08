// YALItraining1432
// Fuboat
#include <cstdio>
#include <algorithm>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#ifdef WIN32
	#define ll "%I64d"
#else
	#define ll "%lld"
#endif
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXN = 5000 + 100;
const LL oo = 1LL<<50;
int n, N;
int a[MAXN], b[MAXN];
bool die[MAXN];
LL f[MAXN];
struct Land{
	int x, y;
	Land(int x = 0, int y = 0):x(x), y(y){}
	bool operator < (const Land &a) const{ return x < a.x || (x == a.x && y < a.y); }
}s[MAXN];
/*Init(sort and abandon some useless land)-----------------------------------------*/
void Init()
{
	int x, y;
	scanf("%d", &n);
	REP(i, 1, n){
		scanf("%d%d", &x, &y);
		s[i] = Land(x, y);
	}
	std::sort(s + 1, s + n + 1);
	rep(i, n, 1) if(!die[i])
		REP(j, 1, i - 1)
			if(s[i].y >= s[j].y)
				die[j] = true;
	REP(i, 1, n)
		if(!die[i]){
			N ++;
			a[N] = s[i].x;
			b[N] = s[i].y;
		}
}
/*Dynamic Programming(f(x) = min{f(i - 1) + a(x) * b(i) | 1 <= i <= x})------------------------------------*/
/*
[含义]
	a(i), b(i) 表示筛去可以被嵌入的矩形后,第 i 个矩形的长和宽;
	f(x)表示购买前x块土地所需的价格; 
[原理]
	在经过以上的处理后,对于任意的i, j(i < j, die[i] = die[j] = false),
	都有 s[i].x < s[j].x && s[i].y > s[j].y.
	否则,若s[i].x > s[j].x, 则 j 将会被 i 筛去 (die[j] = true).
	由于上述的成立,动规的正确性可以保证(请自行证明). 
*/ 
void Solve()
{
	f[0] = 0;
	REP(i, 1, N){
		f[i] = oo;
		REP(j, 1, i)
			Chkmin(f[i], f[j - 1] + 1LL * a[i] * b[j]);
	}
	printf(ll, f[N]);
}
int main()
{
	Init();
	Solve();
	return 0;
}
