#include <iostream>
#include <cstdio>
#include <cmath>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using std::queue;

#define CLEAR(a) memset(a, 0, sizeof(a))
#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

int m, n;
const int MAXNODE = 200000 + 1000, MAXS = 2, MAXM = 1000 + 100, MAXL = 1000 + 100, MAXl = 50000 + 1000, MAXN = 10 + 2;
int dis[MAXN][MAXN], L[MAXM + MAXN];
struct Trie{
	int ch[MAXNODE][MAXS], f[MAXNODE];
	int last[MAXNODE], node[MAXN], sz;
	short fnode[MAXNODE];
	bool cannot[MAXNODE], vis[MAXNODE], val[MAXNODE];
	char T[MAXl];
	inline int idx(char c){ return c - '0'; }
	void Init(){ CLEAR(ch); CLEAR(f); CLEAR(last); CLEAR(node); CLEAR(fnode); CLEAR(cannot); CLEAR(val); sz = 0; }
	void Insert(int v)
	{
		scanf("%s", T);
		int u = 0, len = strlen(T);
		REP(i, 0, len - 1){
			int c = idx(T[i]);
			if(!ch[u][c]) ch[u][c] = ++ sz;
			u = ch[u][c];
		}
		if(v == -1) cannot[u] = true;
		else{
			L[v] = len;
			node[v] = u;
			fnode[u] = v;
			val[u] = true;
		}
	}
	void getFail()
	{
		queue<int> h;
		REP(c, 0, 1){
			int u = ch[0][c];
			if(u) h.push(u);
		}
		while(!h.empty()){
			int r = h.front(); h.pop();
			REP(c, 0, 1){
				int u = ch[r][c];
				if(!u){ ch[r][c] = ch[f[r]][c]; continue; }
				h.push(u);
				int v = f[r];
				while(v && !ch[v][c]) v = f[v];
				f[u] = ch[v][c];
				last[u] = val[f[u]] == 1? f[u] : last[f[u]];
			}
		}
	}
	void Solve(int v)
	{
		queue<int> h;
		queue<int> q;
		CLEAR(vis);
		int u;
		q.push(node[v]);
		h.push(0);
		vis[node[v]] = true;
		while(!q.empty()){
			int r = q.front(); q.pop();
			int d = h.front(); h.pop();
			REP(c, 0, 1){
				u = ch[r][c];
				if(vis[u] || cannot[u]) continue;
				vis[u] = true;
				int j = 0;
				if(val[u]) j = u;
				else if(last[u]) j = last[u];
				while(j){ dis[v][fnode[j]] = d + 1, j = last[j]; }
				q.push(u);
				h.push(d + 1);
			}
		}
	}
}t;
void Init()
{
	t.Init();
	REP(i, 1, n) t.Insert(i);
	REP(i, 1, m) t.Insert(-1);
	t.getFail();
}
int f[5000][MAXN];
bool vis[5000][MAXN];
int dp(int sta, int now)
{
	if(!sta) return 0;
	int ans = 0x3f3f3f3f;
	if(vis[sta][now]) return f[sta][now];
	vis[sta][now] = 1;
	REP(i, 1, n) if(sta & 1 << (i - 1))
		chkmin(ans, dp(sta ^ 1 << (i - 1), i) + dis[now][i]);
	return f[sta][now] = ans;
}
void Solve(){
	CLEAR(vis); CLEAR(f);
	int ans = 0x3f3f3f3f;
	REP(i, 1, n) t.Solve(i);
	REP(i, 1, n) chkmin(ans, dp(((1 << n) - 1) ^ 1 << (i - 1), i) + L[i]);
	printf("%d\n", ans);
}
int main()
{
	while(scanf("%d%d", &n, &m) == 2 && n && m){
		Init();
		Solve();
	}
}
