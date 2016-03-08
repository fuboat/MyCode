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
const int MAXN = 200000 + 1000;
int n, ans, L, R, a[MAXN];

struct segment{
	int sumv[MAXN << 2];
	int s[MAXN];
	
	void build(int o, int l, int r){
		if(l == r){
			s[l] = o;
			scanf("%d", &sumv[o]);
		}
		else{
			int mid = (l + r) >> 1;
			build(o << 1, l, mid);
			build(o << 1|1, mid + 1, r);
			sumv[o] = sumv[o << 1] + sumv[o << 1|1];
		}
	}
	
	void update(int pos, int x)
	{
		int o = s[pos];
		sumv[o] = x;
		o >>= 1;
		while(o != 0){
			sumv[o] = sumv[o << 1] + sumv[o << 1|1];
			o >>= 1;
		}
	}
	
	void query(int o, int l, int r)
	{
		if(L <= l && r <= R)
			ans += sumv[o];
		else{
			int mid = (l + r) >> 1;
			if(L <= mid) query(o << 1, l, mid);
			if(mid < R) query(o << 1|1, mid + 1, r);
		}
	}
}t;

int main()
{
	int cases = 0;
	while(scanf("%d", &n) == 1 && n)
	{
		if(cases > 0)
			printf("\n");
		printf("Case %d:\n", ++cases);
		t.build(1, 1, n);
		char c[100];
		while(scanf("%s", c) && c[0] != 'E'){
			scanf("%d%d", &L, &R);
			if(c[0] == 'M'){
				ans = 0;
				t.query(1, 1, n);
				printf("%d\n", ans);
			}else t.update(L, R);
		}
	}
}
