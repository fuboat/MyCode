/*
	EXPERIENCES:
	1. For the Dynamic Programming on AC trie, we should follow the Fail pointer( ß≈‰÷∏’Î) to update the ans;
*/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define CLEAR(a) memset(a, 0, sizeof(a))
#define LL long long
const int MAXN = 10 + 1, MAXL = 21 + 1, MAXNODE = 102, MAXS = 10;
int MOD;
struct Matrix{
	int a[MAXNODE][MAXNODE];
	int r, c;
	Matrix(){ CLEAR(a); }
	void Sqr(Matrix x)
	{
		if(c != x.r) return ;
		int tmp[MAXNODE][MAXNODE] = {0};
		REP(i, 0, r) REP(j, 0, x.c) REP(k, 0, c)
			(tmp[i][j] += 1LL * a[i][k] * x.a[k][j] % MOD) %= MOD;
			// Haha!
			// If you don't use '1LL', 'int' is not enough to save ((10 ^ 5) * (10 ^ 5) = 10 ^ 10 > maxint)!
		REP(i, 0, r) REP(j, 0, c)
			a[i][j] = tmp[i][j];
	}
	void SSqr()
	{
		int tmp[MAXNODE][MAXNODE] = {0};
		REP(i, 0, r) REP(j, 0, c) REP(k, 0, c)
			(tmp[i][j] += 1LL * a[i][k] * a[k][j] % MOD) %= MOD;
			// Haha!
			// If you don't use '1LL', 'int' is not enough to save ((10 ^ 5) * (10 ^ 5) = 10 ^ 10 > maxint)!
		REP(i, 0, r) REP(j, 0, c)
			a[i][j] = tmp[i][j];
	}
};
struct Trie{
	int ch[MAXNODE][MAXS], sz, s[MAXNODE][MAXNODE], f[MAXNODE];
	bool val[MAXNODE];
	char T[MAXL];
	Matrix start;
	int Idx(char c){ return c - '0'; }
	void Insert()
	{
		scanf("%s", T);
		int u = 0;
		REP(i, 0, strlen(T) - 1){
			int c = Idx(T[i]);
			if(!ch[u][c])
				ch[u][c] = ++ sz;
			u = ch[u][c];
		}
		val[u] = 1;
	}
	void getFail()
	{
		queue<int> q;
		REP(c, 0, MAXS - 1){
			int u = ch[0][c];
			if(!val[u]){
				s[0][u] ++;
				if(u) q.push(u);
			}
		}
		while(!q.empty()){
			int r = q.front(); q.pop();
			REP(c, 0, MAXS - 1){
				int u = ch[r][c];
				if(!u){
					int last = ch[f[r]][c];
					if(!val[last]) 
					// Don't forget this sentences!
					// if val[last] == true, we can't reach to this node(last)! 
					// In this case, s[r][last] = 0.
						(s[r][last] += 1) %= MOD;
					// Pay attention, if u == 0, 'last' is 'ch[f[r]][c]' instead of '0'.
					// Because the pointer will go to node(ch[f[r]][c]) if you add the char 'c'.
					// Remember, the Dynamic Programming is on a AC trie!
					ch[r][c] = last;
					continue;
				}
				int v = f[r];
				while(v && !ch[v][c]) v = f[v];
				f[u] = ch[v][c];
				val[u] |= val[f[u]];
				if(!val[u]){
					(s[r][u] += 1) %= MOD;
					q.push(u);
				}
			}
		}
		start.c = start.r = sz;
		REP(i, 0, sz) REP(j, 0, sz)
			start.a[i][j] = s[i][j];
	}
	int Solve(LL d)
	{
		Matrix from, now;
		REP(i, 0, sz) REP(j, 0, sz)
			from.a[i][j] = s[i][j];
		from.r = from.c = sz;
		now = from;
		char c[64];
		int cnt = 0;
		while(d > 1){
			c[++ cnt] = d & 1;
			d >>= 1;
		}
		rep(i, cnt, 1){
			Matrix tmp = now;
			now.Sqr(tmp);
			if(c[i]) now.Sqr(from);
		}
		int ans = 0;
		REP(i, 0, sz)
			(ans += now.a[0][i]) %= MOD;
		return ans;
	}
}t;
int main()
{
	LL m;
	int n, ans(0);
	scanf("%lld%d%d", &m, &n, &MOD);
	t.Insert();
	t.getFail();
	printf("%d\n", t.Solve(m));
}
