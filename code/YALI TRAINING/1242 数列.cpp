#include <cstdio>
#include <iostream>
using std::max;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 1000;
int n, ans, a[MAXN + 1], f[MAXN + 1][MAXN + 1];
int maxi[MAXN + 1];
void init()
{
	scanf("%d", &n);
    REP(i, 1, n)
    	scanf("%d", &a[i]);
}	

void work()
{
	REP(i, 1, n)
		Rep(j, i, 1)
		{
			f[i][j] = maxi[j - 1] + (j == a[i]);
			ans = max(ans, f[i][j]);
			maxi[j] = max(maxi[j], f[i][j]);
		}
}

int main()
{
	init();
    work();
    printf("%d\n", ans);
    return 0;
}
    		
    
