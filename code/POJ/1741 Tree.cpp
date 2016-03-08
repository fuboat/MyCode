#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define CLEAR(a) memset(a, 0, sizeof(a))
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int MAXN = 1e5, MAXD = MAXN;
void Readin(int &x)
{
	x = 0;
	char c = getchar();
	while (!('0' <= c && c <= '9'))
		c = getchar();
	while ('0' <= c && c <= '9') {
		(x *= 10) += c - '0';
		c = getchar();
	}
}
int head[MAXN], to[MAXN], next[MAXN], val[MAXN];
int tote, k, n, ans;
void AddEdge(int u, int v, int w)
{
	to[++ tote] = v;
	val[tote] = w;
	next[tote] = head[u];
	head[u] = tote;
}
int size[MAXN], biggest[MAXN], used[MAXN];

int cur, dfs_clock;
int dfs[MAXN];
int Dfs(int u, int fa)
{
	int v;
	dfs[++ dfs_clock] = u;
	biggest[u] = size[u] = 0;
	
	for (int i = head[u]; i; i = next[i]) {
		v = to[i];
		if (!used[v] && v != fa) {
			size[u] += Dfs(v, u);
			Chkmax(biggest[u], size[v]);
		}
	}
	
	size[u] ++;
	return size[u];
}

int FindRoot(int u)
{
	static int MinSize;
	static int NewRoot;
	
	int v;
	cur ++;
	dfs_clock = 0;
	MinSize = Dfs(u, -1);
	REP (i, 1, dfs_clock) {
		v = dfs[i];
		if(Chkmin(MinSize, std::max(biggest[v], size[u] - size[v])))
			NewRoot = v;
	}
	
	return NewRoot;
}

int sumv[MAXN];
int cnt;
void Dfs(int u, int fa, int dist)
{
	if(dist <= k)
		ans ++;
	sumv[++ cnt] = dist;
	int v;
	for (int i = head[u]; i; i = next[i]) {
		v = to[i];
		if (!used[v] && v != fa)
			Dfs(v, u, dist + val[i]);
	}
}

inline int Cal()
{
	static int r, tot = 0;
	std::sort(sumv + 1, sumv + cnt + 1);
	r = cnt;
	REP(l, 1, cnt) {
		if(l > r)
			break;
		while(l < r && sumv[r] + sumv[l] > k)
			r --;
		tot += r - l;
	}
	return tot;
}

void Work(int u)
{
	static int v, tmp;

	v = u;
	u = FindRoot(u);
	used[u] = true;
		
	for (int i = head[u]; i; i = next[i]) {
		v = to[i];
		if (!used[v])
			Dfs(v, u, val[i]);
	}

	ans += Cal();
	cnt = 0;
	for (int i = head[u]; i; i = next[i]) {
		v = to[i];
		if (!used[v]) {
			tmp = ans;
			Dfs(v, u, val[i]);
			ans = tmp - Cal();
			cnt = 0;
		}
	}
	
	for (int i = head[u]; i; i = next[i]) {
		v = to[i];
		if(!used[v])
			Work(v);
	}
}

int main()
{
	freopen("in.txt", "r", stdin);
	int u, v, w;
	while (true) {
		Readin(n);
		Readin(k);
		if (!n && !k)
			break;
			
		ans = 0;
		CLEAR(head);
		CLEAR(used);
		tote = 0;
		cur = 0;
		
		REP (i, 1, n - 1) {
			Readin(u);
			Readin(v);
			Readin(w);
			AddEdge(u, v, w);
			AddEdge(v, u, w);
		}
		Work(1);
		printf("%d\n", ans);
	}
}
