#include <cstdio>
#include <cstring>

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 1000000 + 10000;
int n, L, R;

struct segment{
	int sumv[MAXN * 4];
	
	void update(int o, int l, int r)
	{
		int lc = o << 1, rc = o << 1|1, mid = (l + r) >> 1;
		if(L <= l && r <= R) sumv[o] ++;
		else{
			if(L <= mid) update(lc, l, mid);
			if(mid < R) update(rc, mid + 1, r);
		}
	}
	
	void query(int o, int l, int r)
	{
		int lc = o << 1, rc = o << 1|1, mid = (l + r) >> 1;
		if(l != r){
			sumv[lc] += sumv[o];
			sumv[rc] += sumv[o];
			query(lc, l, mid);
			query(rc, mid + 1, r);
		}else printf(l == n? "%d\n" : "%d ", sumv[o]);
		sumv[o] = 0;
	}
}t;

int main()
{
	while(scanf("%d", &n) && n){
		REP(i, 1, n){
			scanf("%d%d", &L, &R);
			t.update(1, 1, n);
		}
		t.query(1, 1, n);
	}
}
