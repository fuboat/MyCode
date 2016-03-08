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
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

const int MAXNODE = 70000 + 1, MAXS = 100, MAXN = 10000 + 1000;
int cnt, m, n;
bool ans[MAXN];
struct Trie{
	int ch[MAXNODE][MAXS];
	int val[MAXNODE];
	int f[MAXNODE];
	int last[MAXNODE];
	int sz;
	int SIGMA_SIZE = MAXS;
	int idx(char c){ return c - '!'; }
	void Init()
	{
		MSET(ch, 0); MSET(val, 0); MSET(f, 0); MSET(last, 0), MSET(ans, 0);
		sz = 1;
		cnt = 0;
	}
	void Insert(char *s, int v)
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
		val[u] = v;
	}
	void Update(int j)
	{
		if(j){
			ans[val[j]] = true;
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
char T[10000 + 1000];
void Init()
{
	scanf("%d", &n);
	t.Init();
	char s[300];
	REP(i, 1, n){
		scanf("%s", s);
		t.Insert(s, i);
	}
	t.getFail();
	scanf("%d", &m);
}
int tot;
void Solve(int now)
{
	MSET(ans, 0);
	scanf("%s", T);
	t.Find(T);
	bool flag = 0;
	REP(i, 1, n) if(ans[i]) flag = 1;
	if(!flag) return ;
	tot ++;
	printf("web %d:", now);
	REP(i, 1, n) if(ans[i]) printf(" %d", i);
	puts("");
}
int main()
{
	Init();
	REP(i, 1, m) Solve(i);
	printf("total: %d\n", tot);
}
