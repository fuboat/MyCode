#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 100 + 100;
struct Mice{
	int t, w;
	bool operator < (const Mice &a) const{
		return t > a.t;
	}
}a[MAXN];
std::priority_queue<int> q;
int n;
int maxt;
void Init()
{
	scanf("%d", &n);
	REP (i, 1, n)
		scanf("%d", &a[i].t);
	REP (i, 1, n)
		scanf("%d", &a[i].w);
	n ++;
	a[n].t = 0;
	std::sort(a + 1, a + n + 1);
}

void Solve()
{
	int ans = 0, cnt;
	q.push(a[1].w);
	for (int i = 2; i <= n; i ++) {
		cnt = a[i - 1].t - a[i].t;
		while (cnt -- && !q.empty()) {
			ans += q.top();
			q.pop();
		}
		q.push(a[i].w);
	}
	printf("%d\n", ans);
}
int main()
{
	Init();
	Solve();
}
