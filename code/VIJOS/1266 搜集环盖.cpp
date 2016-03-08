// VIJOS1266
// Fuboat
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cstring>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define LL unsigned long long 
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 2000, all = 300;
const LL BIT = 1e9;
struct Bignum{
	LL s[all + 10];
	void Update(int pos)
	{
		s[pos + 1] += s[pos] / BIT;
		s[pos] %= BIT;
	}
	Bignum(){ CLEAR(s); }
	Bignum(int x)
	{
		CLEAR(s);
		s[1] = x;
	}
	Bignum(const Bignum &x){ *this = x; }
	Bignum operator * (const Bignum &x) const {
		Bignum y;
		int now;
		REP(i, 1, all)
			REP(j, 1, all) {
				now = i + j - 1;
				y.s[now] += s[i] * x.s[j];
				y.Update(now);
			}
		return y;
	}
	Bignum operator + (const Bignum &x) const {
		Bignum y;
		REP(i, 1, all) {
			y.s[i] += s[i] + x.s[i];
			y.s[i + 1] += y.s[i] / BIT;
			y.s[i] %= BIT;
		}
		return y;
	}
	Bignum operator - (const Bignum &x) const {
		Bignum y(*this);
		REP(i, 1, all) {
			if(y.s[i] < x.s[i]){
				y.s[i + 1] --;
				y.s[i] += BIT;
			}
			y.s[i] -= x.s[i];
		}
		return y;
	}
	Bignum operator / (const LL &x) const {
		Bignum y(*this);
		rep(i, all, 1) {
			if(i - 1)
				y.s[i - 1] += 1LL * y.s[i] % x * BIT;
			y.s[i] /= x;
		}
		return y;
	}
	Bignum operator * (const LL &x) const {
		Bignum y;
		REP(i, 1, all){
			y.s[i] += s[i] * x;
			y.s[i + 1] += y.s[i] / BIT;
			y.s[i] %= BIT;
		}
		return y;
	}
	bool operator == (const Bignum &x) const {
		REP(i, 1, all)
			if(s[i] != x.s[i])
				return false;
		return true;
	}
	bool operator != (const Bignum &x) const
	{ return !(*this == x); }
	bool operator < (const Bignum &x) const {
		rep(i, all, 1)
			if(s[i] < x.s[i])
				return true;
			else if(s[i] > x.s[i])
				return false;
		return false;
	}
	bool operator <= (const Bignum &x) const
	{ return *this < x || *this == x; }
};
struct Frac{
	Bignum up, down;
	Frac(){}
	Frac(Bignum x):
		up(x), down(1){}
	Frac(Bignum up, Bignum down):
		up(up), down(down){}
};
int Length(LL x)
{
	int cnt(0);
	while(x){
		cnt ++;
		x /= 10;
	}
	return cnt;
}
int Length(Bignum x)
{
	int len(0);
	bool flag = true;
	rep(i, all, 1)
		if(x.s[i]){
			if(flag){
				flag = false;
				len += Length(x.s[i]);
			}
			else len += 9;
		}
	return len;
}
void Print(Bignum x, char *T)
{
	bool flag = true;
	rep(i, all, 1)
		if(!flag)
			printf("%.9lld", x.s[i]);
		else if(x.s[i]){
			flag = false;
			printf("%lld", x.s[i]);
		}
	if(flag) putchar('0');
	printf("%s", T);
}
void Print(Frac a, char *s)
{
	int len, line;
	Bignum x(0), tmp(0);
	while(tmp + a.down <= a.up){
		tmp = tmp + a.down;
		x = x + 1;
	}
	a.up = a.up - tmp;
	if (a.up == 0)
		Print(x, "");
	else {
		len = Length(x);
		line = std::max(Length(a.up), Length(a.down));
		
		REP(i, 1, len)
			putchar(' ');
		Print(a.up, "\n");
		if(x != 0)
			Print(x, "");
		REP(i, 1, line)
			putchar('-');
		puts("");
		REP(i, 1, len)
			putchar(' ');
		Print(a.down, "\n");
	}
}
int main()
{
	int n;
	Bignum under(1), on(0), tmp;
	
	scanf("%d", &n);
  	REP(i, 1, n)
		under = under * i;
	REP(i, 1, n)
		on = on + under / i;

	under = under / n;
 	REP(i, 2, n)
  		while(under / i * i == under && on / i * i == on){
			under = under / i;
			on = on / i;
		}
	Print(Frac(on, under), "");
}
