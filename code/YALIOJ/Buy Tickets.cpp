#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 300000 + 1000;
int n, now, L, R;
bool flag;
struct sta{
	int pos, num;
}a[MAXN];
int s[MAXN];

struct segment{
	int sumv[MAXN * 2];
	void init(int o, int l, int r)
	{
		sumv[o] = r - l + 1;
		if(l != r){
			int mid = (l + r) >> 1;
			init(o << 1, l, mid);
			init(o << 1|1, mid + 1, r);
		}
	}
	void update(int o, int l, int r)
	{
		sumv[o] --;
		if(l == r) s[l] = now;
		else{
			int lc = o << 1, rc = o << 1|1, mid = (l + r) >> 1;
			if(L <= sumv[lc]) update(lc, l, mid);
			else{
				L -= sumv[lc];
				update(rc, mid + 1, r);
			}
		}
		//printf("update(o = %d, l = %d, r = %d, sum = %d)\n", o, l, r, sumv[o]);
	}
}t;

int main()
{
	while(scanf("%d", &n) == 1)
	{
		t.init(1, 1, n);
		int pos = 0;
		REP(i, 1, n)
			scanf("%d%d", &a[i].pos, &a[i].num);
		Rep(i, n, 1){
			now = a[i].num; L = a[i].pos + 1;
			t.update(1, 1, n);
		}
		REP(i, 1, n) printf((i == n ? "%d\n":"%d "), s[i]);
	}
}
