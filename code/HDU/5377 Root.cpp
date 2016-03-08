// HDU #5377
// Fuboat
//   [Math]
// - Baby-step
// - discrete logarithm
// - primary root
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define int long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define CLEAR(a) memset(a, 0, sizeof(a))
#define MSET(a, x) memset(a, x, sizeof(a))
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
const int SIZE = 1e6 + 10, MAXM = 1e5 + 1e2, SZ = SIZE - 10;
int m;
int ans[MAXM];

struct HashTable{
	int LogVal[SIZE * 3], val[SIZE * 3], head[SIZE * 3], next[SIZE * 3], tot;
	void Clear()
	{
		tot = 0;
		CLEAR(head);
	}
	int Find(int x)
	{
		for(int i = head[x % SIZE]; i; i = next[i])
			if(val[i] == x)
				return LogVal[i];
				
		return -1;
	}
	void Add(int x, int v)
	{
		if(Find(x) != -1)
			return ;
			
		val[++ tot] = x;
		LogVal[tot] = v;
		x %= SIZE;
		next[tot] = head[x];
		head[x] = tot;
	}
} hash;

int GetInv(int N, int p)
{
	if(N == 1)
		return 1;
	return p - p / N * GetInv(p % N, p) % p;
}

int ExGcd(int a, int b, int &gcd, int &x, int &y)
{
	if(b == 0) {
		gcd = a;
		x = 1;
		y = 0;
	} else {
		ExGcd(b, a % b, gcd, y, x);
		// There is ExGcd(..., y, x), not ExGcd(..., x, y);
		y -= a / b * x;
	}
}

int Ksm(int a, int b, int p)
{
	int tmp = 1;
	while(b) {
		if(b & 1)
			(tmp *= a) %= p;
		(a *= a) %= p;
		b >>= 1;
	}
	return tmp;
}

int GetRoot(int p)
{
	bool flag;
	int Phi = p - 1, totdiv = 0, tmp = Phi;
	static int div[100];
	
	for(int i = 2; i <= tmp / i; i ++) {
		// Get the divisor of 'Phi'; 
		if(tmp % i == 0) {
			div[++ totdiv] = i;
			while(tmp % i == 0)
				tmp /= i;
		}
	}
	if(tmp != 1)
		div[++ totdiv] = tmp;
	
	for(int i = 1; ; i ++) {
		//'1' may also be the root;
		flag = true;
		for(int j = 1; j <= totdiv; j ++)
			if(Ksm(i, Phi / div[j], p) == 1) {
				flag = false;
				break;
			}
			
		if(flag)
			return i;
	}
}

int Left[MAXM], Right[MAXM], A[MAXM], B[MAXM];

int GetLog(int x, int inv, int p)
{
	x %= p;
	int val;
	for(int i = 0; ; i ++) {
		val = hash.Find(x);
		if(val != -1)
			return i * SZ + val;
		(x *= inv) %= p;
	}
}

void GetLogMod(int p)
{
	int d = GetRoot(p), inv = GetInv(Ksm(d, SZ, p), p), tmp, val;
	
	hash.Clear();
	tmp = 1;
	REP(i, 0, std::min(SZ - 1, p - 2)) {
		hash.Add(tmp, i);
		tmp = tmp * d % p;
	}
	
	REP(i, 1, m) {
		A[i] = GetLog(Left[i], inv, p);
		B[i] = GetLog(Right[i], inv, p);
	}
}

void Work(int p)
{
	int a, b, c, gcd, x, y;
	GetLogMod(p);
	REP(i, 1, m) {
		a = A[i];
		b = p - 1;
		c = B[i];
		ExGcd(a, b, gcd, x, y);
		if(c % gcd != 0)
			continue;
		
		x *= c / gcd;
		b /= gcd;
		x %= b;
		if(x < 0)
			x += b;
			
		if(ans[i] != -1)
			Chkmin(ans[i], x);
		else ans[i] = x;
	}
}

main()
{
	int sum, T, kase = 0;
	scanf("%I64d", &T);
	while(T --) {
		scanf("%I64d%I64d", &sum, &m);
		REP(i, 1, m) {
			ans[i] = -1;
			scanf("%I64d%I64d", &Left[i], &Right[i]); 
		} 
			
		REP(i, 2, sum) {
			if(i * i > sum)
				break;
			if(sum % i == 0) {
				Work(i);
				while(sum % i == 0)
					sum /= i;
			}
		}
		if(sum != 1)
			Work(sum);

		printf("Case #%I64d:\n", ++ kase);
		REP(i, 1, m)
			printf("%I64d\n", ans[i]);
	}
}

