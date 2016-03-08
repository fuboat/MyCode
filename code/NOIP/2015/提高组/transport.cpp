#include <cstdio>
#include <cmath>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
bool chkmin(int &x, int y){return y < x? (x = y, true) : false;}
bool chkmax(int &x, int y){return y > x? (x = y, true) : false;}
void readin(int &x)
{
	x = 0;
	char c = 0;
	do c = getchar();
	while(c < '0' || c > '9');
	do{
		(x *= 10) += c - '0';
		c = getchar();
	}while(c >= '0' && c <= '9');
}

const int MAXN = 300000 + 100, MAXM = 300000 + 100;
struct edge{ int to, w, nxt; };
struct Que{ int l, r, lca, far; };
struct About{ int list, with, nxt; };

int pre[MAXN], s_cnt;
edge s[MAXN << 1];
void add(int from, int to, int len)
{
	s[++ s_cnt] = (edge){to, len, pre[from]};
	pre[from] = s_cnt;
}

int aft[MAXN], about_cnt;
About about[MAXN << 1];
void Add(int from, int to, int i)
{
	about[++ about_cnt] = (About){to, i, aft[from]};
	aft[from] = about_cnt;
}

bool vis[MAXN];
int dfs[MAXN], f[MAXN], p[MAXN], dis[MAXN], root[MAXN], dfs_cnt; //The turn of dfs
Que que[MAXM];
int find(int x){ return x == f[x]? f[x] : f[x] = find(f[x]); }
void tarjan(int now)
{
	dfs[++ dfs_cnt] = now;
	vis[now] = 1;
	f[now] = now;
	for(int i = aft[now]; i; i = about[i].nxt){
		int nxt = about[i].list;
		if(vis[nxt]) que[about[i].with].lca = find(nxt);
	}
	for(int i = pre[now]; i; i = s[i].nxt){
		int to = s[i].to, w = s[i].w;
		if(!vis[to]){
			p[to] = now;
			dis[to] = w;
			root[to] = root[now] + w;
			tarjan(to);
			f[to] = now;
		}
	}
}

int m, n, maxl;
void Init()
{
	int from, to, len;
	readin(n);
	readin(m);
	REP(i, 1, n - 1){
		readin(from);
		readin(to);
		readin(len);
		add(from, to, len);
		add(to, from, len);
	}
	REP(i, 1, m){
		readin(from);
		readin(to);
		que[i].l = from; 
		que[i].r = to;
		Add(from, to, i);
		Add(to, from, i);
	}
	tarjan(1);
	REP(i, 1, m){
		Que &now = que[i];
		chkmax(maxl, now.far = root[now.l] + root[now.r] - (root[now.lca] << 1));
	}
}

bool Check(int len)
{
	int ok[MAXN + 100]= {0}, num = 0;
	REP(i, 1, m){
		Que now = que[i];
		if(now.far > len){
			num ++;
			ok[now.lca] -= 2;
			ok[now.l] ++; ok[now.r] ++;
		}
	}
	rep(j, n, 1){
		int now = dfs[j], w = ok[now];
		if(w == num && maxl - dis[now] <= len) return 1;
		ok[p[now]] += w;
	}
	return 0;
}

int Solve()
{
	int l = maxl - 1001, r = maxl, ans, mid;
	if(l < 0) l = -1;
	while(l + 1 < r){
		mid = (l + r) >> 1;
		if(Check(mid)) r = mid;
		else l = mid;
	}
	return r;
}

void Begin(), End();
int main()
{
	//Begin();
	Init();
	printf("%d\n", Solve());
	//End();
	return 0;
}

void Begin()
{
	freopen("transport.in", "r", stdin);
	freopen("transport.out", "w", stdout);
}
void End()
{
	fclose(stdin);
	fclose(stdout);
}
