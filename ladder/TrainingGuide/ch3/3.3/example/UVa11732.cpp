#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
typedef long long LL;
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

const int MAXNODE = 5000000 + 10000;
int n;
char s[2000];

struct Trie{
	char ch[MAXNODE];
	int val[MAXNODE], ok[MAXNODE], pre[MAXNODE], next[MAXNODE], sz, j, u, len;
	LL ans;
	inline void clear(int o){  pre[o] = val[o] = ok[o] = 0;  }
	inline void init(){  ans = sz = 0; clear(0);  }
	inline void insert()
	{
		u = 0; len = strlen(s);
		ans += (val[u] ++);
		REP(i, 0, len - 1){
			for(j = pre[u]; j != 0; j = next[j])
				if(ch[j] == s[i]){
					u = j;
					break;
				}
			if(!j){
				clear(++ sz);
				ch[sz] = s[i];
				next[sz] = pre[u];
				u = pre[u] = sz;
			}
			ans += (val[u] ++) * 2;
		}
		ans += (ok[u] ++);
	}
}t;

int main()
{
	int cnt = 0;
	while(~scanf("%d", &n) && n){
		t.init();
		REP(i, 1, n){
			scanf("%s", s);
			t.insert();
		}
		printf("Case %d: %lld\n", ++ cnt, t.ans);
	}
}
