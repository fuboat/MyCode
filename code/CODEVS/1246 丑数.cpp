#include <iostream>
#include <cstdio>
using namespace std;
#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXK = 100, MAXN = 100000;
const LL oo = 0x7ffffffffffLL;
LL a[MAXK + 2], ans[MAXN + 2], p[MAXK + 2], minx;
int main(){
	int k, n;
	scanf("%d%d", &k, &n);
	ans[0] = 1;
	REP(i, 1, k)
		scanf("%d", &a[i]);
	REP(i, 1, n){
		minx = oo;
		int t;
		REP(j, 1, k){
			int i0 = p[j];
			while(ans[i0] * a[j] < ans[i - 1]){
				i0 ++;
			}
			if(ans[i0] * a[j] <= minx){
				minx = ans[i0] * a[j];
				t = j;
			}
		}
		p[t] ++;
		ans[i] = minx;
		if(ans[i] == ans[i - 1]) i --;
	}
	printf("%lld", ans[n]);
}
