/*
	FROM: USACO
	ID: fuboat
	TASK: comehome
	LANG: C++
	ALGORITHM: Graph Theory
	DATA STRUCTURE: Adjacency List
	MISTAKE: 
	1. Forget to delete the code for debugging;
	2. The size of (edge) s[] is too small (at least double of MAXN);
	EXPERIENCE:
*/
#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
#define MSET(a, x) memset(a, x, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
bool chkmax(int &x, int y){return y > x? (x = y, true) : false;}
bool chkmin(int &x, int y){return y < x? (x = y, true) : false;}
const int MAXN = 10000 + 1000;
int matched['z' + 10], cor[MAXN], dis[MAXN], num;
int n, cnt, pre[MAXN];
struct edge{
	int to, w, next;
	edge(){}
	edge(int to, int w, int next):
		to(to), w(w), next(next){}
}s[MAXN * 2];

inline int match(char c)
{
	return matched[c]? matched[c] : (cor[++ num] = c, matched[c] = num);
}
inline char get()
{
	char c = getchar();
	while(c < 'A' || c > 'Z') c = getchar();
	return c;
}
inline void add(int from, int to,int w)
{
	s[++ cnt] = edge(to, w, pre[from]);
	pre[from] = cnt;
}
void Init()
{
	int from, to, w;
	char c;
	scanf("%d", &n);
	REP(i, 1, n){
		from = match(get());
		to = match(get());
		scanf("%d", &w);
		if(from == to) continue;
		add(from, to, w);
		add(to, from, w);
	}
}
bool vis[MAXN];
queue<int>h;
void Spfa(int origin)
{
	MSET(dis, 0x7f);
	dis[origin] = 0;
	h.push(origin);
	while(!h.empty()){
		int from = h.front(); h.pop();
		vis[from] = 0;
		for(int i = pre[from]; i; i = s[i].next){
			int to = s[i].to, w = s[i].w;
			if(chkmin(dis[to], dis[from] + w))
				if(!vis[to]){
					//printf("dis[%c] = dis[%c] + %d = %d\n", cor[to], cor[from], w, dis[to]);
					vis[to] = 1, h.push(to);
				}
		}
	}
}

void Solve()
{
	int ans = 0x7fffffff;
	char best;
	Spfa(matched['Z']);
	REP(i, 1, n + 1){
		char c = cor[i];
		if('A' > c || c > 'Z') continue;
		if(chkmin(ans, dis[i])) best = c;
	}
	printf("%c %d\n", best, ans);
}

int main()
{
	freopen("comehome.in", "r", stdin);
	freopen("comehome.out", "w", stdout);
	Init();
	Solve();
}
