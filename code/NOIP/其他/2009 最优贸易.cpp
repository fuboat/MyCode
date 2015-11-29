#include <cstdio>
#include <cstring>
#define REP(i, x, y) for(int i = x; i <= y; i ++)
const int MAXN = 100000, MAXM = 500000;
int cnt[2], n, m, p[MAXN + 2], ans = 0, PRI[2][MAXN + 2], PRE[2][MAXN + 2];
int h[MAXN + 2];
bool in[MAXN + 2];
struct edge{
	int to, next;
}S[2][MAXM];	
int max(int x, int y){return x > y? x : y;}

int min(int x, int y){return x < y? x : y;}

void add(int from, int to, bool flag)
{
	cnt[flag] ++;
	int *pre = PRE[flag];
	edge &s = S[flag][cnt[flag]];
	s.to = to;
	s.next = pre[from];
	pre[from] = cnt[flag];
}

void init(bool flag)
{
	int *pri = PRI[flag];
	memset(h, 0, sizeof(h));
	memset(in, 0, sizeof(in));
	if(flag == 0)memset(pri, 0x7f, sizeof(PRI)/2);
	else memset(pri, 0, sizeof(PRI)/2);
	if(flag == 0) h[1] = 1;
	else h[1] = n;
	pri[h[1]] = p[h[1]];
}

int greater(bool flag, int New,int Old)
{
	int *pri = PRI[flag];
	if(flag == 0){
		if(min(New, p[Old]) < pri[Old])
			return min(New, p[Old]);
		else return 0;
	}else{
		if(max(New, p[Old]) > pri[Old])
			return max(New, p[Old]);
		else return 0;
	}
}

void spfa(bool flag)
{
	int *pre = PRE[flag], *pri = PRI[flag];
	edge *s = S[flag];
	init(flag);
	int head = 0, tail = 1;
	do{
		head ++;
		int from = h[head];
		in[from] = 0;
		for(int i = pre[from]; i; i = s[i].next){
			int tmp, to = s[i].to;
			if(tmp = greater(flag, pri[from], to)){
				pri[to] = tmp;
				if(!in[to]){
					tail ++;
					h[tail] = to;
					in[to] = 1;
				}
			}
		}
	}while(head < tail);
	return;
}

int main()
{
	int x, y, z;
	scanf("%d%d", &n, &m);
	REP(i, 1, n) scanf("%d", &p[i]);
	REP(i, 1, m){
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, 0);
		add(y, x, 1);
		if(z == 2){
			add(x, y, 1);
			add(y, x, 0);
		}
	}
	spfa(0);
	spfa(1);
	REP(i, 1, n)
		ans = max(PRI[1][i] - PRI[0][i], ans);
	printf("%d\n", ans);
	return 0;
}
