/*
	EXPERIENCE:
	1. This kind of problem is about both Dynamic and AC-Trie, so we can run Dynamic on AC-trie;
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
map<int, int>idx;
const int MAXN = 50 + 300, MAXM = 50 + 100, MAXP = 10 + 10, MAXS = MAXN, MAXL = 10 + 10, MAXNODE = 100 + 20;
const LL MOD = 1000000000;
int n, m, p;
char TT[MAXN];
struct Bignum{
	int s[20];
	void add(const Bignum &a)
	{
		REP(i, 0, 19) s[i] += a.s[i];
		REP(i, 0, 18){
			s[i + 1] += s[i] / MOD;
			s[i] %= MOD;
		}
	}
	Bignum(){ memset(s, 0, sizeof(s)); }
	void Init(int x){ s[0] = x; }
	void print()
	{
		bool flag = 1;
		rep(i, 19, 0){
			if(i != 0 && !s[i] && flag) continue;
			else printf(flag? "%d" : "%.9d", s[i]);
			flag = 0;
		}
	}
};

struct Trie{
	int ch[MAXNODE][MAXS];
	bool val[MAXNODE];
	bool vis[MAXNODE][MAXM];
	Bignum g[MAXNODE][MAXN];
	int f[MAXNODE];
	int sz;
	void Init()
	{
		MSET(ch, 0); MSET(val, 0); MSET(f, 0); MSET(g, 0); MSET(vis, 0);
		sz = 1;
	}
	void Insert()
	{
		char s[MAXL];
		scanf("%s", s);
		int u = 0, len = strlen(s);
		REP(i, 0, len - 1){
			int c = idx[s[i]];
			if(!c) return ;
			if(!ch[u][c]){
				ch[u][c] = ++ sz;
				val[sz] = 0;
			}
			u = ch[u][c];
		}
		val[u] = 1;
	}
	Bignum getProb(int u, int k)
	{
		Bignum sum;
		if(val[u]){
			sum.Init(0);
			return sum;
		}
		if(k == m){
			sum.Init(1);
			return sum;
		}
		if(vis[u][k]) return g[u][k];
		vis[u][k] = true;
		REP(i, 1, n) sum.add(getProb(ch[u][i], k + 1));
		g[u][k] = sum;
		return sum;
	}
	void getFail()
	{
		queue<int> h;
		REP(c, 0, MAXS - 1){
			int u = ch[0][c];
			if(u) h.push(u);
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
				val[u] |= val[f[u]];
			}
		}
	}
}t;
void Init()
{
	t.Init();
	scanf("%d%d%d%s", &n, &m, &p, TT);
	REP(i, 0, strlen(TT) - 1) idx[TT[i]] = i + 1;
	REP(i, 1, p) t.Insert();
	t.getFail();
}
int main()
{
	Init();
	Bignum ans = t.getProb(0, 0);
	ans.print();
	puts("");
}
