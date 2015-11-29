/*
	FROM: Uva;
	ID: fuboat;
	DATE: 11.28;
	ALGORITHM: Dynamic Programming;
	DATA STRUCTURE: Vector, adjacency list;
	MISTAKE:
	1. (line 30) Use adjacency list in a wrong way(So I have to use vector);
	2. (line 81) Please use 'sum0 += MOD' carefully;
	3. (line 45) Don't forget 'fa[to] = now';
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define Rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
#define LL long long
template <typename T> bool chkmin(T &x, T y){return y < x? (x = y, true) : false;}
template <typename T> bool chkmax(T &x, T y){return y > x? (x = y, true) : false;}
const int MAXN = 1000, MAXM = 1000, MOD = 2000;
int n, m;
int pre[MAXN + 10], bro[MAXN + 10], fa[MAXN + 10], f[MAXN + 10][2], s_cnt;

struct dfstree{
	bool vis[MAXN + 10];
	vector<int>s[MAXN + 10];
	void init(){
		REP(i, 1, n){
			vis[i] = 0;
			s[i].clear();
		}
		s_cnt = 0;
	}
	
	void add(int from, int to){s[from].push_back(to);}
	
	void build(int now){
		REP(i, 0, s[now].size() - 1){
			int to = s[now][i];
			if(!vis[to]){
				fa[to] = now;
				vis[to] = 1;
				bro[to] = pre[now];
				pre[now] = to;
				build(to);
			}
		}
	}
}t;

void init()
{
	t.init();
	REP(i, 1, n) pre[i] = bro[i] = fa[i] = 0;
	int x, y;
	scanf("%d%d", &n, &m);
	REP(i, 1, m){
		scanf("%d%d", &x, &y);
		t.add(x + 1, y + 1);
		t.add(y + 1, x + 1);
	}
	REP(i, 1, n) if(!t.vis[i]){
		t.vis[i] = 1;
		t.build(i);
	}
}

void dp(int now)
{
	int &ans0 = f[now][0], &ans1 = f[now][1], sum0 = 0, sum1 = 0;
	ans0 = ans1 = 0;
	for(int i = pre[now]; i; i = bro[i]){
		dp(i);
		sum0 += f[i][0];
		sum1 += f[i][1];
	}
	sum1 += MOD;
	if(fa[now]){
		ans1 = min(sum0 + 1, sum1);
		ans0 = sum1 + 1;
	}else ans0 = ans1 = min(sum0, sum1);
	return ;
}

void solve()
{
	int ans = 0;
	REP(i, 1, n) if(!fa[i]) dp(i);
	REP(i, 1, n) if(!fa[i]) ans += f[i][0];
	printf("%d %d %d\n", ans / MOD, m - ans % MOD, ans % MOD);
	return ;
}

int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		init();
		solve();
	}
	return 0;
}
