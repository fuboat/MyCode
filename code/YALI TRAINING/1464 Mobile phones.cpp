#include <cstdio>
#define lowbit(pos) (pos & -pos)
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 1024;
int n;
struct fenwick{
	int f[MAXN + 100];
	void add(int pos, int d){
		while(pos <= n){
			f[pos] += d;
			pos += lowbit(pos);
		}
	}
	
	int query(int pos){
		int sum = 0;
		while(pos > 0){
			sum += f[pos];
			pos -= lowbit(pos);
		}
		return sum;
	}
}t[MAXN + 100];

void add(int x, int y, int d)
{
	while(x <= n){
		t[x].add(y, d);
		x += lowbit(x);
	}
}

int query(int x, int y)
{
	int sum = 0;
	while(x > 0){
		sum += t[x].query(y);
		x -= lowbit(x);
	}
	return sum;
}

int main()
{
	int flag, x, y, xl, yl, xr, yr, d;
	scanf("%d%d", &flag, &n);
	while(scanf("%d", &flag) && flag != 3){
		switch (flag){
			case 1:
			scanf("%d%d%d", &x, &y, &d);
			x ++, y ++;
			add(x, y, d);
			break;
			case 2:
			scanf("%d%d%d%d", &xl, &yl, &xr, &yr);
			xl ++, yl ++, xr ++, yr ++;
			printf("%d\n", query(xr, yr) - query(xl - 1, yr) - query(xr, yl - 1) + query(xl - 1, yl - 1));
		}
	}
	return 0;
}
