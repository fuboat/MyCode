#include <cstdio>
#include <algorithm>
using std::sort;
using std::upper_bound;
using std::lower_bound;
const int MAXN = 10000 + 1000;
int s, a[MAXN], b[MAXN], n, m;
void Init()
{
	scanf("%d%d", &s, &n);
	for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
	sort(a + 1, a + n + 1);
	scanf("%d", &m);
	for(int i = 1; i <= m; i ++) scanf("%d", &b[i]);
	sort(b + 1, b + m + 1);
}
void Solve()
{
	int ans = 0;
	for(int i = 1; i <= n; i ++){
		int x = s - a[i], l = lower_bound(b + 1, b + m + 1, x) - b, r = upper_bound(b + 1, b + m + 1, x) - b;
		if(l && b[l] == x) ans += r - l;
	}
	printf("%d\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		Init();
		Solve();
	}
}
