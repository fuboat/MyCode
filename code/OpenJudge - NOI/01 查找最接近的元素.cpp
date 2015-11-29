#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define REP(i, x, y) for(int i = x, _ = y; i <= _;i ++)
using namespace std;
const int MAXN = 100000;
int a[MAXN + 100];
int n, m;

int find(int x){
	int mid = lower_bound(a + 1, a + n + 1, x) - a;
	if(mid != 1 && abs(a[mid - 1] - x) <= abs(a[mid] - x)) return a[mid - 1];
	return a[mid];
}

int main()
{
	scanf("%d", &n);
	REP(i, 1, n) scanf("%d", &a[i]);
	scanf("%d", &m);
	REP(i, 1, m){
		int x;
		scanf("%d", &x);
		printf("%d\n", find(x));
	}
}

