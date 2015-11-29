#include <cstdio>
#include <cmath>

int readin()
{
	int x = 0;bool flag = 0;char c = 0;
	while(c = getchar()){
		if(c == '-'){
			return -readin();
		}
		if(c >= '0'&&c <= '9'){
			x = x * 10 + c - '0';
			flag = 1;
		}
		else if(flag)  return x;
	}
}

#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
bool chkmin(int &x, int y){return y < x? (x = y, true) : false;}
bool chkmax(int &x, int y){return y > x? (x = y, true) : false;}

const int MAXN = 300000, MAXM = 300000, MAXD = 20;
struct edge{
	int to, w, nxt;
}s[MAXN * 3];

struct Que{
	int l, r, lca, far;
}que[MAXN + 100];

struct About{
	int list, with, nxt;
}about[MAXN * 3];

int pre[MAXN + 100], aft[MAXN + 100], d[MAXN + 100], f[MAXN + 100], p[MAXN + 100], dis[MAXN + 100], root[MAXN + 100];
int s_cnt, about_cnt;
bool vis[MAXN + 100];

int find(int x)
{
	if(x != f[x]) f[x] = find(f[x]);
	return f[x];
}
 
int dfs[MAXN + 100], dfs_cnt; //The turn of dfs
int m, n, maxl, maxL, bb, maxd;

void add(int from, int to, int len)
{
	s_cnt ++;
	s[s_cnt] = (edge){to, len, pre[from]};
	pre[from] = s_cnt;
}

void Add(int from, int to, int i)
{
	about_cnt ++;
	about[about_cnt] = (About){to, i, aft[from]};
	aft[from] = about_cnt;
}

void tarjan(int now)
{
	dfs[++ dfs_cnt] = now;
	vis[now] = 1;
	f[now] = now;
	for(int i = aft[now]; i; i = about[i].nxt){
		int nxt = about[i].list;
		if(vis[nxt])
			que[about[i].with].lca = find(nxt);
	}
	for(int i = pre[now]; i; i = s[i].nxt){
		int to = s[i].to;
		if(!vis[to]){
			p[to] = now;
			d[to] = d[now] + 1;
			dis[to] = s[i].w;
			root[to] = root[now] + dis[to];
			tarjan(to);
			f[to] = now;
		}
	}
}
		
void Init()
{
	int from, to, len;
	n = readin();
	m = readin();
	REP(i, 1, n - 1){
		from = readin();
		to = readin();
		len = readin();
		add(from, to, len);
		add(to, from, len);
		chkmax(maxL, len);
	}
	REP(i, 1, m){
		from = readin();
		to = readin();
		que[i].l = from; 
		que[i].r = to;
		Add(from, to, i);
		Add(to, from, i);
	}
	tarjan(1);
	REP(i, 1, m){
		Que &now = que[i];
		now.far = root[now.l] + root[now.r] - (root[now.lca] << 1);
		chkmax(maxl, now.far);
	}
}

void  Begin()
{
	freopen("transport.in", "r", stdin);
	freopen("transport.out", "w", stdout);
}

void End()
{
	fclose(stdin);
	fclose(stdout);
}

bool is_OK(int len)
{
	bool flag = 0;
	int ok[MAXN + 100]= {0}, num = 0;
	REP(i, 1, m){
		Que now = que[i];
		if(now.far > len){
			num ++;
			ok[now.lca] -= 2;
			ok[now.l] ++; ok[now.r] ++;
		}
	}
	Rep(j, n, 1){
		int now = dfs[j];
		for(int i = pre[now]; i; i = s[i].nxt){
			int to = s[i].to;
			if(to != p[now]) ok[now] += ok[to];
		}
		if(ok[now] == num){
			if(maxl - dis[now] <= len) return 1;
			while((ok[p[now]] += ok[now]) == num && (now != bb)){
				now = p[now];
				if(maxl - dis[now] <= len) return 1;
			}
			return 0;
		}
	}
	return 0;
}

int Solve()
{
	int l = maxl - 1000, r = maxl, ans, mid;
	if(l < 0) l = 0;
	while(l < r){
		mid = (l + r) >> 1;
		if(is_OK(mid))
			r = mid;
		else l = mid + 1;
	}
	return l;
}

int main()
{
	//Begin();
	Init();
	printf("%d\n", Solve());
	//End();
	return 0;
}
