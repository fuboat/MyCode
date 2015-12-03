#include <cstdio>
#include <algorithm>
#include <cstring>
#define LL long long
using namespace std;
const int MAXN = 500000 + 1000;
int a[MAXN], b[MAXN], n;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
struct fenwick{
	int s[MAXN];
	void add(int pos, int x)
	{
		while(pos <= n){
			s[pos] += x;
			pos += pos & -pos;
		}
	}
	
	int sum(int pos)
	{
		int sum = 0;
		while(pos > 0){
			sum += s[pos];
			pos -= pos & -pos;
		}
		return sum;
	}
}t;

int main()
{
	while(scanf("%d", &n) && n){
		memset(t.s, 0, sizeof(t.s));
		REP(i, 1, n){
			scanf("%d", &a[i]);
			b[i] = a[i];
		}
		sort(b + 1, b + n + 1);
		LL ans = 0;
		Rep(i, n, 1){
			int pos = lower_bound(b + 1, b + n + 1, a[i]) - b;
			ans += t.sum(pos - 1);
			t.add(pos, 1);
		}
		printf("%lld\n", ans);
	}
}
