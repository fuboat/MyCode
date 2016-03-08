// Codeforces #549F
// Fuboat
// 'int' is not enough!
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#define LL long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
bool Chkmax(LL &x, LL y) { return y > x? x = y, true : false; }
bool Chkmin(LL &x, LL y) { return y < x? x = y, true : false; }
const int MAXN = 6*1e5 + 1e3, MAXK = 2 * 1e6 + 1e3;

int n, k;
LL a[MAXN];
int sumv[MAXK];
LL tot;
void MaxInLeft(int l, int r)
{
	int mid = (l + r) >> 1, i = mid, j = mid + 1;
	LL maxl = a[i], maxr = a[j], sum1 = a[i], sum2 = a[j];
	
	sumv[a[j] % k] ++;
	while (i >= l && maxl <= maxr) {
		i --;
		Chkmax(maxl, a[i]);
		sum1 += a[i];
	}
	while (i >= l && j <= r) {
		while (j < r && a[j + 1] < maxl) {
			j ++;
			Chkmax(maxr, a[j]);
			sum2 += a[j];
			sumv[sum2 % k] ++;
		}
		do {
			tot += sumv[(k - (sum1 - maxl) % k) % k];
			i --;
			sum1 += a[i];
		} while (i >= l && !Chkmax(maxl, a[i]));
	}
	sum2 = 0;
	REP(i, mid + 1, r) {
		(sum2 += a[i]) %= k;
		sumv[sum2] = 0; 
	}
}
void MaxInRight(int l, int r)
{
	int mid = (l + r) >> 1, i = mid, j = mid + 1;
	LL maxl = a[i], maxr = a[j], sum1 = a[i], sum2 = a[j];
	
	sumv[a[i] % k] ++;
	while (j <= r && maxr < maxl) {
		j ++;
		Chkmax(maxr, a[j]);
		sum2 += a[j];
	}
	while (i >= l && j <= r) {
		while (i > l && a[i - 1] <= maxr) {
			i --;
			Chkmax(maxl, a[i]);
			sum1 += a[i];
			sumv[sum1 % k] ++;
		}
		do {
			tot += sumv[(k - (sum2 - maxr) % k) % k];
			j ++;
			sum2 += a[j];
		} while(j <= r && !Chkmax(maxr, a[j]));
	}
	sum1 = 0;
	rep(i, mid, l) {
		(sum1 += a[i]) %= k;
		sumv[sum1] = 0;
	}
}
void Work(int l, int r)
{
	if(l >= r)
		return ;
		
	int mid = l + (r - l) / 2;
	Work(mid + 1, r);
	Work(l, mid);

	MaxInLeft(l, r);
	MaxInRight(l, r);
}
int main()
{
	scanf("%d%d", &n, &k);
	REP(i, 1, n)
		scanf("%I64d", &a[i]);
	Work(1, n);
	printf("%I64d\n", tot);
}
