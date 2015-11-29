#include <cstdio>
#include <cstdlib>
#define LL long long
inline void update(LL &x, LL y)
{
	if(y > x)  x = y;
}
inline LL min(LL x, LL y)
{
	return x < y? x : y;
}

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 10000, MAXP = 1000000, MAXL = 100000, oo = 0x7fffffff;
struct juxing{
	LL xl, xr, y;
	juxing(){}
	juxing(LL xl, LL xr, LL y):
		xl(xl), xr(xr), y(y){}
}a[MAXN + 1];
LL n, ans = oo;
LL minx = 0x7ffffffffffLL;

LL check(int mid)
{
	LL lsum = 0;
	REP(i, 1, n){	
		LL xl = a[i].xl, xr = a[i].xr, y = a[i].y;
		if(xr <= mid) lsum += (xr - xl) * y;
		else if(xl >= mid) lsum -= (xr - xl) * y;
		else lsum += ((mid + mid) - xl - xr) * y;
	}
	return lsum;
}

int main()
{
	scanf("%d", &n);
	LL l = 0, r = 0;
	REP(i, 1, n){
		LL x, y, lx, ly;
		scanf("%d%d%d%d", &x, &y, &lx, &ly);
		a[i] = juxing(x, x + lx, ly);
		update(r, x + lx);
	}
	r = 101000000;
	while(l <= r){
		LL mid = (l + r) >> 1, lsum = check(mid);
		if(lsum >= 0) r = mid - 1;
		else if(lsum < 0) l = mid + 1;
	}
	if(abs(check(l)) < abs(check(r)))  printf("%d\n", l);
	else printf("%d\n", r);
	return 0;
}
			
