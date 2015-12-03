/*
	FROM: UVaLive
	ID: fuboat
	ALGORITHM: Math
	DATA STRUCTURE: Fenwick
	MISTAKE:
	1.(line 29) 's[pos] += x', not 's[pos] += pos' or 's[x] += pos';
	2.(line 30) 'pos += pos & -pos', not 'pos += x & -x' or 'x += x & -x';
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
const int MAXN = 20000 + 100, MAXA = 100000 + 10;
int a[MAXN], maxa, n;
struct fenwick{
	int s[MAXA];
	void add(int pos, int x)
	{
		while(pos <= maxa){
			s[pos] += x;
			pos += pos & -pos;
		}
	}
	
	int sum(int pos)
	{
		int sum = 0;
		while(pos > 0){
			sum += s[pos];
			pos -= pos & -pos;
		}
		return sum;
	}
}t;

int c[MAXN], d[MAXN];

int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		maxa = 0;
		REP(i, 1, n){
			scanf("%d", &a[i]);
			chkmax(maxa, a[i]);
		}
		memset(t.s, 0, sizeof(t.s));
		REP(i, 1, n){
			c[i] = t.sum(a[i]);
			t.add(a[i], 1);
		}
		memset(t.s, 0, sizeof(t.s));
		Rep(i, n, 1){
			d[i] = t.sum(a[i]);
			t.add(a[i], 1);
		}
		LL ans = 0;
		REP(i, 1, n)
			ans += c[i] * (n - i - d[i]) + (i - c[i] - 1) * d[i];
		printf("%lld\n", ans);
	}
}
