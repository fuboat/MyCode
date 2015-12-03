#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 50000 + 1000;
int n;
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
	int T, x, pos, l, r;
	char c[100];
	scanf("%d", &T);
	REP(z, 1, T){
		printf("Case %d:\n", z);
		memset(t.s, 0, sizeof(t.s));
		scanf("%d", &n);
		REP(i, 1, n){
			scanf("%d", &x);
			t.add(i, x);
		}
		while(scanf("%s", c) && c[0] != 'E'){
			if(c[0] == 'Q'){
				scanf("%d%d", &l, &r);
				printf("%d\n", t.sum(r) - t.sum(l - 1));
			}
			else if(c[0] == 'A'){
				scanf("%d%d", &pos, &x);
				t.add(pos, x);
			}
			else if(c[0] == 'S'){
				scanf("%d%d", &pos, &x);
				t.add(pos, -x);
			}
		}
	}
}
