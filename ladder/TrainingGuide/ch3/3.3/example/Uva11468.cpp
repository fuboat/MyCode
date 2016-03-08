/*
	FROM: UVa
	TASK: 11468
	ID: fuboat
	DATASTRUCTURE: AC-Trie
	ALGORITHM: Default
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
#define LD double
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

const int MAXNODE = 10000, MAXS = 100, MAXK = 20 + 10;
LD ok[MAXS];
int idx(char c){ return c - '!'; }
struct Trie{
	int ch[MAXNODE][MAXS];
	bool val[MAXNODE];
	bool vis[MAXNODE][MAXS];
	int f[MAXNODE];
	LD g[MAXNODE][MAXS];
	int sz;
	void Init()
	{
		MSET(ch, 0); MSET(val, 0);
		MSET(f, 0); MSET(vis, 0);
		REP(i, 0, MAXS - 1) ok[i] = 0.0;
		sz = 0;
	}
	void Insert(char *s)
	{
		int u = 0, len = strlen(s);
		REP(i, 0, len - 1){
			int c = idx(s[i]);
			if(!ch[u][c]) ch[u][c] = ++ sz;
			u = ch[u][c];
		}
		val[u] = true;
	}
	LD Find(int u, int len)
	{
		//DEBUG("Find(u = %d, len = %d)\n", u, len);
		if(!len) return 1.0;
		if(vis[u][len]) return g[u][len];
		vis[u][len] = 1;
		LD &sum = g[u][len];
		sum = 0.0;
		REP(i, 0, MAXS - 1) if(!val[ch[u][i]])
			if(ok[i]) sum += ok[i] * Find(ch[u][i], len - 1);
		return sum;
	}
	void getFail()
	{
		queue<int> h;
		f[0] = 0;
		REP(c, 0, MAXS - 1){
			int u = ch[0][c];
			if(u){ f[u] = 0; h.push(u); }
		}
		while(!h.empty()){
			int r = h.front(); h.pop();
			REP(c, 0, MAXS - 1){
				int u = ch[r][c];
				if(!u){ ch[r][c] = ch[f[r]][c]; continue; }
				h.push(u);
				int v = f[r];
				while(v && !ch[v][c]) v = f[v];
				f[u] = ch[v][c];
				if(val[f[u]]) val[u] = true;
			}
		}
	}
};
Trie t;

int main()
{
	int TT;
	scanf("%d", &TT);
	REP(zzz, 1, TT){
		printf("Case #%d: ", zzz);
		t.Init();
		int k;
		scanf("%d", &k);
		char s[100];
		REP(i, 1, k){
			scanf("%s", s);
			t.Insert(s);
		}
		t.getFail();
		int n;
		scanf("%d", &n);
		REP(i, 1, n){
			scanf("%s", s);
			scanf("%lf", &ok[idx(s[0])]);
		}
		int len;
		scanf("%d", &len);
		printf("%lf\n", t.Find(0, len));
	}
}
