#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
template <typename T> bool Chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool Chkmax(T &x, T y){return y > x? (x = y, true) : false;}
using std::queue;
int n, cnt[5], HASH[5];
const int MAXN = 50 + 10, MAXl = 10 + 10, MAXL = 40 + 10, MAXNODE = MAXN * MAXl, MAXS = 4;
struct sta{
	int x[4];
	sta(){}
	sta(int x0, int x1, int x2, int x3){
		x[0] = x0, x[1] = x1, x[2] = x2, x[3] = x3;
	}
	int hash()
	{
		int sum = 0;
		REP(i, 0, 3) sum += HASH[i] * x[i];
		return sum;
	}
	bool empty()
	{
		REP(i, 0, 3) if(x[i]) return false;
		return true;
	}
};
int f[MAXNODE], ch[MAXNODE][MAXS], last[MAXNODE], val[MAXNODE], sz;
short g[15001][MAXNODE];
bool vis[15001][MAXNODE];
short idx[200];
char T[MAXL];
struct Trie{
	void Init()
	{
		MSET(ch, 0); MSET(val, 0); MSET(last, 0); MSET(vis, 0);
		MSET(g, 0); MSET(f, 0); sz = 0; MSET(cnt, 0);
	}
	void Insert()
	{
		scanf("%s", T);
		int u = 0;
		REP(i, 0, strlen(T) - 1){
			int c = idx[(int)T[i]];
			if(!ch[u][c]) ch[u][c] = ++ sz;
			u = ch[u][c];
		}
		val[u] ++;
	}
	void getFail()
	{
		queue<int>q;
		REP(c, 0, 3){
			int u = ch[0][c];
			if(u) q.push(u);
		}
		while(!q.empty()){
			int r = q.front(); q.pop();
			REP(c, 0, 3){
				int u = ch[r][c];
				if(!u){ ch[r][c] = ch[f[r]][c]; continue; }
				q.push(u);
				int v = f[r];
				while(v && !ch[v][c]) v = f[v];
				f[u] = ch[v][c];
				val[u] += val[f[u]];
			}
		}
	}
}t;
void Update(int &ans, int u)
{
	while(u){
		ans += val[u];
		u = last[u];
	}
}
int dp(sta d, int u, int ha)
{
	int sum = 0;
	if(!ha){ return val[u]; }
	if(vis[ha][u]) return g[ha][u];
	vis[ha][u] = true;
	REP(c, 0, 3)
		if(d.x[c]){
			d.x[c] --;
			Chkmax(sum, dp(d, ch[u][c], ha - HASH[c]));
			d.x[c] ++;
		}
	//printf("dp(u = %d, 'A' = %d, 'C' = %d, 'G' = %d, 'T' = %d, sum = %d)\n", u, d.x[0], d.x[1], d.x[2], d.x[3], sum);
	return g[ha][u] = sum + val[u];
}
//HASH, cnt, idx;
void Init()
{
	t.Init();
	REP(i, 1, n) t.Insert();
	t.getFail();
	scanf("%s", T);
	REP(i, 0, strlen(T) - 1) cnt[idx[1 * T[i]]] ++;
	HASH[0] = 1;
	REP(i, 1, 3) HASH[i] = HASH[i - 1] * (cnt[i - 1] + 1);
}
int main()
{
	int TT = 0;
	idx['A'] = 0, idx['C'] = 1, idx['G'] = 2, idx['T'] = 3;
	while(scanf("%d", &n) == 1 && n){
		Init();
		sta from(cnt[0], cnt[1], cnt[2], cnt[3]);
		printf("Case %d: %d\n", ++TT, dp(from, 0, from.hash()));
	}
}

