#include <cstdio>
#include <iostream>
using std::max;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 100000;
int n, ans;
int f[MAXN + 1], a[MAXN + 1]; //表示最后一次吃的免费午餐的数量所对应的最大天数 

int find(int x)
{
	int l = 0, r = n;
	while(l < r){
	 	int mid =l + ((r - l) >> 1);
	 	if(f[mid] >= x)
	 		r = mid;
	 	else l = mid + 1;
	}
	return l;
}

int main()
{
	memset(f, 0x7f, sizeof(f));
	f[0] = 0;
	scanf("%d", &n);
	REP(i, 1, n) scanf("%d", &a[i]);
	Rep(i, n, 1){
		int pos;
		f[pos = find(a[i])] = a[i];
		ans = max(ans, pos);
	}
	printf("%d\n", ans);
	return 0;
}
