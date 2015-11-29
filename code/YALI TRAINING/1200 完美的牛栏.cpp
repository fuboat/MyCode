#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdlib>
using std::queue;
using std::vector;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 200, MAXM = 200;
int a[MAXN * 3], f[MAXN * 3], n, m;
vector<int>s[MAXN * 3];
queue<int>h;
bool vis[MAXN * 3], c[MAXN * 3][MAXN * 3];

inline void add(int from, int to)
{
	s[from].push_back(to);
	s[to].push_back(from);
	c[from][to] = 1;
}

void update(int &x, int y)
{
	if(y < x) x = y;
}

int bfs(int down)
{
	h.push(0);
	
	memset(vis, 0, sizeof(vis));
	memset(a, 0, sizeof(a));
	memset(f, 0, sizeof(f));
	
	while(!h.empty()){
		int from = h.front(); h.pop();
		REP(i, 0, s[from].size() - 1){
			int to = s[from][i];
			if(!vis[to] && c[from][to]){
				vis[to] = true;
				f[to] = from;
				h.push(to);
			}
		}
	}
	if(!vis[down]) return false;
	for(int i = down; i != 0; i = f[i]){
		c[f[i]][i] = 0;
		c[i][f[i]] = 1;
	}
	return true;
}
		
int main()
{
	scanf("%d%d", &n, &m);
	REP(i, 1, n){
		int tmp, to;
		scanf("%d", &tmp);
		REP(j, 1, tmp){
			scanf("%d", &to);
			add(i, to + n);
		}
	}
	REP(i, 1, n) add(0, i);
	REP(i, 1, m) add(n + i, n + m + 1);
	int cnt = 0, ans = 0;
	while(cnt = bfs(n + m + 1)) ans += cnt;
	printf("%d\n", ans);

	return 0;
}

