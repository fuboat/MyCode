#include <cstdio>
#include <iostream>
#define LD double
inline LD f(LD x){ return ((2 * x - 4) * x + 3) * x - 6; }
int main()
{
	LD e, l = -10, r = 10;
	scanf("%lf", &e);
	while(r - l > e){
		LD mid = (l + r) / 2;
		if(f(l) * f(mid) < 0) r = mid;
		else if(f(mid) == 0.0){
			printf("%.8lf", mid);
			return 0;
		}
		else l = mid;
	}
	printf("%.8lf", (l + r) / 2);
}
