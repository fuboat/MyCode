// CODEVS2926
// Fuboat
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#define LL unsigned long long
#define CLEAR(s) memset(s, 0, sizeof(s))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 1000;
const LL BIT = 1e7;
struct Bignum{
	LL s[50];
	Bignum(){ CLEAR(s); }
	Bignum(int x)
	{
		CLEAR(s);
		s[1] = x;
	}
	Bignum(const Bignum &x){ *this = x; }
	Bignum operator * (const int &x) const {
		Bignum y;
		int now;
		REP(i, 1, 40){
			y.s[i] += s[i] * x;
			y.s[i + 1] += y.s[i] / BIT;
			y.s[i] %= BIT;
		}
		return y;
	}
	Bignum operator + (const Bignum &x) const {
		Bignum y;
		REP(i, 1, 40){
			y.s[i] = s[i] + x.s[i];
			y.s[i + 1] += y.s[i] / BIT;
			y.s[i + 1] %= BIT;
		}
		return y;
	}
	Bignum operator / (const int &x) const {
		Bignum y(*this);
		rep(i, 40, 1){
			if(i - 1)
				y.s[i - 1] += 1LL * y.s[i] % x * BIT;
			y.s[i] /= x;
		}
		return y;
	}
};
void Print(Bignum x, char *T)
{
	bool flag = true;
	rep(i, 40, 1)
		if(!flag)
			printf("%.7lld", x.s[i]);
		else if(x.s[i]){
			flag = false;
			printf("%lld", x.s[i]);
		}
	if(flag) putchar('0');
	printf("%s", T);
}
int main()
{
	Bignum ans1(1), ans2(1), ans3(1), tmp(2), ans;
	int cnt(0), tot(0), all, n;
	
	scanf("%d", &n);
	all = n * (n + 1) / 2;
	
	if(all % 3 == 0)
		cnt = all / 3;
	else cnt = all / 3 + 1;
	for(int i = n; i > 0; i -= 2)
		tot += i;
	
	REP(i, 1, cnt + 1)
		ans1 = ans1 * 2;
	REP(i, 1, all)
		ans2 = ans2 * 2;
	REP(i, 1, tot)
		ans3 = ans3 * 2;
	ans = ans1 + ans2 + ans3 * 3;
	
	Print(ans / 6, (char*)"\n");
}
