// BZOJ  #3505
// Fuboat
// Math
#include <cstdio>
#include <iostream>
#include <algorithm>
#define LL unsigned long long
#define REP(i, x, y) for(int i = x; i <= y; i ++)
using namespace std;
const int MAXN = 1000 + 100;
LL fac[MAXN * MAXN][4];
bool vis[MAXN * MAXN][4];
// 'fac[MAXN][MAXN]' is wrong!
// 'M' can only be '3' at most;
// but 'N' can be 'MAXN * MAXN'!
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
int main()
{
	int n, m, x, y;
	LL ans, less = 0, tmp;
	scanf("%d%d", &n, &m);
	
	ans = (m + 1) * (n + 1);
	ans = ans * (ans - 1) / 2 * (ans - 2) / 3;
	REP(i, -n, n)
		REP(j, -m, m) {
			if(!i && !j)
				// The two node of three is at the same position;
				// But when initing, this situation isn't counted;
				// So there is no need to count them; 
				continue;
				
			x = abs(i);
			y = abs(j);
			tmp = Gcd(x, y);
			less += 1LL * (tmp - 1) * (n - x + 1) * (m - y + 1);
		}
	ans -= less / 2;
	std::cout << ans << endl;
}
