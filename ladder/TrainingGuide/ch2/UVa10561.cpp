// UVa10561
// Fuboat
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#define CLEAR(a) memset(a, 0, sizeof(a))
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
const int MAXN = 300 + 100;
int vis[MAXN], g[MAXN], f[MAXN], sum[MAXN];
bool ok[MAXN];
char s[MAXN];
int n;

int SG(int x)
{
	if(x <= 0) return 0;
	if(x <= 3) return 1;
	if(vis[x]) return g[x];
	vis[x] = true;
	
	std::vector<bool> used(MAXN, 0);
	int &ans = g[x];
	REP(i, -2, x - 3)
		used[SG(i) ^ SG(x - i - 5)] = true;
		
	ans = 0;
	while(used[ans])
		ans ++;
	return ans;
}
void Init()
{
	CLEAR(f);
	CLEAR(sum);
	CLEAR(s);
	CLEAR(ok);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	REP(i, 1, n) if(s[i] == 'X')
		REP(j, i - 2, i + 2)
			if(j > 0)
				ok[j] = true;
					
	REP(i, 1, n) {
		f[i] = f[i - 1] + 1;
		if(ok[i])
			f[i] = 0;
	}
}
bool Special(int x)
{
	if(s[x] == 'X')
		return false;
	if(x > 2 && s[x - 1] == 'X' && s[x - 2] == 'X')
		return true;
	if(x > 1 && s[x - 1] == 'X' && s[x + 1] == 'X')
		return true;
	if(s[x + 1] == 'X' && s[x + 2] == 'X')
		return true;
	return false;
}
bool Special()
{
	std::vector<int> ans;
	bool flag(0), first(1);
	REP(i, 1, n)
		if(Special(i)) {
			flag = true;
			ans.push_back(i);
		}
			
	if(!flag)
		return false;
		
	puts("WINNING");
	REP(i, 0, ans.size() - 1) {
		if(i)
			putchar(' ');
		printf("%d", ans[i]);
	}
	puts("");
	return true;
}
void Solve()
{
	int ans(0), tmp;
	bool first(true);
	
	if(Special())
		return ;
	REP(i, 1, n)
		if(f[i] > f[i + 1])
			ans ^= SG(f[i]);
	rep(i, n, 1)
		if(!ok[i] && f[i] < f[i + 1])
			sum[i] = sum[i + 1];
		else sum[i] = f[i];
		
	if(ans){
		puts("WINNING");
		REP(i, 1, n) if(!ok[i]) {
			tmp = ans ^ SG(sum[i]);
			if((tmp ^ SG(f[i] - 3) ^ SG(sum[i] - f[i] - 2)) == 0) {
				if(first) first = false;
				else putchar(' ');
				printf("%d", i);
			}
		}
	}else puts("LOSING");
	puts("");
}
int main()
{
	int T;
	scanf("%d", &T);
	while(T --){
		Init();
		Solve();
	}
}
