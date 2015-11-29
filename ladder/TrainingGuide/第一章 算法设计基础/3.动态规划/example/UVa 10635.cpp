#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 250, MAXA = 62500;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
int ok[MAXA + 10], f[MAXA + 10], g[MAXA + 10];

int main()
{
	int T, n, p, q, cnt = 0;
	scanf("%d", &T);
	while(++ cnt <= T){
		int ans = 0;
		scanf("%d%d%d", &n, &p, &q);
		memset(ok, 0, sizeof(ok));
		memset(g, 0x7f, sizeof(g));
		REP(i, 1, p + 1){
			int tmp;
			scanf("%d", &tmp);
			ok[tmp] = i;
		}
		REP(i, 1, q + 1){
			int tmp;
			scanf("%d", &tmp);
			f[i] = ok[tmp];
		}
		REP(i, 1, q + 1)
			if(f[i]){
				int pos = lower_bound(g + 1, g + p + 1, f[i]) - g;
				g[pos] = f[i];
				chkmax(ans, pos);
			}
		printf("Case %d: %d\n", cnt, ans);
	}
	return 0;
}
