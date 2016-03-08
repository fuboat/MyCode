/*
	ID: fuboat
	LANG: C++
	TASK: agrinet
	ALGORITHM: Prim
	DATE STRUCTURE: Adjacency Matrix
	MISTAKE:
	1.(line 38) There is not 'dis[x] + far[x][i]', only 'far[x][i]'; 
*/
#include <cstdio>
#define REP(i, x, y) for(int i = x, _= y; i <= _; i ++)
template <typename T> inline bool chkmax(T &x, T y){ return y > x? x = y, true : false;}
template <typename T> inline bool chkmin(T &x, T y){ return y < x? x = y, true : false;}
const int MAXN = 100 + 100, oo = 0x3f3f3f3f;
int far[MAXN][MAXN], dis[MAXN];
int n;
bool vis[MAXN];

void Init()
{
	scanf("%d", &n);
	REP(i, 1, n) REP(j, 1, n)
		scanf("%d", &far[i][j]);
}

void Prim()
{
	int ans = 0;
	REP(i, 1, n) dis[i] = oo;
	dis[1] = 0;
	REP(j, 1, n){
		int minx = oo, x = 0;
		REP(i, 1, n)
			if(!vis[i] && chkmin(minx, dis[i]))
				x = i;
		vis[x] = 1;
		ans += dis[x];
		REP(i, 1, n) if(!vis[i])
			chkmin(dis[i], far[x][i]);
	}
	printf("%d\n", ans);
}

int main()
{
	freopen("agrinet.in", "r", stdin);
	freopen("agrinet.out", "w", stdout);
	Init();
	Prim();
}
