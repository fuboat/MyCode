#include <cstdio>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 10000, MAXK = 10000;
int main()
{
	int T, n, k, m;
	while(scanf("%d%d%d", &n, &k, &m) && n && k && m){
		int ans = 0;
		REP(i, 2, n) ans = (ans + k) % i;
        ans = ((ans - (k - 1) + m) % n + n) % n;
		printf("%d\n", ans? ans : n);
	}
	return 0;
}
