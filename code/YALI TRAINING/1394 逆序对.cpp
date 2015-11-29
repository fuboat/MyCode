#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#ifdef WIN32
	#define ll "%I64d"
	#define ll0 "%015I64d"
#else 
	#define ll "%015lld"
#endif

#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 50, MAXM = 3000;
LL MOD = (LL)1e16;
int n, m;

struct bignum{
	LL a[11];
	bignum operator+ (const bignum &x){
		REP(i, 0, 10) a[i] += x.a[i];
		REP(i, 0, 9){
			a[i + 1] += a[i] / MOD;
			a[i] %= MOD; 
		}
		return *this;
	}
	bignum operator= (const bignum &x){
		memcpy(a, x.a, sizeof(a));
		return *this;
	}
	void print(){
		bool flag = 0;
		Rep(i, 10, 0){
			if(!a[i] && !flag) continue;
			if(!flag){
				flag = 1;
				printf(ll, a[i]);
			}
			else{
				printf(ll0, a[i]);
			}
		}
	} 
}f[MAXN + 5][MAXM + 5];

int main()
{
	memset(f, 0, sizeof(f));
	scanf("%d%d", &n, &m);
	f[0][0].a[0] = 1;
	for(int i = 1; i <= n; i ++)
	for(int j = 1; j <= i; j ++)
	for(int k = j - 1; k <= m; k ++)
		f[i][k] = f[i][k] + f[i - 1][k - j + 1];
	f[n][m].print();
	return 0;
}
	
