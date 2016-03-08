/*
	ID: fuboat
	TASK: contact
	LANG: C++
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#define REP(i, x, y) for(int i = x, _ = y; i <= _; i ++)
#define rep(i, x, y) for(int i = x, _ = y; i >= _; i --)
using std::vector;
using std::max;
const int MAXL = 200000 + 1000, MAXN = 50 + 10, MAXA = 100000;
char s[MAXL];
vector<int>ans[MAXL];
int a, b, n, sum[MAXA], maxx;
void Init()
{
	scanf("%d%d%d", &a, &b, &n);
	int len = 0;
	while(scanf("%s", s + len) != EOF) len = strlen(s);
	REP(i, 0, len - 1){
		int x = 1;
		REP(j, 0, b - 1){
			if(i - j < 0) break ;
			x ^= (1 << j);
			x |= (1 << (j + 1));
			if(s[i - j] == '1') x |= 1 << j;
			sum[x] ++;
			maxx = max(sum[x], maxx);
		}
	}
	REP(i, 1 << a, 1 <<(b + 1))
		if(sum[i]) ans[sum[i]].push_back(i);
}
void bit_print(int x)
{
	bool c[MAXA];
	int cnt = 0;
	while(x){
		c[++ cnt] = (x & 1);
		x >>= 1;
	}
	for(int i = cnt - 1; i >= 1; i --)
		printf("%d", c[i]);
}
int bitcount(int x){ return x? bitcount(x >> 1) + 1:0; }
void Solve()
{
	int cnt = 0;
	rep(i, maxx, 1){
		if(!ans[i].size()) continue;
		cnt ++;
		printf("%d", i);
		REP(j, 0, ans[i].size() - 1){
			if(j && j % 6) putchar(' ');
			else puts("");
			bit_print(ans[i][j]);
		}
		puts("");
		if(cnt == n) break;
	}
}
int main()
{
	freopen("contact.in", "r", stdin);
	freopen("contact.out", "w", stdout);
	Init();
	Solve();
	fclose(stdin);
	fclose(stdout);
}
