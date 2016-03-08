/*
	MISTAKE: 
	1. Sometimes 'int' is not enough to save some number, while 'long long' is OK;
	EXPERIENCE:
	1. Modularization(模块化)
	2. Many details(细节){
		|The Parameters(参数) of function are used in a wrong way;
		|What does 'L' mean? The length of string;
		|Clearing all the thing between two cases is the msafest;
	}
*/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

#define LL long long
#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

const int MAXNODE = 3000 + 1000, MAXS = 2, MAXN = 100 + 100, MOD = 1000000009, MAXL = 200 + 100, MAXl = 20 + 10;
const char ss[10][5] = {"0000", "0001" ,"0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001"};
struct Trie{
	int ch[MAXNODE][MAXS];
	bool val[MAXNODE];
	int f[MAXNODE];
	LL g[2][MAXNODE][MAXL];
	bool vis[2][MAXNODE][MAXL];
	bool ans;
	char T[MAXL];
	int L;
	int sz;
	int idx(char c){ return c - '0'; }
	void Init(){ MSET(ch[0], 0); MSET(g, 0); sz = val[0] = false; }
	void Insert()
	{
		scanf("%s", T);
		int u = 0, len = strlen(T);
		REP(i, 0, len - 1){
			int c = idx(T[i]);
			if(!ch[u][c]){
				ch[u][c] = ++ sz;
				MSET(ch[sz], 0);
				val[sz] = 0;
			}
			u = ch[u][c];
		}
		val[u] = true;
	}
	int Solve()
	{
		MSET(vis, 0);
		scanf("%s", T);
		L = strlen(T);
		int u(0); LL sum(0); ans = 0;
	 	if(L > 1) sum = Find(false, true, 0, 1) % MOD;
		REP(i, L > 1? 1 : 0, T[0] - '0'){
			int j = u;
			REP(k, 0, 3){
				j = ch[j][idx(ss[i][k])];
				if(val[j]) break;
			}
			if(!val[j])
				(sum += Find(i == T[0] - '0'? true : false, false, j, 1)) %= MOD;
		}
		return sum;
	}
	LL Find(bool ok, bool tt, int u, int len)
	{
		if(len == L){ ans |= ok; return 1; }
		LL sum = 0;
		if(!ok && vis[tt][u][len]) return g[tt][u][len];
		REP(i, tt && len != L - 1? 1 : 0, ok? T[len] - '0' : 9){
			int j = u;
			REP(k, 0, 3){
				j = ch[j][idx(ss[i][k])];
				if(val[j]) break;
			}
			if(!val[j]){
				if(ok && i == T[len] - '0')
					 (sum += Find(true,  false, j, len + 1)) %= MOD;
				else (sum += Find(false, false, j, len + 1)) %= MOD;
			}
		}
		if(tt && len != L - 1)
			(sum += Find(ok, true, 0, len + 1)) %= MOD;
		if(!ok){
			g[tt][u][len] = sum;
			vis[tt][u][len] = true;
		}
		return sum;
	}
	void getFail()
	{
		queue<int> q;
		REP(c, 0, MAXS - 1){
			int u = ch[0][c];
			if(u) {f[u] = 0; q.push(u); }
		}
		while(!q.empty()){
			int r = q.front(); q.pop();
			REP(c, 0, MAXS - 1){
				int u = ch[r][c];
				if(!u){ ch[r][c] = ch[f[r]][c]; continue; }
				q.push(u);
				int v = f[r];
				while(v && !ch[v][c]) v = f[v];
				f[u] = ch[v][c];
				val[u] |= val[f[u]];
			}
		}
	}
};
Trie t;
void Init()
{
	t.Init();
	int n;
	scanf("%d", &n);
	REP(i, 1, n) t.Insert();
	t.getFail();
}
void Solve()
{
	LL sum = t.Solve() - t.ans;
	LL ans = (0LL + t.Solve() + MOD - sum) % MOD;
	printf("%lld\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T --){ Init(); Solve(); }
}
