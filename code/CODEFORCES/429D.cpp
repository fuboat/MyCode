#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define int long long
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i <= _; i ++)
template <typename T> bool Chkmin(T &x, T y){ return y < x? (x = y, true) : false; }
template <typename T> bool Chkmax(T &x, T y){ return y > x? (x = y, true) : false; }
const int MAXN = 1e5 + 1e3;
int a[MAXN], b[MAXN], Node[MAXN];
int n, ans;
int Dis(int x, int y)
{
	return (x - y) * (x - y) + (b[x] - b[y]) * (b[x] - b[y]);
}
bool MinY(const int &x, const int &y) { return b[x] < b[y]? true : false; }
void Work(int l, int r)
{
	if(l == r)
		return ;
	int mid = (l + r) >> 1, L, R;
	Work(l, mid);
	Work(mid + 1, r);
	
	int cnt1 = 0, cnt = 0;
	REP(i, std::max(mid - ans, l), std::min(mid + ans, r))
		Node[++ cnt] = i;
	
	std::sort(Node + 1, Node + cnt + 1, MinY);
	REP(i, 1, cnt)
		REP(j, i + 1, cnt) {
			L = Node[i];
			R = Node[j];
			if((b[R] - b[L]) * (b[R] - b[L]) > ans)
				break;
			Chkmin(ans, Dis(L, R));
		}
}
main()
{
	ans = 1LL << 60;
	scanf("%I64d", &n);
	REP(i, 1, n)
		scanf("%I64d", &a[i]);
	b[0] = 0;
	REP(i, 1, n)
		b[i] = b[i - 1] + a[i];
	Work(1, n);
	printf("%I64d\n", ans);
}
