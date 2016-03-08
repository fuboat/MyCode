/*
*/
#include <cstdio>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

LL ans = 0;
const int MAXNODE = 10000000 + 10000;
struct Trie{
	int ch[MAXNODE][2];
	int val[MAXNODE];
	int sz;
	void clear(){MSET(ch[0], -1); sz = 1; val[0] = 0;}
	void insert(char *s)
	{
		int u = 0, len = strlen(s);
		val[0] ++;
		REP(i, 0, len - 1){
			int c = s[i] - '0';
			if(ch[u][c] == -1){
				MSET(ch[sz], -1);
				val[sz] = 0;
				ch[u][c] = sz ++;
			}
			u = ch[u][c];
			val[u] ++;
		}
	}
	void stat(int d, int o){
		if(ch[o][0] != -1) stat(d + 1, ch[o][0]);
		if(ch[o][1] != -1) stat(d + 1, ch[o][1]);
		chkmax(ans, 1LL * d * val[o]);
	}
}t;
int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		t.clear();
		int n;
		scanf("%d", &n);
		REP(i, 1, n){
			char s[500];
			scanf("%s", s);
			t.insert(s);
		}
		ans = 0;
		t.stat(0, 0);
		printf("%lld\n", ans);
	}
}
