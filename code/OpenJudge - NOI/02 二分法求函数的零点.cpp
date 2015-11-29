#include <cstdio>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const double a[] = {1, -15, 85, -225, 274, -121};
double f(double x){
	double ans = 0;
	REP(i, 0, 4){
		ans += a[i];
		ans *= x;
	}
	return ans + a[5];
}

int main(){
	double l = 1.5, r = 2.4;
	while(r - l > 1e-7){
		double mid = (l + r) / 2;
		if(f(mid) < 0) r = mid;
		else l = mid;
	}
	printf("%.6f", l);
	return 0;
}
