#ifdef WIN32
	#define ll "%I64d"
#else
	#define ll "%lld"
#endif
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#define LD long double
#define pii pair<int, int>
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 50000;
int a[MAXN + 100], f[MAXN + 100];

int main()
{
	int n, m, b, e;
	scanf("%d", &n);
	REP(i, 1, n){
		scanf("%d%d", &b, &e);
		a[b] ++;  a[e + 1] --;
	}
	f[0] = a[0];
	REP(i, 1, MAXN)
		f[i] = f[i - 1] + a[i];
	scanf("%d", &m);
	REP(i, 1, m){
		scanf("%d", &b);
		printf("%d\n", f[b]);
	}
	return 0;
}		
