#include <cstdio>
#include <iostream>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 2000000 + 100;
int maxv[MAXN * 2];
int x, pos, L, R, ans;
void update(int o, int l, int r)
{
	int mid = (l + r) >> 1;
	if(l == r) maxv[o] = x;
	else{
		if(pos <= mid) update(o << 1, l, mid);
		else update(o << 1|1, mid + 1, r);
		maxv[o] = max(maxv[o << 1], maxv[o << 1|1]);
	}
	//printf("update(o = %d, l = %d, r = %d, maxv = %d)\n", o, l, r, maxv[o]);
}

int query(int o, int l, int r)
{
	if(L <= l && r <= R)
		ans = max(ans, maxv[o]);
	else{
		int mid = (l + r) >> 1;
		if(L <= mid) query(o << 1, l, mid);
		if(mid < R) query(o << 1|1, mid + 1, r);
	}
}

int main()
{
	int n, m;
	while(scanf("%d%d", &n, &m) == 2){
		REP(i, 1, n){
			scanf("%d", &x);
			pos = i;
			update(1, 1, n);
		}
		char c[10];
		REP(i, 1, m){
			scanf("%s", c);
			if(c[0] == 'Q'){
				ans = 0;
				scanf("%d%d", &L, &R);
				if(L > R) L ^= R ^= L ^= R;
				query(1, 1, n);
				printf("%d\n", ans);
			}else{
				scanf("%d%d", &pos, &x);
				update(1, 1, n);
			}
		}
	}
}
