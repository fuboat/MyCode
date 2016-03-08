#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#define MSET(a, x) memset(a, x, sizeof(a))
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 100000 + 1000;
int n, sum, L, R;
int ans[MAXN];
struct sta{
	int l, r, pos;
	bool operator < (const sta &a) const{
		if(r != a.r) return r > a.r;
		return l < a.l;
	}
}a[MAXN];
struct segment{
	int sumv[MAXN * 2];
	void update(int o, int l, int r)
	{
		if(l == r) sumv[o] ++;
		else{
			int lc = o << 1, rc = o << 1|1;
			int mid = (l + r) >> 1;
			if(L <= mid) update(lc, l, mid);
			else update(rc, mid + 1, r);
			sumv[o] = sumv[lc] + sumv[rc];
		}
	}
	
	void query(int o, int l, int r)
	{
		if(r <= R)
			sum += sumv[o];
		else{
			int mid = (l + r) >> 1;
			query(o << 1, l, mid);
			if(mid < R) query(o << 1|1, mid + 1, r);
		}
	}
}t;
int main()
{
	while(scanf("%d", &n) && n){
		int maxx = 0;
		memset(t.sumv, 0, sizeof(t.sumv));
		REP(i, 1, n){
			scanf("%d%d", &a[i].l, &a[i].r);
			a[i].pos = i;
			a[i].l ++;
			a[i].r ++;
			chkmax(maxx, a[i].l);
		}
		sort(a + 1, a + n + 1);
		REP(i, 1, n){
			R = a[i].l;
			sum = 0;
			if(a[i].l == a[i - 1].l && a[i].r == a[i-1].r) ans[a[i].pos] = ans[a[i - 1].pos];
			else{
				t.query(1, 1, maxx);
				ans[a[i].pos] = sum;
			}
			L = a[i].l;
			t.update(1, 1, maxx);
		}
		printf("%d", ans[1]);
		REP(i, 2, n)
			printf(" %d", ans[i]);
		putchar('\n');
	}
}
