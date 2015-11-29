#include <cstdio>
#include <queue>
#include <cstring>

using std::queue;
inline int min(int x, int y)
{
	return x < y? x : y;
}

#define REP(i, x, y) for(int i =x ,_ = y; i <= _; i ++)
const int MAXN = 200;

int c[MAXN + 1][MAXN + 1];
bool vis[MAXN + 1];
int ans = 0, cnt = 0, m, n;
int pre[MAXN + 1], son[MAXN + 1], f[MAXN + 1];
queue<int>h;

struct edge{
	int from, to, next;
	edge(){}
	edge(int from, int to, int next):
		from(from),to(to), next(next){}
}s[MAXN * MAXN * 2 + 1];

int bfs()
{
	h.push(1);
	memset(f, 0, sizeof(f));
	memset(vis, 0, sizeof(vis));
	memset(pre, 0, sizeof(pre));
	vis[1] = true;
	f[1] = 0x7fffffff;
	while(!h.empty()){
		int from = h.front(); h.pop();
		for(int i = son[from]; i; i = s[i].next)
			if(!vis[s[i].to] && c[from][s[i].to]){
				int to = s[i].to;
				pre[to] = i;
				h.push(to);
				vis[to] = true;
				f[to] = min(c[from][to], f[from]);
			}
	}
	if(!vis[n]) return 0;
	int now = n;
	while(now != 1){
		int line = pre[now];
		int from = s[line].from;
		c[from][now] -= f[n];
		c[now][from] += f[n];
		now = from;
	}
	return f[n];
}
		

void add(int from, int to, int w)
{
	s[++ cnt] = edge(from, to, son[from]);
	son[from] = cnt;
	c[from][to] = w;
	s[++ cnt] = edge(to, from, son[to]);
	son[to] = cnt;
}

int main()
{
	scanf("%d", &n);
	REP(i, 1, n - 1){
		int num;
		scanf("%d", &num);
		REP(j, 1, num){
			int to;
			scanf("%d", &to);
			if(to <= i) continue;
			if(i == 1 || to == n) add(i, to, 1);
			else add(i, to, MAXN);
		}
	}
	int tmp = 0;
	while(tmp = bfs()) ans += tmp;
	printf("%d\n", ans);
	system("pause");
	return 0;
}
