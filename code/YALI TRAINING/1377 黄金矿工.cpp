#ifdef WIN32
	#define ll "%I64d"
#else
	#define ll "%lld"
#endif
#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
bool chkmin(LL &x, LL y){return y < x? (x = y, true) : false;}
bool chkmax(LL &x, LL y){return y > x? (x = y, true) : false;}
const int MAXN = 300;
const LL oo = 0x7fffffff;
LL a[MAXN + 100][MAXN + 100], sum[MAXN + 100][MAXN + 100], all[MAXN + 100][MAXN + 100], ans[MAXN + 100];
int n;
LL maxx = 0;

int main()
{
	scanf(ll, &n);
	REP(i, 1, n)
		REP(j, 1, n){
			scanf(ll, &a[i][j]);
			if(!a[i][j]) a[i][j] = -oo;
			all[i][j] = all[i][j - 1] + a[i][j];
			sum[i][j] = sum[i - 1][j] + all[i][j];
		}
	REP(i, 1, n)
		REP(j, i, n){
			REP(k, 1, n)  ans[k] = sum[j][k] - sum[i - 1][k];
			LL minx = 0;
			REP(k, 1, n){
				if(ans[k] - minx - 10 > maxx) maxx = ans[k] - minx - 10;
				chkmin(minx, ans[k]);
			}
		}
	printf(ll, maxx);
	return 0;
}
