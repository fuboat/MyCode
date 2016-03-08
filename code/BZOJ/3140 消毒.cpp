#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define MSET(a, x) memset(a, x, sizeof(a))
#define CLEAR(a) MSET(a, 0)
template <typename T> bool Chkmax(T &x, T y) { return y > x? x = y, true : false; }
template <typename T> bool Chkmin(T &x, T y) { return y < x? x = y, true : false; }
const int MAXN = 5000 + 100, oo = 0x3f3f3f3f;
using std::min;
using std::swap;
int cur, totP, ans, a, b, c;
int vis[MAXN], match[MAXN], P[3];
int g[MAXN][MAXN];
struct Point{
	int P[3];
	Point(){}
	Point(int a, int b, int c, int MIN) {
		P[0] = a;
		P[1] = b;
		P[2] = c;
		swap(P[MIN], P[2]);
	}
} poi[MAXN];
bool Dfs(int u)
{
	REP (v, 1, P[1]) 
		if (g[u][v] && vis[v] != cur) {
			vis[v] = cur;
			if (match[v] == 0 || Dfs(match[v])) {
				match[v] = u;
				return true;
			}
		}
	return false;
}
int Hungary()
{
	int tot = 0;
	REP (i, 1, P[1])
		match[i] = 0;
	REP (i, 1, P[0]) {
		cur ++;
		if (Dfs(i))
			tot ++;
	}
	return tot;
}
void Init()
{
	int mina, MIN, x;
	P[0] = a;
	P[1] = b;
	P[2] = c;
	totP = 0;
	mina = min(P[0], min(P[1], P[2]));
	
	REP (i, 0, 2)
		if (P[i] == mina) {
			MIN = i;
			swap(P[i], P[2]);
			break;
		}
		
	REP (i, 1, a)
		REP (j, 1, b)
			REP (k, 1, c) {
				scanf("%d", &x);
				if (x == 1)
				poi[++ totP] = Point(i, j, k, MIN);
			}
}
int kill[MAXN];
void Search(int now, int used)
{
	if (now > P[2]) {
		Point p;
		REP (i, 1, P[0])
			REP (j, 1, P[1])
				g[i][j] = 0;
		
		REP (i, 1, totP) {
			p = poi[i];
			if (!kill[p.P[2]])
				g[p.P[0]][p.P[1]] = 1;
		}
		
		Chkmin(ans, Hungary() + used);
		return ;
	}
	kill[now] = 1;
	Search(now + 1, used + 1);
	kill[now] = 0;
	Search(now + 1, used);
}
void Solve()
{
	ans = oo;
	Search(1, 0);
	printf("%d\n", ans);
}
int main()
{
	int T;
	scanf("%d", &T);
	while (T --) {
		scanf("%d%d%d", &a, &b, &c);
		Init();
		Solve();
	}
}

