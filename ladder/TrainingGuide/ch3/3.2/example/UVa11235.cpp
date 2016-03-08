/* 
	FROM: UVa
	TASK: 11235
	ID: fuboat
	ALGORITHM: Especial
	DATA STRUCTURE: RMQ
	MISTAKE:
	1.(line 34) Forget to init maxv[][0];
	2.(line 43) 'maxv[r - (1 << k) + 1][k]', not 'maxv[r - (1 << k)][k]';
*/
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

const int MAXN = 100000 + 1000, MAXD = log((double)MAXN)/log(2.0) + 20;
int a[MAXN], left[MAXN * 3], right[MAXN * 3], S[MAXN * 3], n, q;
int *lft = left + 120000, *rht = right + 120000, *sum = S + 120000;

struct rmq{
	int maxv[MAXN][MAXD];
	void init()
	{
		memset(maxv, 0, sizeof(maxv));
		int d = log((double)n)/log(2.0);
		REP(i, 1, n) maxv[i][0] = sum[a[i]];
		REP(k, 1, d) REP(i, 1, n)
			if(i + (1 << k) - 1 <= n)
				maxv[i][k] = max(maxv[i][k - 1], maxv[i + (1 << k - 1)][k - 1]);
	}
	int query(int l, int r)
	{
		if(l > r) return 0;
		int k = log((double)(r - l + 1))/log(2.0);
		return max(maxv[l][k], maxv[r - (1 << k) + 1][k]);
	}
}t;

int RMQ(int l, int r)
{
	if(r < l) return 0;
	if(a[l] == a[r]) return r - l + 1;
	int maxv = t.query(rht[a[l]] + 1, lft[a[r]] - 1);
	chkmax(maxv, rht[a[l]] - l + 1);
	chkmax(maxv, r - lft[a[r]] + 1);
	return maxv;
}

int main()
{
	while(scanf("%d", &n) && n){
		memset(a, 0, sizeof(a));
		memset(left, 0, sizeof(left));
		memset(right, 0, sizeof(right));
		memset(S, 0, sizeof(S));
		scanf("%d", &q);
		int l, r;
		REP(i, 1, n){
			scanf("%d", &a[i]);
			if(i == 1 || a[i] != a[i - 1]){
				if(i != 1) rht[a[i - 1]] = i - 1;
				lft[a[i]] = i;
			}
			sum[a[i]] ++;
		}
		rht[a[n]] = n;
		t.init();
		REP(i, 1, q){
			scanf("%d%d", &l, &r);
			printf("%d\n", RMQ(l, r));
		}
	}
}
