// codeforces #346D
// Fuboat
// Graph
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0)
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
const int MAXN = 1e6 + 1e3, MAXM = MAXN, oo = 0x3f3f3f3f;
int n, m, tote, S, T;
int head[MAXN], next[MAXM], to[MAXM], dp[MAXN], out[MAXN], pos[MAXN], cur[MAXN];
// ·´Ïò±ß 
void AddEdge(int u, int v)
{
	to[++ tote] = v;
	next[tote] = head[u];
	head[u] = tote;
}
void Init()
{
	int u, v;
	scanf("%d%d", &n, &m);
	REP(i, 1, m) {
		scanf("%d%d", &u, &v);
		AddEdge(v, u);
		out[u] ++;
	}
	scanf("%d%d", &S, &T);
}
void Solve()
{
	int u, v, num;
	std::deque<int> q, p;
	
	q.push_front(T);
	p.push_front(++ cur[T]); 
	MSET(dp, 0x3f); 
	dp[T] = 0;
	
	while(!q.empty()) {
		u = q.front();
		q.pop_front();
		num = p.front();
		p.pop_front();
		if(num != cur[u])
			continue;
		
		for(int i = head[u]; i; i = next[i]) {
			v = to[i];
			out[v] --;
			if(out[v] == 0) {
				if(Chkmin(dp[v], dp[u])) { 
					q.push_front(v);
					p.push_front(++ cur[v]);
				}
			} else {
				if(Chkmin(dp[v], dp[u] + 1)) {
					q.push_back(v);
					p.push_front(++ cur[v]); 
				}
			}
		}
	}
}
int main()
{
	Init();
	Solve();
	
	if(dp[S] == oo)
		dp[S] = -1; 
	printf("%d\n", dp[S]); 
}
