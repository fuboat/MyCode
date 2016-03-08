// BZOJ #2818
// Fuboat
// Math
#include <cstdio>
#include <iostream>
#include <algorithm>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
const int MAXN = 1e7 + 1e5;
int totpri;
LL phi[MAXN], pri[MAXN];
bool vis[MAXN];
void GetPhi(int N)
{
	int prime;
	LL now;
	// 'int' is not enough for 'i * prime' ("now = i * prime", line 29)!
	
	REP(i, 2, N) {
		if(!vis[i]) {
			pri[++ totpri] = i;
			phi[i] = i - 1;
			// Don't forget the sentence above!
		}
			
		REP(j, 1, totpri) {
			prime = pri[j];
			now = i * prime;
			if(now > N)
				break;
			// Warning!
			// 'Runtime Error' may be from here!
			// No need to continue to calculate if 'now > n'!
			vis[now] = true;
			
			if(i % prime == 0) {
				phi[now] = phi[i] * prime;
				break; 
			} else
				phi[now] = phi[i] * (prime - 1);
		}
	}
}
int main()
{
	int n; 
	LL ans = 0;
	scanf("%d", &n);
	GetPhi(n);
	phi[1] = 1;
	
	REP(i, 2, n)
		phi[i] += phi[i - 1];
		
	REP(i, 1, totpri) {
		ans += 1LL * phi[n / pri[i]] * 2 - 1;
	}
	printf("%lld\n", ans);
}
