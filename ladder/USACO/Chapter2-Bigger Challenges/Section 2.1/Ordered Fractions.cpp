/*
	ID: fuboat
	TASK: frac1
	LANG: C++
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 160 + 10;
int n, cnt;
 
struct frac{
	int up, down;
	bool operator < (const frac &a) const{
		return up * a.down < a.up * down;
	}
}s[MAXN * MAXN];

int gcd(int a, int b)
{
	if(b) return gcd(b, a % b);
	return a;
}

int main()
{
	freopen("frac1.in", "r", stdin);
	freopen("frac1.out", "w", stdout);
	scanf("%d", &n);
	REP(i, 0, n) REP(j, i, n)
		if(gcd(i, j) == 1)
			s[++ cnt] = (frac){i, j};
	sort(s + 1, s + cnt + 1);
	REP(i, 1, cnt) printf("%d/%d\n", s[i].up, s[i].down);
}
