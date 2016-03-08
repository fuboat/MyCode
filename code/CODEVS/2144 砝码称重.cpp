#include <cstdio>
#include <map>
#define LL long long
int Chkmin(int &x, int y) { return y < x? x = y, true : false; }
const int MAXN = 30 + 10, oo = 0x3f3f3f3f;
using std::map;
map<LL, int> s;
int n;
LL m;
int w[MAXN];
void Init()
{
	scanf("%d%lld", &n, &m);
	for (int i = 1; i <= n; i ++)
		scanf("%d", &w[i]); 
	int p = 0, j, cnt;
	LL tot;
	for (int i = 0; i <= (1 << n / 2) - 1; i ++) {
		p = 1, cnt = tot = 0, j = i;
		while (j) {
			if (j & 1) {
				tot += w[p];
				cnt ++;
			}
			j >>= 1;
			p ++;
		}
		if (s.count(tot))
			Chkmin(s[tot], cnt);
		else
			s[tot] = cnt;
	}
}
void Solve()
{
	int p = 0, j, cnt, ans = oo;
	LL tot;
	for (int i = 0; i <= (1 << n - n / 2) - 1; i ++) {
		p = 1, cnt = tot = 0, j = i;
		while (j) {
			if (j & 1) {
				tot += w[p + n / 2];
				cnt ++;
			}
			j >>= 1;
			p ++;
		}
		if (s.count(m - tot))
			Chkmin(ans, s[m - tot] + cnt);
	}
	printf("%d\n", ans == oo? -1 : ans);
}
int main()
{
	Init();
	Solve();
}
