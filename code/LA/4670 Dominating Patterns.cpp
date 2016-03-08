#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;

#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

const int MAXNODE = 200000 + 1000, MAXS = 30, MAXN = 150 + 100, MAXl = 100;
int cnt;
map<string, int> to;
struct Trie{
	int ch[MAXNODE][MAXS];
	int val[MAXNODE];
	int f[MAXNODE];
	int ans[MAXNODE];
	int last[MAXNODE];
	int sz;
	int best;
	int SIGMA_SIZE;
	int idx(char c){ return c - 'a'; }
	void Init()
	{
		SIGMA_SIZE = 26;
		MSET(ch, 0); MSET(val, 0); MSET(f, 0); MSET(last, 0), MSET(ans, 0);
		to.clear();
		sz = 1;
		cnt = 0;
		best = 0;
	}
	void Insert(char *s)
	{
		int u = 0, len = strlen(s);
		REP(i, 0, len - 1){
			int c = idx(s[i]);
			if(!ch[u][c]){
				ch[u][c] = ++ sz;
				val[sz] = 0;
			}
			u = ch[u][c];
		}
		to[string(s)] = u;
		val[u] = 1;
	}
	void Update(int j)
	{
		if(j){
			ans[j] ++;
			if(val[j]) best = max(best, ans[j]);
			Update(last[j]);
		}
	}
	void Find(char *T)
	{
		int L = strlen(T), j = 0;
		REP(i, 0, L - 1){
			int c = idx(T[i]);
			while(j && !ch[j][c]) j = f[j];
			j = ch[j][c];
			if(val[j]) Update(j);
			else Update(last[j]);
		}
	}
	void getFail()
	{
		queue<int> h;
		f[0] = 0;
		REP(c, 0, SIGMA_SIZE - 1){
			int u = ch[0][c];
			if(u){last[u] = f[u] = 0; h.push(u);}
		}
		while(!h.empty()){
			int r = h.front(); h.pop();
			REP(c, 0, SIGMA_SIZE - 1){
				int u = ch[r][c];
				if(!u) continue;
				h.push(u);
				int v = f[r];
				while(v && !ch[v][c]) v = f[v];
				f[u] = ch[v][c];
				last[u] = val[f[u]]? f[u] : last[f[u]];
			}
		}
	}
};
Trie t;
char T[1000000 + 1000];
char s[MAXN][MAXl];
int main()
{
	int n;
	while(scanf("%d", &n) && n)
	{
		t.Init();
		REP(i, 1, n){
			scanf("%s", s[i]);
			t.Insert(s[i]);
		}
		t.getFail();
		scanf("%s", T);
		t.Find(T);
		
		printf("%d\n", t.best);
		REP(i, 1, n)
			if(t.ans[to[string(s[i])]] == t.best)
				puts(s[i]);
	}
}
