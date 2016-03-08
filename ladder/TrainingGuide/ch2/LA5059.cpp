// LA5059
// Fuboat
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
LL SG(LL x)
{
	if(x == 2) return 1;
	if(x == 1) return 0;
	if(x & 1) return SG(x / 2);
	return x / 2;
}
int main()
{
	int T, n;
	LL x, flag;
	scanf("%d", &T);
	while(T --){
		flag = 0;
		scanf("%d", &n);
		REP(i, 1, n){
			scanf("%lld", &x);
			flag ^= SG(x);
		}
		puts(flag? "YES" : "NO");
	}
}
