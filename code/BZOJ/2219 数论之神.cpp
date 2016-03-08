// BZOJ #2219
// Fuboat
// Math
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstring>
#include <vector>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define CLEAR(a) memset(a, 0, sizeof(a))
#define MSET(a, x) memset(a, x, sizeof(a))
using std::vector;
template <typename T> bool Chkmax(T &x, T y) { return x < y? x = y, true : false; } 
template <typename T> bool Chkmin(T &x, T y) { return x > y? x = y, true : false; }
const int oo = 0x3f3f3f3f, MAXINT = 0x7fffffff; 
int Ksm(int a, int k, int mod = MAXINT)
{
	int ans = 1;
	while(k) {
		if(k & 1)
			(ans *= a) %= mod;
		(a *= a) %= mod;
		k >>= 1;
	}
	return ans;
}
struct Divisor{
	int p, k, phi, val;
	Divisor(){}
	Divisor(int p, int k):
		p(p), k(k), val(Ksm(p, k)) {
			phi = val / p * (p - 1);
		}
	// Attention:
	/*
		Divisor(int p, int k):
			p(p), k(k), val(Ksm(p, k)), phi(val / p * (p - 1)) {}
	*/
	// The writing method above is wrong;
	// Because when 'phi' get its val, 'val' in '(...)' is null;
	void Print(char* s = "")
	{
		printf("%d %d %d%s", p, k, phi, s);
	}
};
Divisor NewDivisor(int &x, int p)
{
	int cnt = 0;
	while(x % p == 0) {
		x /= p;
		cnt ++;
	}
	return Divisor(p, cnt);
}
std::vector<Divisor> Divid(int x)
{
	std::vector<Divisor> div;
	for(int i = 2; i <= x / i; i ++)
		if(x % i == 0)
			div.push_back(NewDivisor(x, i));
	
	if(x != 1)
		div.push_back(NewDivisor(x, x));
	return div;
}
int Gcd(int a, int b)
{
	int r;
	while(b) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int Cal(int A, int B, Divisor t)
{
	int p = t.p, k = t.k, P = t.val, gcd;
	Divisor tmp;
	B %= P;
	if(B == 0)
		return Ksm(p, k - ((k - 1) / A + 1));
		
	gcd = Gcd(B, P);
	if(gcd == 1)
		return Gcd(A, t.phi);
	else {
		tmp = NewDivisor(gcd, p);
		k = tmp.k;
		P /= tmp.val;
		if(k % A)
			return 0;
		return Gcd(A, P / p * (p - 1)) * Ksm(p, k - k / A);
	}
}
int main()
{
	int T, A, B, K, ans;
	vector<Divisor> div;
	scanf("%d", &T);
	while(T --) {
		ans = 1;
		scanf("%d%d%d", &A, &B, &K);
		div = Divid(2 * K + 1);
		for(int i = 0; i < div.size(); i ++) {
			ans *= Cal(A, B, div[i]);
			//div[i].Print("\n");
		}
		printf("%d\n", ans);
	}
	return 0;
}
