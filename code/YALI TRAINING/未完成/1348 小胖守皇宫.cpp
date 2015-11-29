/*
	TASK: 1348
*/
/*
	Ëã·¨£ºÊ÷ÐÎdp
*/
#include <cstdio>
#include <iostream>
using std::max;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
const int MAXN = 1500;
int bro[MAXN + 10], pre[MAXN + 10], w[MAXN + 10];
int f[MAXN + 10][2];
int n;
bool vis[MAXN + 10], ok[MAXN + 10];

void init()
{
	scanf("%d", &n);
	REP(i, 1, n){
		int now, e, num, This;
		scanf("%d%d%d", &now, &e, &num);
		if(num) scanf("%d", &pre[i]);
		This = pre[i];
		ok[This] = 1;
		REP(j, 2, num){
			scanf("%d", &bro[This]);
			This = bro[This];
			ok[This] = 1;
		}
	}
}
		
void solve(int x)
{
	if(vis[x]) return ;
	vis[x] = 1;
	f[x][0] = 0;
	f[x][1] = w[x];
	int now = pre[x];
	while(now){
		solve(now);
		now = bro[now];
	}
	now = pre[x];
	while(now){
		f[x][0] += f[now][1];
		f[x][1] += f[now][0];
		now = bro[now];
	}
	return ;
}

int main()
{
	init();
	REP(i, 1, n) solve(i);
	
}
