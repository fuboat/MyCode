#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
using namespace std;
const int MAXN = 5000, MAXL = 10000, MAXW = 10000;
int n, ans, f[MAXN + 1];
struct stick{
	int l, w;
	bool operator < (const stick &x) const{
		if(x.l != l) return l < x.l;
		return w < x.w;
	}
}a[MAXN + 1];

int main(){
	scanf("%d", &n);
	REP(i, 1, n)
		scanf("%d%d", &a[i].l, &a[i].w);
	sort(a + 1, a + n + 1);
	Rep(i, n, 1){
		int maxx = 0;
		REP(j, i + 1, n){
			if(a[i].l > a[j].l || a[i].w > a[j].w)
				maxx = max(f[j], maxx);
		}
		ans = max(ans, f[i] = maxx + 1);
	}
	printf("%d\n", ans);
	system("pause");
	return 0;
}
			
