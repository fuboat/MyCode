#include <cstdio>
#include <map>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
using std::map;
map<int, int>ok;
const int MAXN = 200000, oo = 0x7fffffff;
int pre[MAXN + 100], next[MAXN + 100], a[MAXN + 100];

bool can(int pos, int L, int R)
{
	return pre[pos] < L && next[pos] > R;
}

bool check(int L, int R){
	if(R < L) return 1;
	REP(d, 0, (L + R) << 1){
		if(L + d > R - d) break;
		if(can(L + d, L, R))
      		return check(L, L + d - 1) && check(L + d + 1, R);
    	if(L + d == R - d) break;
    	if(can(R - d, L, R))
      		return check(R - d + 1, R) && check(L, R - d - 1);
	}
	return 0;
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		int n;
		scanf("%d", &n);
		REP(i, 1, n) scanf("%d", &a[i]);
		REP(i, 1, n){
			int now = a[i];
			if(ok.count(now))
				pre[i] = ok[now];
			else pre[i] = -1;
			ok[now] = i;
		}
		ok.clear();
		Rep(i, n, 1){
			int now = a[i];
			if(ok.count(now))
				next[i] = ok[now];
			else next[i] = oo;
			ok[now] = i;
		}
		ok.clear();
		if(check(1, n)) printf("non-boring\n");
   	 	else printf("boring\n");
   	 }
}
