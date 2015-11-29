#include <cstdio>
#include <cstring>
#include <cstdlib>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 1000, MAXM = 1000;
int m, n, link[MAXN + MAXM + 100];
bool used[MAXN + MAXM + 100];
struct edge{
	int to, next;
	edge(){}
	edge(int to, int next):
		to(to), next(next){}
}s[MAXN * 3];
int s_cnt, pre[MAXN + MAXM + 100];
bool ok[MAXN + MAXM + 100][MAXN + MAXM + 100];


template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}

void add(int from, int to)
{
	s_cnt ++;
	s[s_cnt] = edge(to, pre[from]);
	pre[from] = s_cnt;
}

bool dfs(int now)
{
	for(int i = pre[now]; i; i = s[i].next){
		int to = s[i].to;
		if(!used[to]){
			used[to] = 1;
			if(link[to] == -1 || dfs(link[to])){
				link[to] = now;
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	scanf("%d%d", &n, &m);
	REP(i, 1, m){
		int x, y;
		scanf("%d%d", &x, &y);
		add(i, x);
		add(i, y);
	}
	int sum = 0;
	REP(i, 0, n)  link[i] = -1;
	REP(i, 1, m){
		REP(j, 0, n)  used[j] = 0; 
		if(dfs(i)) sum ++;
		else{
			printf("%d\n", sum);
			return 0;
		}
	}
	printf("%d\n", sum);
	return 0;
}

