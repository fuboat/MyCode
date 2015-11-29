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
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

#define REP(i, x, y) for(int i = x; i <= y; i ++)
#define Rep(i, x, y) for(int i = x; i >= y; i --)
#define LL long long
#define LD long double
#define pii pair<int, int>
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y , true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y , true) : false;}
const int MAXN = 3000;
const LL oo = 0x7fffffffff;
int n, s, a[MAXN + 100];
LL sum[MAXN + 100];
LL ans = oo;
LL f[MAXN + 100];
int main(){
	scanf("%d%d", &n, &s);
	REP(i, 1, n){
		scanf("%d", &a[i]);
		sum[i] = sum[i - 1] + a[i];
	}
	REP(i, 1, n){
		f[i] = oo;
		REP(j, 0, i - 1)
			chkmin(f[i], f[j] + (n - i) * s + i * (sum[i] - sum[j]));
	}
	printf("%d\n", f[n]);
	return 0;
}
