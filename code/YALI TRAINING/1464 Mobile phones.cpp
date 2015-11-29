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
const int MAXN = 1024;
int n;
struct fenwick{
	int f[MAXN + 100][MAXN + 100];
	void add(int x, int y, int d){
		int now = x;
		while(now <= n){
			int tmp = y;
			while(tmp <= n){
				f[now][tmp] += d;
				tmp += tmp & -tmp;
			}
			now += now & -now;
		}
	}
	
	int query(int x, int y){
		int now = x, sum = 0;
		while(now > 0){
			int tmp = y;
			while(tmp > 0){
				sum += f[now][tmp];
				tmp -= tmp & -tmp;
			}
			now -= now & -now;
		}
		return sum;
	}
}t;

int main()
{
	int flag, x, y, xl, yl, xr, yr, d;
	scanf("%d%d", &flag, &n);
	while(scanf("%d", &flag) && flag != 3){
		switch (flag){
			case 1:
			scanf("%d%d%d", &x, &y, &d);
			x ++, y ++;
			t.add(x, y, d);
			break;
			case 2:
			scanf("%d%d%d%d", &xl, &yl, &xr, &yr);
			xl ++, yl ++, xr ++, yr ++;
			printf("%d\n", t.query(xr, yr) - t.query(xl - 1, yr) - t.query(xr, yl - 1) + t.query(xl - 1, yl - 1));
		}
	}
}
