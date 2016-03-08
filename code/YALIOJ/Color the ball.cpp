#include <cstdio>
#include <cstring>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _ ; i ++)
const int MAXN = 100000 + 1000;
int f[MAXN];
int main()
{
	int n;
	while(scanf("%d", &n) && n){
		int l, r;
		REP(i, 1, n){
			scanf("%d%d", &l, &r);
			f[l] ++, f[r + 1] --;
		}
		printf("%d", f[1]);
		REP(i, 2, n){
			f[i] += f[i - 1];
			printf(" %d", f[i]);
		}
		putchar('\n');
		memset(f, 0, sizeof(f));
	}
}

