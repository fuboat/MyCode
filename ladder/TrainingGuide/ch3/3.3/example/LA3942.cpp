/*
	FROM: UVaLive
	TASK: 3942
	ID: fuboat
	DATASTRUCTURE: Trie
	ALGORITHM: Default
	MISTAKES:
	1.(line 65) using t.insert() before using t.clear();
	2.(line 59) Forget to mod;
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

const int MAXNODE = 1000000, MAXS = 30, MAXL = 300000 + 1000, MOD = 20071027;
int f[MAXL];
int n;
char s[MAXL];

struct Trie{
	int ch[MAXNODE][MAXS];
	int val[MAXNODE];
	int sz;
	inline void clear(){sz = 1; memset(ch, 0, sizeof(ch));memset(val, 0, sizeof(val));}
	inline int idx(char c){ return c - 'a'; }
	void insert(char *s)
	{
		int u = 0, len = strlen(s);
		REP(i, 0, len - 1){
			int c = idx(s[i]);
			if(!ch[u][c]){
				sz ++;
				ch[u][c] = sz;
				val[sz] = 0;
			}
			u = ch[u][c];
		}
		val[u] = 1;
	}
	
	void find(int v, int len)
	{
		int u = 0;
		REP(i, v, len - 1){
			int c = idx(s[i]);
			if(!ch[u][c]) return ;
			u = ch[u][c];
			if(val[u])
				(f[v] += f[i + 1]) %= MOD;
		}
	}
}t;

void Init()
{
	t.clear();
	char dic[1000];
	scanf("%d", &n);
	REP(i, 1, n){
		scanf("%s", dic);
		t.insert(dic);
	}
}

void Solve()
{
	int len = strlen(s);
	memset(f, 0, sizeof(f));
	f[len] = 1;
	Rep(i, len - 1, 0)
		t.find(i, len);
}

int main()
{
	int cases = 0;
	while(scanf("%s", s) != EOF){
		Init();
		Solve();
		printf("Case %d: %d\n", ++ cases, f[0]);
	}
}
