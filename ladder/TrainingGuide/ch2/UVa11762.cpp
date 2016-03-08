// UVa11762
// Fuboat
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define LD double
const int MAXN = 1000000 + 100;
bool flag[MAXN], vis[MAXN];
int pri[MAXN];
int totprime;
LD f[MAXN];
void Prime(int x)
{
	REP(i, 2, x){
		if(!flag[i])
			pri[++ totprime] = i;
		for(int j = 1; pri[j] * i <= x; j ++){
			flag[pri[j] * i] = true;
			if(i % pri[j] == 0)
				break;
		}
	}
}
LD DP(int x)
{
	if(vis[x])
		return f[x];
	else if(x == 1)
		return 0.0;
	vis[x] = true;
	
	int g(0), p(0);
	LD &ans = f[x];
	ans = 0.0;
	REP(i, 1, totprime){
		if(pri[i] > x)
			break;
		p ++;
		if(x % pri[i] == 0){
			g ++;
			ans += DP(x / pri[i]);
		}
	}
	return ans = (ans + p) / g;
}
int main()
{
	int T, x;
	scanf("%d", &T);
	Prime(MAXN - 100);
	REP(i, 1, T){
		printf("Case %d: ", i);
		scanf("%d", &x);
		printf("%.10lf\n", DP(x));
	}
}
